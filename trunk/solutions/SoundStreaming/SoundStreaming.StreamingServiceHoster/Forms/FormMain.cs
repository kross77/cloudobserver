using System;
using System.Drawing;
using System.Threading;
using System.Diagnostics;
using System.ServiceModel;
using System.ServiceModel.Description;
using System.Text.RegularExpressions;
using System.Windows.Forms;

using CloudObserver.Policies;
using CloudObserver.Services.StreamingService;

namespace SoundStreaming.StreamingServiceHoster
{
    public partial class FormMain : Form
    {
        #region Fields

        private string ipAddress;
        private int bufferLength;
        private bool hosting;
        private string serviceUri;
        private bool alwaysOnTop;
        private ServiceState state;

        private PoliciesManager policiesManager;
        private ServiceHost streamingServiceHost;
        private StreamingServiceDiagnostics diagnostics;
        private Regex ipAddressRegex = new Regex(ipAddressRegexPattern);

        #endregion

        #region Constants

        private const int port = 9000;
        private const int maxReceivedMessageSize = 2147483647;
        private const int maxArrayLength = 2147483647;
        private const string localhostIpAddress = "127.0.0.1";
        private const string ipAddressRegexPattern = @"^((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[0-9][0-9]|[0-9])\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[0-9][0-9]|[0-9])\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[0-9][0-9]|[0-9])\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[0-9][0-9]|[0-9]))$";

        #endregion

        #region Properties

        public string IpAddress
        {
            get { return ipAddress; }
            set
            {
                if (ipAddressRegex.IsMatch(value))
                {
                    ipAddress = value;
                    textBoxIpAddress.Text = value;
                    checkBoxLocalhost.Checked = (value == localhostIpAddress);
                    checkBoxLocalhost.Enabled = (value != localhostIpAddress);
                    policiesManager.IpAddress = value;
                    ServiceUri = "http://" + value + ":" + port.ToString() + "/StreamingService";
                }
                else
                    IpAddress = ipAddress;
            }
        }

        public int BufferLength
        {
            get { return bufferLength; }
            set
            {
                bufferLength = value;
                numericUpDownBufferLength.Value = value;
                progressBarBufferPosition.Maximum = value;
                progressBarLastReadPosition.Maximum = value;
            }
        }

        public bool Hosting
        {
            get { return hosting; }
            set
            {
                hosting = value;
                if (value)
                {
                    policiesManager.ConnectPort(9000);
                    ThreadPool.QueueUserWorkItem(new WaitCallback(StreamingServiceHostProcess));
                }
                else
                {
                    if ((streamingServiceHost != null) && (streamingServiceHost.State == CommunicationState.Opened)) streamingServiceHost.Close();
                    streamingServiceHost = null;
                    diagnostics = null;
                    ResetDiagnostics();
                    if (State == ServiceState.Stopping) State = ServiceState.Stopped;
                }
            }
        }

        public string ServiceUri
        {
            get { return serviceUri; }
            set
            {
                serviceUri = value;
                textBoxServiceUri.Text = value;
            }
        }

        public bool AlwaysOnTop
        {
            get { return alwaysOnTop; }
            set
            {
                alwaysOnTop = value;
                checkBoxAlwaysOnTop.Checked = value;
                TopMost = value;
            }
        }

        public ServiceState State
        {
            get { return state; }
            set
            {
                state = value;
                switch (value)
                {
                    case ServiceState.Created:
                        IpAddress = IpAddress;
                        ServiceUri = ServiceUri;
                        buttonStartStopService.Text = "Start Service";
                        labelState.Text = "State: created.";
                        labelState.ForeColor = Color.Gray;
                        break;
                    case ServiceState.Starting:
                        textBoxIpAddress.Enabled = false;
                        checkBoxLocalhost.Enabled = false;
                        numericUpDownBufferLength.Enabled = false;
                        buttonStartStopService.Enabled = false;
                        labelState.Text = "State: starting...";
                        labelState.ForeColor = Color.Orange;
                        Hosting = true;
                        break;
                    case ServiceState.Started:
                        buttonStartStopService.Enabled = true;
                        buttonStartStopService.Text = "Stop Service";
                        labelState.Text = "State: started.";
                        labelState.ForeColor = Color.Green;
                        linkLabelCheckService.Enabled = true;
                        break;
                    case ServiceState.Stopping:
                        buttonStartStopService.Enabled = false;
                        labelState.Text = "State: stopping...";
                        labelState.ForeColor = Color.Orange;
                        linkLabelCheckService.Enabled = false;
                        Hosting = false;
                        break;
                    case ServiceState.Stopped:
                        textBoxIpAddress.Enabled = true;
                        IpAddress = IpAddress;
                        ServiceUri = ServiceUri;
                        numericUpDownBufferLength.Enabled = true;
                        buttonStartStopService.Enabled = true;
                        buttonStartStopService.Text = "Start Service";
                        labelState.Text = "State: stopped.";
                        labelState.ForeColor = Color.DarkRed;
                        linkLabelCheckService.Enabled = false;
                        buttonStartStopService.Focus();
                        break;
                    case ServiceState.Faulted:
                        textBoxIpAddress.Enabled = true;
                        IpAddress = IpAddress;
                        ServiceUri = ServiceUri;
                        numericUpDownBufferLength.Enabled = true;
                        buttonStartStopService.Enabled = true;
                        buttonStartStopService.Text = "Restart Service";
                        labelState.Text = "State: faulted.";
                        labelState.ForeColor = Color.Red;
                        linkLabelCheckService.Enabled = false;
                        buttonStartStopService.Focus();
                        break;
                }
            }
        }

        #endregion

        #region Constructors

        public FormMain()
        {
            InitializeComponent();
            CheckForIllegalCrossThreadCalls = false;

            policiesManager = new PoliciesManager(IpAddress);

            IpAddress = localhostIpAddress;
            BufferLength = 1048576;
            AlwaysOnTop = true;
            State = ServiceState.Created;

            policiesManager.ConnectPort(port);
        }

        #endregion

        #region Private Methods

        private void InitializeServiceHost()
        {
            streamingServiceHost = new ServiceHost(new StreamingService(bufferLength), new Uri(ServiceUri));

            ServiceMetadataBehavior serviceMetadataBehavior = streamingServiceHost.Description.Behaviors.Find<ServiceMetadataBehavior>();
            if (serviceMetadataBehavior == null)
            {
                serviceMetadataBehavior = new ServiceMetadataBehavior();
                serviceMetadataBehavior.HttpGetEnabled = true;
                streamingServiceHost.Description.Behaviors.Add(serviceMetadataBehavior);
            }
            else
                serviceMetadataBehavior.HttpGetEnabled = true;

            ServiceDebugBehavior serviceDebugBehavior = streamingServiceHost.Description.Behaviors.Find<ServiceDebugBehavior>();
            if (serviceDebugBehavior == null)
            {
                serviceDebugBehavior = new ServiceDebugBehavior();
                serviceDebugBehavior.IncludeExceptionDetailInFaults = true;
                streamingServiceHost.Description.Behaviors.Add(serviceDebugBehavior);
            }
            else
                serviceDebugBehavior.IncludeExceptionDetailInFaults = true;

            BasicHttpBinding binding = new BasicHttpBinding();
            binding.BypassProxyOnLocal = true;
            binding.MaxReceivedMessageSize = maxReceivedMessageSize;
            binding.OpenTimeout = TimeSpan.FromMinutes(5);
            binding.CloseTimeout = TimeSpan.FromMinutes(5);
            binding.ReceiveTimeout = TimeSpan.FromMinutes(30);
            binding.SendTimeout = TimeSpan.FromMinutes(30);
            binding.ReaderQuotas.MaxArrayLength = maxArrayLength;
            binding.TransferMode = TransferMode.Streamed;
            streamingServiceHost.AddServiceEndpoint(typeof(IStreamingService), binding, "");
        }

        private void StreamingServiceHostProcess(object state)
        {
            try
            {
                InitializeServiceHost();
                streamingServiceHost.Open();

                diagnostics = (streamingServiceHost.SingletonInstance as StreamingService).GetDiagnostics();
                diagnostics.DiagnosticsUpdated += new EventHandler(DiagnosticsUpdated);
                ResetDiagnostics();
                State = ServiceState.Started;
            }
            catch (Exception)
            {
                State = ServiceState.Faulted;
                Hosting = false;
            }
        }

        private void ResetDiagnostics()
        {
            labelBufferPosition.Text = "Buffer position: 0 / 0";
            progressBarBufferPosition.Value = 0;
            labelLastReadPosition.Text = "Last read position: 0 / 0";
            progressBarLastReadPosition.Value = 0;
            if (diagnostics != null)
            {
                labelBufferPosition.Text = "Buffer position: 0 / " + diagnostics.BufferPosition.ToString();
                labelLastReadPosition.Text = "Last read position: 0 / " + diagnostics.LastReadPosition.ToString();
                DiagnosticsUpdated(this, EventArgs.Empty);
            }
        }

        #endregion

        #region Event Handlers

        private void DiagnosticsUpdated(object sender, EventArgs e)
        {
            labelBufferPosition.Text = "Buffer position: " + diagnostics.BufferPosition.ToString() + " / " + BufferLength;
            progressBarBufferPosition.Value = diagnostics.BufferPosition;
            labelLastReadPosition.Text = "Last read position: " + diagnostics.LastReadPosition.ToString() + " / " + BufferLength;
            progressBarLastReadPosition.Value = diagnostics.LastReadPosition;
        }

        private void FormMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            State = ServiceState.Stopping;
            policiesManager.Reset();
        }

        private void textBoxIpAddress_Leave(object sender, EventArgs e)
        {
            IpAddress = textBoxIpAddress.Text;
        }

        private void checkBoxLocalhost_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxLocalhost.Checked)
                IpAddress = localhostIpAddress;
        }

        private void numericUpDownBufferLength_ValueChanged(object sender, EventArgs e)
        {
            BufferLength = (int)numericUpDownBufferLength.Value;
        }

        private void buttonStartStopService_Click(object sender, EventArgs e)
        {
            switch (State)
            {
                case ServiceState.Created:
                case ServiceState.Stopped:
                case ServiceState.Faulted:
                    State = ServiceState.Starting;
                    break;
                case ServiceState.Started:
                    State = ServiceState.Stopping;
                    break;
            }
        }

        private void linkLabelCheckService_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start(ServiceUri);
        }

        private void checkBoxAlwaysOnTop_CheckedChanged(object sender, EventArgs e)
        {
            AlwaysOnTop = checkBoxAlwaysOnTop.Checked;
        }

        #endregion
    }
}