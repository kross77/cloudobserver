/**
 * This is a generated class and is not intended for modfication.  To customize behavior
 * of this service wrapper you may modify the generated sub-class of this class - Gateway.as.
 */
package services.gateway
{
import mx.rpc.AsyncToken;
import com.adobe.fiber.core.model_internal;
import mx.rpc.AbstractOperation;
import mx.rpc.soap.mxml.WebService;
import mx.rpc.soap.mxml.Operation;
import com.adobe.fiber.services.wrapper.WebServiceWrapper;

[ExcludeClass]
internal class _Super_Gateway extends WebServiceWrapper
{
     
    // Constructor
    public function _Super_Gateway()
    {
        // initialize service control
         _serviceControl = new WebService();
         var operations:Object = new Object();
         var operation:Operation;         
         
         operation = new Operation(null, "GetWorkBlock");
		 operation.resultType = String; 		 
         operations["GetWorkBlock"] = operation;
    
         _serviceControl.operations = operations;              

  

         _serviceControl.service = "Gateway";
         _serviceControl.port = "BasicHttpBinding_IGateway";
         _serviceControl.wsdl = "http://localhost:4773/cloudobserver?wsdl";
         _serviceControl.loadWSDL();
      
     
         model_internal::initialize();
    }

	/**
	  * This method is a generated wrapper used to call the 'GetWorkBlock' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GetWorkBlock() : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GetWorkBlock");
		var _internal_token:AsyncToken = _internal_operation.send() ;

		return _internal_token;
	}   
	 
}

}
