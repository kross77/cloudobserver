using System;
using System.ServiceModel;

namespace CloudObserver.Services.StreamingService
{
    [ServiceContract(Namespace = "Silverlight", CallbackContract = typeof(IStreamingServiceCallback))]
    public interface IStreamingService
    {
        [OperationContract(IsOneWay = true)]
        void Send(byte[] data);

        [OperationContract(IsOneWay = true)]
        void SetSubscriptionResponse(byte[] response);

        [OperationContract(IsOneWay = true)]
        void Subscribe(TimeSpan timeout);

        [OperationContract(IsOneWay = true)]
        void Unsubscribe();
    }
}