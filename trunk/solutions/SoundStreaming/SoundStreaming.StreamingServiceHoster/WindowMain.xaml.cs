using System;
using System.Threading;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;

using CloudObserver.Policies;
using CloudObserver.Services;
using CloudObserver.Services.Bindings;
using CloudObserver.Services.StreamingService;

namespace SoundStreaming.StreamingServiceHoster
{
    public partial class WindowMain : Window
    {
        #region Fields
        private string ipAddress;
        private int port;
        private int bufferLength;
        private string serviceUri;
        private bool alwaysOnTop;
        private bool hosting;

        private PoliciesManager policiesManager;
        private DebugServiceHost streamingServiceHost;
        private StreamingServiceDiagnostics diagnostics;
        private Regex ipAddressRegex = new Regex(ipAddressRegexPattern);
        #endregion

        #region Constants
        private const string localhostIpAddress = "127.0.0.1";
        private const int defaultPort = 9000;
        private const int minPort = 1024;
        private const int maxPort = 65535;
        private const int minBufferLength = 2048;
        private const int maxBufferLength = 2147483647;
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

        public int BufferLength
        {
            get { return bufferLength; }
            set
            {
                if ((value >= minBufferLength) && (value <= maxBufferLength))
                {
                    bufferLength = value;
                    textBoxBufferLength.Text = value.ToString();
                    progressBarBufferPosition.Maximum = value;
                    progressBarLastReadPosition.Maximum = value;
                }
                else
                    BufferLength = bufferLength;
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
                checkBoxAlwaysOnTop.IsChecked = value;
                this.Topmost = value;
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
                    try
                    {
                        policiesManager = new PoliciesManager(IpAddress);
                        policiesManager.ConnectPort(port);
                        streamingServiceHost = new DebugServiceHost(typeof(IStreamingService),
                            new ClientHttpBinding(),
                            new StreamingService(bufferLength),
                            new Uri(ServiceUri));
                        diagnostics = (streamingServiceHost.SingletonInstance as StreamingService).GetDiagnostics();
                        diagnostics.DiagnosticsUpdated += new EventHandler(DiagnosticsUpdated);
                        streamingServiceHost.Opening += new EventHandler(ServiceHostOpening);
                        streamingServiceHost.Opened += new EventHandler(ServiceHostOpened);
                        streamingServiceHost.Closing += new EventHandler(ServiceHostClosing);
                        streamingServiceHost.Closed += new EventHandler(ServiceHostClosed);
                        streamingServiceHost.Faulted += new EventHandler(ServiceHostFaulted);
                        streamingServiceHost.Open();
                    }
                    catch (Exception)
                    {
                        Hosting = false;
                    }
                }
                else
                {
                    if (streamingServiceHost != null)
                    {
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
            BufferLength = 1048576;
            AlwaysOnTop = false;
            hosting = false;
        }
        #endregion

        #region Private Methods
        private void UpdateServiceUri()
        {
            ServiceUri = "http://" + ipAddress.ToString() + ":" + port.ToString() + "/StreamingService";
        }

        private void ResetDiagnostics()
        {
            textBlockBufferPosition.Text = "Buffer position: 0 / " + bufferLength;
            progressBarBufferPosition.Value = 0;
            textBlockLastReadPosition.Text = "Last read position: 0 / " + bufferLength;
            progressBarLastReadPosition.Value = 0;
        }
        #endregion

        #region Event Handlers
        private void DiagnosticsUpdated(object sender, EventArgs e)
        {
            textBlockBufferPosition.Text = "Buffer position: " + diagnostics.BufferPosition.ToString() + " / " + BufferLength;
            progressBarBufferPosition.Value = diagnostics.BufferPosition;
            textBlockLastReadPosition.Text = "Last read position: " + diagnostics.LastReadPosition.ToString() + " / " + BufferLength;
            progressBarLastReadPosition.Value = diagnostics.LastReadPosition;
        }

        void ServiceHostOpening(object sender, EventArgs e)
        {
            textBoxIpAddress.IsEnabled = false;
            checkBoxLocalhost.IsEnabled = false;
            textBoxPort.IsEnabled = false;
            textBoxBufferLength.IsEnabled = false;
            buttonStartStopService.IsEnabled = false;
            textBlockState.Text = "State: starting...";
            textBlockState.Foreground = Brushes.Orange;
        }

        void ServiceHostOpened(object sender, EventArgs e)
        {
            buttonStartStopService.IsEnabled = true;
            buttonStartStopService.Content = "Stop Service";
            textBlockState.Text = "State: started.";
            textBlockState.Foreground = Brushes.Green;
            textBlockCheckServiceLink.IsEnabled = true;
            textBlockCheckServiceLink.Foreground = Brushes.Blue;
        }

        void ServiceHostClosing(object sender, EventArgs e)
        {
            buttonStartStopService.IsEnabled = false;
            textBlockState.Text = "State: stopping...";
            textBlockState.Foreground = Brushes.Orange;
            textBlockCheckServiceLink.IsEnabled = false;
            textBlockCheckServiceLink.Foreground = Brushes.Gray;
        }

        void ServiceHostClosed(object sender, EventArgs e)
        {
            textBoxIpAddress.IsEnabled = true;
            IpAddress = IpAddress;
            textBoxPort.IsEnabled = true;
            textBoxBufferLength.IsEnabled = true;
            buttonStartStopService.IsEnabled = true;
            buttonStartStopService.Content = "Start Service";
            textBlockState.Text = "State: stopped.";
            textBlockState.Foreground = Brushes.DarkRed;
            textBlockCheckServiceLink.IsEnabled = false;
            textBlockCheckServiceLink.Foreground = Brushes.Gray;
            buttonStartStopService.Focus();
        }

        void ServiceHostFaulted(object sender, EventArgs e)
        {
            textBoxIpAddress.IsEnabled = true;
            IpAddress = IpAddress;
            textBoxPort.IsEnabled = true;
            textBoxBufferLength.IsEnabled = true;
            buttonStartStopService.IsEnabled = true;
            buttonStartStopService.Content = "Restart Service";
            textBlockState.Text = "State: faulted.";
            textBlockState.Foreground = Brushes.Red;
            textBlockCheckServiceLink.IsEnabled = false;
            textBlockCheckServiceLink.Foreground = Brushes.Gray;
            buttonStartStopService.Focus();
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

        private void textBoxBufferLength_LostKeyboardFocus(object sender, KeyboardFocusChangedEventArgs e)
        {
            int newBufferLength;
            BufferLength = (Int32.TryParse(textBoxBufferLength.Text, out newBufferLength)) ? newBufferLength : bufferLength;
        }

        private void buttonStartStopService_Click(object sender, RoutedEventArgs e)
        {
            Hosting = !Hosting;
        }

        private void textBlockCheckService_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            System.Diagnostics.Process.Start(ServiceUri);
        }

        private void checkBoxAlwaysOnTop_Checked(object sender, RoutedEventArgs e)
        {
            AlwaysOnTop = true;
        }

        private void checkBoxAlwaysOnTop_Unchecked(object sender, RoutedEventArgs e)
        {
            AlwaysOnTop = false;
        }
        #endregion
    }
}