using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;

namespace CloudObserverUserInterface
{
	public partial class CamerasViewer : UserControl
	{
		public CamerasViewer()
		{
			InitializeComponent();
		}

        private void ButtonAddCamera_Click(object sender, RoutedEventArgs e)
        {    
			  Conteiner.Height =  Conteiner.Height +200;
			 
			WrapPanelCameras.Width = Conteiner.Width;
			WrapPanelCameras.Height = Conteiner.Width;
            WrapPanelCameras.MinimizedColumnWidth = 300;
           // WrapPanelCameras.MaxWidth = Conteiner.Width;

			
            WrapPanelCameras.Items.Add(new CameraControl());
        }
	}
}