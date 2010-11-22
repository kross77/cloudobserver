using System;
using System.Diagnostics;

namespace CloudObserverWriter
{
    public class Program
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Cloud Observer Writer 1.0.0");
            Console.WriteLine("by CloudForever (c) team");
            Console.WriteLine();

            string url = "";
            string server = "";
            string nickname = "";
            bool webcam = false;

            int i = 0;
            while (i < args.Length)
                switch (args[i])
                {
                    case "-nickname":
                        nickname = args[i + 1];
                        i += 2;
                        break;
                    case "-server":
                        server = args[i + 1];
                        i += 2;
                        break;
                    case "-url":
                        url = args[i + 1];
                        i += 2;
                        break;
                    case "-webcam":
                        webcam = true;
                        i++;
                        break;
                    default:
                        Console.WriteLine("Unknown argument '" + args[i] + "' skipped.");
                        i++;
                        break;
                }

            if (!webcam && (url == string.Empty))
            {
                Console.Write("Please, enter your camera stream url or type 'webcam' to use your web camera: ");
                url = Console.ReadLine();
                if (url == "webcam")
                    webcam = true;
            }
            else
                if (webcam)
                    Console.WriteLine("Stream will be captured from your default web camera.");
                else
                    Console.WriteLine("Camera stream will be captured from the following url: " + url);

            if (server == string.Empty)
            {
                Console.Write("Please, enter Cloud Observer server url: ");
                server = Console.ReadLine();
            }
            else
                Console.WriteLine("Stream will be broadcasted to the following Cloud Observer server: " + server);

            if (nickname == string.Empty)
            {
                Console.Write("Please, enter the nickname to use with the stream: ");
                nickname = Console.ReadLine();
            }
            else
                Console.WriteLine("Stream will have the following nickname: " + nickname);
            Console.WriteLine();

            ProcessStartInfo vlcProcessStartInfo = new ProcessStartInfo();
            vlcProcessStartInfo.FileName = @".\VLC\vlc1.exe";
            vlcProcessStartInfo.Arguments = "-I -o " + (webcam ? "dshow:// vdev adev size=\"640x480\"" : ("-R " + url + " --file-caching=10 --rtsp-caching=10 --realrtsp-caching=10 --rtsp-session-timeout=-1")) +
                " --sout=\"#transcode{vcodec=FLV1,acodec=mp3,ab=128,channels=2,samplerate=44100}:duplicate{dst=std{access=http{mime=video/x-flv},mux=ffmpeg{flv},dst=:8095/stream.flv}}\"";
            vlcProcessStartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            Process vlcProcess = new Process();
            vlcProcess.StartInfo = vlcProcessStartInfo;
            vlcProcess.Start();

            StreamProxy streamProxy = new StreamProxy(new Uri(server), nickname);
            Console.WriteLine("Your stream is now being broadcasted. Press any key to stop and exit...");
            Console.WriteLine();
            streamProxy.Start();
            Console.ReadKey();
            streamProxy.Stop();

            try
            {
                vlcProcess.Kill();
            }
            catch (Exception)
            {
            }
        }
    }
}
