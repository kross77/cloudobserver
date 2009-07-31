using System;
using System.IO;
using System.Timers;
using System.ServiceModel;
using CloudObserverBroadcastServiceLibrary;

namespace SimpleBroadcaster
{
    class Program
    {
        static ICloudObserverBroadcastService client;
        static int i = 0;
        static int framesCounter = 0;
        const string baseAddress = @"C:\";

        static void Main(string[] args)
        {
            client = ChannelFactory<ICloudObserverBroadcastService>.CreateChannel(new BasicHttpBinding(), new EndpointAddress("http://localhost:9000/CloudObserverBroadcastService"));
            Console.Write("FPS: ");
            int fps = Int32.Parse(Console.ReadLine());
            Timer timer = new Timer(1000 / fps);
            timer.Elapsed += new ElapsedEventHandler(timer_Elapsed);
            timer.Start();
            Console.WriteLine("Press any key to stop broadcasting...");
            Console.ReadKey();
        }

        static void timer_Elapsed(object sender, ElapsedEventArgs e)
        {
            client.WriteFrame(1, File.ReadAllBytes(baseAddress + i + ".jpg"));
            i = (i + 1) % 2;
            framesCounter++;
            Console.WriteLine("  total frames sent: " + framesCounter);
        }
    }
}