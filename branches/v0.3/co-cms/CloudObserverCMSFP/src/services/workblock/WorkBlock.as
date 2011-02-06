/**
 * This is a generated sub-class of _WorkBlock.as and is intended for behavior
 * customization.  This class is only generated when there is no file already present
 * at its target location.  Thus custom behavior that you add here will survive regeneration
 * of the super-class. 
 **/
 
package services.workblock
{
	import mx.rpc.AsyncToken;
	import com.adobe.fiber.core.model_internal;
	import mx.rpc.AbstractOperation;
	import mx.collections.ArrayCollection;
	import mx.rpc.soap.mxml.WebService;
	import mx.rpc.soap.mxml.Operation;
	import com.adobe.fiber.services.wrapper.WebServiceWrapper;
public class WorkBlock extends WebServiceWrapper
{
	
	// Constructor
	public function WorkBlock()
	{
	}
	public function serviceStart(serviceURL:String):void
	{
		// initialize service control
		_serviceControl = new WebService();
		var operations:Object = new Object();
		var operation:Operation;         
		
		operation = new mx.rpc.soap.mxml.Operation(null, "IWannaRead");
		operation.resultType = String; 		 
		operations["IWannaRead"] = operation;         		 

		operation = new mx.rpc.soap.mxml.Operation(null, "IWannaWrite");
		operation.resultType = String; 		 
		operations["IWannaWrite"] = operation;
		
		_serviceControl.operations = operations;              
		
		
		_serviceControl.service = "WorkBlock";
		_serviceControl.port = "BasicHttpBinding_IWorkBlock";
		_serviceControl.wsdl = serviceURL;
		_serviceControl.loadWSDL();
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
	public function IWannaRead(ids:Array) : mx.rpc.AsyncToken
	{
		//model_internal::loadWSDLIfNecessary();
		var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("IWannaRead");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(ids) ;
		
		return _internal_token;
	} 
	public function IWannaWrite(id:int, contentType:String) : mx.rpc.AsyncToken
	{
			model_internal::loadWSDLIfNecessary();
		var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("IWannaWrite");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(id,contentType) ;
		
		return _internal_token;
	}           
	
}

}
