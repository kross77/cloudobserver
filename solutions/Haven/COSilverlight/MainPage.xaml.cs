using System.Windows;
using System.Windows.Controls;
using System.IO.IsolatedStorage;
using System.IO;

namespace COSilverlight
{
	public partial class MainPage : UserControl
	{
		private const string FILENAME = "localName.txt";

        private IsolatedStorageFileStream isfs;
        //private bool isShiftDown = false;
		// begin=)
		public MainPage()
		{
			InitializeComponent();
			border.Visibility = invisiable.Visibility; // hide cameras list
			loadLocalStorage(); // try to load data from local Storage
		}

      //ACTIONS
		private void playBut(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            play();
        }
		
        private void KeyUP(object sender, System.Windows.Input.KeyEventArgs e)
        {
        	if(e.Key.ToString() == "Enter")
			{
				play();
			}
        }
		//LOGIK
        void play()
        {
            saveLocalStorage(UserName.Text); //save Text input "Name" data to local Storage
            border.Visibility = image.Visibility; //SHOW ITEMS LIST
            Canvas.Visibility = invisiable.Visibility; //HIDE "NAME" INPUT
        }
        // update data to local storage
        void saveLocalStorage(string value)
        {
            IsolatedStorageFile store = IsolatedStorageFile.GetUserStoreForApplication();
            if(store.FileExists(FILENAME))
                isfs = new IsolatedStorageFileStream(FILENAME, FileMode.Truncate, store);
            else
                isfs = new IsolatedStorageFileStream(FILENAME, FileMode.OpenOrCreate, store);

            StreamWriter streamWriter = new StreamWriter(isfs);
            streamWriter.Write(value);
            streamWriter.Flush();
            streamWriter.Close();
            isfs = null;
        }

        // load date from local storage
        void loadLocalStorage()
        {
            IsolatedStorageFile store = IsolatedStorageFile.GetUserStoreForApplication();

            if(store.FileExists(FILENAME)){
                isfs = new IsolatedStorageFileStream(FILENAME, FileMode.OpenOrCreate, store);
                StreamReader streamReader = new StreamReader(isfs);
                string s;
                while ((s = streamReader.ReadLine()) != null)
                    UserName.Text = (s);
				
                streamReader.Close();
            }
        }

	
	}
}