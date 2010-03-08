using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Animation;

namespace CloudObserver.Gui
{
    public partial class WindowMain : Window
    {
        /// <summary>
        /// The number of milliseconds for a panel to collapse or expand.
        /// </summary>
        private const int animationTime = 200;

        /// <summary>
        /// Cloud Observer system instance default name.
        /// </summary>
        private const string defaultInstanceName = "Cloud Observer";

        /// <summary>
        /// Cloud Observer system instance default gateway address.
        /// </summary>
        private const string defaultInstanceGatewayAddress = "http://localhost:4773/cloudobserver";

        /// <summary>
        /// The number of instances created.
        /// </summary>
        private int instancesCount = 0;

        /// <summary>
        /// Currently expanded panel.
        /// </summary>
        private Panel expandedPanel = null;

        public WindowMain()
        {
            InitializeComponent();

            // Set instance default values.
            SetInstanceDefaultValues();
        }

        /// <summary>
        /// Sets instance default values.
        /// </summary>
        private void SetInstanceDefaultValues()
        {
            textBoxNewInstanceName.Text = defaultInstanceName;
            textBoxNewInstanceGatewayAddress.Text = defaultInstanceGatewayAddress;
            if (instancesCount > 0)
            {
                textBoxNewInstanceName.Text += " " + instancesCount.ToString();
                textBoxNewInstanceGatewayAddress.Text += instancesCount.ToString();
            }
            instancesCount++;
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

            // Try to get a new instance gateway uri.
            Uri instanceUri = null;
            try
            {
                instanceUri = new Uri(textBoxNewInstanceGatewayAddress.Text);
            }
            catch (UriFormatException)
            {
                MessageBox.Show("Invalid gateway address. Please, enter a correct http address.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                buttonNewInstanceLaunch.IsEnabled = true;
                return;
            }

            // Display License Agreement window.
            if (new WindowLicenseAgreement().ShowDialog() == false)
            {
                buttonNewInstanceLaunch.IsEnabled = true;
                return;
            }

            // Start the new instance launch process.
            new WindowLaunch(textBoxNewInstanceName.Text, instanceUri).ShowDialog();

            // Collapse the new instance panel.
            ExpandPanel(stackPanelNewInstance);

            // Set instance default values.
            SetInstanceDefaultValues();

            // Enable the new instance button.
            buttonNewInstanceLaunch.IsEnabled = true;
        }

        private void LinkLabelExistingConnections_Click(object sender, RoutedEventArgs e)
        {
            // Expand the existing connections panel.
            ExpandPanel(stackPanelExistingConnections);
        }

        private void LinkLabelTerminateServices_Click(object sender, RoutedEventArgs e)
        {
            ProcessStartInfo cmdProcessStartInfo = new ProcessStartInfo("cmd", @"/c ""taskkill /im csvchost.exe""");
            cmdProcessStartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            Process.Start(cmdProcessStartInfo);
            MessageBox.Show("All running Cloud Observer system services have been terminated.", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
        }

        private void LinkLabelClose_Click(object sender, RoutedEventArgs e)
        {
            // Close the window and the application.
            Close();
        }
    }
}