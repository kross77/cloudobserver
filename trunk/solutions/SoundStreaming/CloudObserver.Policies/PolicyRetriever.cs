using System;
using System.IO;
using System.Text;
using System.ServiceModel.Web;

namespace CloudObserver.Policies
{
    /// <summary>
    /// Policy retriever service realization class.
    /// </summary>
    public class PolicyRetriever : IPolicyRetriever
    {
        #region IPolicyRetrieverService Members

        /// <summary>
        /// Provides Silverlight policies.
        /// </summary>
        /// <returns>XML-formatted stream with Silverlight policy settings.</returns>
        public Stream GetSilverlightPolicy()
        {
            WebOperationContext.Current.OutgoingResponse.ContentType = "application/xml";
            return new MemoryStream(Encoding.UTF8.GetBytes(Properties.Resources.clientaccesspolicy));
        }

        #endregion
    }
}