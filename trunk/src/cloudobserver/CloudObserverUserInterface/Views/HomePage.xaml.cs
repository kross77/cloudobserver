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
using CloudObserverUserInterface.CloudObserverServiceReference;

namespace CloudObserverUserInterface
{
    public partial class HomePage : Page
    {
        private CloudObserverServiceClient client;
        private RegistrationWindow registrationWindow;

        public HomePage()
        {
            InitializeComponent();

            client = new CloudObserverServiceClient();
            client.UserLoginCompleted += new EventHandler<UserLoginCompletedEventArgs>(client_UserLoginCompleted);
        }

        // Executes when the user navigates to this page.
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
        }

        private void ButtonLogin_Click(object sender, RoutedEventArgs e)
        {
            client.UserLoginAsync(TextBoxEmail.Text, PasswordBoxPassword.Password);
        }

        private void ButtonRegister_Click(object sender, RoutedEventArgs e)
        {
            registrationWindow = new RegistrationWindow();
            registrationWindow.Show();
        }

        private void client_UserLoginCompleted(object sender, UserLoginCompletedEventArgs e)
        {
            MessageBox.Show(e.Result ? "Login succeed." : "Invalid login or password.");
        }
    }
}