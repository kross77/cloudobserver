
/**
 * This is a generated class and is not intended for modfication.  To customize behavior
 * of this service wrapper you may modify the generated sub-class of this class - CloudObserverService.as.
 */
package services.cloudobserverservice
{
import mx.rpc.AsyncToken;
import fr.core.model_internal;
import mx.rpc.AbstractOperation;
import mx.rpc.soap.mxml.WebService;
import mx.rpc.soap.mxml.Operation;
import fr.services.wrapper.WebServiceWrapper;

[ExcludeClass]
internal class _Super_CloudObserverService extends WebServiceWrapper
{
     
    // Constructor
    public function _Super_CloudObserverService()
    {
        // initialize service control
         _serviceControl = new WebService();
         var operations:Object = new Object();
         var operation:Operation;         
         
         operation = new Operation(null, "CameraSetDescription");
         operations["CameraSetDescription"] = operation;
    
         operation = new Operation(null, "CameraSetIcon");
         operations["CameraSetIcon"] = operation;
    
         operation = new Operation(null, "GroupAdd");
		 operation.resultType = int; 		 
         operations["GroupAdd"] = operation;
    
         operation = new Operation(null, "GroupRemove");
         operations["GroupRemove"] = operation;
    
         operation = new Operation(null, "GroupGetID");
		 operation.resultType = int; 		 
         operations["GroupGetID"] = operation;
    
         operation = new Operation(null, "GroupGetName");
		 operation.resultType = String; 		 
         operations["GroupGetName"] = operation;
    
         operation = new Operation(null, "GroupGetDescription");
		 operation.resultType = String; 		 
         operations["GroupGetDescription"] = operation;
    
         operation = new Operation(null, "GroupGetIcon");
		 operation.resultType = int; 		 
         operations["GroupGetIcon"] = operation;
    
         operation = new Operation(null, "GroupGetPrivacy");
		 operation.resultType = int; 		 
         operations["GroupGetPrivacy"] = operation;
    
         operation = new Operation(null, "GroupGetRegistrationDate");
		 operation.resultType = Date; 		 
         operations["GroupGetRegistrationDate"] = operation;
    
         operation = new Operation(null, "GroupGetMembers");
		 operation.resultElementType = int;
         operations["GroupGetMembers"] = operation;
    
         operation = new Operation(null, "GroupGetCameras");
		 operation.resultElementType = int;
         operations["GroupGetCameras"] = operation;
    
         operation = new Operation(null, "GroupSetName");
         operations["GroupSetName"] = operation;
    
         operation = new Operation(null, "GroupSetDescription");
         operations["GroupSetDescription"] = operation;
    
         operation = new Operation(null, "GroupSetIcon");
         operations["GroupSetIcon"] = operation;
    
         operation = new Operation(null, "GroupSetPrivacy");
         operations["GroupSetPrivacy"] = operation;
    
         operation = new Operation(null, "GroupMemberAdd");
         operations["GroupMemberAdd"] = operation;
    
         operation = new Operation(null, "GroupMemberRemove");
         operations["GroupMemberRemove"] = operation;
    
         operation = new Operation(null, "GroupMemberGetPrivileges");
		 operation.resultType = int; 		 
         operations["GroupMemberGetPrivileges"] = operation;
    
         operation = new Operation(null, "GroupMemberSetPrivileges");
         operations["GroupMemberSetPrivileges"] = operation;
    
         operation = new Operation(null, "GroupCameraAdd");
         operations["GroupCameraAdd"] = operation;
    
         operation = new Operation(null, "GroupCameraRemove");
         operations["GroupCameraRemove"] = operation;
    
         operation = new Operation(null, "FrameAdd");
		 operation.resultType = int; 		 
         operations["FrameAdd"] = operation;
    
         operation = new Operation(null, "FrameRemove");
         operations["FrameRemove"] = operation;
    
         operation = new Operation(null, "FrameGetContent");
		 operation.resultType = int; 		 
         operations["FrameGetContent"] = operation;
    
         operation = new Operation(null, "FrameGetMarker");
		 operation.resultType = String; 		 
         operations["FrameGetMarker"] = operation;
    
         operation = new Operation(null, "UserIsEmailAvailable");
		 operation.resultType = Boolean; 		 
         operations["UserIsEmailAvailable"] = operation;
    
         operation = new Operation(null, "UserLogin");
		 operation.resultType = Boolean; 		 
         operations["UserLogin"] = operation;
    
         operation = new Operation(null, "UserAdd");
		 operation.resultType = int; 		 
         operations["UserAdd"] = operation;
    
         operation = new Operation(null, "UserRemove");
         operations["UserRemove"] = operation;
    
         operation = new Operation(null, "UserGetID");
		 operation.resultType = int; 		 
         operations["UserGetID"] = operation;
    
         operation = new Operation(null, "UserGetEmail");
		 operation.resultType = String; 		 
         operations["UserGetEmail"] = operation;
    
         operation = new Operation(null, "UserGetPassword");
		 operation.resultType = String; 		 
         operations["UserGetPassword"] = operation;
    
         operation = new Operation(null, "UserGetName");
		 operation.resultType = String; 		 
         operations["UserGetName"] = operation;
    
         operation = new Operation(null, "UserGetDescription");
		 operation.resultType = String; 		 
         operations["UserGetDescription"] = operation;
    
         operation = new Operation(null, "UserGetIcon");
		 operation.resultType = int; 		 
         operations["UserGetIcon"] = operation;
    
         operation = new Operation(null, "UserGetRegistrationDate");
		 operation.resultType = Date; 		 
         operations["UserGetRegistrationDate"] = operation;
    
         operation = new Operation(null, "UserGetGroups");
		 operation.resultElementType = int;
         operations["UserGetGroups"] = operation;
    
         operation = new Operation(null, "UserSetPassword");
         operations["UserSetPassword"] = operation;
    
         operation = new Operation(null, "UserSetName");
         operations["UserSetName"] = operation;
    
         operation = new Operation(null, "UserSetDescription");
         operations["UserSetDescription"] = operation;
    
         operation = new Operation(null, "UserSetIcon");
         operations["UserSetIcon"] = operation;
    
         operation = new Operation(null, "CameraIsPathAvailable");
		 operation.resultType = Boolean; 		 
         operations["CameraIsPathAvailable"] = operation;
    
         operation = new Operation(null, "CameraAdd");
		 operation.resultType = int; 		 
         operations["CameraAdd"] = operation;
    
         operation = new Operation(null, "CameraRemove");
         operations["CameraRemove"] = operation;
    
         operation = new Operation(null, "CameraGetID");
		 operation.resultType = int; 		 
         operations["CameraGetID"] = operation;
    
         operation = new Operation(null, "CameraGetPath");
		 operation.resultType = String; 		 
         operations["CameraGetPath"] = operation;
    
         operation = new Operation(null, "CameraGetName");
		 operation.resultType = String; 		 
         operations["CameraGetName"] = operation;
    
         operation = new Operation(null, "CameraGetDescription");
		 operation.resultType = String; 		 
         operations["CameraGetDescription"] = operation;
    
         operation = new Operation(null, "CameraGetIcon");
		 operation.resultType = int; 		 
         operations["CameraGetIcon"] = operation;
    
         operation = new Operation(null, "CameraGetRegistrationDate");
		 operation.resultType = Date; 		 
         operations["CameraGetRegistrationDate"] = operation;
    
         operation = new Operation(null, "CameraGetGroups");
		 operation.resultElementType = int;
         operations["CameraGetGroups"] = operation;
    
         operation = new Operation(null, "CameraGetFrames");
		 operation.resultElementType = int;
         operations["CameraGetFrames"] = operation;
    
         operation = new Operation(null, "CameraSetName");
         operations["CameraSetName"] = operation;
    
         _serviceControl.operations = operations;              

  

         _serviceControl.service = "CloudObserverService";
         _serviceControl.port = "BasicHttpBinding_ICloudObserverService";
         _serviceControl.wsdl = "http://localhost:2101/CloudObserverWebsite/CloudObserverService.svc?wsdl";
         _serviceControl.loadWSDL();
      
     
         model_internal::initialize();
    }

	/**
	  * This method is a generated wrapper used to call the 'CameraSetDescription' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function CameraSetDescription(cameraID:int, description:String) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("CameraSetDescription");
		var _internal_token:AsyncToken = _internal_operation.send(cameraID,description) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'CameraSetIcon' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function CameraSetIcon(cameraID:int, icon:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("CameraSetIcon");
		var _internal_token:AsyncToken = _internal_operation.send(cameraID,icon) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'GroupAdd' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GroupAdd(name:String, description:String, icon:int, privacy:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GroupAdd");
		var _internal_token:AsyncToken = _internal_operation.send(name,description,icon,privacy) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'GroupRemove' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GroupRemove(groupID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GroupRemove");
		var _internal_token:AsyncToken = _internal_operation.send(groupID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'GroupGetID' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GroupGetID(name:String) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GroupGetID");
		var _internal_token:AsyncToken = _internal_operation.send(name) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'GroupGetName' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GroupGetName(groupID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GroupGetName");
		var _internal_token:AsyncToken = _internal_operation.send(groupID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'GroupGetDescription' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GroupGetDescription(groupID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GroupGetDescription");
		var _internal_token:AsyncToken = _internal_operation.send(groupID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'GroupGetIcon' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GroupGetIcon(groupID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GroupGetIcon");
		var _internal_token:AsyncToken = _internal_operation.send(groupID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'GroupGetPrivacy' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GroupGetPrivacy(groupID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GroupGetPrivacy");
		var _internal_token:AsyncToken = _internal_operation.send(groupID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'GroupGetRegistrationDate' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GroupGetRegistrationDate(groupID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GroupGetRegistrationDate");
		var _internal_token:AsyncToken = _internal_operation.send(groupID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'GroupGetMembers' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GroupGetMembers(groupID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GroupGetMembers");
		var _internal_token:AsyncToken = _internal_operation.send(groupID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'GroupGetCameras' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GroupGetCameras(groupID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GroupGetCameras");
		var _internal_token:AsyncToken = _internal_operation.send(groupID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'GroupSetName' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GroupSetName(groupID:int, name:String) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GroupSetName");
		var _internal_token:AsyncToken = _internal_operation.send(groupID,name) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'GroupSetDescription' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GroupSetDescription(groupID:int, description:String) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GroupSetDescription");
		var _internal_token:AsyncToken = _internal_operation.send(groupID,description) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'GroupSetIcon' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GroupSetIcon(groupID:int, icon:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GroupSetIcon");
		var _internal_token:AsyncToken = _internal_operation.send(groupID,icon) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'GroupSetPrivacy' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GroupSetPrivacy(groupID:int, privacy:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GroupSetPrivacy");
		var _internal_token:AsyncToken = _internal_operation.send(groupID,privacy) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'GroupMemberAdd' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GroupMemberAdd(userID:int, groupID:int, privileges:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GroupMemberAdd");
		var _internal_token:AsyncToken = _internal_operation.send(userID,groupID,privileges) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'GroupMemberRemove' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GroupMemberRemove(userID:int, groupID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GroupMemberRemove");
		var _internal_token:AsyncToken = _internal_operation.send(userID,groupID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'GroupMemberGetPrivileges' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GroupMemberGetPrivileges(userID:int, groupID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GroupMemberGetPrivileges");
		var _internal_token:AsyncToken = _internal_operation.send(userID,groupID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'GroupMemberSetPrivileges' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GroupMemberSetPrivileges(userID:int, groupID:int, privileges:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GroupMemberSetPrivileges");
		var _internal_token:AsyncToken = _internal_operation.send(userID,groupID,privileges) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'GroupCameraAdd' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GroupCameraAdd(cameraID:int, groupID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GroupCameraAdd");
		var _internal_token:AsyncToken = _internal_operation.send(cameraID,groupID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'GroupCameraRemove' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function GroupCameraRemove(cameraID:int, groupID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("GroupCameraRemove");
		var _internal_token:AsyncToken = _internal_operation.send(cameraID,groupID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'FrameAdd' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function FrameAdd(cameraID:int, content:int, marker:String) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("FrameAdd");
		var _internal_token:AsyncToken = _internal_operation.send(cameraID,content,marker) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'FrameRemove' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function FrameRemove(frameID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("FrameRemove");
		var _internal_token:AsyncToken = _internal_operation.send(frameID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'FrameGetContent' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function FrameGetContent(frameID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("FrameGetContent");
		var _internal_token:AsyncToken = _internal_operation.send(frameID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'FrameGetMarker' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function FrameGetMarker(frameID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("FrameGetMarker");
		var _internal_token:AsyncToken = _internal_operation.send(frameID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'UserIsEmailAvailable' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function UserIsEmailAvailable(email:String) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("UserIsEmailAvailable");
		var _internal_token:AsyncToken = _internal_operation.send(email) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'UserLogin' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function UserLogin(email:String, password:String) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("UserLogin");
		var _internal_token:AsyncToken = _internal_operation.send(email,password) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'UserAdd' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function UserAdd(email:String, password:String, name:String, description:String, icon:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("UserAdd");
		var _internal_token:AsyncToken = _internal_operation.send(email,password,name,description,icon) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'UserRemove' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function UserRemove(userID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("UserRemove");
		var _internal_token:AsyncToken = _internal_operation.send(userID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'UserGetID' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function UserGetID(email:String) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("UserGetID");
		var _internal_token:AsyncToken = _internal_operation.send(email) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'UserGetEmail' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function UserGetEmail(userID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("UserGetEmail");
		var _internal_token:AsyncToken = _internal_operation.send(userID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'UserGetPassword' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function UserGetPassword(userID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("UserGetPassword");
		var _internal_token:AsyncToken = _internal_operation.send(userID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'UserGetName' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function UserGetName(userID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("UserGetName");
		var _internal_token:AsyncToken = _internal_operation.send(userID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'UserGetDescription' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function UserGetDescription(userID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("UserGetDescription");
		var _internal_token:AsyncToken = _internal_operation.send(userID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'UserGetIcon' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function UserGetIcon(userID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("UserGetIcon");
		var _internal_token:AsyncToken = _internal_operation.send(userID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'UserGetRegistrationDate' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function UserGetRegistrationDate(userID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("UserGetRegistrationDate");
		var _internal_token:AsyncToken = _internal_operation.send(userID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'UserGetGroups' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function UserGetGroups(userID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("UserGetGroups");
		var _internal_token:AsyncToken = _internal_operation.send(userID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'UserSetPassword' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function UserSetPassword(userID:int, password:String) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("UserSetPassword");
		var _internal_token:AsyncToken = _internal_operation.send(userID,password) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'UserSetName' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function UserSetName(userID:int, name:String) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("UserSetName");
		var _internal_token:AsyncToken = _internal_operation.send(userID,name) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'UserSetDescription' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function UserSetDescription(userID:int, description:String) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("UserSetDescription");
		var _internal_token:AsyncToken = _internal_operation.send(userID,description) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'UserSetIcon' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function UserSetIcon(userID:int, icon:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("UserSetIcon");
		var _internal_token:AsyncToken = _internal_operation.send(userID,icon) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'CameraIsPathAvailable' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function CameraIsPathAvailable(path:String) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("CameraIsPathAvailable");
		var _internal_token:AsyncToken = _internal_operation.send(path) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'CameraAdd' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function CameraAdd(name:String, description:String, icon:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("CameraAdd");
		var _internal_token:AsyncToken = _internal_operation.send(name,description,icon) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'CameraRemove' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function CameraRemove(cameraID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("CameraRemove");
		var _internal_token:AsyncToken = _internal_operation.send(cameraID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'CameraGetID' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function CameraGetID(path:String) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("CameraGetID");
		var _internal_token:AsyncToken = _internal_operation.send(path) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'CameraGetPath' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function CameraGetPath(cameraID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("CameraGetPath");
		var _internal_token:AsyncToken = _internal_operation.send(cameraID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'CameraGetName' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function CameraGetName(cameraID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("CameraGetName");
		var _internal_token:AsyncToken = _internal_operation.send(cameraID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'CameraGetDescription' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function CameraGetDescription(cameraID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("CameraGetDescription");
		var _internal_token:AsyncToken = _internal_operation.send(cameraID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'CameraGetIcon' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function CameraGetIcon(cameraID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("CameraGetIcon");
		var _internal_token:AsyncToken = _internal_operation.send(cameraID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'CameraGetRegistrationDate' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function CameraGetRegistrationDate(cameraID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("CameraGetRegistrationDate");
		var _internal_token:AsyncToken = _internal_operation.send(cameraID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'CameraGetGroups' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function CameraGetGroups(cameraID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("CameraGetGroups");
		var _internal_token:AsyncToken = _internal_operation.send(cameraID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'CameraGetFrames' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function CameraGetFrames(cameraID:int) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("CameraGetFrames");
		var _internal_token:AsyncToken = _internal_operation.send(cameraID) ;

		return _internal_token;
	}   

	/**
	  * This method is a generated wrapper used to call the 'CameraSetName' operation. It returns an AsyncToken whose 
	  * result property will be populated with the result of the operation when the server response is received. 
	  * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
	  * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an AsyncToken whose result property will be populated with the result of the operation when the server response is received.
	  */          
	public function CameraSetName(cameraID:int, name:String) : AsyncToken
	{
		model_internal::loadWSDLIfNecessary();
		var _internal_operation:AbstractOperation = _serviceControl.getOperation("CameraSetName");
		var _internal_token:AsyncToken = _internal_operation.send(cameraID,name) ;

		return _internal_token;
	}   

}

}
