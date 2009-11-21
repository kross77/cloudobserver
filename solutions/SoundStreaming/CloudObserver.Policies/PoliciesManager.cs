using System;
using System.Collections.Generic;
using System.ServiceModel;
using System.ServiceModel.Description;

namespace CloudObserver.Policies
{
    /// <summary>
    /// Manages Silverlight and Flash cross-domain access.
    /// </summary>
    public class PoliciesManager
    {
        #region Fields
        /// <summary>
        /// An IP address at which policies are managed.
        /// </summary>
        private string ipAddress;

        /// <summary>
        /// A dictionary of controlled ports. The second value contains the number of references to the specified port.
        /// </summary>
        private Dictionary<int, int> controlledPorts;

        /// <summary>
        /// A dictionary of controlled ports. The second value is the System.ServiceModel.ServiceHost object
        /// used to operate CloudObserver.Policies.PolicyRetriever service on the specified port.
        /// </summary>
        private Dictionary<int, ServiceHost> policyRetrievers;
        #endregion

        #region Properties
        /// <summary>
        /// Gets or sets an IP address at which policies are managed.
        /// </summary>
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
        /// <summary>
        /// Initializes a new instance of the CloudObserver.Policies.PoliciesManager class with the localhost IP address.
        /// </summary>
        public PoliciesManager() : this("localhost") { }

        /// <summary>
        /// Initializes a new instance of the CloudObserver.Policies.PoliciesManager class with the provided IP address.
        /// </summary>
        /// <param name="ipAddress">An IP address at which policies will be managed.</param>
        public PoliciesManager(string ipAddress)
        {
            this.ipAddress = ipAddress;
            this.controlledPorts = new Dictionary<int, int>();
            this.policyRetrievers = new Dictionary<int, ServiceHost>();
        }
        #endregion

        #region Public Methods
        /// <summary>
        /// Connects port to the policies management. If the port is already managed just increases the number of references to it.
        /// </summary>
        /// <param name="port">Port to connect.</param>
        public void ConnectPort(int port)
        {
            if (!controlledPorts.ContainsKey(port))
            {
                controlledPorts[port] = 1;
                HostPolicyRetriever(port);
            }
            else
                controlledPorts[port]++;
        }

        /// <summary>
        /// Disconnects port from the policies management. The port will be removed from policies management only if its references value falls to zero.
        /// </summary>
        /// <param name="port"></param>
        public void DisconnectPort(int port)
        {
            controlledPorts[port]--;
            if (controlledPorts[port] == 0)
                ReleasePort(port);
        }

        /// <summary>
        /// Resets policies manager. All ports will be removed from policies management.
        /// </summary>
        public void Reset()
        {
            foreach (ServiceHost policyRetriever in policyRetrievers.Values)
                policyRetriever.Close();
            controlledPorts.Clear();
            policyRetrievers.Clear();
        }
        #endregion

        #region Private Methods
        /// <summary>
        /// Hosts CloudObserver.Policies.PolicyRetriever service at the specified port.
        /// </summary>
        /// <param name="port">The port at which to host CloudObserver.Policies.PolicyRetriever.</param>
        private void HostPolicyRetriever(int port)
        {
            policyRetrievers[port] = new ServiceHost(typeof(PolicyRetriever), new Uri("http://" + ipAddress + ":" + port + "/"));
            policyRetrievers[port].AddServiceEndpoint(typeof(IPolicyRetriever), new WebHttpBinding(), "").Behaviors.Add(new WebHttpBehavior());
            policyRetrievers[port].Open();
        }

        /// <summary>
        /// Completely disconnects the port from policies management.
        /// </summary>
        /// <param name="port"></param>
        private void ReleasePort(int port)
        {
            policyRetrievers[port].Close();
            controlledPorts.Remove(port);
            policyRetrievers.Remove(port);
        }

        /// <summary>
        /// Restarts policies manager. All ports will remain in their current state.
        /// </summary>
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