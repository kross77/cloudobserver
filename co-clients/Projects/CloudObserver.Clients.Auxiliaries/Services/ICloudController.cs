using System;
using System.ServiceModel;

namespace CloudObserver.Clients.Auxiliaries.Services
{
    [ServiceContract]
    public interface ICloudController
    {
        [OperationContract]
        void ConnectDevice(string ipAddress);

        [OperationContract]
        string GetWorkBlock();

        [OperationContract]
        void RegisterStream(int id, string address, string contentType);

        [OperationContract]
        void GetStreamInformation(int id, out string address, out string contentType);
    }
}
