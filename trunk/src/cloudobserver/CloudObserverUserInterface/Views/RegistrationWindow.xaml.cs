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
using CloudObserverUserInterface.CloudObserverServiceReference;

namespace CloudObserverUserInterface.Views
{
    public partial class RegistrationWindow : ChildWindow
    {
        enum CorrectnessCheckElement { Email, Password };

        CloudObserverServiceClient client;
        bool emailChecked = true;
        bool emailChecking = false;
        bool emailCorrect = false;
        bool passwordCorrect = false;
        byte[] icon;

        public RegistrationWindow()
        {           
            InitializeComponent();

            client = new CloudObserverServiceClient();
            client.UserIsEmailAvailableCompleted += new EventHandler<UserIsEmailAvailableCompletedEventArgs>(client_UserIsEmailAvailableCompleted);
            client.UserAddCompleted += new EventHandler<UserAddCompletedEventArgs>(client_UserAddCompleted);

            DispatcherTimer emailChecker = new DispatcherTimer();
            emailChecker.Interval = new TimeSpan(0, 0, 0, 1, 0);
            emailChecker.Tick += new EventHandler(emailChecker_Tick);
            emailChecker.Start();

            icon = new byte[16384]; // 16384 max
            for (int i = 0; i < 16384; i++) icon[i] = 1;
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
                LabelEmailStatus.Foreground = new SolidColorBrush(Colors.Red);
                emailChecked = false;
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
                ButtonRegister.Content = (int)fileStream.Length;
                icon = new BinaryReader(fileStream).ReadBytes((int)fileStream.Length);
                BitmapImage bitmapImage = new BitmapImage();
                bitmapImage.SetSource(fileStream);
                ImageIcon.Source = bitmapImage;
                fileStream.Close();
            }
        }

        private void ButtonRegister_Click(object sender, RoutedEventArgs e)
        {
            client.UserAddAsync(TextBoxEmail.Text, PasswordBoxPassword.Password, TextBoxName.Text, TextBoxDescription.Text, icon);
        }

        private void client_UserIsEmailAvailableCompleted(object sender, UserIsEmailAvailableCompletedEventArgs e)
        {
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
            MessageBox.Show("Registration succeed. New user ID is " + e.Result + ".");
            Close();
        }

        private void emailChecker_Tick(object sender, EventArgs e)
        {
            if (!emailChecked && !emailChecking)
            {
                client.UserIsEmailAvailableAsync(TextBoxEmail.Text);
                emailChecking = true;
            }
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