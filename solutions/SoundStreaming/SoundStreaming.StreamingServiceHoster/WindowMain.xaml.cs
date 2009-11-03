using System;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Description;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;

using CloudObserver.Policies;
using CloudObserver.Services;
using CloudObserver.Services.StreamingService;

namespace SoundStreaming.StreamingServiceHoster
{
    public partial class WindowMain : Window
    {
        #region Fields
        private string ipAddress;
        private int port;
        private string serviceUri;
        private bool hosting;
        private int subscribers;
        private Int64 dataTransferred;

        private PoliciesManager policiesManager;
        private ServiceHost streamingServiceHost;
        private Regex ipAddressRegex = new Regex(ipAddressRegexPattern);
        #endregion

        #region Constants
        private const string localhostIpAddress = "127.0.0.1";
        private const int defaultPort = 9000;
        private const int minPort = 1024;
        private const int maxPort = 65535;
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
                    checkBoxLocalhost.IsChecked = (value == localhostIpAddress);
                    checkBoxLocalhost.IsEnabled = (value != localhostIpAddress);
                    UpdateServiceUri();
                }
                else
                    IpAddress = ipAddress;
            }
        }

        public int Port
        {
            get { return port; }
            set
            {
                if ((value >= minPort) && (value <= maxPort))
                {
                    port = value;
                    textBoxPort.Text = value.ToString();
                    UpdateServiceUri();
                }
                else
                    Port = port;
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

        public bool Hosting
        {
            get { return hosting; }
            set
            {
                hosting = value;
                if (value)
                {
                    Thread thread = new Thread(new ThreadStart(HostStreamingService));
                    thread.IsBackground = true;
                    thread.Start();
                }
                else
                {
                    if (streamingServiceHost != null)
                    {
                        if (streamingServiceHost.State == CommunicationState.Opened)
                            streamingServiceHost.Close();
                        streamingServiceHost = null;
                    }
                    if (policiesManager != null)
                    {
                        policiesManager.Reset();
                        policiesManager = null;
                    }
                    ResetDiagnostics();
                }
            }
        }
        #endregion

        #region Constructors
        public WindowMain()
        {
            InitializeComponent();

            IpAddress = localhostIpAddress;
            Port = defaultPort;
            hosting = false;
            dataTransferred = 0;
        }
        #endregion

        #region Private Methods
        private void HostStreamingService()
        {
            try
            {
                policiesManager = new PoliciesManager(IpAddress);
                policiesManager.ConnectPort(port);
                StreamingService streamingService = new StreamingService();
                streamingService.DataTransfered += new EventHandler<DataTransferredEventArgs>(ServiceDataTransferredInvoke);
                streamingService.SubscribersChanged += new EventHandler<SubscribersChangedEventArgs>(ServiceSubscribersChangedInvoke);

                Uri httpAddress = new Uri("http://" + ipAddress.ToString() + ":" + port.ToString() + "/StreamingService");
                Uri netTcpAddress = new Uri("net.tcp://" + ipAddress.ToString() + ":9001/StreamingService");
                streamingServiceHost = new ServiceHost(streamingService, new Uri[] { httpAddress, netTcpAddress });
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

                ServiceThrottlingBehavior serviceThrottlingBehavior = new ServiceThrottlingBehavior()
                {
                    MaxConcurrentCalls = 500,
                    MaxConcurrentSessions = 500,
                    MaxConcurrentInstances = 500
                };
                streamingServiceHost.Description.Behaviors.Add(serviceThrottlingBehavior);

                streamingServiceHost.AddServiceEndpoint(typeof(IStreamingService), new ExternalPollingDuplexHttpBinding(), "");
                streamingServiceHost.AddServiceEndpoint(typeof(IStreamingService), new InternalNetTcpBinding(), "");
                streamingServiceHost.Opening += new EventHandler(ServiceHostOpeningInvoke);
                streamingServiceHost.Opened += new EventHandler(ServiceHostOpenedInvoke);
                streamingServiceHost.Closing += new EventHandler(ServiceHostClosingInvoke);
                streamingServiceHost.Closed += new EventHandler(ServiceHostClosedInvoke);
                streamingServiceHost.Faulted += new EventHandler(ServiceHostFaultedInvoke);
                streamingServiceHost.Open();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                Hosting = false;
            }
        }

        private void UpdateServiceUri()
        {
            ServiceUri = "http://" + ipAddress.ToString() + ":" + port.ToString() + "/StreamingService";
        }

        private void ResetDiagnostics()
        {
            textBlockDataTransferred.Text = "Data transferred: 0 B";
            textBlockSubscribers.Text = "Subscribers: 0";
        }
        #endregion

        #region Event Handlers

        private void ServiceDataTransferred()
        {
            double value = dataTransferred;
            value /= 1024;
            string suffix = "KB";
            if (value > 999)
            {
                value /= 1024;
                suffix = "MB";
            }
            if (value > 999)
            {
                value /= 1024;
                suffix = "GB";
            }
            textBlockDataTransferred.Text = "Data transferred: " + value.ToString("0.00") + " " + suffix + " (" + dataTransferred.ToString("0,0") + " B)";
        }

        private void ServiceDataTransferredInvoke(object sender, DataTransferredEventArgs e)
        {
            dataTransferred += e.DataLength;
            this.Dispatcher.Invoke(new ThreadStart(ServiceDataTransferred));
        }

        private void ServiceSubscribersChanged()
        {
            textBlockSubscribers.Text = "Subscribers: " + subscribers.ToString();
        }

        private void ServiceSubscribersChangedInvoke(object sender, SubscribersChangedEventArgs e)
        {
            subscribers = e.Subscribers;
            this.Dispatcher.Invoke(new ThreadStart(ServiceSubscribersChanged));
        }

        private void ServiceHostOpening()
        {
            textBoxIpAddress.IsEnabled = false;
            checkBoxLocalhost.IsEnabled = false;
            textBoxPort.IsEnabled = false;
            buttonStartStopService.IsEnabled = false;
            textBlockState.Text = "State: starting...";
            textBlockState.Foreground = Brushes.Orange;
        }

        private void ServiceHostOpeningInvoke(object sender, EventArgs e)
        {
            this.Dispatcher.Invoke(new ThreadStart(ServiceHostOpening));
        }

        private void ServiceHostOpened()
        {
            buttonStartStopService.IsEnabled = true;
            buttonStartStopService.Content = "Stop Service";
            textBlockState.Text = "State: started.";
            textBlockState.Foreground = Brushes.Green;
            textBlockCheckServiceLink.IsEnabled = true;
            textBlockCheckServiceLink.Foreground = Brushes.Blue;
        }

        private void ServiceHostOpenedInvoke(object sender, EventArgs e)
        {
            this.Dispatcher.Invoke(new ThreadStart(ServiceHostOpened));
        }

        private void ServiceHostClosing()
        {
            buttonStartStopService.IsEnabled = false;
            textBlockState.Text = "State: stopping...";
            textBlockState.Foreground = Brushes.Orange;
            textBlockCheckServiceLink.IsEnabled = false;
            textBlockCheckServiceLink.Foreground = Brushes.Gray;
        }

        private void ServiceHostClosingInvoke(object sender, EventArgs e)
        {
            this.Dispatcher.Invoke(new ThreadStart(ServiceHostClosing));
        }

        private void ServiceHostClosed()
        {
            textBoxIpAddress.IsEnabled = true;
            IpAddress = IpAddress;
            textBoxPort.IsEnabled = true;
            buttonStartStopService.IsEnabled = true;
            buttonStartStopService.Content = "Start Service";
            textBlockState.Text = "State: stopped.";
            textBlockState.Foreground = Brushes.DarkRed;
            textBlockCheckServiceLink.IsEnabled = false;
            textBlockCheckServiceLink.Foreground = Brushes.Gray;
            buttonStartStopService.Focus();
        }

        private void ServiceHostClosedInvoke(object sender, EventArgs e)
        {
            this.Dispatcher.Invoke(new ThreadStart(ServiceHostClosed));
        }

        private void ServiceHostFaulted()
        {
            textBoxIpAddress.IsEnabled = true;
            IpAddress = IpAddress;
            textBoxPort.IsEnabled = true;
            buttonStartStopService.IsEnabled = true;
            buttonStartStopService.Content = "Start Service";
            textBlockState.Text = "State: faulted.";
            textBlockState.Foreground = Brushes.Red;
            textBlockCheckServiceLink.IsEnabled = false;
            textBlockCheckServiceLink.Foreground = Brushes.Gray;
            buttonStartStopService.Focus();
        }

        private void ServiceHostFaultedInvoke(object sender, EventArgs e)
        {
            this.Dispatcher.Invoke(new ThreadStart(ServiceHostFaulted));
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            Hosting = false;
        }

        private void textBoxIpAddress_LostKeyboardFocus(object sender, KeyboardFocusChangedEventArgs e)
        {
            IpAddress = textBoxIpAddress.Text;
        }

        private void checkBoxLocalhost_Checked(object sender, RoutedEventArgs e)
        {
            IpAddress = localhostIpAddress;
        }

        private void textBoxPort_LostKeyboardFocus(object sender, KeyboardFocusChangedEventArgs e)
        {
            int newPort;
            Port = (Int32.TryParse(textBoxPort.Text, out newPort)) ? newPort : port;
        }

        private void buttonStartStopService_Click(object sender, RoutedEventArgs e)
        {
            Hosting = !Hosting;
        }

        private void textBlockCheckService_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            System.Diagnostics.Process.Start(ServiceUri);
        }
        #endregion
    }
}