/**
 * This is a generated sub-class of _Gateway.as and is intended for behavior
 * customization.  This class is only generated when there is no file already present
 * at its target location.  Thus custom behavior that you add here will survive regeneration
 * of the super-class. 
 **/
 
package services.gateway
{
		import mx.rpc.AsyncToken;

		import mx.rpc.AbstractOperation;
		import mx.collections.ArrayCollection;
		import mx.rpc.soap.mxml.WebService;
		import mx.rpc.soap.mxml.Operation;
		import com.adobe.fiber.services.wrapper.WebServiceWrapper;
public class Gateway extends WebServiceWrapper
{
	/**
	 * This is a generated sub-class of _WorkBlock.as and is intended for behavior
	 * customization.  This class is only generated when there is no file already present
	 * at its target location.  Thus custom behavior that you add here will survive regeneration
	 * of the super-class. 
	 **/
			// Constructor
			public function Gateway()
			{
			
			}
			public function serviceStart(serviceURL:String):void
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
				_serviceControl.wsdl = serviceURL;
				_serviceControl.loadWSDL();			
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
				var _internal_operation:AbstractOperation = _serviceControl.getOperation("GetWorkBlock");
				var _internal_token:AsyncToken = _internal_operation.send() ;	
				return _internal_token;
			}   
			
			
		}
		
	}
