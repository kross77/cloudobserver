using System;
using System.IO;
using System.Net;
using System.Text;

namespace NetworkUtilities.HttpGet
{
    public class HttpGet
    {
        private const int bufferSize = 1024;

        public static void Main(string[] args)
        {
            Console.WriteLine("Network Utilities: HTTP GET" + Environment.NewLine + "Cloud Observer Team (c) 2010" + Environment.NewLine);
            Console.WriteLine("Type '@exit' to exit the program." + Environment.NewLine);

            FileStream fileStream = null;
            Console.Write("Save response to file? (Y/N) ");
            bool saveToFile = (Console.ReadLine().ToUpper()[0] == 'Y');
            if (saveToFile)
            {
                Console.Write("File name: ");
                string fileName = Console.ReadLine();
                fileStream = File.Create(fileName);
            }

            Console.Write("URI: ");
            string uri = Console.ReadLine();
            while (uri != "@exit")
            {
                try
                {
                    Stream responseStream = WebRequest.Create(uri).GetResponse().GetResponseStream();
                    byte[] buffer = new byte[bufferSize];
                    int read = responseStream.Read(buffer, 0, bufferSize);
                    while (read > 0)
                    {
                        Console.Write(Encoding.UTF8.GetString(buffer, 0, read));
                        if (saveToFile)
                            fileStream.Write(buffer, 0, read);
                        read = responseStream.Read(buffer, 0, bufferSize);
                    }
                    Console.WriteLine();
                }
                catch (Exception e)
                {
                    Console.Write(e.Message + Environment.NewLine);
                }
                finally
                {
                    if (saveToFile)
                        fileStream.Close();
                }
                Console.Write(Environment.NewLine + "URI: ");
                uri = Console.ReadLine();
            }
        }
    }
}