/**
 * This is a generated class and is not intended for modfication.  To customize behavior
 * of this service wrapper you may modify the generated sub-class of this class - WorkBlock.as.
 */
package services.workblock
{
import mx.rpc.AsyncToken;
import com.adobe.fiber.core.model_internal;
import mx.rpc.AbstractOperation;
import mx.collections.ArrayCollection;
import mx.rpc.soap.mxml.WebService;
import mx.rpc.soap.mxml.Operation;
import com.adobe.fiber.services.wrapper.WebServiceWrapper;

[ExcludeClass]
internal class _Super_WorkBlock extends WebServiceWrapper
{
     
    // Constructor
    public function _Super_WorkBlock()
    {
        // initialize service control
         _serviceControl = new WebService();
         var operations:Object = new Object();
         var operation:Operation;         
         
         operation = new Operation(null, "GetTcpStreamUriToRead");
		 operation.resultType = String; 		 
         operations["GetTcpStreamUriToRead"] = operation;
    
         _serviceControl.operations = operations;              

  

         _serviceControl.service = "WorkBlock";
         _serviceControl.port = "BasicHttpBinding_IWorkBlock";
         _serviceControl.wsdl = "http://localhost/";
         _serviceControl.loadWSDL();
      
     
         model_internal::initialize();
    }

	/**
	  * This method is a generated wrapper used to call the 'GetTcpStreamUriToRead' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GetTcpStreamUriToRead(contentIds:ArrayCollection) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GetTcpStreamUriToRead");
		var _internal_token:AsyncToken = _internal_operation.send(contentIds) ;

		return _internal_token;
	}   
	 
}

}
