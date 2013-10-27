#region

using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using Transport.Protocol.Utilities;
using ZeroMQ;

#endregion

namespace TransportService
{
    public static class Extensions
    {
        public static byte[] ToByteArray(this string tag)
        {
            return Encoding.UTF8.GetBytes(tag);
        }
    }

    internal class Program
    {
        private static void TestProtocol()
        {
            var schema = SchemaPrinter.Print();
            Console.WriteLine(schema);
            File.WriteAllText("TransportProtocol.proto", schema);
        }

        private static void TestZmq()
        {
            var context = ZmqContext.Create();
            var publisher = context.CreateSocket(SocketType.XPUB);
            publisher.Bind("tcp://*:4780");

            var subscriberA = context.CreateSocket(SocketType.XSUB);
            subscriberA.Connect("tcp://127.0.0.1:4780");
            subscriberA.Subscribe("A".ToByteArray());


            var subscriberB = context.CreateSocket(SocketType.XSUB);
            subscriberB.Connect("tcp://127.0.0.1:4780");
            subscriberB.Subscribe("B".ToByteArray());

            subscriberA.ReceiveReady += OnMessageToA;
            subscriberB.ReceiveReady += OnMessageToB;
            publisher.SendReady += OnSender;

            var poller = new Poller(new List<ZmqSocket> {publisher, subscriberA, subscriberB});

            var sleep = new TimeSpan(0, 0, 1);
            while (true)
            {
                poller.Poll(sleep);
            }
        }

        private static void OnMessageToA(object sender, SocketEventArgs e)
        {
            var result = e.Socket.ReceiveMessage();
            if (result.FrameCount > 1)
            {
                Console.WriteLine("A said: {0}", Encoding.UTF8.GetString(result[1].Buffer));
            }
            else
            {
                Console.WriteLine("error on A");
            }
        }

        private static void OnMessageToB(object sender, SocketEventArgs e)
        {
            var result = e.Socket.ReceiveMessage();
            if (result.FrameCount > 1)
            {
                Console.WriteLine("B said: {0}", Encoding.UTF8.GetString(result[1].Buffer));
            }
            else
            {
                Console.WriteLine("error on B");
            }
        }

        private static void OnSender(object sender, SocketEventArgs e)
        {
            var m2A = new ZmqMessage();
            m2A.Append("A".ToByteArray());
            m2A.Append("data".ToByteArray());
            e.Socket.SendMessage(m2A);

            var m2B = new ZmqMessage();
            m2B.Append("B".ToByteArray());
            m2B.Append("data 2".ToByteArray());
            e.Socket.SendMessage(m2B);
        }

        private static void Main()
        {
            try
            {
                TestProtocol();
                TestZmq();
            }
            catch (Exception e)
            {
                Console.Write(e);
                Console.ReadKey();
            }
        }
    }
}
