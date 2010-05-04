using System.ServiceModel;

namespace CloudObserver.Services.GW
{
    [ServiceContract]
    public interface IGateway// : IService
    {
        //[OperationContract]
        //string GetWorkBlock();

        [OperationContract]
        string IWannaRead(int[] ids, out string contentTypes);

        [OperationContract]
        string IWannaWrite(int id);

        [OperationContract]
        string IWannaWriteCustom(int id, string contentType);
    }
}
