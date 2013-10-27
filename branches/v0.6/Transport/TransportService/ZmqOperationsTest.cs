using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ZeroMQ;

namespace TransportService
{
    internal class ZmqOperationsTest
    {
        private static int _sentCounter;

        public static void TestZmqOperations()
        {
            _sentCounter = 0;

            var context = ZmqContext.Create();

            var server = context.CreateSocket(SocketType.ROUTER);
            server.Bind("tcp://*:4782");

            var clientA = context.CreateSocket(SocketType.DEALER);
            clientA.Identity = "A".ToByteArray();
            clientA.Connect("tcp://localhost:4782");

            var clientB = context.CreateSocket(SocketType.DEALER);
            clientB.Identity = "B".ToByteArray();
            clientB.Connect("tcp://localhost:4782");

            clientA.ReceiveReady += OnServerResponseToA;
            clientB.ReceiveReady += OnServerResponseToB;
            server.ReceiveReady += OnServerRequest;

            var poller = new Poller(new List<ZmqSocket> { clientA, clientB, server });

            var timeout = new TimeSpan(0, 0, 1);

            while (true)
            {
                poller.Poll(timeout);
                clientA.Send("Hello".ToByteArray());
            }
        }

        private static void OnServerResponseToA(object sender, SocketEventArgs e)
        {
            var result = e.Socket.ReceiveMessage();

            var message = result.Aggregate("", (current, f) => current + f.Buffer.ToUtf8() + "\n");
            Console.Write("client A receiverd: {0}", message);
        }

        private static void OnServerResponseToB(object sender, SocketEventArgs e)
        {
            var result = e.Socket.ReceiveMessage();

            var message = result.Aggregate("", (current, f) => current + f.Buffer.ToUtf8() + "\n");
            Console.Write("client B receiverd: {0}", message);
        }

        private static void OnServerRequest(object sender, SocketEventArgs e)
        {
            var server = e.Socket;
            var result = server.ReceiveMessage();

            if (result.FrameCount > 1)
            {
                var senderId = result[0].Buffer.ToUtf8();
                var message = new byte[0];
                for(var i = 1; i < result.FrameCount; ++i)
                {
                    message = message.Concat(result[i].Buffer).ToArray();
                }

                Console.WriteLine("server received: {0}, from {1}", message.ToUtf8(), senderId);

                server.SendMore(senderId.ToByteArray());
                server.Send("world".ToByteArray());
            }
        }
    }
}