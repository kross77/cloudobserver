using System;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.ServiceModel.Description;
using CloudObserverPolicyRetrieverServiceLibrary;

namespace SimplePolicyRetrieverServiceHoster
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                string serviceAddress = "http://localhost:9000/";
                ServiceHost serviceHost = new ServiceHost(typeof(CloudObserverPolicyRetrieverService), new Uri(serviceAddress));
                serviceHost.AddServiceEndpoint(typeof(ICloudObserverPolicyRetrieverService), new WebHttpBinding(), "").Behaviors.Add(new WebHttpBehavior());
                serviceHost.Open();
                Console.WriteLine("Cloud Observer Policy Retriever service hosted at " + serviceAddress);
                Console.Write("Press any key to stop hosting...");
                Console.ReadKey();
                serviceHost.Close();
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.Message);
                Console.ReadKey();
            }
        }
    }
}