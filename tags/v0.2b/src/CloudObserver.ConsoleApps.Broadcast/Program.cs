using System;
using System.IO;
using System.ServiceModel;
using System.Timers;
using CloudObserver.Services;

namespace CloudObserver.ConsoleApps.Broadcast
{
    class Program
    {
        static int cameraID;
        static int currentFrame = 0;
        static string sourceType;
        static string[] sourceUri;
        static int framesCounter = 0;
        static Timer framesTimer;
        static Timer broadcastingTimer;
        static BroadcastServiceContract broadcastServiceClient;
        static IPCamerasServiceContract ipCamerasServiceClient;

        [STAThread]
        static void Main(string[] args)
        {
            if ((args.Length > 0) && (args[0] == "/?"))
            {
                Console.Write("Usage: CloudObserver.ConsoleApps.Broadcast <cameraID> <fpsLimit> <controllerServiceUri> <sourceType> <sourceUri> [<provideCredentials>] [<userName>] [<password>]");
                return;
            }
            int fpsLimit;
            string controllerServiceUri;
            bool provideCredentials = false;
            string userName = "";
            string password = "";
            if (args.Length > 0)
            {
                cameraID = Int32.Parse(args[0]);
                Console.WriteLine("Camera ID: " + cameraID);
                fpsLimit = Int32.Parse(args[1]);
                Console.WriteLine("FPS limit: " + fpsLimit);
                controllerServiceUri = args[2];
                Console.WriteLine("Controller Service URI: " + controllerServiceUri);
                sourceType = args[3];
                Console.WriteLine("Source type: " + sourceType);
                switch (sourceType)
                {
                    case "Files":
                        sourceUri = new string[args.Length - 4];
                        for (int i = 4; i < args.Length; i++)
                            sourceUri[i - 4] = args[i];
                        break;
                    case "JPEG":
                    case "MJPEG":
                        sourceUri = new string[1];
                        sourceUri[0] = args[4];
                        Console.WriteLine("Source URI: " + sourceUri[0]);
                        provideCredentials = Boolean.Parse(args[5]);
                        Console.WriteLine("Provide credentials: " + provideCredentials);
                        if (provideCredentials)
                        {
                            userName = args[6];
                            Console.WriteLine("UserName: " + userName);
                            password = args[7];
                            Console.WriteLine("Password: " + password);
                        }
                        break;
                    default:
                        Console.Write("Invalid source type. Use 'JPEG' or 'MJPEG' for IP cameras source and 'Files' for local files source.");
                        Console.ReadKey();
                        return;
                }
            }
            else
            {
                Console.Write("Camera ID: ");
                cameraID = Int32.Parse(Console.ReadLine());
                Console.Write("FPS limit: ");
                fpsLimit = Int32.Parse(Console.ReadLine());
                Console.Write("Controller Service URI: ");
                controllerServiceUri = Console.ReadLine();
                Console.WriteLine("Select source type:");
                Console.WriteLine("  1. Local Files");
                Console.WriteLine("  2. JPEG IP Camera");
                Console.WriteLine("  3. MJPEG IP Camera");
                Console.Write("Source type: ");
                string temp = Console.ReadLine();
                while ((temp != "1") && (temp != "2") && (temp != "3"))
                {
                    Console.SetCursorPosition(13, Console.CursorTop - 1);
                    temp = Console.ReadLine();
                }
                switch (temp)
                {
                    case "1":
                        sourceType = "Files";
                        break;
                    case "2":
                        sourceType = "JPEG";
                        break;
                    case "3":
                        sourceType = "MJPEG";
                        break;
                    default:
                        return;
                }
                switch (sourceType)
                {
                    case "Files":
                        System.Windows.Forms.OpenFileDialog openFileDialogServiceFiles = new System.Windows.Forms.OpenFileDialog();
                        openFileDialogServiceFiles.Filter = "JPEG (*.jpg; *.jpeg)|*.jpg;*.jpeg";
                        openFileDialogServiceFiles.Multiselect = true;
                        if (openFileDialogServiceFiles.ShowDialog() != System.Windows.Forms.DialogResult.OK) return;
                        sourceUri = openFileDialogServiceFiles.FileNames;
                        break;
                    case "JPEG":
                    case "MJPEG":
                        sourceUri = new string[1];
                        Console.Write("Source URI: ");
                        sourceUri[0] = Console.ReadLine();
                        Console.Write("Provide credentials? (Y/N) ");
                        temp = Console.ReadLine().ToUpper();
                        while ((temp != "Y") && (temp != "N"))
                        {
                            Console.SetCursorPosition(27, Console.CursorTop - 1);
                            temp = Console.ReadLine().ToUpper();
                        }
                        provideCredentials = (temp == "Y");
                        if (provideCredentials)
                        {
                            Console.Write("UserName: ");
                            userName = Console.ReadLine();
                            Console.Write("Password: ");
                            password = Console.ReadLine();
                        }
                        break;
                    default:
                        Console.Write("Invalid source type. Use 'JPEG' or 'MJPEG' for IP cameras source and 'Files' for local files source.");
                        Console.ReadKey();
                        return;
                }
            }

            if (sourceType == "Files")
                foreach (string uri in sourceUri)
                    Console.WriteLine("Source URI: " + uri);
            Console.WriteLine();

            try
            {
                ControllerServiceContract controllerServiceClient = ChannelFactory<ControllerServiceContract>.CreateChannel(new BasicHttpBinding(), new EndpointAddress(controllerServiceUri));
                switch (sourceType)
                {
                    case "Files":
                        broadcastServiceClient = ChannelFactory<BroadcastServiceContract>.CreateChannel(new BasicHttpBinding(),
                            new EndpointAddress(controllerServiceClient.GetServiceUri(ServiceType.BroadcastService)));
                        broadcastingTimer = new Timer(1000 / fpsLimit);
                        broadcastingTimer.Elapsed += new ElapsedEventHandler(broadcastingTimer_Elapsed);
                        broadcastingTimer.Start();
                        Console.WriteLine("Broadcasting from local files.");
                        Console.Write("Press any key to stop broadcasting...");
                        Console.CursorVisible = false;
                        Console.ReadKey();
                        broadcastingTimer.Stop();
                        break;
                    case "JPEG":
                    case "MJPEG":
                        ipCamerasServiceClient = ChannelFactory<IPCamerasServiceContract>.CreateChannel(new BasicHttpBinding(),
                            new EndpointAddress(controllerServiceClient.GetServiceUri(ServiceType.IPCamerasService)));
                        ipCamerasServiceClient.SetSource(cameraID, sourceType, sourceUri[0]);
                        ipCamerasServiceClient.SetFPSLimit(cameraID, fpsLimit);
                        if (provideCredentials) ipCamerasServiceClient.SetCredentials(cameraID, userName, password);
                        ipCamerasServiceClient.StartBroadcasting(cameraID);
                        framesTimer = new Timer(100);
                        framesTimer.Start();
                        framesTimer.Elapsed += new ElapsedEventHandler(framesTimer_Elapsed);
                        Console.WriteLine("Broadcasting from " + sourceType + " IP camera at " + sourceUri[0]);
                        Console.Write("Press any key to stop broadcasting...");
                        Console.CursorVisible = false;
                        Console.ReadKey();
                        ipCamerasServiceClient.StopBroadcasting(cameraID);
                        break;
                }
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.ToString());
                Console.ReadKey();
            }
        }

        static void broadcastingTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            broadcastServiceClient.WriteFrame(cameraID, File.ReadAllBytes(sourceUri[currentFrame]));
            currentFrame = (currentFrame + 1) % sourceUri.Length;
            framesCounter++;
            Console.SetCursorPosition(60, 0);
            Console.Write("Frames: " + framesCounter);
        }

        static void framesTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            Console.SetCursorPosition(60, 0);
            Console.Write("Frames: " + ipCamerasServiceClient.GetFramesCounter(cameraID));
        }
    }
}