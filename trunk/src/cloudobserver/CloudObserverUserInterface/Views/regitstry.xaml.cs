using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using System.Windows.Media.Imaging;
using System.ServiceModel;
using System.Runtime.Serialization;
using CloudObserverUserInterface.CloudObserverServiceReference;



namespace CloudObserverUserInterface.Views
{
    public partial class regitstry : ChildWindow
    {
        CloudObserverServiceReference.CloudObserverServiceClient clientProxy;
        bool curEmailRegistered = false;

        public regitstry()
        {
            clientProxy = new CloudObserverServiceReference.CloudObserverServiceClient();
            InitializeComponent();
        }

        private void RegistryButton_Click(object sender, RoutedEventArgs e)
        {
            if (System.Windows.Controls.PasswordBox.Equals(PasswordBox.Password, PasswordCheckBox.Password))
            {
                AnswerLabel.Content = "";
                
                clientProxy.IsEmailRegisteredCompleted += new EventHandler<System.ComponentModel.AsyncCompletedEventArgs>(IsEmailRegisteredCompletedHandler);
                clientProxy.IsEmailRegisteredAsync(LoginTextbox.Text);
 
            }
            else
            {
                AnswerLabel.Content = "Проверьте пароли";
            
            }
        }

        private void IsEmailRegisteredCompletedHandler(Object sender, System.ComponentModel.AsyncCompletedEventArgs e)
        { 
            
        }

        private void exitButton_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void SetImageButton_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog fileOpen = new OpenFileDialog();
            fileOpen.Filter = "PNG Files|*.png";
            fileOpen.ShowDialog();
            BitmapImage im = new BitmapImage();
            im.SetSource((fileOpen.File.OpenRead()));

            Image image = new Image();
            image.Source = im;
            image.Width = 91;//<Image Name="ShowImage" Height="60" Width="91" Canvas.Left="9" Canvas.Top="288"/>
            image.Height = 60;
            image.Stretch = Stretch.Fill;
            Canvas panel;
            panel = this.FindName("RegCanvas") as Canvas;
            panel.Children.Add(image);
            //Image. = new BitmapImage(new Uri(ofd.File.ToString(), UriKind.RelativeOrAbsolute));
        }
    }
}

