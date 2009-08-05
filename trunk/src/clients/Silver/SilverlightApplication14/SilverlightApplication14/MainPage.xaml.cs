using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;

namespace SilverlightApplication14
{
	public partial class MainPage : UserControl
	{
		public MainPage()
		{
			// Required to initialize variables
			InitializeComponent();
		}

		private void fun1(object sender, System.Windows.Input.MouseButtonEventArgs e)
		{
		tttt.Height = tttt.Height + 400; // TODO: Add event handler implementation here.
		tttt.Children.Add( new UserControl1());
		}
	}
}