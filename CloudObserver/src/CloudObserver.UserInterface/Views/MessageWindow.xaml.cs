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
using System.Windows.Threading;

namespace CloudObserver.UserInterface
{
    public partial class MessageWindow : ChildWindow
    {
        public MessageWindow(string message, string title, TimeSpan timeSpan)
        {
            InitializeComponent();

            LabelMessage.Content = message;
            this.Title = title;
            DispatcherTimer lifeTimeTimer = new DispatcherTimer();
            lifeTimeTimer.Interval = timeSpan;
            lifeTimeTimer.Tick += new EventHandler(lifeTimeTimer_Tick);
            lifeTimeTimer.Start();
        }

        void lifeTimeTimer_Tick(object sender, EventArgs e)
        {
            Close();
        }
    }
}