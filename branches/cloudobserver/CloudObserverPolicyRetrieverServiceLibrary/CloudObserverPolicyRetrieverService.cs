using System;
using System.IO;
using System.Text;
using System.ServiceModel.Web;

namespace CloudObserverPolicyRetrieverServiceLibrary
{
    public class CloudObserverPolicyRetrieverService : ICloudObserverPolicyRetrieverService
    {
        public Stream GetSilverlightPolicy()
        {
            WebOperationContext.Current.OutgoingResponse.ContentType = "application/xml";
            return new MemoryStream(Encoding.UTF8.GetBytes(CloudObserverPolicyRetrieverServiceLibrary.Properties.Resources.clientaccesspolicy));
        }

        public Stream GetFlashPolicy()
        {
            WebOperationContext.Current.OutgoingResponse.ContentType = "application/xml";
            return new MemoryStream(Encoding.UTF8.GetBytes(CloudObserverPolicyRetrieverServiceLibrary.Properties.Resources.crossdomain));
        }
    }
}