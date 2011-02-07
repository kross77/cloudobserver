using System;
using System.Reflection;
using System.ServiceModel;
using System.ServiceModel.Description;
using System.Windows.Forms;

namespace SimpleServiceHoster
{
    class Program
    {
        private const int MAX_RECEIVED_MESSAGE_SIZE = 2147483647;
        private const int MAX_ARRAY_LENGTH = 2147483647;

        [STAThread]
        static void Main(string[] args)
        {
            string serviceDLL;
            string serviceName;
            if (args.Length == 2)
            {
                serviceDLL = args[0];
                serviceName = args[1];
            }
            else
            {
                OpenFileDialog openFileDialog = new OpenFileDialog();
                openFileDialog.Filter = "Dynamic Link Library (*.dll)|*.dll";
                if (openFileDialog.ShowDialog() != DialogResult.OK) return;
                serviceDLL = openFileDialog.FileName;
                serviceName = openFileDialog.SafeFileName.Substring(0, openFileDialog.SafeFileName.Length - 11);
            }
            try
            {
                Assembly serviceDLLAssembly = Assembly.LoadFile(serviceDLL);
                Type serviceType = serviceDLLAssembly.GetType(serviceName + "Library." + serviceName);
                Type serviceContractType = serviceDLLAssembly.GetType(serviceName + "Library.I" + serviceName);
                Console.WriteLine("Loaded: " + serviceName);

                string serviceAddress = @"http://localhost:9000/" + serviceName;

                ServiceHost serviceHost = new ServiceHost(serviceType, new Uri(serviceAddress));

                ServiceMetadataBehavior serviceMetadataBehavior = serviceHost.Description.Behaviors.Find<ServiceMetadataBehavior>();
                if (serviceMetadataBehavior == null)
                {
                    serviceMetadataBehavior = new ServiceMetadataBehavior();
                    serviceMetadataBehavior.HttpGetEnabled = true;
                    serviceHost.Description.Behaviors.Add(serviceMetadataBehavior);
                }
                else
                    serviceMetadataBehavior.HttpGetEnabled = true;

                ServiceDebugBehavior serviceDebugBehavior = serviceHost.Description.Behaviors.Find<ServiceDebugBehavior>();
                if (serviceDebugBehavior == null)
                {
                    serviceDebugBehavior = new ServiceDebugBehavior();
                    serviceDebugBehavior.IncludeExceptionDetailInFaults = true;
                    serviceHost.Description.Behaviors.Add(serviceDebugBehavior);
                }
                else
                    serviceDebugBehavior.IncludeExceptionDetailInFaults = true;

                BasicHttpBinding binding = new BasicHttpBinding();
                binding.BypassProxyOnLocal = true;
                binding.MaxReceivedMessageSize = MAX_RECEIVED_MESSAGE_SIZE;
                binding.OpenTimeout = TimeSpan.FromMinutes(5);
                binding.CloseTimeout = TimeSpan.FromMinutes(5);
                binding.ReceiveTimeout = TimeSpan.FromMinutes(30);
                binding.SendTimeout = TimeSpan.FromMinutes(30);
                binding.ReaderQuotas.MaxArrayLength = MAX_ARRAY_LENGTH;
                serviceHost.AddServiceEndpoint(serviceContractType, binding, "");

                serviceHost.Open();

                Console.WriteLine("Service hosted at " + serviceAddress);
                Console.Write("Press any key to stop hosting...");
                Console.ReadKey();
                serviceHost.Close();
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.ToString());
                Console.ReadKey();
            }
        }
    }
}