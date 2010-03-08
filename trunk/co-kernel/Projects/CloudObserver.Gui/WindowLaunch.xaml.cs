using System;
using System.Threading;
using System.Diagnostics;
using System.ComponentModel;
using System.ServiceModel;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Animation;

using CloudObserver.Services;
using CloudObserver.Gui.Controls;

namespace CloudObserver.Gui
{
    public partial class WindowLaunch : Window
    {
        /// <summary>
        /// A filename of the Cloud Observer Service Host application.
        /// </summary>
        private const string serviceHostProcessFileName = "csvchost.exe";

        /// <summary>
        /// The number of milliseconds for a service to start.
        /// </summary>
        private const int serviceStartTimeout = 2000;

        /// <summary>
        /// The instance name.
        /// </summary>
        private string instanceName;
        
        /// <summary>
        /// The instance gateway address.
        /// </summary>
        private string instanceGatewayAddress;

        private OperationStage operationStage1 = null;
        private OperationStage operationStage2 = null;
        private OperationStage operationStage3 = null;
        private OperationStage operationStage4 = null;
        private OperationStage operationStage5 = null;
        private OperationStage operationStage6 = null;

        private OperationResult operationResult = null;

        private const int GWL_STYLE = -16;
        private const int WS_SYSMENU = 0x80000;
        [DllImport("user32.dll", SetLastError = true)]
        private static extern int GetWindowLong(IntPtr hWnd, int nIndex);
        [DllImport("user32.dll")]
        private static extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);

        public WindowLaunch(string instanceName, Uri instanceGatewayUri)
        {
            InitializeComponent();
            InitializeOperations();

            this.instanceName = instanceName;
            this.instanceGatewayAddress = instanceGatewayUri.ToString();
        }

        private void InitializeOperations()
        {
            operationStage1 = new OperationStage("Preparing the launch configuration...");
            stackPanel.Children.Add(operationStage1);
            operationStage2 = new OperationStage("Launching the gateway service...");
            stackPanel.Children.Add(operationStage2);
            operationStage3 = new OperationStage("Checking the gateway service...");
            stackPanel.Children.Add(operationStage3);
            operationStage4 = new OperationStage("Launching the controller service...");
            stackPanel.Children.Add(operationStage4);
            operationStage5 = new OperationStage("Checking the controller service...");
            stackPanel.Children.Add(operationStage5);
            operationStage6 = new OperationStage("Finishing the launch...");
            stackPanel.Children.Add(operationStage6);

            operationResult = new OperationResult(new RoutedEventHandler(ButtonOK_Click));
            stackPanel.Children.Add(operationResult);
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            // Remove the window's icon and close button.
            IntPtr hwnd = new WindowInteropHelper(this).Handle;
            SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_SYSMENU);

            // Start the new instance of the system.
            new Thread(new ThreadStart(LaunchProcess)).Start();
        }

        /// <summary>
        /// Starts a new instance of the system.
        /// </summary>
        private void LaunchProcess()
        {
            // Stage 1: Prepare the launch configuration.
            operationStage1.Start();
            string gatewayServiceAddress = instanceGatewayAddress;
            string controllerServiceAddress = instanceGatewayAddress + @"\cc-0";
            operationStage1.Succeed();

            // Stage 2: Launch the gateway service.
            operationStage2.Start();
            ProcessStartInfo gatewayServiceHostProcessStartInfo = new ProcessStartInfo();
            gatewayServiceHostProcessStartInfo.FileName = serviceHostProcessFileName;
            gatewayServiceHostProcessStartInfo.Arguments = gatewayServiceAddress + " GW";
            gatewayServiceHostProcessStartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            Process gatewayServiceHostProcess = new Process();
            gatewayServiceHostProcess.StartInfo = gatewayServiceHostProcessStartInfo;
            gatewayServiceHostProcess.Start();
            Thread.Sleep(serviceStartTimeout);
            if (gatewayServiceHostProcess.HasExited)
            {
                operationStage2.Failed();
                LaunchFailed();
                return;
            }
            operationStage2.Succeed();

            // Stage 3: Check the gateway service.
            operationStage3.Start();
            using (ChannelFactory<IGateway> channelFactory = new ChannelFactory<IGateway>(new BasicHttpBinding(), gatewayServiceAddress))
            {
                IGateway gateway = channelFactory.CreateChannel();
                try
                {
                    gateway.Test();
                }
                catch (Exception)
                {
                    operationStage3.Failed();
                    LaunchFailed();
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
            operationStage3.Succeed();

            // Stage 4: Launch the controller service.
            operationStage4.Start();
            ProcessStartInfo controllerServiceHostProcessStartInfo = new ProcessStartInfo();
            controllerServiceHostProcessStartInfo.FileName = serviceHostProcessFileName;
            controllerServiceHostProcessStartInfo.Arguments = controllerServiceAddress + " CC";
            controllerServiceHostProcessStartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            Process controllerServiceHostProcess = new Process();
            controllerServiceHostProcess.StartInfo = controllerServiceHostProcessStartInfo;
            controllerServiceHostProcess.Start();
            Thread.Sleep(serviceStartTimeout);
            if (controllerServiceHostProcess.HasExited)
            {
                operationStage4.Failed();
                LaunchFailed();
                return;
            }
            operationStage4.Succeed();

            // Stage 5: Check the controller service.
            operationStage5.Start();
            using (ChannelFactory<ICloudController> channelFactory = new ChannelFactory<ICloudController>(new BasicHttpBinding(), controllerServiceAddress))
            {
                ICloudController controller = channelFactory.CreateChannel();
                try
                {
                    controller.Test();
                }
                catch (Exception)
                {
                    operationStage5.Failed();
                    LaunchFailed();
                    return;
                }
                finally
                {
                    try
                    {
                        ((IClientChannel)controller).Close();
                    }
                    catch (Exception)
                    {
                        ((IClientChannel)controller).Abort();
                    }
                }
            }
            operationStage5.Succeed();

            // Stage 6: Finish the launch.
            operationStage6.Start();
            operationStage6.Succeed();

            LaunchSucceed();
        }

        private void LaunchSucceed()
        {
            operationResult.ShowResult("System launch succeed.");
        }

        private void LaunchFailed()
        {
            operationResult.ShowResult("System launch failed.");
        }

        private void ButtonOK_Click(object sender, RoutedEventArgs e)
        {
            // Close the window.
            Close();
        }
    }
}