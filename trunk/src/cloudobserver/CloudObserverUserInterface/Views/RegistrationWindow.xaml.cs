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
using System.IO;
using System.ServiceModel;
using System.Runtime.Serialization;
using System.Windows.Threading;
using CloudObserverUserInterface.CloudObserverAuthorizationServiceReference;

namespace CloudObserverUserInterface.Views
{
    public partial class RegistrationWindow : ChildWindow
    {
        enum CorrectnessCheckElement { Email, Password };

        bool emailChecked = true;
        bool emailChecking = false;
        bool emailCorrect = false;
        bool passwordCorrect = false;
        byte[] icon;
        private MessageWindow errorMessageWindow;
        CloudObserverAuthorizationServiceClient authorizationServiceClient;

        public RegistrationWindow()
        {           
            InitializeComponent();

            authorizationServiceClient = new CloudObserverAuthorizationServiceClient();
            authorizationServiceClient.UserIsEmailAvailableCompleted += new EventHandler<UserIsEmailAvailableCompletedEventArgs>(client_UserIsEmailAvailableCompleted);
            authorizationServiceClient.UserAddCompleted += new EventHandler<UserAddCompletedEventArgs>(client_UserAddCompleted);

            DispatcherTimer emailChecker = new DispatcherTimer();
            emailChecker.Interval = new TimeSpan(0, 0, 0, 1, 0);
            emailChecker.Tick += new EventHandler(emailChecker_Tick);
            emailChecker.Start();
        }

        private void TextBoxEmail_TextChanged(object sender, TextChangedEventArgs e)
        {
            SetCorrectness(CorrectnessCheckElement.Email, false);
            if (TextBoxEmail.Text.Equals(""))
            {
                LabelEmailStatus.Content = "Empty email.";
                LabelEmailStatus.Foreground = new SolidColorBrush(Colors.Red);
            } else {
                LabelEmailStatus.Content = "Checking availability...";
                LabelEmailStatus.Foreground = new SolidColorBrush(Colors.Orange);
                emailChecked = false;
                emailChecking = false;
            }
        }

        private void PasswordBoxPassword_PasswordChanged(object sender, RoutedEventArgs e)
        {
            if (PasswordBoxPassword.Password.Equals(""))
            {
                LabelPasswordStatus.Content = "Empty password.";
                LabelPasswordStatus.Foreground = new SolidColorBrush(Colors.Red);
                SetCorrectness(CorrectnessCheckElement.Password, false);
            }
            else
            {
                if (PasswordBoxPassword.Password.Equals(PasswordBoxPasswordConfirmation.Password))
                {
                    LabelPasswordStatus.Content = "OK.";
                    LabelPasswordStatus.Foreground = new SolidColorBrush(Colors.Green);
                    SetCorrectness(CorrectnessCheckElement.Password, true);
                }
                else
                {
                    LabelPasswordStatus.Content = "Passwords do not match.";
                    LabelPasswordStatus.Foreground = new SolidColorBrush(Colors.Red);
                    SetCorrectness(CorrectnessCheckElement.Password, false);
                }
            }
        }

        private void TextBoxDescription_TextChanged(object sender, TextChangedEventArgs e)
        {
            LabelDescriptionStatus.Content = "Symbols left: " + (2048 - TextBoxDescription.Text.Length) + ".";
        }

        private void ButtonLoadIcon_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "PNG Files (*.png)|*.png";
            if (openFileDialog.ShowDialog().Equals(true))
            {
                FileStream fileStream = openFileDialog.File.OpenRead();
                icon = new BinaryReader(fileStream).ReadBytes((int)fileStream.Length);
                BitmapImage bitmapImage = new BitmapImage();
                bitmapImage.SetSource(fileStream);
                ImageIcon.Source = bitmapImage;
                fileStream.Close();
            }
        }

        private void ButtonRegister_Click(object sender, RoutedEventArgs e)
        {
            authorizationServiceClient.UserAddAsync(TextBoxEmail.Text, PasswordBoxPassword.Password, TextBoxName.Text, TextBoxDescription.Text, icon);
        }

        private void client_UserIsEmailAvailableCompleted(object sender, UserIsEmailAvailableCompletedEventArgs e)
        {
            if (e.Error != null)
            {
                LabelEmailStatus.Content = "Connection error.";
                LabelEmailStatus.Foreground = new SolidColorBrush(Colors.Red);
                if (errorMessageWindow == null)
                {
                    errorMessageWindow = new MessageWindow("Can't access authorization service.", "Error", new TimeSpan(0, 0, 2));
                    errorMessageWindow.Closed += new EventHandler(errorMessageWindow_Closed);
                    errorMessageWindow.Show();
                }
                return;
            }
            emailChecking = false;
            if (e.Result)
            {
                LabelEmailStatus.Content = "Email is available.";
                LabelEmailStatus.Foreground = new SolidColorBrush(Colors.Green);
                SetCorrectness(CorrectnessCheckElement.Email, true);
            }
            else
            {
                LabelEmailStatus.Content = "Email is already registered.";
                LabelEmailStatus.Foreground = new SolidColorBrush(Colors.Red);
                SetCorrectness(CorrectnessCheckElement.Email, false);
            }
            emailChecked = true;
        }

        private void client_UserAddCompleted(object sender, UserAddCompletedEventArgs e)
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
            new MessageWindow("Resigtration complete.", "Registration", new TimeSpan(0, 0, 0, 1)).Show();
            Close();
        }

        private void emailChecker_Tick(object sender, EventArgs e)
        {
            if (!emailChecked && !emailChecking)
            {
                authorizationServiceClient.UserIsEmailAvailableAsync(TextBoxEmail.Text);
                emailChecking = true;
            }
        }

        private void errorMessageWindow_Closed(object sender, EventArgs e)
        {
            errorMessageWindow = null;
        }

        private void SetCorrectness(CorrectnessCheckElement correctnessCheckElement, bool value)
        {
            switch (correctnessCheckElement)
            {
                case CorrectnessCheckElement.Email:
                    emailCorrect = value;
                    break;
                case CorrectnessCheckElement.Password:
                    passwordCorrect = value;
                    break;
            }
            ButtonRegister.IsEnabled = (emailCorrect & passwordCorrect);
        }
    }
}