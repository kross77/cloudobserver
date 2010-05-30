using System;
using System.IO;
using System.Text;
using System.ServiceModel.Web;

namespace CloudObserver.Kernel.Policies
{
    /// <summary>
    /// Policy retriever service realization class.
    /// </summary>
    public class PolicyRetriever : IPolicyRetriever
    {
        /// <summary>
        /// Provides Flash policy file.
        /// </summary>
        /// <returns>Stream containing Flash policy file.</returns>
        public Stream GetFlashPolicy()
        {
            WebOperationContext.Current.OutgoingResponse.ContentType = "application/xml";
            return new MemoryStream(Encoding.UTF8.GetBytes(Properties.Resources.crossdomain));
        }
    }
}
