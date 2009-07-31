using System;
using System.Timers;
using System.ServiceModel;
using CloudObserverRemoteCamerasServiceLibrary;

namespace SimpleCampusBroadcaster
{
    class Program
    {
        static ICloudObserverRemoteCamerasService remoteCamerasServiceClient;
        static int cameraID;
        static int framesCounter;
        static int framesCounterBackup;

        static void Main(string[] args)
        {
            remoteCamerasServiceClient = ChannelFactory<ICloudObserverRemoteCamerasService>.CreateChannel(new BasicHttpBinding(), new EndpointAddress("http://localhost:9000/CloudObserverRemoteCamerasService"));
            Console.Write("CameraID: ");
            cameraID = Int32.Parse(Console.ReadLine());
            remoteCamerasServiceClient.SetSource(cameraID, @"http://89.106.173.195/snap.jpg");
            Console.WriteLine("Source http://89.106.173.195/snap.jpg added.");
            remoteCamerasServiceClient.SetCredentials(cameraID, "live", "live");
            Console.Write("FPS: ");
            int fps = Int32.Parse(Console.ReadLine());
            remoteCamerasServiceClient.SetFPS(cameraID, fps);
            remoteCamerasServiceClient.StartBroadcasting(cameraID);
            Console.WriteLine("Remote camera broadcasting started.");
            framesCounter = 0;
            framesCounterBackup = 0;
            Timer timer = new Timer(250);
            timer.Elapsed += new ElapsedEventHandler(timer_Elapsed);
            timer.Start();
            Console.WriteLine("Press any key to stop broadcasting...");
            Console.ReadKey();
        }

        static void timer_Elapsed(object sender, ElapsedEventArgs e)
        {
            int framesCounter = remoteCamerasServiceClient.GetFramesCounter(cameraID);
            if (framesCounter != framesCounterBackup)
            {
                Console.WriteLine("  total frames sent: " + framesCounter);
                framesCounterBackup = framesCounter;
            }
        }
    }
}