using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using CloudObserver.UserInterface.Views;
using CloudObserver.UserInterface.AuthenticationServiceReference;

namespace CloudObserver.UserInterface
{
	public partial class LoginControl : UserControl
	{
        private MessageWindow errorMessageWindow;
        private RegistrationWindow registrationWindow;
        private AuthenticationServiceContractClient authenticationServiceClient;

		public LoginControl()
		{
			InitializeComponent();

            authenticationServiceClient = new AuthenticationServiceContractClient();
            authenticationServiceClient.UserLoginCompleted += new EventHandler<UserLoginCompletedEventArgs>(client_UserLoginCompleted);
		}

        private void ButtonLogin_Click(object sender, RoutedEventArgs e)
        {
            authenticationServiceClient.UserLoginAsync(TextBoxEmail.Text, PasswordBoxPassword.Password);
        }

        private void ButtonRegister_Click(object sender, RoutedEventArgs e)
        {
            registrationWindow = new RegistrationWindow();
            registrationWindow.Show();
        }

        private void client_UserLoginCompleted(object sender, UserLoginCompletedEventArgs e)
        {
            if (e.Error != null)
            {
                if (errorMessageWindow == null)
                {
                    errorMessageWindow = new MessageWindow("Can't access authorization service.", "Error", new TimeSpan(0, 0, 2));
                    errorMessageWindow.Closed += new EventHandler(errorMessageWindow_Closed);
                    errorMessageWindow.Show();
                }
                return;
            }
            new MessageWindow(e.Result ? "Login succeed." : "Login failed. Invalid email or password.", "Login", new TimeSpan(0, 0, 0, 2)).Show();
        }

        private void errorMessageWindow_Closed(object sender, EventArgs e)
        {
            errorMessageWindow = null;
        }

        private void userCredentialsChanged(object sender, EventArgs e)
        {
            ButtonLogin.IsEnabled = ((TextBoxEmail.Text != "") && (PasswordBoxPassword.Password != ""));
        }
	}
}