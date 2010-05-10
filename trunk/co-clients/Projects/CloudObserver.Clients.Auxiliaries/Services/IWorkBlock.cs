using System.ServiceModel;

namespace CloudObserver.Clients.Auxiliaries.Services
{
    [ServiceContract]
    public interface IWorkBlock
    {
        [OperationContract]
        string IWannaRead(int[] ids);

        [OperationContract]
        string IWannaWrite(int id, string contentType);

        [OperationContract]
        void ConnectToController(string controllerAddress);
    }
}
