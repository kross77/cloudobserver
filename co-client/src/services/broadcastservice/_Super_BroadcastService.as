
/**
 * This is a generated class and is not intended for modfication.  To customize behavior
 * of this service wrapper you may modify the generated sub-class of this class - BroadcastService.as.
 */
package services.broadcastservice
{
import flash.utils.ByteArray;

import fr.core.model_internal;
import fr.services.wrapper.WebServiceWrapper;

import mx.rpc.AbstractOperation;
import mx.rpc.AsyncToken;
import mx.rpc.soap.mxml.Operation;
import mx.rpc.soap.mxml.WebService;

[ExcludeClass]
internal class _Super_BroadcastService extends WebServiceWrapper
{
     
    // Constructor
    public function _Super_BroadcastService()
    {
        // initialize service control
         _serviceControl = new WebService();
         var operations:Object = new Object();
         var operation:Operation;         
         
         operation = new Operation(null, "ReadFrame");
		 operation.resultType = ByteArray; 		 
         operations["ReadFrame"] = operation;
    
         operation = new Operation(null, "WriteFrame");
         operations["WriteFrame"] = operation;
    
         _serviceControl.operations = operations;              

  

         _serviceControl.service = "CloudObserverBroadcastService";
         _serviceControl.port = "BasicHttpBinding_ICloudObserverBroadcastService";
        // _serviceControl.wsdl = "http://93.100.45.201:9000/CloudObserverBroadcastService?wsdl";
        // _serviceControl.loadWSDL();
      
     
         model_internal::initialize();
    }

	/**
	  * This method is a generated wrapper used to call the 'ReadFrame' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function ReadFrame(cameraID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("ReadFrame");
		var _internal_token:AsyncToken = _internal_operation.send(cameraID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'WriteFrame' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function WriteFrame(cameraID:int, frame:ByteArray) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("WriteFrame");
		var _internal_token:AsyncToken = _internal_operation.send(cameraID,frame) ;

		return _internal_token;
	}   

}

}
