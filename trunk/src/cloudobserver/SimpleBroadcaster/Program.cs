using System;
using System.IO;
using System.Timers;
using System.ServiceModel;
using CloudObserverBroadcastServiceLibrary;

namespace SimpleBroadcaster
{
    class Program
    {
        static int cameraID;
        static int currentImage = 0;
        static int framesCounter = 0;
        static string basePath = @"C:\";
        static Timer broadcastingTimer;
        static ICloudObserverBroadcastService broadcastServiceClient;

        static void Main(string[] args)
        {
            try
            {
                broadcastServiceClient = ChannelFactory<ICloudObserverBroadcastService>.CreateChannel(new BasicHttpBinding(), new EndpointAddress(@"http://localhost:9000/CloudObserverBroadcastService"));
                Console.Write("CameraID: ");
                cameraID = Int32.Parse(Console.ReadLine());
                Console.Write("FPS: ");
                int fps = Int32.Parse(Console.ReadLine());
                broadcastingTimer = new Timer(1000 / fps);
                broadcastingTimer.Elapsed += new ElapsedEventHandler(broadcastingTimer_Elapsed);
                broadcastingTimer.Start();
                Console.WriteLine("Broadcast started.");
                Console.WriteLine("Press any key to stop broadcasting...");
                Console.CursorVisible = false;
                Console.ReadKey();
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.Message);
                Console.ReadKey();
            }
        }

        static void broadcastingTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            framesCounter++;
            Console.SetCursorPosition(0, 5);
            Console.Write("Frames: " + framesCounter);
            try
            {
                broadcastServiceClient.WriteFrame(cameraID, File.ReadAllBytes(basePath + currentImage + ".jpg"));
                currentImage = (currentImage + 1) % 8;
            }
            catch (Exception exception)
            {
                broadcastingTimer.Stop();
                Console.Clear();
                Console.Write(exception.Message);
                Console.ReadKey();
            }
        }
    }
}