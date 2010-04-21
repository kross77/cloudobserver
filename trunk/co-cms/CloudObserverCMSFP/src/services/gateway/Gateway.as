/**
 * This is a generated sub-class of _Gateway.as and is intended for behavior
 * customization.  This class is only generated when there is no file already present
 * at its target location.  Thus custom behavior that you add here will survive regeneration
 * of the super-class. 
 **/
 
package services.gateway
{
	import com.adobe.fiber.core.model_internal;
	import com.adobe.fiber.services.wrapper.WebServiceWrapper;
	import com.adobe.serializers.utility.TypeUtility;
	import mx.collections.ArrayCollection;
	import mx.rpc.AbstractOperation;
	import mx.rpc.AsyncToken;
	import mx.rpc.soap.mxml.Operation;
	import mx.rpc.soap.mxml.WebService;
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
				_serviceControl = new mx.rpc.soap.mxml.WebService();
				var operations:Object = new Object();
				var operation:mx.rpc.soap.mxml.Operation;    
				
				operation = new mx.rpc.soap.mxml.Operation(null, "IWannaRead");
				operation.resultType = String; 		 
				operations["IWannaRead"] = operation;
				
				_serviceControl.operations = operations;
				try
				{
					_serviceControl.convertResultHandler = com.adobe.serializers.utility.TypeUtility.convertResultHandler;
				}
				catch (e: Error)
				{ /* Flex 3.4 and eralier does not support the convertResultHandler functionality. */ }
				
				
				
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
			public function IWannaRead(contentIds:Array) : mx.rpc.AsyncToken
			{
				var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("IWannaRead");
				var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(contentIds) ;
				return _internal_token;
			}   
			
			
		}
		
	}
