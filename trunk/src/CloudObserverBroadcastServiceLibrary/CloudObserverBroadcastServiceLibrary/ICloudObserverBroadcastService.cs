using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace CloudObserverBroadcastServiceLibrary
{
    [ServiceContract]
    public interface ICloudObserverBroadcastServer
    {
        [OperationContract]
        void bindMeToCamera(int clientID, int cameraID);

        [OperationContract]
        void setMeAsCamera(int cameraID);

        [OperationContract]
        byte[] getNextFrame(int cameraID);

        [OperationContract]
        void setNextFrame(byte[] frame);
    }
}
