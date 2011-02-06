using System;
using System.IO;
using System.Text;
using System.ServiceModel.Web;

namespace CloudObserver.Policies
{
    public class PolicyRetriever : PolicyRetrieverContract
    {
        public Stream GetSilverlightPolicy()
        {
            WebOperationContext.Current.OutgoingResponse.ContentType = "application/xml";
            return new MemoryStream(Encoding.UTF8.GetBytes(Properties.Resources.clientaccesspolicy));
        }

        public Stream GetFlashPolicy()
        {
            WebOperationContext.Current.OutgoingResponse.ContentType = "application/xml";
            return new MemoryStream(Encoding.UTF8.GetBytes(Properties.Resources.crossdomain));
        }
    }
}