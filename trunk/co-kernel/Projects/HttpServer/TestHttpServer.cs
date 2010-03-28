using System;
using System.Collections;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace HttpServerPrototype.HttpServer
{
    public class TestHttpServer
    {
        private int port;
        private TcpListener listener;
        private Thread thread;

        public string Name;
        public Hashtable ResponseStatuses;

        public bool IsAlive
        {
            get
            {
                return thread.IsAlive;
            }
        }

        public TestHttpServer(int port)
        {
            this.port = port;
            ResponseStatusInit();
        }

        private void Listen()
        {
            listener = new TcpListener(IPAddress.Any, port);
            listener.Start();

            while (true)
            {
                TestHttpRequest request = new TestHttpRequest(listener.AcceptTcpClient(), this);
                Thread requestThread = new Thread(new ThreadStart(request.Process));
                requestThread.IsBackground = true;
                requestThread.Start();
            }
        }

        private void ResponseStatusInit()
        {
            ResponseStatuses = new Hashtable();

            ResponseStatuses.Add(200, "200 Ok");
            ResponseStatuses.Add(201, "201 Created");
            ResponseStatuses.Add(202, "202 Accepted");
            ResponseStatuses.Add(204, "204 No Content");

            ResponseStatuses.Add(301, "301 Moved Permanently");
            ResponseStatuses.Add(302, "302 Redirection");
            ResponseStatuses.Add(304, "304 Not Modified");

            ResponseStatuses.Add(400, "400 Bad Request");
            ResponseStatuses.Add(401, "401 Unauthorized");
            ResponseStatuses.Add(403, "403 Forbidden");
            ResponseStatuses.Add(404, "404 Not Found");

            ResponseStatuses.Add(500, "500 Internal Server Error");
            ResponseStatuses.Add(501, "501 Not Implemented");
            ResponseStatuses.Add(502, "502 Bad Gateway");
            ResponseStatuses.Add(503, "503 Service Unavailable");
        }

        public void Start()
        {
            thread = new Thread(new ThreadStart(Listen));
            thread.Start();
        }

        public void Stop()
        {
            listener.Stop();
            thread.Abort();
        }
    }
}
