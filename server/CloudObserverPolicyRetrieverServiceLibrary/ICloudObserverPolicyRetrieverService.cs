using System;
using System.IO;
using System.ServiceModel;
using System.ServiceModel.Web;

namespace CloudObserverPolicyRetrieverServiceLibrary
{
    [ServiceContract]
    public interface ICloudObserverPolicyRetrieverService
    {
        [OperationContract, WebGet(UriTemplate = "/clientaccesspolicy.xml")]
        Stream GetSilverlightPolicy();

        [OperationContract, WebGet(UriTemplate = "/crossdomain.xml")]
        Stream GetFlashPolicy();
    }
}