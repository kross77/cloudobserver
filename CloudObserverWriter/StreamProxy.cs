using System;
using System.Threading;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace CloudObserverWriter
{
    public class StreamProxy
    {
        private const int BUFFER_SIZE = 8192;

        private Thread thread;

        private Uri serverUri;
        private string nickname;

        public StreamProxy(Uri serverUri, string nickname)
        {
            this.serverUri = serverUri;
            this.nickname = nickname;
        }

        private void Listen()
        {
            while (true)
                try
                {
                    Stream vlcStream = WebRequest.Create("http://localhost:8095/stream.flv").GetResponse().GetResponseStream();
                    NetworkStream networkStream = new TcpClient(serverUri.Host, serverUri.Port).GetStream();

                    byte[] header = Encoding.ASCII.GetBytes("GET /" + nickname + "?action=write HTTP/1.1\r\n\r\n");
                    networkStream.Write(header, 0, header.Length);

                    int read = 0;
                    byte[] buffer = new byte[BUFFER_SIZE];
                    do
                    {
                        read = vlcStream.Read(buffer, 0, BUFFER_SIZE);
                        networkStream.Write(buffer, 0, read);
                    }
                    while (read > 0);
                }
                catch (Exception)
                {
                }
        }

        public void Start()
        {
            this.thread = new Thread(new ThreadStart(this.Listen));
            this.thread.IsBackground = true;
            this.thread.Start();
        }

        public void Stop()
        {
            this.thread.Abort();
        }
    }
}
