using System;
using System.Diagnostics;
using System.Net;
using System.Net.Sockets;

namespace CloudObserverWriter
{
    public class Writer
    {
        private const ushort MIN_DYNAMIC_PORT = 49152;
        private const ushort MAX_DYNAMIC_PORT = 65535;

        private Process vlcProcess;
        private StreamProxy streamProxy;
        private string cameraUrl;
        private string serverUrl;
        private string nickname;
        private bool webcam;
        

        public Writer(string serverUrl, string nickname)
        {
            this.serverUrl = serverUrl;
            this.nickname = nickname;
            this.webcam = true;
        }

        public Writer(string cameraUrl, string serverUrl, string nickname)
        {
            this.cameraUrl = cameraUrl;
            this.serverUrl = serverUrl;
            this.nickname = nickname;
            this.webcam = false;
        }

        public void Start()
        {
            uint dynamicPort = GetFreePort();
            Console.WriteLine("Dynamic local port is " + dynamicPort.ToString() + ".");

            ProcessStartInfo vlcProcessStartInfo = new ProcessStartInfo();
            vlcProcessStartInfo.FileName = @".\VLC\vlc1.exe";
            vlcProcessStartInfo.Arguments = "-I -o " + (webcam ? "dshow:// vdev adev size=\"640x480\"" : ("-R " + cameraUrl + " --file-caching=10 --rtsp-caching=10 --realrtsp-caching=10 --rtsp-session-timeout=-1")) +
                " --sout=\"#transcode{vcodec=FLV1,acodec=mp3,ab=128,channels=2,samplerate=44100}:duplicate{dst=std{access=http{mime=video/x-flv},mux=ffmpeg{flv},dst=:" + dynamicPort.ToString() + "/stream.flv}}\"";
            vlcProcessStartInfo.CreateNoWindow = true;

            vlcProcess = Process.Start(vlcProcessStartInfo);

            streamProxy = new StreamProxy(new Uri("http://localhost:" + dynamicPort + "/stream.flv"), new Uri(serverUrl), nickname);
            streamProxy.Start();
        }

        public void Stop()
        {
            streamProxy.Stop();
        }

        public void Close()
        {
            if ((vlcProcess != null) && (!vlcProcess.HasExited))
                vlcProcess.Kill();
        }

        private static uint GetFreePort()
        {
            Random random = new Random();
            int port;
            do
            {
                port = random.Next(MIN_DYNAMIC_PORT, MAX_DYNAMIC_PORT);
            } while (!CheckPort(port));

            return (uint)port;
        }

        private static bool CheckPort(int port)
        {
            try
            {
                Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                socket.Bind(new IPEndPoint(IPAddress.Loopback, port));
                socket.Close();

                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }
    }
}
