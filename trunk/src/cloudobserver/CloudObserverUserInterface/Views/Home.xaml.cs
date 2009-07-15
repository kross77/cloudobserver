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
using System.Windows.Navigation;
using System.Windows.Shapes;
using CloudObserverUserInterface.Views;

namespace CloudObserverUserInterface
{
    public partial class Home : Page
    {
        private regitstry RegistryWindow;

        public Home()
        {
            InitializeComponent();
            //создать подключение к сервису
        }

        // Executes when the user navigates to this page.
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
        }

        private void LoginButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void RegisterButton_Click(object sender, RoutedEventArgs e)
        {
            RegistryWindow = new regitstry();
            RegistryWindow.Title = "Регистрация";
            RegistryWindow.Show();
        }
    }
}