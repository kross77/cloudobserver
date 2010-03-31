using System;
using System.ServiceModel;

using CloudObserver.Services;

namespace CloudObserver
{
    public static class TestClient
    {
        public static void Main(string[] args)
        {
            Console.Write("Gateway Address: ");
            string gatewayServiceAddress = Console.ReadLine();

            string workBlockServiceAddress;
            using (ChannelFactory<IGateway> channelFactory = new ChannelFactory<IGateway>(new BasicHttpBinding(), gatewayServiceAddress))
            {
                IGateway gateway = channelFactory.CreateChannel();
                try
                {
                    workBlockServiceAddress = gateway.GetWorkBlock();
                }
                catch (Exception exception)
                {
                    Console.Write("An error occured while communicating with the gateway service. Details: " + exception.Message);
                    return;
                }
                finally
                {
                    try
                    {
                        ((IClientChannel)gateway).Close();
                    }
                    catch (Exception)
                    {
                        ((IClientChannel)gateway).Abort();
                    }
                }
            }

            string tcpStreamAddress;
            using (ChannelFactory<IWorkBlock> channelFactory = new ChannelFactory<IWorkBlock>(new BasicHttpBinding(), workBlockServiceAddress))
            {
                IWorkBlock workBlock = channelFactory.CreateChannel();
                try
                {
                    Random random = new Random();
                    int n = random.Next(10);
                    int[] contentIds = new int[n];
                    Console.Write("Requesting content ids:");
                    for (int i = 0; i < n; i++)
                    {
                        contentIds[i] = random.Next(Byte.MaxValue);
                        Console.Write(" " + contentIds[i].ToString());
                    }
                    Console.WriteLine(".");
                    
                    tcpStreamAddress = workBlock.GetTcpStreamUriToRead(contentIds);
                }
                catch (Exception exception)
                {
                    Console.Write("An error occured while communicating with the work block service. Details: " + exception.Message);
                    return;
                }
                finally
                {
                    try
                    {
                        ((IClientChannel)workBlock).Close();
                    }
                    catch (Exception)
                    {
                        ((IClientChannel)workBlock).Abort();
                    }
                }
            }

            Console.WriteLine("Stream Address: " + tcpStreamAddress);
            Console.WriteLine("Press any key...");
            Console.ReadKey();
        }
    }
}
