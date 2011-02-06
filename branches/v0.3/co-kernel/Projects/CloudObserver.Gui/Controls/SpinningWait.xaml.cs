using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace CloudObserver.Gui.Controls
{
    /// <summary>
    /// A spinning wait control.
    /// </summary>
    public partial class SpinningWait : UserControl
    {
        private BitmapImage checkMarkImage = null;
        private BitmapImage crossMarkImage = null;

        public SpinningWait()
        {
            InitializeComponent();

            checkMarkImage = new BitmapImage(new Uri("../Assets/CheckMark.png", UriKind.Relative));
            crossMarkImage = new BitmapImage(new Uri("../Assets/CrossMark.png", UriKind.Relative));
        }

        /// <summary>
        /// Stops the spinner and shows a green check mark.
        /// </summary>
        public void OperationSucceed()
        {
            canvasSpinner.Visibility = Visibility.Collapsed;
            imageResult.Source = checkMarkImage;
        }

        /// <summary>
        /// Stops the spinner and shows a red cross mark.
        /// </summary>
        public void OperationFailed()
        {
            canvasSpinner.Visibility = Visibility.Collapsed;
            imageResult.Source = crossMarkImage;
        }
    }
}