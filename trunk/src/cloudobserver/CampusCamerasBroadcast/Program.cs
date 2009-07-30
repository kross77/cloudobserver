using System;
using System.Timers;
using System.ServiceModel;
using CloudObserverVirtualCamerasServiceLibrary;

namespace CampusCamerasBroadcast
{
    class Program
    {
        static ICloudObserverVirtualCamerasService client;
        static int cameraID;
        static int framesCounter;
        static int framesCounterBackup;

        static void Main(string[] args)
        {
            client = ChannelFactory<ICloudObserverVirtualCamerasService>.CreateChannel(new BasicHttpBinding(), new EndpointAddress("http://localhost:9000/CloudObserverVirtualCamerasService"));
            Console.Write("CameraID: ");
            cameraID = Int32.Parse(Console.ReadLine());
            for (int i = 0; i < 5; i++)
                client.AddSource(cameraID, @"http://www.campus.spbu.ru/images/webcam/camera" + (i + 1) + ".jpg", 1);
            foreach (string source in client.GetSources(cameraID))
                Console.WriteLine("  source added: " + source);
            Console.Write("FPS: ");
            int fps = Int32.Parse(Console.ReadLine());
            client.SetFPS(cameraID, fps);
            client.StartBroadcasting(cameraID);
            Console.WriteLine("Campus cameras broadcasting started.");
            framesCounter = 0;
            framesCounterBackup = 0;
            Timer timer = new Timer(250);
            timer.Elapsed += new ElapsedEventHandler(timer_Elapsed);
            timer.Start();
            Console.Write("Press any key to stop broadcasting...");
            Console.ReadKey();
        }

        static void timer_Elapsed(object sender, ElapsedEventArgs e)
        {
            int framesCounter = client.GetFramesCounter(cameraID);
            if (framesCounter != framesCounterBackup)
            {
                Console.WriteLine("  total frames sent: " + framesCounter);
                framesCounterBackup = framesCounter;
            }
        }
    }
}