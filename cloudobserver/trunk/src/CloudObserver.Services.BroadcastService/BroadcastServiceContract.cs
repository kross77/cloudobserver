using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceContract]
    public interface BroadcastServiceContract : ServiceContract
    {
        [OperationContract]
        byte[] ReadFrame(int cameraID);

        [OperationContract]
        void WriteFrame(int cameraID, byte[] frame);
    }
}