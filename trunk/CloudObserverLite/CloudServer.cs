using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using Microsoft.Win32;

namespace CloudObserverLite
{
    public class CloudServer
    {
        private const string DEFAULT_NAME = "Cloud Observer Lite 1.0.0";
        private const ushort DEFAULT_PORT = 4773;

        private TcpListener listener;
        private Thread thread;

        private string name;
        private ushort port;
        private uint clientsCount;
        private LogWriter logWriter;

        public CloudServer() : this(DEFAULT_NAME, DEFAULT_PORT) { }

        public CloudServer(string name) : this(name, DEFAULT_PORT) { }

        public CloudServer(ushort port) : this(DEFAULT_NAME, port) { }

        public CloudServer(string name, ushort port)
        {
            this.name = name;
            this.port = port;
            this.clientsCount = 0;
            this.logWriter = LogWriter.GetInstance();
        }

        public void Listen()
        {
            this.listener = new TcpListener(IPAddress.Any, this.port);
            this.listener.Start();
            this.logWriter.WriteLog("Server started. Waiting for connections...");

            while (true)
            {
                try
                {
                    CloudClient client = new CloudClient(this, ++this.clientsCount, this.listener.AcceptTcpClient());
                    Thread clientThread = new Thread(new ThreadStart(client.Process));
                    clientThread.Name = "Client " + this.clientsCount.ToString();
                    clientThread.IsBackground = true;
                    clientThread.Start();
                }
                catch (Exception)
                {
                }
            }
        }

        public void Start()
        {
            this.thread = new Thread(new ThreadStart(this.Listen));
            this.thread.Name = "Server";
            this.thread.IsBackground = true;
            this.thread.Start();
        }

        public void Stop()
        {
            this.listener.Stop();
            this.logWriter.WriteLog("Server stopped.");
            this.logWriter.Close();

            this.thread.Abort();
        }

        public void OnResponse(ref HttpRequestStruct httpRequest, ref HttpResponseStruct httpResponse)
        {
            string path = Directory.GetCurrentDirectory() + "\\" + httpRequest.url.Replace("/", "\\");

            if (Directory.Exists(path))
            {
                if (File.Exists(path + "index.html"))
                    path += "\\index.html";
                else
                {
                    string[] directories = Directory.GetDirectories(path);
                    string[] files = Directory.GetFiles(path);

                    string bodyString = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\n";
                    bodyString += "<HTML><HEAD>\n";
                    bodyString += "<META http-equiv=Content-Type content=\"text/html; charset=windows-1252\">\n";
                    bodyString += "</HEAD>\n";
                    bodyString += "<BODY><p>Folder listing, to do not see this add a 'index.html' document\n<p>\n";
                    for (int i = 0; i < directories.Length; i++)
                        bodyString += "<br><a href = \"" + httpRequest.url + Path.GetFileName(directories[i]) + "/\">[" + Path.GetFileName(directories[i]) + "]</a>\n";
                    for (int i = 0; i < files.Length; i++)
                        bodyString += "<br><a href = \"" + httpRequest.url + Path.GetFileName(files[i]) + "\">" + Path.GetFileName(files[i]) + "</a>\n";
                    bodyString += "</BODY></HTML>\n";

                    httpResponse.bodyData = Encoding.ASCII.GetBytes(bodyString);
                    return;
                }
            }

            if (File.Exists(path))
            {
                RegistryKey registryKey = Registry.ClassesRoot.OpenSubKey(Path.GetExtension(path), true);
                string registryValue = (string)registryKey.GetValue("Content Type");

                httpResponse.fileStream = File.Open(path, FileMode.Open);
                if (registryValue != "")
                    httpResponse.headers["Content-type"] = registryValue;

                httpResponse.headers["Content-Length"] = httpResponse.fileStream.Length;
            }
            else
            {
                httpResponse.status = (int)ResponseState.NOT_FOUND;

                string bodyString = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\n";
                bodyString += "<HTML><HEAD>\n";
                bodyString += "<META http-equiv=Content-Type content=\"text/html; charset=windows-1252\">\n";
                bodyString += "</HEAD>\n";
                bodyString += "<BODY>File not found!</BODY></HTML>\n";

                httpResponse.bodyData = Encoding.ASCII.GetBytes(bodyString);
            }
        }
    }
}
