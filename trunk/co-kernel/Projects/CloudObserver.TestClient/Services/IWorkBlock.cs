using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceContract]
    public interface IWorkBlock : IService
    {
        [OperationContract]
        string GetTcpStreamUriToRead(int[] contentIds);

        [OperationContract]
        string GetTcpStreamUriToWrite(int contentId);
    }
}
