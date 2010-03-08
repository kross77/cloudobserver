using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;

namespace CloudObserver.Gui
{
    public partial class WindowLicenseAgreement : Window
    {
        public WindowLicenseAgreement()
        {
            InitializeComponent();
        }

        private void ButtonPrint_Click(object sender, RoutedEventArgs e)
        {
            PrintDialog printDialog = new PrintDialog();
            if (printDialog.ShowDialog() == true)
            {
                FlowDocument flowDocument = new FlowDocument(new Paragraph(new Run(textBoxLicenseAgreement.Text)));
                flowDocument.PagePadding = new Thickness(100);
                printDialog.PrintDocument((flowDocument as IDocumentPaginatorSource).DocumentPaginator, "Cloud Observer License Agreement");
            }
        }

        private void ButtonAccept_Click(object sender, RoutedEventArgs e)
        {
            DialogResult = true;
        }
    }
}