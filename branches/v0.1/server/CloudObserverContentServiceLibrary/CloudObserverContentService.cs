using System;
using System.ServiceModel;
using CloudObserverDatabaseLibrary;
using CloudObserverStorageServiceLibrary;
using CloudObserverBroadcastServiceLibrary;

namespace CloudObserverContentServiceLibrary
{
    public class CloudObserverContentService : ICloudObserverContentService
    {
        private CloudObserverDatabase database = null;
        private ICloudObserverStorageService client;
        private ICloudObserverBroadcastService broadcastClient;

        public CloudObserverContentService()
        {
            database = new CloudObserverDatabase();
            client = new ChannelFactory<ICloudObserverStorageService>(new BasicHttpBinding(), "http://localhost:9000/CloudObserverStorageService").CreateChannel();
            broadcastClient = new ChannelFactory<ICloudObserverBroadcastService>(new BasicHttpBinding(), "http://localhost:9000/CloudObserverBroadcastService").CreateChannel();
        }

        public string Echo(string input)
        {
            return input;
        }

        public void LoadTranslation(DateTime start, DateTime stop, int frequency, int fromCamera, int toCamera)
        {
            int[] indexes = database.getFrameIndexesArray(start, stop);
            for (int i = 0; i < indexes.Length; i++)
            {
                string strTime = database.FrameGetMarker(indexes[i]);
                DateTime time = new DateTime();
                try
                {
                    time = DateTime.Parse(strTime);
                }
                catch (System.ArgumentNullException)
                { ; }
                catch (System.FormatException)
                { ; }   
                byte[] frame = client.GetFromStorage(fromCamera.ToString() + @"\" + time.Year.ToString() + "-" + time.Month.ToString() + "-" + time.Day.ToString() + "-" + time.Hour.ToString() + "-" + time.Minute.ToString() + "-" + time.Second.ToString() + "-" + time.Millisecond.ToString() + ".img");
                broadcastClient.WriteFrame(toCamera, frame, time, false);
                if (i + 1 < indexes.Length)
                {
                    string strTimenext = database.FrameGetMarker(indexes[i]);
                    DateTime timenext = DateTime.Parse(strTime);
                    System.Threading.Thread.Sleep((int)(1000/frequency));
                    //timenext.Millisecond + timenext.Second * 1000 + timenext.Minute * 60000 + timenext.Hour * 3600000 - (time.Millisecond + time.Second * 1000 + time.Minute * 60000 + time.Hour * 3600000)
                }
            }
        }
    }
}