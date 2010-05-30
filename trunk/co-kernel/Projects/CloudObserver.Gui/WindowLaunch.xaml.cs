using CloudObserver.Kernel.Services;
using CloudObserver.Gui.Controls;
using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.ServiceModel;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Animation;

namespace CloudObserver.Gui
{
    public partial class WindowLaunch : Window
    {
        /// <summary>
        /// A filename of the Cloud Observer Service Host application.
        /// </summary>
        private const string resourcesManagerProcessFileName = "coresmgr.exe";

        /// <summary>
        /// The number of milliseconds for a service to start.
        /// </summary>
        private const int serviceStartTimeout = 2000;

        private string resourceManagerIp;
        private string resourceManagerAddress;

        private OperationStage operationStage1 = null;
        private OperationStage operationStage2 = null;
        private OperationStage operationStage3 = null;

        private OperationResult operationResult = null;

        private const int GWL_STYLE = -16;
        private const int WS_SYSMENU = 0x80000;
        [DllImport("user32.dll", SetLastError = true)]
        private static extern int GetWindowLong(IntPtr hWnd, int nIndex);
        [DllImport("user32.dll")]
        private static extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);

        public WindowLaunch(string publicIpAddress)
        {
            InitializeComponent();
            InitializeOperations();

            resourceManagerIp = publicIpAddress;
            resourceManagerAddress = "http://" + publicIpAddress + ":4773/rm";
        }

        private void InitializeOperations()
        {
            operationStage1 = new OperationStage("Preparing the launch configuration...");
            stackPanel.Children.Add(operationStage1);
            operationStage2 = new OperationStage("Launching the instance...");
            stackPanel.Children.Add(operationStage2);
            operationStage3 = new OperationStage("Finishing the launch...");
            stackPanel.Children.Add(operationStage3);

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
            try
            {
                ProcessStartInfo serviceHostProcessStartInfo = new ProcessStartInfo();
                serviceHostProcessStartInfo.FileName = resourcesManagerProcessFileName;
                serviceHostProcessStartInfo.Arguments = resourceManagerIp;
                serviceHostProcessStartInfo.WindowStyle = ProcessWindowStyle.Hidden;
                Process serviceHostProcess = new Process();
                serviceHostProcess.StartInfo = serviceHostProcessStartInfo;
                serviceHostProcess.Start();
            }
            catch (Exception)
            {
            }
            operationStage1.Succeed();

            // Stage 2: Launch the gateway service.
            operationStage2.Start();
            using (ChannelFactory<IResourcesManager> channelFactory = new ChannelFactory<IResourcesManager>(new BasicHttpBinding(), resourceManagerAddress))
            {
                IResourcesManager resourceManager = channelFactory.CreateChannel();
                try
                {
                    resourceManager.StartCloudObserver();
                    Thread.Sleep(5000);
                    operationStage2.Succeed();
                }
                catch (Exception)
                {
                    operationStage2.Failed();
                }
                finally
                {
                    try
                    {
                        ((IClientChannel)resourceManager).Close();
                    }
                    catch (Exception)
                    {
                        ((IClientChannel)resourceManager).Abort();
                    }
                }
            }

            // Stage 3: Finish the launch.
            operationStage3.Start();
            operationStage3.Succeed();

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
