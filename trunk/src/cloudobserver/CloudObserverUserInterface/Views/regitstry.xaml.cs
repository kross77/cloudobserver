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

namespace CloudObserverUserInterface.Views
{
    public partial class regitstry : ChildWindow
    {
        public regitstry()
        {
            InitializeComponent();
        }

        private void RegistryButton_Click(object sender, RoutedEventArgs e)
        {
            if (System.Windows.Controls.PasswordBox.Equals(PasswordBox.Password, PasswordCheckBox.Password))
            {
                AnswerLabel.Content = "";

 
            
            }
            else
            {
                AnswerLabel.Content = "Проверьте пароли";
            
            }
        }

        private void exitButton_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void SetImageButton_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "PNG Files|*.png";
            ofd.ShowDialog();
            ImageFileTextbox.Text = ofd.File.ToString();
            //Image. = new BitmapImage(new Uri(ofd.File.ToString(), UriKind.RelativeOrAbsolute));
        }
    }
}

