using System;
using System.Runtime.InteropServices;

namespace CloudObserverWriter
{
    public class Program
    {
        private static Writer writer;

        [DllImport("Kernel32")]
        private static extern bool SetConsoleCtrlHandler(HandlerRoutine handler, bool add);

        private delegate bool HandlerRoutine(CtrlTypes ctrlType);

        private enum CtrlTypes
        {
            CTRL_C_EVENT,
            CTRL_BREAK_EVENT,
            CTRL_CLOSE_EVENT,
            CTRL_LOGOFF_EVENT,
            CTRL_SHUTDOWN_EVENT
        }

        private static bool ConsoleCtrlCheck(CtrlTypes ctrlType)
        {
            switch (ctrlType)
            {
                case CtrlTypes.CTRL_C_EVENT:
                case CtrlTypes.CTRL_BREAK_EVENT:
                case CtrlTypes.CTRL_CLOSE_EVENT:
                case CtrlTypes.CTRL_LOGOFF_EVENT:
                case CtrlTypes.CTRL_SHUTDOWN_EVENT:
                    Close();
                    return true;
                default:
                    return false;
            }
        }

        private static void Close()
        {
            writer.Close();

            Environment.Exit(0);
        }

        public static void Main(string[] args)
        {
            Console.WriteLine("Cloud Observer Writer 1.0.0");
            Console.WriteLine("by CloudForever (c) team");
            Console.WriteLine();

            string cameraUrl = "";
            string serverUrl = "";
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
                        serverUrl = args[i + 1];
                        i += 2;
                        break;
                    case "-url":
                        cameraUrl = args[i + 1];
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

            if (!webcam && (cameraUrl == string.Empty))
            {
                Console.Write("Please, enter your camera stream url or type 'webcam' to use your web camera: ");
                cameraUrl = Console.ReadLine();
                if (cameraUrl == "webcam")
                    webcam = true;
            }
            else
                if (webcam)
                    Console.WriteLine("Stream will be captured from your default web camera.");
                else
                    Console.WriteLine("Camera stream will be captured from the following url: " + cameraUrl);

            if (serverUrl == string.Empty)
            {
                Console.Write("Please, enter Cloud Observer server url: ");
                serverUrl = Console.ReadLine();
            }
            else
                Console.WriteLine("Stream will be broadcasted to the following Cloud Observer server: " + serverUrl);

            if (nickname == string.Empty)
            {
                Console.Write("Please, enter the nickname to use with the stream: ");
                nickname = Console.ReadLine();
            }
            else
                Console.WriteLine("Stream will have the following nickname: " + nickname);
            Console.WriteLine();

            HandlerRoutine consoleCtrlHandler = new HandlerRoutine(ConsoleCtrlCheck);
            SetConsoleCtrlHandler(consoleCtrlHandler, true);

            writer = webcam ? new Writer(serverUrl, nickname) : new Writer(cameraUrl, serverUrl, nickname);

            Console.WriteLine("Your stream is now being broadcasted. Press any key to stop and exit...");
            Console.WriteLine();
            writer.Start();
            Console.ReadKey();
            Close();
        }
    }
}
