/**
 * This is a generated sub-class of _Api.as and is intended for behavior
 * customization.  This class is only generated when there is no file already present
 * at its target location.  Thus custom behavior that you add here will survive regeneration
 * of the super-class. 
 **/
 
package services.api
{

	
	import com.adobe.fiber.core.model_internal;
	import com.adobe.fiber.services.wrapper.HTTPServiceWrapper;
	import mx.rpc.AbstractOperation;
	import mx.rpc.AsyncToken;
	import mx.rpc.http.HTTPMultiService;
	import mx.rpc.http.Operation;
	
	import com.adobe.serializers.xml.XMLSerializationFilter;

public class Api extends HTTPServiceWrapper
{
	private static var serializer0:XMLSerializationFilter = new XMLSerializationFilter();
	// Constructor
	public function Api()
	{
	}
	public function serviceStart(serviceURL:String):void
	{
		// initialize service control
		_serviceControl = new mx.rpc.http.HTTPMultiService();
		var operations:Array = new Array();
		var operation:mx.rpc.http.Operation;
		var argsArray:Array;       
		///////////// xml methods todo add get streams from all method
		operation = new mx.rpc.http.Operation(null, "getData");
		operation.url = serviceURL;
		operation.method = "GET";
		argsArray = new Array("method","key");
		operation.argumentNames = argsArray;         
		operation.serializationFilter = serializer0;
		operation.properties = new Object();
		operation.properties["xPath"] = "/::node/::streamID";
		operation.resultElementType = String;
		operations.push(operation);
		///////////////// string methods
		
		operation = new mx.rpc.http.Operation(null, "createPassword");
		operation.url = serviceURL;
		operation.method = "GET";
		argsArray = new Array("method","key","userEmail","newUserPass");
		operation.argumentNames = argsArray;         
		operation.serializationFilter = serializer0;
		operation.resultType = String; 		 
		operations.push(operation);
		
		operation = new mx.rpc.http.Operation(null, "createUser");
		operation.url = serviceURL;
		operation.method = "GET";
		argsArray = new Array("method","userName","userEmail","userPass");
		operation.argumentNames = argsArray;         
		operation.serializationFilter = serializer0;
		operation.resultType = String; 		 
		operations.push(operation);
		
		operation = new mx.rpc.http.Operation(null, "createUserWithStream");
		operation.url = serviceURL;
		operation.method = "GET";
		argsArray = new Array("method","streamId","userName","userEmail","userPass");
		operation.argumentNames = argsArray;         
		operation.serializationFilter = serializer0;
		operation.resultType = String; 		 
		operations.push(operation);
		
		operation = new mx.rpc.http.Operation(null, "createUserWithStreamFast");
		operation.url = serviceURL;
		operation.method = "GET";
		argsArray = new Array("method","streamId","userName");
		operation.argumentNames = argsArray;         
		operation.serializationFilter = serializer0;
		operation.resultType = String; 		 
		operations.push(operation);
		
		operation = new mx.rpc.http.Operation(null, "deleteStream");
		operation.url = serviceURL;
		operation.method = "GET";
		argsArray = new Array("method","key","streamId");
		operation.argumentNames = argsArray;         
		operation.serializationFilter = serializer0;
		operation.resultType = String; 		 
		operations.push(operation);
		
		operation = new mx.rpc.http.Operation(null, "deleteUser");
		operation.url = serviceURL;
		operation.method = "GET";
		argsArray = new Array("method","key","userName","userEmail","userPass");
		operation.argumentNames = argsArray;         
		operation.serializationFilter = serializer0;
		operation.resultType = String; 		 
		operations.push(operation);
		
		operation = new mx.rpc.http.Operation(null, "getGatewayAddress");
		operation.url = serviceURL;
		operation.method = "GET";
		argsArray = new Array("method","key");
		operation.argumentNames = argsArray;         
		operation.serializationFilter = serializer0;
		operation.resultType = String; 		 
		operations.push(operation);
		
		operation = new mx.rpc.http.Operation(null, "getMyName");
		operation.url = serviceURL;
		operation.method = "GET";
		argsArray = new Array("method","key");
		operation.argumentNames = argsArray;         
		operation.serializationFilter = serializer0;
		operation.resultType = String; 		 
		operations.push(operation);
		
		operation = new mx.rpc.http.Operation(null, "LogIn");
		operation.url = serviceURL;
		operation.method = "GET";
		argsArray = new Array("method","userEmail","userPass");
		operation.argumentNames = argsArray;         
		operation.serializationFilter = serializer0;
		operation.resultType = String; 		 
		operations.push(operation);
		
		operation = new mx.rpc.http.Operation(null, "LogOut");
		operation.url = serviceURL;
		operation.method = "GET";
		argsArray = new Array("method","key");
		operation.argumentNames = argsArray;         
		operation.serializationFilter = serializer0;
		operation.resultType = String; 		 
		operations.push(operation);
		
		operation = new mx.rpc.http.Operation(null, "setMyName");
		operation.url = serviceURL;
		operation.method = "GET";
		argsArray = new Array("method","key","newUserName");
		operation.argumentNames = argsArray;         
		operation.serializationFilter = serializer0;
		operation.resultType = String; 		 
		operations.push(operation);
		
		operation = new mx.rpc.http.Operation(null, "setStream");
		operation.url = serviceURL;
		operation.method = "GET";
		argsArray = new Array("method","key","streamId");
		operation.argumentNames = argsArray;         
		operation.serializationFilter = serializer0;
		operation.resultType = String; 		 
		operations.push(operation);
		
		///////////////////
		_serviceControl.operationList = operations;  
		
		
		
		model_internal::initialize();
	}
	
	/**
	 * This method is a generated wrapper used to call the 'getData' operation. It returns an mx.rpc.AsyncToken whose 
	 * result property will be populated with the result of the operation when the server response is received. 
	 * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	 * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
	 *
	 * @see mx.rpc.AsyncToken
	 * @see mx.rpc.CallResponder 
	 *
	 * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	 */          
	public function getData(key:String) : mx.rpc.AsyncToken
	{
		var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("getData");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send("getMyStreams",key) ;
		
		return _internal_token;
	}   

	/**
	 * This method is a generated wrapper used to call the 'createPassword' operation. It returns an mx.rpc.AsyncToken whose 
	 * result property will be populated with the result of the operation when the server response is received. 
	 * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	 * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
	 *
	 * @see mx.rpc.AsyncToken
	 * @see mx.rpc.CallResponder 
	 *
	 * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	 */          
	public function createPassword(method:String, key:String, userEmail:String, newUserPass:String) : mx.rpc.AsyncToken
	{
		var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("createPassword");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send("createPassword",key,userEmail,escape(newUserPass)) ;
		
		return _internal_token;
	}   
	
	/**
	 * This method is a generated wrapper used to call the 'createUser' operation. It returns an mx.rpc.AsyncToken whose 
	 * result property will be populated with the result of the operation when the server response is received. 
	 * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	 * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
	 *
	 * @see mx.rpc.AsyncToken
	 * @see mx.rpc.CallResponder 
	 *
	 * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	 */          
	public function createUser( userName:String, userEmail:String, userPass:String) : mx.rpc.AsyncToken
	{
		var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("createUser");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send("createUser",escape(userName),userEmail,escape(userPass)) ;
		
		return _internal_token;
	}   
	
	/**
	 * This method is a generated wrapper used to call the 'createUserWithStream' operation. It returns an mx.rpc.AsyncToken whose 
	 * result property will be populated with the result of the operation when the server response is received. 
	 * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	 * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
	 *
	 * @see mx.rpc.AsyncToken
	 * @see mx.rpc.CallResponder 
	 *
	 * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	 */          
	public function createUserWithStream( streamId:String, userName:String, userEmail:String, userPass:String) : mx.rpc.AsyncToken
	{
		var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("createUserWithStream");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send("createUserWithStream",streamId,escape(userName),escape(userEmail),escape(userPass)) ;
		
		return _internal_token;
	}   
	
	/**
	 * This method is a generated wrapper used to call the 'createUserWithStreamFast' operation. It returns an mx.rpc.AsyncToken whose 
	 * result property will be populated with the result of the operation when the server response is received. 
	 * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	 * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
	 *
	 * @see mx.rpc.AsyncToken
	 * @see mx.rpc.CallResponder 
	 *
	 * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	 */          
	public function createUserWithStreamFast( streamId:String, userName:String) : mx.rpc.AsyncToken
	{
		var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("createUserWithStreamFast");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send("createUserWithStreamFast",streamId,escape(userName)) ;
		
		return _internal_token;
	}   
	
	/**
	 * This method is a generated wrapper used to call the 'deleteStream' operation. It returns an mx.rpc.AsyncToken whose 
	 * result property will be populated with the result of the operation when the server response is received. 
	 * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	 * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
	 *
	 * @see mx.rpc.AsyncToken
	 * @see mx.rpc.CallResponder 
	 *
	 * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	 */          
	public function deleteStream( key:String, streamId:String) : mx.rpc.AsyncToken
	{
		var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("deleteStream");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send("deleteStream",key,streamId) ;
		
		return _internal_token;
	}   
	
	/**
	 * This method is a generated wrapper used to call the 'deleteUser' operation. It returns an mx.rpc.AsyncToken whose 
	 * result property will be populated with the result of the operation when the server response is received. 
	 * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	 * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
	 *
	 * @see mx.rpc.AsyncToken
	 * @see mx.rpc.CallResponder 
	 *
	 * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	 */          
	public function deleteUser( key:String, userName:String, userEmail:String, userPass:String) : mx.rpc.AsyncToken
	{
		var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("deleteUser");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send("deleteUser",key,escape(userName),escape(userEmail),escape(userPass)) ;
		
		return _internal_token;
	}   
	
	/**
	 * This method is a generated wrapper used to call the 'getGatewayAddress' operation. It returns an mx.rpc.AsyncToken whose 
	 * result property will be populated with the result of the operation when the server response is received. 
	 * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	 * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
	 *
	 * @see mx.rpc.AsyncToken
	 * @see mx.rpc.CallResponder 
	 *
	 * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	 */          
	public function getGatewayAddress( key:String) : mx.rpc.AsyncToken
	{
		var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("getGatewayAddress");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send("getGatewayAddress",key) ;
		
		return _internal_token;
	}   
	
	/**
	 * This method is a generated wrapper used to call the 'getMyName' operation. It returns an mx.rpc.AsyncToken whose 
	 * result property will be populated with the result of the operation when the server response is received. 
	 * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	 * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
	 *
	 * @see mx.rpc.AsyncToken
	 * @see mx.rpc.CallResponder 
	 *
	 * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	 */          
	public function getMyName( key:String) : mx.rpc.AsyncToken
	{
		var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("getMyName");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send("getMyName",key) ;
		
		return _internal_token;
	}   
	
	/**
	 * This method is a generated wrapper used to call the 'LogIn' operation. It returns an mx.rpc.AsyncToken whose 
	 * result property will be populated with the result of the operation when the server response is received. 
	 * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	 * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
	 *
	 * @see mx.rpc.AsyncToken
	 * @see mx.rpc.CallResponder 
	 *
	 * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	 */          
	public function LogIn(userEmail:String, userPass:String) : mx.rpc.AsyncToken
	{
		var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("LogIn");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send("logIn",escape(userEmail),escape(userPass)) ;
		
		return _internal_token;
	}   
	
	/**
	 * This method is a generated wrapper used to call the 'LogOut' operation. It returns an mx.rpc.AsyncToken whose 
	 * result property will be populated with the result of the operation when the server response is received. 
	 * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	 * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
	 *
	 * @see mx.rpc.AsyncToken
	 * @see mx.rpc.CallResponder 
	 *
	 * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	 */          
	public function LogOut( key:String) : mx.rpc.AsyncToken
	{
		var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("LogOut");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send("logOut",key) ;
		
		return _internal_token;
	}   
	
	/**
	 * This method is a generated wrapper used to call the 'setMyName' operation. It returns an mx.rpc.AsyncToken whose 
	 * result property will be populated with the result of the operation when the server response is received. 
	 * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	 * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
	 *
	 * @see mx.rpc.AsyncToken
	 * @see mx.rpc.CallResponder 
	 *
	 * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	 */          
	public function setMyName( key:String, newUserName:String) : mx.rpc.AsyncToken
	{
		var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("setMyName");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send("setMyName",key,escape(newUserName)) ;
		
		return _internal_token;
	}   
	
	/**
	 * This method is a generated wrapper used to call the 'setStream' operation. It returns an mx.rpc.AsyncToken whose 
	 * result property will be populated with the result of the operation when the server response is received. 
	 * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	 * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
	 *
	 * @see mx.rpc.AsyncToken
	 * @see mx.rpc.CallResponder 
	 *
	 * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	 */          
	public function setStream( key:String, streamId:String) : mx.rpc.AsyncToken
	{
		var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("setStream");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send("setStream",key,streamId) ;
		
		return _internal_token;
	}   
               
}

}
