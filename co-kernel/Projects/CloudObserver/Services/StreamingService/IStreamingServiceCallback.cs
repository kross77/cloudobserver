using System;
using System.ServiceModel;

namespace CloudObserver.Services.StreamingService
{
    [ServiceContract]
    public interface IStreamingServiceCallback
    {
        [OperationContract(IsOneWay = true)]
        void DataCallback(byte[] data);

        [OperationContract(IsOneWay = true)]
        void SubscriptionResponse(byte[] response);
    }
}