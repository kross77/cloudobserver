using System;
using System.IO;
using System.Collections.Generic;
using System.ServiceModel;
using CloudObserverStorageServiceLibrary;
using CloudObserverDatabaseLibrary;

namespace CloudObserverBroadcastServiceLibrary
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class CloudObserverBroadcastService : ICloudObserverBroadcastService
    {
        Dictionary<int, byte[]> frames;
        private ICloudObserverStorageService client;
        private CloudObserverDatabase database = null;

        public CloudObserverBroadcastService()
        {
            frames = new Dictionary<int, byte[]>();
            database = new CloudObserverDatabase();
        }

        public byte[] ReadFrame(int cameraID)
        {
            if (frames.ContainsKey(cameraID))
                return frames[cameraID];
            else
                return CloudObserverBroadcastServiceLibrary.Properties.Resources.NoImageFrame;
        }

        public void WriteFrame(int cameraID, byte[] frame, DateTime time, bool WriteToDataBase)
        {

            if (WriteToDataBase)
            {
                string FileName;
                FileName = time.Year.ToString() + "-" + time.Month.ToString() + "-" + time.Day.ToString() + "-" + time.Hour.ToString() + "-" + time.Minute.ToString() + "-" + time.Second.ToString() + "-" + time.Millisecond.ToString() + ".img";
                client = new ChannelFactory<ICloudObserverStorageService>(new BasicHttpBinding(), "http://localhost:9000/CloudObserverStorageService").CreateChannel();
                client.SaveIntoStorage(cameraID.ToString() + @"\" + FileName,frame);
                database.FrameAdd(cameraID, frame, time.ToString());
            }
            frames[cameraID] = frame;
        }
    }
}