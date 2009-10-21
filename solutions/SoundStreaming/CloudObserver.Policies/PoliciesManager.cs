using System;
using System.Collections.Generic;
using System.ServiceModel;
using System.ServiceModel.Description;

namespace CloudObserver.Policies
{
    public class PoliciesManager
    {
        #region Fields

        private string ipAddress;
        private Dictionary<int, int> controlledPorts;
        private Dictionary<int, ServiceHost> policyRetrievers;

        #endregion

        #region Constants

        private const string localhostIpAddress = "127.0.0.1";

        #endregion

        #region Properties

        public string IpAddress
        {
            get { return ipAddress; }
            set
            {
                ipAddress = value;
                Restart();
            }
        }

        #endregion

        #region Constructors

        public PoliciesManager() : this(localhostIpAddress) { }

        public PoliciesManager(string ipAddress)
        {
            this.ipAddress = ipAddress;
            controlledPorts = new Dictionary<int, int>();
            policyRetrievers = new Dictionary<int, ServiceHost>();
        }

        #endregion

        #region Public Methods

        public void ConnectPort(int port)
        {
            if (!controlledPorts.ContainsKey(port))
            {
                controlledPorts[port] = 0;
                HostPolicyRetriever(port);
            }
            else
                controlledPorts[port]++;
        }

        public void DisconnectPort(int port)
        {
            controlledPorts[port]--;
            if (controlledPorts[port] == 0)
                ReleasePort(port);
        }

        public void Reset()
        {
            foreach (ServiceHost policyRetriever in policyRetrievers.Values)
                policyRetriever.Close();
            controlledPorts.Clear();
            policyRetrievers.Clear();
        }

        #endregion

        #region Private Methods

        private void HostPolicyRetriever(int port)
        {
            policyRetrievers[port] = new ServiceHost(typeof(PolicyRetriever), new Uri("http://" + ipAddress + ":" + port + "/"));
            policyRetrievers[port].AddServiceEndpoint(typeof(IPolicyRetriever), new WebHttpBinding(), "").Behaviors.Add(new WebHttpBehavior());
            policyRetrievers[port].Open();
        }

        private void ReleasePort(int port)
        {
            policyRetrievers[port].Close();
            controlledPorts.Remove(port);
            policyRetrievers.Remove(port);
        }

        private void Restart()
        {
            foreach (int port in controlledPorts.Keys)
            {
                ServiceHost policyRetriever = policyRetrievers[port];
                policyRetriever.Close();
                HostPolicyRetriever(port);
            }
        }

        #endregion
    }
}