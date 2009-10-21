using System;
using System.IO;
using System.ServiceModel;
using System.ServiceModel.Web;

namespace CloudObserver.Policies
{
    /// <summary>
    /// Policy retriever service contract interface.
    /// </summary>
    [ServiceContract]
    public interface IPolicyRetriever
    {
        /// <summary>
        /// Provides Silverlight policies.
        /// </summary>
        /// <returns>XML-formatted stream with Silverlight policy settings.</returns>
        [OperationContract, WebGet(UriTemplate = "/clientaccesspolicy.xml")]
        Stream GetSilverlightPolicy();
    }
}