using CloudObserver.Kernel.Services;
using System;
using System.Diagnostics;
using System.ServiceModel;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Animation;

namespace CloudObserver.Gui
{
    public partial class WindowMain : Window
    {
        /// <summary>
        /// A filename of the Cloud Observer Service Host application.
        /// </summary>
        private const string resourcesManagerProcessFileName = "coresmgr.exe";

        /// <summary>
        /// The number of milliseconds for a service to start.
        /// </summary>
        private const int serviceStartTimeout = 2000;

        /// <summary>
        /// The number of milliseconds for a panel to collapse or expand.
        /// </summary>
        private const int animationTime = 200;

        /// <summary>
        /// Currently expanded panel.
        /// </summary>
        private Panel expandedPanel = null;

        public WindowMain()
        {
            InitializeComponent();;
        }

        /// <summary>
        /// Expands the given panel, collapsing the previously expanded one. Collapses the panel, if it is already expanded.
        /// </summary>
        /// <param name="panel">A panel to expand.</param>
        /// <remarks>It is possible to expand any control, derived from the Panel class.</remarks>
        private void ExpandPanel(Panel panel)
        {
            // Create storyboard to animate the process.
            Storyboard storyboard = new Storyboard();

            // Collapse the previously expanded panel, if any.
            if (expandedPanel != null)
            {
                DoubleAnimation collapseAnimation = new DoubleAnimation(expandedPanel.Height, 0, TimeSpan.FromMilliseconds(animationTime));
                Storyboard.SetTarget(collapseAnimation, expandedPanel);
                Storyboard.SetTargetProperty(collapseAnimation, new PropertyPath(Panel.HeightProperty));
                storyboard.Children.Add(collapseAnimation);
            }

            // Expand given panel if necessary.
            if (panel != expandedPanel)
            {
                DoubleAnimation expandAnimation = new DoubleAnimation(panel.Height, panel.ActualHeight, TimeSpan.FromMilliseconds(animationTime));
                Storyboard.SetTarget(expandAnimation, panel);
                Storyboard.SetTargetProperty(expandAnimation, new PropertyPath(Panel.HeightProperty));
                storyboard.Children.Add(expandAnimation);
                expandedPanel = panel;
            }
            else
                expandedPanel = null;

            // Play the animation.
            storyboard.Begin();
        }

        private void LinkLabelNewInstance_Click(object sender, RoutedEventArgs e)
        {
            // Expand the new instance panel.
            ExpandPanel(stackPanelNewInstance);
        }

        private void ButtonNewInstanceLaunch_Click(object sender, RoutedEventArgs e)
        {
            // Disable the new instance button.
            buttonNewInstanceLaunch.IsEnabled = false;

            // Display License Agreement window.
            if (new WindowLicenseAgreement().ShowDialog() == false)
            {
                buttonNewInstanceLaunch.IsEnabled = true;
                return;
            }

            // Start the new instance launch process.
            new WindowLaunch(textBoxPublicIpAddress.Text).ShowDialog();

            // Collapse the new instance panel.
            ExpandPanel(stackPanelNewInstance);

            // Enable the new instance button.
            buttonNewInstanceLaunch.IsEnabled = true;
        }

        private void LinkLabelConnect_Click(object sender, RoutedEventArgs e)
        {
            ExpandPanel(stackPanelConnect);
        }

        private void ButtonConnect_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                ProcessStartInfo serviceHostProcessStartInfo = new ProcessStartInfo();
                serviceHostProcessStartInfo.FileName = resourcesManagerProcessFileName;
                serviceHostProcessStartInfo.Arguments = textBoxPublicIpAddress.Text;
                serviceHostProcessStartInfo.WindowStyle = ProcessWindowStyle.Hidden;
                Process serviceHostProcess = new Process();
                serviceHostProcess.StartInfo = serviceHostProcessStartInfo;
                serviceHostProcess.Start();
            }
            catch (Exception)
            {
            }

            using (ChannelFactory<IResourcesManager> channelFactory = new ChannelFactory<IResourcesManager>(new BasicHttpBinding(), "http://" + textBoxPublicIpAddress.Text + ":4773/rm"))
            {
                IResourcesManager resourceManager = channelFactory.CreateChannel();
                try
                {
                    resourceManager.SupportCloudObserver(textBoxControllerAddressToConnect.Text);
                    MessageBox.Show("The machine was successfully connected to an existing Cloud Observer infrastructure at " + textBoxControllerAddressToConnect.Text + ".", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
                }
                catch (Exception)
                {
                    MessageBox.Show("Failed to connect this machine to an existing Cloud Observer infrastructure at " + textBoxControllerAddressToConnect.Text + ".", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
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
        }

        private void LinkLabelExistingConnections_Click(object sender, RoutedEventArgs e)
        {
            // Expand the existing connections panel.
            ExpandPanel(stackPanelExistingConnections);
        }

        private void LinkLabelTerminateServices_Click(object sender, RoutedEventArgs e)
        {
            ProcessStartInfo cmdProcessStartInfo1 = new ProcessStartInfo("cmd", @"/c ""taskkill /im cosvchst.exe""");
            cmdProcessStartInfo1.WindowStyle = ProcessWindowStyle.Hidden;
            Process.Start(cmdProcessStartInfo1);

            ProcessStartInfo cmdProcessStartInfo2 = new ProcessStartInfo("cmd", @"/c ""taskkill /im coresmgr.exe""");
            cmdProcessStartInfo2.WindowStyle = ProcessWindowStyle.Hidden;
            Process.Start(cmdProcessStartInfo2);

            MessageBox.Show("All running Cloud Observer system services have been terminated.", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
        }

        private void LinkLabelClose_Click(object sender, RoutedEventArgs e)
        {
            // Close the window and the application.
            Close();
        }
    }
}
