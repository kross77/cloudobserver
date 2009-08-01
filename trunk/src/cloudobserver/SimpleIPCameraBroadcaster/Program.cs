using System;
using System.Timers;
using System.ServiceModel;
using CloudObserverVirtualCamerasServiceLibrary;

namespace SimpleIPCameraBroadcaster
{
    class Program
    {
        static int cameraID;
        static Timer framesTimer;
        static ICloudObserverVirtualCamerasService virtualCamerasServiceClient;

        static void Main(string[] args)
        {
            try
            {
                virtualCamerasServiceClient = ChannelFactory<ICloudObserverVirtualCamerasService>.CreateChannel(new BasicHttpBinding(), new EndpointAddress("http://localhost:9000/CloudObserverVirtualCamerasService"));
                Console.Write("CameraID: ");
                cameraID = Int32.Parse(Console.ReadLine());
                virtualCamerasServiceClient.SetSource(cameraID, @"http://89.106.173.195/snap.jpg");
                Console.Write("FPS: ");
                int fps = Int32.Parse(Console.ReadLine());
                virtualCamerasServiceClient.SetCredentials(cameraID, "live", "live");
                virtualCamerasServiceClient.SetFPS(cameraID, fps);
                virtualCamerasServiceClient.StartBroadcasting(cameraID);
                Console.WriteLine("Broadcast started.");
                framesTimer = new Timer(100);
                framesTimer.Elapsed += new ElapsedEventHandler(framesTimer_Elapsed);
                framesTimer.Start();
                Console.WriteLine("Press any key to stop broadcasting...");
                Console.CursorVisible = false;
                Console.ReadKey();
            }
            catch (Exception exception)
            {
                Console.Write(exception.Message);
                Console.ReadKey();
            }
        }

        static void framesTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            Console.SetCursorPosition(0, 5);
            try
            {
                Console.Write("Frames: " + virtualCamerasServiceClient.GetFramesCounter(cameraID));
            }
            catch (Exception exception)
            {
                framesTimer.Stop();
                Console.Clear();
                Console.Write(exception.Message);
                Console.ReadKey();
            }
        }
    }
}