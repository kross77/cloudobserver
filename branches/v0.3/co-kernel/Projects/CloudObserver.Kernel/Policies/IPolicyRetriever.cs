using System;
using System.IO;
using System.ServiceModel;
using System.ServiceModel.Web;

namespace CloudObserver.Kernel.Policies
{
    /// <summary>
    /// Policy retriever service contract interface.
    /// </summary>
    [ServiceContract]
    public interface IPolicyRetriever
    {
        /// <summary>
        /// Provides Flash policy file.
        /// </summary>
        /// <returns>Stream containing Flash policy file.</returns>
        [OperationContract, WebGet(UriTemplate = "/crossdomain.xml")]
        Stream GetFlashPolicy();
    }
}
