using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.IO;

namespace StreamReceiver
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                IPAddress ipAd = IPAddress.Parse("127.0.0.1"); //use local m/c IP address, and use the same in the client
                /* Initializes the Listener */
                TcpListener myList = new TcpListener(ipAd, 8001);
                /* Start Listeneting at the specified port */
                myList.Start();
                Console.WriteLine("The server is running at port 8001...");
                Console.WriteLine("The local End point is :" + myList.LocalEndpoint);
                Console.WriteLine("Waiting for a connection.....");
                Socket s = myList.AcceptSocket();
                Console.WriteLine("Connection accepted from " + s.RemoteEndPoint);
                byte[] b = new byte[1024];
                string path = @"c:\copied.mp3";
                using (FileStream sw = File.Create(path))
                {

                    while (true)
                    {
                        int k = s.Receive(b);
                        if (k == 0)
                            break;
                        else
                            sw.Write(b, 0, k);                        
                    }
                    sw.Close();
                }
                
                //for (int i = 0; i < k; i++)
                 //   Console.Write(Convert.ToChar(b[i]));
                //ASCIIEncoding asen = new ASCIIEncoding();
                //s.Send(asen.GetBytes("The string was recieved by the server."));
                //Console.WriteLine("\nSent Acknowledgement");
                /* clean up */
                s.Close();
                Console.WriteLine("Recieved...");
                myList.Stop();
            }
            catch (Exception e)
            {
                Console.WriteLine("Error..... " + e.StackTrace);
            }
        }
    }
}
