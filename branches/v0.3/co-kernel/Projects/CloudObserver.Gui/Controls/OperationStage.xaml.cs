using System;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Animation;

namespace CloudObserver.Gui.Controls
{
    public partial class OperationStage : UserControl
    {
        /// <summary>
        /// The number of milliseconds for a panel to expand.
        /// </summary>
        private const int animationTime = 200;

        public OperationStage(string operation)
        {
            InitializeComponent();

            textBlock.Text = operation;
        }

        public void Start()
        {
            Dispatcher.Invoke(new ThreadStart(delegate { ExpandPanel(stackPanel); }));
        }

        public void Succeed()
        {
            Dispatcher.Invoke(new ThreadStart(delegate { spinningWait.OperationSucceed(); }));
        }

        public void Failed()
        {
            Dispatcher.Invoke(new ThreadStart(delegate { spinningWait.OperationFailed(); }));
        }

        /// <summary>
        /// Expands the given panel.
        /// </summary>
        /// <param name="panel">A panel to expand.</param>
        /// <remarks>It is possible to expand any control, derived from the Panel class.</remarks>
        private void ExpandPanel(Panel panel)
        {
            // Create storyboard to animate the process.
            Storyboard storyboard = new Storyboard();

            // Expand the given panel.
            DoubleAnimation expandAnimation = new DoubleAnimation(panel.Height, 16, TimeSpan.FromMilliseconds(animationTime));
            Storyboard.SetTarget(expandAnimation, panel);
            Storyboard.SetTargetProperty(expandAnimation, new PropertyPath(Panel.HeightProperty));
            storyboard.Children.Add(expandAnimation);

            // Play the animation.
            storyboard.Begin();
        }
    }
}