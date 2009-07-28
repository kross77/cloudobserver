using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace CloudObserverBroadcastServiceLibrary
{
    [ServiceContract]
    public interface ICloudObserverBroadcastService
    {
        [OperationContract]
        void bindMeToCamera(int clientID, int cameraID, int ident);

        [OperationContract]
        void setMeAsCamera(int cameraID, int ident);

        [OperationContract]
        byte[] getNextFrame(int cameraID, int ident);

        [OperationContract]
        void setNextFrame(byte[] frame,int ident);

        [OperationContract]
        void clean();
    }
}
