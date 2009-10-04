using System;
using System.Collections.Generic;
using System.ServiceModel;
using System.ServiceModel.Description;

namespace CloudObserver.Policies
{
    public class PoliciesManager
    {
        private string externalIP;
        private Dictionary<int, int> controlledPorts;
        private Dictionary<int, ServiceHost> policyRetrievers;

        public PoliciesManager()
        {
            controlledPorts = new Dictionary<int, int>();
            policyRetrievers = new Dictionary<int, ServiceHost>();
        }

        public void SetExternalIP(string externalIP)
        {
            this.externalIP = externalIP;
            this.Rehost();
        }

        public void ConnectPort(int port)
        {
            if ((!controlledPorts.ContainsKey(port)) || (controlledPorts[port] == 0))
            {
                controlledPorts[port] = 0;
                policyRetrievers[port] = new ServiceHost(typeof(PolicyRetriever), new Uri("http://" + externalIP + ":" + port + "/"));
                policyRetrievers[port].AddServiceEndpoint(typeof(PolicyRetrieverContract), new WebHttpBinding(), "").Behaviors.Add(new WebHttpBehavior());
                policyRetrievers[port].Open();
            } else
                controlledPorts[port]++;
        }

        public void DisconnectPort(int port)
        {
            controlledPorts[port]--;
            if (controlledPorts[port] == 0)
            {
                policyRetrievers[port].Close();
                controlledPorts.Remove(port);
                policyRetrievers.Remove(port);
            }
        }

        public void ReleasePort(int port)
        {
            policyRetrievers[port].Close();
            controlledPorts.Remove(port);
            policyRetrievers.Remove(port);
        }

        public void Reset()
        {
            foreach (ServiceHost policyRetriever in policyRetrievers.Values)
                policyRetriever.Close();
            controlledPorts.Clear();
            policyRetrievers.Clear();
        }

        private void Rehost()
        {
            foreach (int port in policyRetrievers.Keys)
            {
                ServiceHost policyRetriever = policyRetrievers[port];
                policyRetriever.Close();
                policyRetriever = new ServiceHost(typeof(PolicyRetriever), new Uri("http://" + externalIP + ":" + port + "/"));
                policyRetriever.AddServiceEndpoint(typeof(PolicyRetrieverContract), new WebHttpBinding(), "").Behaviors.Add(new WebHttpBehavior());
                policyRetriever.Open();
            }
        }
    }
}