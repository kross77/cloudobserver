using System;
using System.IO;
using System.ServiceModel;
using System.ServiceModel.Web;

namespace CloudObserver.Policies
{
    [ServiceContract]
    public interface PolicyRetrieverContract
    {
        [OperationContract, WebGet(UriTemplate = "/clientaccesspolicy.xml")]
        Stream GetSilverlightPolicy();

        [OperationContract, WebGet(UriTemplate = "/crossdomain.xml")]
        Stream GetFlashPolicy();
    }
}