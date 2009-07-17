/**
 * CloudObserverServiceService.as
 * This file was auto-generated from WSDL by the Apache Axis2 generator modified by Adobe
 * Any change made to this file will be overwritten when the code is re-generated.
 */
 /**
  * Usage example: to use this service from within your Flex application you have two choices:
  * Use it via Actionscript only
  * Use it via MXML tags
  * Actionscript sample code:
  * Step 1: create an instance of the service; pass it the LCDS destination string if any
  * var myService:CloudObserverService= new CloudObserverService();
  * Step 2: for the desired operation add a result handler (a function that you have already defined previously)  
  * myService.addGroupGetIDEventListener(myResultHandlingFunction);
  * Step 3: Call the operation as a method on the service. Pass the right values as arguments:
  * myService.GroupGetID(myname);
  *
  * MXML sample code:
  * First you need to map the package where the files were generated to a namespace, usually on the <mx:Application> tag, 
  * like this: xmlns:srv="generated.webservices.*"
  * Define the service and within its tags set the request wrapper for the desired operation
  * <srv:CloudObserverService id="myService">
  *   <srv:GroupGetID_request_var>
  *		<srv:GroupGetID_request name=myValue/>
  *   </srv:GroupGetID_request_var>
  * </srv:CloudObserverService>
  * Then call the operation for which you have set the request wrapper value above, like this:
  * <mx:Button id="myButton" label="Call operation" click="myService.GroupGetID_send()" />
  */
package generated.webservices
{
	import mx.rpc.AsyncToken;
	import flash.events.EventDispatcher;
	import mx.rpc.events.ResultEvent;
	import mx.rpc.events.FaultEvent;
	import flash.utils.ByteArray;
	import mx.rpc.soap.types.*;

    /**
     * Dispatches when a call to the operation GroupGetID completes with success
     * and returns some data
     * @eventType GroupGetIDResultEvent
     */
    [Event(name="GroupGetID_result", type="generated.webservices.GroupGetIDResultEvent")]
    
    /**
     * Dispatches when a call to the operation GroupGetName completes with success
     * and returns some data
     * @eventType GroupGetNameResultEvent
     */
    [Event(name="GroupGetName_result", type="generated.webservices.GroupGetNameResultEvent")]
    
    /**
     * Dispatches when a call to the operation GroupGetDescription completes with success
     * and returns some data
     * @eventType GroupGetDescriptionResultEvent
     */
    [Event(name="GroupGetDescription_result", type="generated.webservices.GroupGetDescriptionResultEvent")]
    
    /**
     * Dispatches when a call to the operation GroupGetIcon completes with success
     * and returns some data
     * @eventType GroupGetIconResultEvent
     */
    [Event(name="GroupGetIcon_result", type="generated.webservices.GroupGetIconResultEvent")]
    
    /**
     * Dispatches when a call to the operation GroupGetPrivacy completes with success
     * and returns some data
     * @eventType GroupGetPrivacyResultEvent
     */
    [Event(name="GroupGetPrivacy_result", type="generated.webservices.GroupGetPrivacyResultEvent")]
    
    /**
     * Dispatches when a call to the operation GroupGetRegistrationDate completes with success
     * and returns some data
     * @eventType GroupGetRegistrationDateResultEvent
     */
    [Event(name="GroupGetRegistrationDate_result", type="generated.webservices.GroupGetRegistrationDateResultEvent")]
    
    /**
     * Dispatches when a call to the operation GroupGetMembers completes with success
     * and returns some data
     * @eventType GroupGetMembersResultEvent
     */
    [Event(name="GroupGetMembers_result", type="generated.webservices.GroupGetMembersResultEvent")]
    
    /**
     * Dispatches when a call to the operation GroupGetCameras completes with success
     * and returns some data
     * @eventType GroupGetCamerasResultEvent
     */
    [Event(name="GroupGetCameras_result", type="generated.webservices.GroupGetCamerasResultEvent")]
    
    /**
     * Dispatches when a call to the operation GroupSetName completes with success
     * and returns some data
     * @eventType GroupSetNameResultEvent
     */
    [Event(name="GroupSetName_result", type="generated.webservices.GroupSetNameResultEvent")]
    
    /**
     * Dispatches when a call to the operation GroupSetDescription completes with success
     * and returns some data
     * @eventType GroupSetDescriptionResultEvent
     */
    [Event(name="GroupSetDescription_result", type="generated.webservices.GroupSetDescriptionResultEvent")]
    
    /**
     * Dispatches when a call to the operation GroupSetIcon completes with success
     * and returns some data
     * @eventType GroupSetIconResultEvent
     */
    [Event(name="GroupSetIcon_result", type="generated.webservices.GroupSetIconResultEvent")]
    
    /**
     * Dispatches when a call to the operation GroupSetPrivacy completes with success
     * and returns some data
     * @eventType GroupSetPrivacyResultEvent
     */
    [Event(name="GroupSetPrivacy_result", type="generated.webservices.GroupSetPrivacyResultEvent")]
    
    /**
     * Dispatches when a call to the operation GroupMemberAdd completes with success
     * and returns some data
     * @eventType GroupMemberAddResultEvent
     */
    [Event(name="GroupMemberAdd_result", type="generated.webservices.GroupMemberAddResultEvent")]
    
    /**
     * Dispatches when a call to the operation GroupMemberRemove completes with success
     * and returns some data
     * @eventType GroupMemberRemoveResultEvent
     */
    [Event(name="GroupMemberRemove_result", type="generated.webservices.GroupMemberRemoveResultEvent")]
    
    /**
     * Dispatches when a call to the operation GroupMemberGetPrivileges completes with success
     * and returns some data
     * @eventType GroupMemberGetPrivilegesResultEvent
     */
    [Event(name="GroupMemberGetPrivileges_result", type="generated.webservices.GroupMemberGetPrivilegesResultEvent")]
    
    /**
     * Dispatches when a call to the operation GroupMemberSetPrivileges completes with success
     * and returns some data
     * @eventType GroupMemberSetPrivilegesResultEvent
     */
    [Event(name="GroupMemberSetPrivileges_result", type="generated.webservices.GroupMemberSetPrivilegesResultEvent")]
    
    /**
     * Dispatches when a call to the operation GroupCameraAdd completes with success
     * and returns some data
     * @eventType GroupCameraAddResultEvent
     */
    [Event(name="GroupCameraAdd_result", type="generated.webservices.GroupCameraAddResultEvent")]
    
    /**
     * Dispatches when a call to the operation GroupCameraRemove completes with success
     * and returns some data
     * @eventType GroupCameraRemoveResultEvent
     */
    [Event(name="GroupCameraRemove_result", type="generated.webservices.GroupCameraRemoveResultEvent")]
    
    /**
     * Dispatches when a call to the operation FrameAdd completes with success
     * and returns some data
     * @eventType FrameAddResultEvent
     */
    [Event(name="FrameAdd_result", type="generated.webservices.FrameAddResultEvent")]
    
    /**
     * Dispatches when a call to the operation FrameRemove completes with success
     * and returns some data
     * @eventType FrameRemoveResultEvent
     */
    [Event(name="FrameRemove_result", type="generated.webservices.FrameRemoveResultEvent")]
    
    /**
     * Dispatches when a call to the operation FrameGetContent completes with success
     * and returns some data
     * @eventType FrameGetContentResultEvent
     */
    [Event(name="FrameGetContent_result", type="generated.webservices.FrameGetContentResultEvent")]
    
    /**
     * Dispatches when a call to the operation FrameGetMarker completes with success
     * and returns some data
     * @eventType FrameGetMarkerResultEvent
     */
    [Event(name="FrameGetMarker_result", type="generated.webservices.FrameGetMarkerResultEvent")]
    
    /**
     * Dispatches when a call to the operation UserIsEmailAvailable completes with success
     * and returns some data
     * @eventType UserIsEmailAvailableResultEvent
     */
    [Event(name="UserIsEmailAvailable_result", type="generated.webservices.UserIsEmailAvailableResultEvent")]
    
    /**
     * Dispatches when a call to the operation UserLogin completes with success
     * and returns some data
     * @eventType UserLoginResultEvent
     */
    [Event(name="UserLogin_result", type="generated.webservices.UserLoginResultEvent")]
    
    /**
     * Dispatches when a call to the operation UserAdd completes with success
     * and returns some data
     * @eventType UserAddResultEvent
     */
    [Event(name="UserAdd_result", type="generated.webservices.UserAddResultEvent")]
    
    /**
     * Dispatches when a call to the operation UserRemove completes with success
     * and returns some data
     * @eventType UserRemoveResultEvent
     */
    [Event(name="UserRemove_result", type="generated.webservices.UserRemoveResultEvent")]
    
    /**
     * Dispatches when a call to the operation UserGetID completes with success
     * and returns some data
     * @eventType UserGetIDResultEvent
     */
    [Event(name="UserGetID_result", type="generated.webservices.UserGetIDResultEvent")]
    
    /**
     * Dispatches when a call to the operation UserGetEmail completes with success
     * and returns some data
     * @eventType UserGetEmailResultEvent
     */
    [Event(name="UserGetEmail_result", type="generated.webservices.UserGetEmailResultEvent")]
    
    /**
     * Dispatches when a call to the operation UserGetPassword completes with success
     * and returns some data
     * @eventType UserGetPasswordResultEvent
     */
    [Event(name="UserGetPassword_result", type="generated.webservices.UserGetPasswordResultEvent")]
    
    /**
     * Dispatches when a call to the operation UserGetName completes with success
     * and returns some data
     * @eventType UserGetNameResultEvent
     */
    [Event(name="UserGetName_result", type="generated.webservices.UserGetNameResultEvent")]
    
    /**
     * Dispatches when a call to the operation UserGetDescription completes with success
     * and returns some data
     * @eventType UserGetDescriptionResultEvent
     */
    [Event(name="UserGetDescription_result", type="generated.webservices.UserGetDescriptionResultEvent")]
    
    /**
     * Dispatches when a call to the operation UserGetIcon completes with success
     * and returns some data
     * @eventType UserGetIconResultEvent
     */
    [Event(name="UserGetIcon_result", type="generated.webservices.UserGetIconResultEvent")]
    
    /**
     * Dispatches when a call to the operation UserGetRegistrationDate completes with success
     * and returns some data
     * @eventType UserGetRegistrationDateResultEvent
     */
    [Event(name="UserGetRegistrationDate_result", type="generated.webservices.UserGetRegistrationDateResultEvent")]
    
    /**
     * Dispatches when a call to the operation UserGetGroups completes with success
     * and returns some data
     * @eventType UserGetGroupsResultEvent
     */
    [Event(name="UserGetGroups_result", type="generated.webservices.UserGetGroupsResultEvent")]
    
    /**
     * Dispatches when a call to the operation UserSetPassword completes with success
     * and returns some data
     * @eventType UserSetPasswordResultEvent
     */
    [Event(name="UserSetPassword_result", type="generated.webservices.UserSetPasswordResultEvent")]
    
    /**
     * Dispatches when a call to the operation UserSetName completes with success
     * and returns some data
     * @eventType UserSetNameResultEvent
     */
    [Event(name="UserSetName_result", type="generated.webservices.UserSetNameResultEvent")]
    
    /**
     * Dispatches when a call to the operation UserSetDescription completes with success
     * and returns some data
     * @eventType UserSetDescriptionResultEvent
     */
    [Event(name="UserSetDescription_result", type="generated.webservices.UserSetDescriptionResultEvent")]
    
    /**
     * Dispatches when a call to the operation UserSetIcon completes with success
     * and returns some data
     * @eventType UserSetIconResultEvent
     */
    [Event(name="UserSetIcon_result", type="generated.webservices.UserSetIconResultEvent")]
    
    /**
     * Dispatches when a call to the operation CameraIsPathAvailable completes with success
     * and returns some data
     * @eventType CameraIsPathAvailableResultEvent
     */
    [Event(name="CameraIsPathAvailable_result", type="generated.webservices.CameraIsPathAvailableResultEvent")]
    
    /**
     * Dispatches when a call to the operation CameraAdd completes with success
     * and returns some data
     * @eventType CameraAddResultEvent
     */
    [Event(name="CameraAdd_result", type="generated.webservices.CameraAddResultEvent")]
    
    /**
     * Dispatches when a call to the operation CameraRemove completes with success
     * and returns some data
     * @eventType CameraRemoveResultEvent
     */
    [Event(name="CameraRemove_result", type="generated.webservices.CameraRemoveResultEvent")]
    
    /**
     * Dispatches when a call to the operation CameraGetID completes with success
     * and returns some data
     * @eventType CameraGetIDResultEvent
     */
    [Event(name="CameraGetID_result", type="generated.webservices.CameraGetIDResultEvent")]
    
    /**
     * Dispatches when a call to the operation CameraGetPath completes with success
     * and returns some data
     * @eventType CameraGetPathResultEvent
     */
    [Event(name="CameraGetPath_result", type="generated.webservices.CameraGetPathResultEvent")]
    
    /**
     * Dispatches when a call to the operation CameraGetName completes with success
     * and returns some data
     * @eventType CameraGetNameResultEvent
     */
    [Event(name="CameraGetName_result", type="generated.webservices.CameraGetNameResultEvent")]
    
    /**
     * Dispatches when a call to the operation CameraGetDescription completes with success
     * and returns some data
     * @eventType CameraGetDescriptionResultEvent
     */
    [Event(name="CameraGetDescription_result", type="generated.webservices.CameraGetDescriptionResultEvent")]
    
    /**
     * Dispatches when a call to the operation CameraGetIcon completes with success
     * and returns some data
     * @eventType CameraGetIconResultEvent
     */
    [Event(name="CameraGetIcon_result", type="generated.webservices.CameraGetIconResultEvent")]
    
    /**
     * Dispatches when a call to the operation CameraGetRegistrationDate completes with success
     * and returns some data
     * @eventType CameraGetRegistrationDateResultEvent
     */
    [Event(name="CameraGetRegistrationDate_result", type="generated.webservices.CameraGetRegistrationDateResultEvent")]
    
    /**
     * Dispatches when a call to the operation CameraGetGroups completes with success
     * and returns some data
     * @eventType CameraGetGroupsResultEvent
     */
    [Event(name="CameraGetGroups_result", type="generated.webservices.CameraGetGroupsResultEvent")]
    
    /**
     * Dispatches when a call to the operation CameraGetFrames completes with success
     * and returns some data
     * @eventType CameraGetFramesResultEvent
     */
    [Event(name="CameraGetFrames_result", type="generated.webservices.CameraGetFramesResultEvent")]
    
    /**
     * Dispatches when a call to the operation CameraSetName completes with success
     * and returns some data
     * @eventType CameraSetNameResultEvent
     */
    [Event(name="CameraSetName_result", type="generated.webservices.CameraSetNameResultEvent")]
    
    /**
     * Dispatches when a call to the operation CameraSetDescription completes with success
     * and returns some data
     * @eventType CameraSetDescriptionResultEvent
     */
    [Event(name="CameraSetDescription_result", type="generated.webservices.CameraSetDescriptionResultEvent")]
    
    /**
     * Dispatches when a call to the operation CameraSetIcon completes with success
     * and returns some data
     * @eventType CameraSetIconResultEvent
     */
    [Event(name="CameraSetIcon_result", type="generated.webservices.CameraSetIconResultEvent")]
    
    /**
     * Dispatches when a call to the operation GroupAdd completes with success
     * and returns some data
     * @eventType GroupAddResultEvent
     */
    [Event(name="GroupAdd_result", type="generated.webservices.GroupAddResultEvent")]
    
    /**
     * Dispatches when a call to the operation GroupRemove completes with success
     * and returns some data
     * @eventType GroupRemoveResultEvent
     */
    [Event(name="GroupRemove_result", type="generated.webservices.GroupRemoveResultEvent")]
    
	/**
	 * Dispatches when the operation that has been called fails. The fault event is common for all operations
	 * of the WSDL
	 * @eventType mx.rpc.events.FaultEvent
	 */
    [Event(name="fault", type="mx.rpc.events.FaultEvent")]

	public class CloudObserverService extends EventDispatcher implements ICloudObserverService
	{
    	private var _baseService:BaseCloudObserverService;
        
        /**
         * Constructor for the facade; sets the destination and create a baseService instance
         * @param The LCDS destination (if any) associated with the imported WSDL
         */  
        public function CloudObserverService(destination:String=null,rootURL:String=null)
        {
        	_baseService = new BaseCloudObserverService(destination,rootURL);
        }
        
		//stub functions for the GroupGetID operation
          

        /**
         * @see ICloudObserverService#GroupGetID()
         */
        public function groupGetID(name:String):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.groupGetID(name);
            _internal_token.addEventListener("result",_GroupGetID_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#GroupGetID_send()
		 */    
        public function groupGetID_send():AsyncToken
        {
        	return groupGetID(_GroupGetID_request.name);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _GroupGetID_request:GroupGetID_request;
		/**
		 * @see ICloudObserverService#GroupGetID_request_var
		 */
		[Bindable]
		public function get groupGetID_request_var():GroupGetID_request
		{
			return _GroupGetID_request;
		}
		
		/**
		 * @private
		 */
		public function set groupGetID_request_var(request:GroupGetID_request):void
		{
			_GroupGetID_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _groupGetID_lastResult:Number;
		[Bindable]
		/**
		 * @see ICloudObserverService#GroupGetID_lastResult
		 */	  
		public function get groupGetID_lastResult():Number
		{
			return _groupGetID_lastResult;
		}
		/**
		 * @private
		 */
		public function set groupGetID_lastResult(lastResult:Number):void
		{
			_groupGetID_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addGroupGetID()
		 */
		public function addgroupGetIDEventListener(listener:Function):void
		{
			addEventListener(GroupGetIDResultEvent.GroupGetID_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _GroupGetID_populate_results(event:ResultEvent):void
		{
			var e:GroupGetIDResultEvent = new GroupGetIDResultEvent();
		            e.result = event.result as Number;
		                       e.headers = event.headers;
		             groupGetID_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the GroupGetName operation
          

        /**
         * @see ICloudObserverService#GroupGetName()
         */
        public function groupGetName(groupID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.groupGetName(groupID);
            _internal_token.addEventListener("result",_GroupGetName_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#GroupGetName_send()
		 */    
        public function groupGetName_send():AsyncToken
        {
        	return groupGetName(_GroupGetName_request.groupID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _GroupGetName_request:GroupGetName_request;
		/**
		 * @see ICloudObserverService#GroupGetName_request_var
		 */
		[Bindable]
		public function get groupGetName_request_var():GroupGetName_request
		{
			return _GroupGetName_request;
		}
		
		/**
		 * @private
		 */
		public function set groupGetName_request_var(request:GroupGetName_request):void
		{
			_GroupGetName_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _groupGetName_lastResult:String;
		[Bindable]
		/**
		 * @see ICloudObserverService#GroupGetName_lastResult
		 */	  
		public function get groupGetName_lastResult():String
		{
			return _groupGetName_lastResult;
		}
		/**
		 * @private
		 */
		public function set groupGetName_lastResult(lastResult:String):void
		{
			_groupGetName_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addGroupGetName()
		 */
		public function addgroupGetNameEventListener(listener:Function):void
		{
			addEventListener(GroupGetNameResultEvent.GroupGetName_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _GroupGetName_populate_results(event:ResultEvent):void
		{
			var e:GroupGetNameResultEvent = new GroupGetNameResultEvent();
		            e.result = event.result as String;
		                       e.headers = event.headers;
		             groupGetName_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the GroupGetDescription operation
          

        /**
         * @see ICloudObserverService#GroupGetDescription()
         */
        public function groupGetDescription(groupID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.groupGetDescription(groupID);
            _internal_token.addEventListener("result",_GroupGetDescription_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#GroupGetDescription_send()
		 */    
        public function groupGetDescription_send():AsyncToken
        {
        	return groupGetDescription(_GroupGetDescription_request.groupID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _GroupGetDescription_request:GroupGetDescription_request;
		/**
		 * @see ICloudObserverService#GroupGetDescription_request_var
		 */
		[Bindable]
		public function get groupGetDescription_request_var():GroupGetDescription_request
		{
			return _GroupGetDescription_request;
		}
		
		/**
		 * @private
		 */
		public function set groupGetDescription_request_var(request:GroupGetDescription_request):void
		{
			_GroupGetDescription_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _groupGetDescription_lastResult:String;
		[Bindable]
		/**
		 * @see ICloudObserverService#GroupGetDescription_lastResult
		 */	  
		public function get groupGetDescription_lastResult():String
		{
			return _groupGetDescription_lastResult;
		}
		/**
		 * @private
		 */
		public function set groupGetDescription_lastResult(lastResult:String):void
		{
			_groupGetDescription_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addGroupGetDescription()
		 */
		public function addgroupGetDescriptionEventListener(listener:Function):void
		{
			addEventListener(GroupGetDescriptionResultEvent.GroupGetDescription_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _GroupGetDescription_populate_results(event:ResultEvent):void
		{
			var e:GroupGetDescriptionResultEvent = new GroupGetDescriptionResultEvent();
		            e.result = event.result as String;
		                       e.headers = event.headers;
		             groupGetDescription_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the GroupGetIcon operation
          

        /**
         * @see ICloudObserverService#GroupGetIcon()
         */
        public function groupGetIcon(groupID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.groupGetIcon(groupID);
            _internal_token.addEventListener("result",_GroupGetIcon_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#GroupGetIcon_send()
		 */    
        public function groupGetIcon_send():AsyncToken
        {
        	return groupGetIcon(_GroupGetIcon_request.groupID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _GroupGetIcon_request:GroupGetIcon_request;
		/**
		 * @see ICloudObserverService#GroupGetIcon_request_var
		 */
		[Bindable]
		public function get groupGetIcon_request_var():GroupGetIcon_request
		{
			return _GroupGetIcon_request;
		}
		
		/**
		 * @private
		 */
		public function set groupGetIcon_request_var(request:GroupGetIcon_request):void
		{
			_GroupGetIcon_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _groupGetIcon_lastResult:flash.utils.ByteArray;
		[Bindable]
		/**
		 * @see ICloudObserverService#GroupGetIcon_lastResult
		 */	  
		public function get groupGetIcon_lastResult():flash.utils.ByteArray
		{
			return _groupGetIcon_lastResult;
		}
		/**
		 * @private
		 */
		public function set groupGetIcon_lastResult(lastResult:flash.utils.ByteArray):void
		{
			_groupGetIcon_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addGroupGetIcon()
		 */
		public function addgroupGetIconEventListener(listener:Function):void
		{
			addEventListener(GroupGetIconResultEvent.GroupGetIcon_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _GroupGetIcon_populate_results(event:ResultEvent):void
		{
			var e:GroupGetIconResultEvent = new GroupGetIconResultEvent();
		            e.result = event.result as flash.utils.ByteArray;
		                       e.headers = event.headers;
		             groupGetIcon_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the GroupGetPrivacy operation
          

        /**
         * @see ICloudObserverService#GroupGetPrivacy()
         */
        public function groupGetPrivacy(groupID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.groupGetPrivacy(groupID);
            _internal_token.addEventListener("result",_GroupGetPrivacy_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#GroupGetPrivacy_send()
		 */    
        public function groupGetPrivacy_send():AsyncToken
        {
        	return groupGetPrivacy(_GroupGetPrivacy_request.groupID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _GroupGetPrivacy_request:GroupGetPrivacy_request;
		/**
		 * @see ICloudObserverService#GroupGetPrivacy_request_var
		 */
		[Bindable]
		public function get groupGetPrivacy_request_var():GroupGetPrivacy_request
		{
			return _GroupGetPrivacy_request;
		}
		
		/**
		 * @private
		 */
		public function set groupGetPrivacy_request_var(request:GroupGetPrivacy_request):void
		{
			_GroupGetPrivacy_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _groupGetPrivacy_lastResult:Number;
		[Bindable]
		/**
		 * @see ICloudObserverService#GroupGetPrivacy_lastResult
		 */	  
		public function get groupGetPrivacy_lastResult():Number
		{
			return _groupGetPrivacy_lastResult;
		}
		/**
		 * @private
		 */
		public function set groupGetPrivacy_lastResult(lastResult:Number):void
		{
			_groupGetPrivacy_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addGroupGetPrivacy()
		 */
		public function addgroupGetPrivacyEventListener(listener:Function):void
		{
			addEventListener(GroupGetPrivacyResultEvent.GroupGetPrivacy_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _GroupGetPrivacy_populate_results(event:ResultEvent):void
		{
			var e:GroupGetPrivacyResultEvent = new GroupGetPrivacyResultEvent();
		            e.result = event.result as Number;
		                       e.headers = event.headers;
		             groupGetPrivacy_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the GroupGetRegistrationDate operation
          

        /**
         * @see ICloudObserverService#GroupGetRegistrationDate()
         */
        public function groupGetRegistrationDate(groupID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.groupGetRegistrationDate(groupID);
            _internal_token.addEventListener("result",_GroupGetRegistrationDate_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#GroupGetRegistrationDate_send()
		 */    
        public function groupGetRegistrationDate_send():AsyncToken
        {
        	return groupGetRegistrationDate(_GroupGetRegistrationDate_request.groupID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _GroupGetRegistrationDate_request:GroupGetRegistrationDate_request;
		/**
		 * @see ICloudObserverService#GroupGetRegistrationDate_request_var
		 */
		[Bindable]
		public function get groupGetRegistrationDate_request_var():GroupGetRegistrationDate_request
		{
			return _GroupGetRegistrationDate_request;
		}
		
		/**
		 * @private
		 */
		public function set groupGetRegistrationDate_request_var(request:GroupGetRegistrationDate_request):void
		{
			_GroupGetRegistrationDate_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _groupGetRegistrationDate_lastResult:Date;
		[Bindable]
		/**
		 * @see ICloudObserverService#GroupGetRegistrationDate_lastResult
		 */	  
		public function get groupGetRegistrationDate_lastResult():Date
		{
			return _groupGetRegistrationDate_lastResult;
		}
		/**
		 * @private
		 */
		public function set groupGetRegistrationDate_lastResult(lastResult:Date):void
		{
			_groupGetRegistrationDate_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addGroupGetRegistrationDate()
		 */
		public function addgroupGetRegistrationDateEventListener(listener:Function):void
		{
			addEventListener(GroupGetRegistrationDateResultEvent.GroupGetRegistrationDate_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _GroupGetRegistrationDate_populate_results(event:ResultEvent):void
		{
			var e:GroupGetRegistrationDateResultEvent = new GroupGetRegistrationDateResultEvent();
		            e.result = event.result as Date;
		                       e.headers = event.headers;
		             groupGetRegistrationDate_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the GroupGetMembers operation
          

        /**
         * @see ICloudObserverService#GroupGetMembers()
         */
        public function groupGetMembers(groupID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.groupGetMembers(groupID);
            _internal_token.addEventListener("result",_GroupGetMembers_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#GroupGetMembers_send()
		 */    
        public function groupGetMembers_send():AsyncToken
        {
        	return groupGetMembers(_GroupGetMembers_request.groupID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _GroupGetMembers_request:GroupGetMembers_request;
		/**
		 * @see ICloudObserverService#GroupGetMembers_request_var
		 */
		[Bindable]
		public function get groupGetMembers_request_var():GroupGetMembers_request
		{
			return _GroupGetMembers_request;
		}
		
		/**
		 * @private
		 */
		public function set groupGetMembers_request_var(request:GroupGetMembers_request):void
		{
			_GroupGetMembers_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _groupGetMembers_lastResult:ArrayOfint;
		[Bindable]
		/**
		 * @see ICloudObserverService#GroupGetMembers_lastResult
		 */	  
		public function get groupGetMembers_lastResult():ArrayOfint
		{
			return _groupGetMembers_lastResult;
		}
		/**
		 * @private
		 */
		public function set groupGetMembers_lastResult(lastResult:ArrayOfint):void
		{
			_groupGetMembers_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addGroupGetMembers()
		 */
		public function addgroupGetMembersEventListener(listener:Function):void
		{
			addEventListener(GroupGetMembersResultEvent.GroupGetMembers_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _GroupGetMembers_populate_results(event:ResultEvent):void
		{
			var e:GroupGetMembersResultEvent = new GroupGetMembersResultEvent();
		            e.result = event.result as ArrayOfint;
		                       e.headers = event.headers;
		             groupGetMembers_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the GroupGetCameras operation
          

        /**
         * @see ICloudObserverService#GroupGetCameras()
         */
        public function groupGetCameras(groupID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.groupGetCameras(groupID);
            _internal_token.addEventListener("result",_GroupGetCameras_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#GroupGetCameras_send()
		 */    
        public function groupGetCameras_send():AsyncToken
        {
        	return groupGetCameras(_GroupGetCameras_request.groupID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _GroupGetCameras_request:GroupGetCameras_request;
		/**
		 * @see ICloudObserverService#GroupGetCameras_request_var
		 */
		[Bindable]
		public function get groupGetCameras_request_var():GroupGetCameras_request
		{
			return _GroupGetCameras_request;
		}
		
		/**
		 * @private
		 */
		public function set groupGetCameras_request_var(request:GroupGetCameras_request):void
		{
			_GroupGetCameras_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _groupGetCameras_lastResult:ArrayOfint;
		[Bindable]
		/**
		 * @see ICloudObserverService#GroupGetCameras_lastResult
		 */	  
		public function get groupGetCameras_lastResult():ArrayOfint
		{
			return _groupGetCameras_lastResult;
		}
		/**
		 * @private
		 */
		public function set groupGetCameras_lastResult(lastResult:ArrayOfint):void
		{
			_groupGetCameras_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addGroupGetCameras()
		 */
		public function addgroupGetCamerasEventListener(listener:Function):void
		{
			addEventListener(GroupGetCamerasResultEvent.GroupGetCameras_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _GroupGetCameras_populate_results(event:ResultEvent):void
		{
			var e:GroupGetCamerasResultEvent = new GroupGetCamerasResultEvent();
		            e.result = event.result as ArrayOfint;
		                       e.headers = event.headers;
		             groupGetCameras_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the GroupSetName operation
          

        /**
         * @see ICloudObserverService#GroupSetName()
         */
        public function groupSetName(groupID:Number,name:String):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.groupSetName(groupID,name);
            _internal_token.addEventListener("result",_GroupSetName_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#GroupSetName_send()
		 */    
        public function groupSetName_send():AsyncToken
        {
        	return groupSetName(_GroupSetName_request.groupID,_GroupSetName_request.name);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _GroupSetName_request:GroupSetName_request;
		/**
		 * @see ICloudObserverService#GroupSetName_request_var
		 */
		[Bindable]
		public function get groupSetName_request_var():GroupSetName_request
		{
			return _GroupSetName_request;
		}
		
		/**
		 * @private
		 */
		public function set groupSetName_request_var(request:GroupSetName_request):void
		{
			_GroupSetName_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _groupSetName_lastResult:Object;
		[Bindable]
		/**
		 * @see ICloudObserverService#GroupSetName_lastResult
		 */	  
		public function get groupSetName_lastResult():Object
		{
			return _groupSetName_lastResult;
		}
		/**
		 * @private
		 */
		public function set groupSetName_lastResult(lastResult:Object):void
		{
			_groupSetName_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addGroupSetName()
		 */
		public function addgroupSetNameEventListener(listener:Function):void
		{
			addEventListener(GroupSetNameResultEvent.GroupSetName_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _GroupSetName_populate_results(event:ResultEvent):void
		{
			var e:GroupSetNameResultEvent = new GroupSetNameResultEvent();
		            e.result = event.result as Object;
		                       e.headers = event.headers;
		             groupSetName_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the GroupSetDescription operation
          

        /**
         * @see ICloudObserverService#GroupSetDescription()
         */
        public function groupSetDescription(groupID:Number,description:String):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.groupSetDescription(groupID,description);
            _internal_token.addEventListener("result",_GroupSetDescription_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#GroupSetDescription_send()
		 */    
        public function groupSetDescription_send():AsyncToken
        {
        	return groupSetDescription(_GroupSetDescription_request.groupID,_GroupSetDescription_request.description);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _GroupSetDescription_request:GroupSetDescription_request;
		/**
		 * @see ICloudObserverService#GroupSetDescription_request_var
		 */
		[Bindable]
		public function get groupSetDescription_request_var():GroupSetDescription_request
		{
			return _GroupSetDescription_request;
		}
		
		/**
		 * @private
		 */
		public function set groupSetDescription_request_var(request:GroupSetDescription_request):void
		{
			_GroupSetDescription_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _groupSetDescription_lastResult:Object;
		[Bindable]
		/**
		 * @see ICloudObserverService#GroupSetDescription_lastResult
		 */	  
		public function get groupSetDescription_lastResult():Object
		{
			return _groupSetDescription_lastResult;
		}
		/**
		 * @private
		 */
		public function set groupSetDescription_lastResult(lastResult:Object):void
		{
			_groupSetDescription_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addGroupSetDescription()
		 */
		public function addgroupSetDescriptionEventListener(listener:Function):void
		{
			addEventListener(GroupSetDescriptionResultEvent.GroupSetDescription_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _GroupSetDescription_populate_results(event:ResultEvent):void
		{
			var e:GroupSetDescriptionResultEvent = new GroupSetDescriptionResultEvent();
		            e.result = event.result as Object;
		                       e.headers = event.headers;
		             groupSetDescription_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the GroupSetIcon operation
          

        /**
         * @see ICloudObserverService#GroupSetIcon()
         */
        public function groupSetIcon(groupID:Number,icon:flash.utils.ByteArray):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.groupSetIcon(groupID,icon);
            _internal_token.addEventListener("result",_GroupSetIcon_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#GroupSetIcon_send()
		 */    
        public function groupSetIcon_send():AsyncToken
        {
        	return groupSetIcon(_GroupSetIcon_request.groupID,_GroupSetIcon_request.icon);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _GroupSetIcon_request:GroupSetIcon_request;
		/**
		 * @see ICloudObserverService#GroupSetIcon_request_var
		 */
		[Bindable]
		public function get groupSetIcon_request_var():GroupSetIcon_request
		{
			return _GroupSetIcon_request;
		}
		
		/**
		 * @private
		 */
		public function set groupSetIcon_request_var(request:GroupSetIcon_request):void
		{
			_GroupSetIcon_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _groupSetIcon_lastResult:Object;
		[Bindable]
		/**
		 * @see ICloudObserverService#GroupSetIcon_lastResult
		 */	  
		public function get groupSetIcon_lastResult():Object
		{
			return _groupSetIcon_lastResult;
		}
		/**
		 * @private
		 */
		public function set groupSetIcon_lastResult(lastResult:Object):void
		{
			_groupSetIcon_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addGroupSetIcon()
		 */
		public function addgroupSetIconEventListener(listener:Function):void
		{
			addEventListener(GroupSetIconResultEvent.GroupSetIcon_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _GroupSetIcon_populate_results(event:ResultEvent):void
		{
			var e:GroupSetIconResultEvent = new GroupSetIconResultEvent();
		            e.result = event.result as Object;
		                       e.headers = event.headers;
		             groupSetIcon_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the GroupSetPrivacy operation
          

        /**
         * @see ICloudObserverService#GroupSetPrivacy()
         */
        public function groupSetPrivacy(groupID:Number,privacy:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.groupSetPrivacy(groupID,privacy);
            _internal_token.addEventListener("result",_GroupSetPrivacy_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#GroupSetPrivacy_send()
		 */    
        public function groupSetPrivacy_send():AsyncToken
        {
        	return groupSetPrivacy(_GroupSetPrivacy_request.groupID,_GroupSetPrivacy_request.privacy);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _GroupSetPrivacy_request:GroupSetPrivacy_request;
		/**
		 * @see ICloudObserverService#GroupSetPrivacy_request_var
		 */
		[Bindable]
		public function get groupSetPrivacy_request_var():GroupSetPrivacy_request
		{
			return _GroupSetPrivacy_request;
		}
		
		/**
		 * @private
		 */
		public function set groupSetPrivacy_request_var(request:GroupSetPrivacy_request):void
		{
			_GroupSetPrivacy_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _groupSetPrivacy_lastResult:Object;
		[Bindable]
		/**
		 * @see ICloudObserverService#GroupSetPrivacy_lastResult
		 */	  
		public function get groupSetPrivacy_lastResult():Object
		{
			return _groupSetPrivacy_lastResult;
		}
		/**
		 * @private
		 */
		public function set groupSetPrivacy_lastResult(lastResult:Object):void
		{
			_groupSetPrivacy_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addGroupSetPrivacy()
		 */
		public function addgroupSetPrivacyEventListener(listener:Function):void
		{
			addEventListener(GroupSetPrivacyResultEvent.GroupSetPrivacy_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _GroupSetPrivacy_populate_results(event:ResultEvent):void
		{
			var e:GroupSetPrivacyResultEvent = new GroupSetPrivacyResultEvent();
		            e.result = event.result as Object;
		                       e.headers = event.headers;
		             groupSetPrivacy_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the GroupMemberAdd operation
          

        /**
         * @see ICloudObserverService#GroupMemberAdd()
         */
        public function groupMemberAdd(userID:Number,groupID:Number,privileges:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.groupMemberAdd(userID,groupID,privileges);
            _internal_token.addEventListener("result",_GroupMemberAdd_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#GroupMemberAdd_send()
		 */    
        public function groupMemberAdd_send():AsyncToken
        {
        	return groupMemberAdd(_GroupMemberAdd_request.userID,_GroupMemberAdd_request.groupID,_GroupMemberAdd_request.privileges);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _GroupMemberAdd_request:GroupMemberAdd_request;
		/**
		 * @see ICloudObserverService#GroupMemberAdd_request_var
		 */
		[Bindable]
		public function get groupMemberAdd_request_var():GroupMemberAdd_request
		{
			return _GroupMemberAdd_request;
		}
		
		/**
		 * @private
		 */
		public function set groupMemberAdd_request_var(request:GroupMemberAdd_request):void
		{
			_GroupMemberAdd_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _groupMemberAdd_lastResult:Object;
		[Bindable]
		/**
		 * @see ICloudObserverService#GroupMemberAdd_lastResult
		 */	  
		public function get groupMemberAdd_lastResult():Object
		{
			return _groupMemberAdd_lastResult;
		}
		/**
		 * @private
		 */
		public function set groupMemberAdd_lastResult(lastResult:Object):void
		{
			_groupMemberAdd_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addGroupMemberAdd()
		 */
		public function addgroupMemberAddEventListener(listener:Function):void
		{
			addEventListener(GroupMemberAddResultEvent.GroupMemberAdd_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _GroupMemberAdd_populate_results(event:ResultEvent):void
		{
			var e:GroupMemberAddResultEvent = new GroupMemberAddResultEvent();
		            e.result = event.result as Object;
		                       e.headers = event.headers;
		             groupMemberAdd_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the GroupMemberRemove operation
          

        /**
         * @see ICloudObserverService#GroupMemberRemove()
         */
        public function groupMemberRemove(userID:Number,groupID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.groupMemberRemove(userID,groupID);
            _internal_token.addEventListener("result",_GroupMemberRemove_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#GroupMemberRemove_send()
		 */    
        public function groupMemberRemove_send():AsyncToken
        {
        	return groupMemberRemove(_GroupMemberRemove_request.userID,_GroupMemberRemove_request.groupID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _GroupMemberRemove_request:GroupMemberRemove_request;
		/**
		 * @see ICloudObserverService#GroupMemberRemove_request_var
		 */
		[Bindable]
		public function get groupMemberRemove_request_var():GroupMemberRemove_request
		{
			return _GroupMemberRemove_request;
		}
		
		/**
		 * @private
		 */
		public function set groupMemberRemove_request_var(request:GroupMemberRemove_request):void
		{
			_GroupMemberRemove_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _groupMemberRemove_lastResult:Object;
		[Bindable]
		/**
		 * @see ICloudObserverService#GroupMemberRemove_lastResult
		 */	  
		public function get groupMemberRemove_lastResult():Object
		{
			return _groupMemberRemove_lastResult;
		}
		/**
		 * @private
		 */
		public function set groupMemberRemove_lastResult(lastResult:Object):void
		{
			_groupMemberRemove_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addGroupMemberRemove()
		 */
		public function addgroupMemberRemoveEventListener(listener:Function):void
		{
			addEventListener(GroupMemberRemoveResultEvent.GroupMemberRemove_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _GroupMemberRemove_populate_results(event:ResultEvent):void
		{
			var e:GroupMemberRemoveResultEvent = new GroupMemberRemoveResultEvent();
		            e.result = event.result as Object;
		                       e.headers = event.headers;
		             groupMemberRemove_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the GroupMemberGetPrivileges operation
          

        /**
         * @see ICloudObserverService#GroupMemberGetPrivileges()
         */
        public function groupMemberGetPrivileges(userID:Number,groupID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.groupMemberGetPrivileges(userID,groupID);
            _internal_token.addEventListener("result",_GroupMemberGetPrivileges_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#GroupMemberGetPrivileges_send()
		 */    
        public function groupMemberGetPrivileges_send():AsyncToken
        {
        	return groupMemberGetPrivileges(_GroupMemberGetPrivileges_request.userID,_GroupMemberGetPrivileges_request.groupID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _GroupMemberGetPrivileges_request:GroupMemberGetPrivileges_request;
		/**
		 * @see ICloudObserverService#GroupMemberGetPrivileges_request_var
		 */
		[Bindable]
		public function get groupMemberGetPrivileges_request_var():GroupMemberGetPrivileges_request
		{
			return _GroupMemberGetPrivileges_request;
		}
		
		/**
		 * @private
		 */
		public function set groupMemberGetPrivileges_request_var(request:GroupMemberGetPrivileges_request):void
		{
			_GroupMemberGetPrivileges_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _groupMemberGetPrivileges_lastResult:Number;
		[Bindable]
		/**
		 * @see ICloudObserverService#GroupMemberGetPrivileges_lastResult
		 */	  
		public function get groupMemberGetPrivileges_lastResult():Number
		{
			return _groupMemberGetPrivileges_lastResult;
		}
		/**
		 * @private
		 */
		public function set groupMemberGetPrivileges_lastResult(lastResult:Number):void
		{
			_groupMemberGetPrivileges_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addGroupMemberGetPrivileges()
		 */
		public function addgroupMemberGetPrivilegesEventListener(listener:Function):void
		{
			addEventListener(GroupMemberGetPrivilegesResultEvent.GroupMemberGetPrivileges_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _GroupMemberGetPrivileges_populate_results(event:ResultEvent):void
		{
			var e:GroupMemberGetPrivilegesResultEvent = new GroupMemberGetPrivilegesResultEvent();
		            e.result = event.result as Number;
		                       e.headers = event.headers;
		             groupMemberGetPrivileges_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the GroupMemberSetPrivileges operation
          

        /**
         * @see ICloudObserverService#GroupMemberSetPrivileges()
         */
        public function groupMemberSetPrivileges(userID:Number,groupID:Number,privileges:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.groupMemberSetPrivileges(userID,groupID,privileges);
            _internal_token.addEventListener("result",_GroupMemberSetPrivileges_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#GroupMemberSetPrivileges_send()
		 */    
        public function groupMemberSetPrivileges_send():AsyncToken
        {
        	return groupMemberSetPrivileges(_GroupMemberSetPrivileges_request.userID,_GroupMemberSetPrivileges_request.groupID,_GroupMemberSetPrivileges_request.privileges);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _GroupMemberSetPrivileges_request:GroupMemberSetPrivileges_request;
		/**
		 * @see ICloudObserverService#GroupMemberSetPrivileges_request_var
		 */
		[Bindable]
		public function get groupMemberSetPrivileges_request_var():GroupMemberSetPrivileges_request
		{
			return _GroupMemberSetPrivileges_request;
		}
		
		/**
		 * @private
		 */
		public function set groupMemberSetPrivileges_request_var(request:GroupMemberSetPrivileges_request):void
		{
			_GroupMemberSetPrivileges_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _groupMemberSetPrivileges_lastResult:Object;
		[Bindable]
		/**
		 * @see ICloudObserverService#GroupMemberSetPrivileges_lastResult
		 */	  
		public function get groupMemberSetPrivileges_lastResult():Object
		{
			return _groupMemberSetPrivileges_lastResult;
		}
		/**
		 * @private
		 */
		public function set groupMemberSetPrivileges_lastResult(lastResult:Object):void
		{
			_groupMemberSetPrivileges_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addGroupMemberSetPrivileges()
		 */
		public function addgroupMemberSetPrivilegesEventListener(listener:Function):void
		{
			addEventListener(GroupMemberSetPrivilegesResultEvent.GroupMemberSetPrivileges_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _GroupMemberSetPrivileges_populate_results(event:ResultEvent):void
		{
			var e:GroupMemberSetPrivilegesResultEvent = new GroupMemberSetPrivilegesResultEvent();
		            e.result = event.result as Object;
		                       e.headers = event.headers;
		             groupMemberSetPrivileges_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the GroupCameraAdd operation
          

        /**
         * @see ICloudObserverService#GroupCameraAdd()
         */
        public function groupCameraAdd(cameraID:Number,groupID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.groupCameraAdd(cameraID,groupID);
            _internal_token.addEventListener("result",_GroupCameraAdd_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#GroupCameraAdd_send()
		 */    
        public function groupCameraAdd_send():AsyncToken
        {
        	return groupCameraAdd(_GroupCameraAdd_request.cameraID,_GroupCameraAdd_request.groupID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _GroupCameraAdd_request:GroupCameraAdd_request;
		/**
		 * @see ICloudObserverService#GroupCameraAdd_request_var
		 */
		[Bindable]
		public function get groupCameraAdd_request_var():GroupCameraAdd_request
		{
			return _GroupCameraAdd_request;
		}
		
		/**
		 * @private
		 */
		public function set groupCameraAdd_request_var(request:GroupCameraAdd_request):void
		{
			_GroupCameraAdd_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _groupCameraAdd_lastResult:Object;
		[Bindable]
		/**
		 * @see ICloudObserverService#GroupCameraAdd_lastResult
		 */	  
		public function get groupCameraAdd_lastResult():Object
		{
			return _groupCameraAdd_lastResult;
		}
		/**
		 * @private
		 */
		public function set groupCameraAdd_lastResult(lastResult:Object):void
		{
			_groupCameraAdd_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addGroupCameraAdd()
		 */
		public function addgroupCameraAddEventListener(listener:Function):void
		{
			addEventListener(GroupCameraAddResultEvent.GroupCameraAdd_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _GroupCameraAdd_populate_results(event:ResultEvent):void
		{
			var e:GroupCameraAddResultEvent = new GroupCameraAddResultEvent();
		            e.result = event.result as Object;
		                       e.headers = event.headers;
		             groupCameraAdd_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the GroupCameraRemove operation
          

        /**
         * @see ICloudObserverService#GroupCameraRemove()
         */
        public function groupCameraRemove(cameraID:Number,groupID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.groupCameraRemove(cameraID,groupID);
            _internal_token.addEventListener("result",_GroupCameraRemove_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#GroupCameraRemove_send()
		 */    
        public function groupCameraRemove_send():AsyncToken
        {
        	return groupCameraRemove(_GroupCameraRemove_request.cameraID,_GroupCameraRemove_request.groupID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _GroupCameraRemove_request:GroupCameraRemove_request;
		/**
		 * @see ICloudObserverService#GroupCameraRemove_request_var
		 */
		[Bindable]
		public function get groupCameraRemove_request_var():GroupCameraRemove_request
		{
			return _GroupCameraRemove_request;
		}
		
		/**
		 * @private
		 */
		public function set groupCameraRemove_request_var(request:GroupCameraRemove_request):void
		{
			_GroupCameraRemove_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _groupCameraRemove_lastResult:Object;
		[Bindable]
		/**
		 * @see ICloudObserverService#GroupCameraRemove_lastResult
		 */	  
		public function get groupCameraRemove_lastResult():Object
		{
			return _groupCameraRemove_lastResult;
		}
		/**
		 * @private
		 */
		public function set groupCameraRemove_lastResult(lastResult:Object):void
		{
			_groupCameraRemove_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addGroupCameraRemove()
		 */
		public function addgroupCameraRemoveEventListener(listener:Function):void
		{
			addEventListener(GroupCameraRemoveResultEvent.GroupCameraRemove_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _GroupCameraRemove_populate_results(event:ResultEvent):void
		{
			var e:GroupCameraRemoveResultEvent = new GroupCameraRemoveResultEvent();
		            e.result = event.result as Object;
		                       e.headers = event.headers;
		             groupCameraRemove_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the FrameAdd operation
          

        /**
         * @see ICloudObserverService#FrameAdd()
         */
        public function frameAdd(cameraID:Number,content:flash.utils.ByteArray,marker:String):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.frameAdd(cameraID,content,marker);
            _internal_token.addEventListener("result",_FrameAdd_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#FrameAdd_send()
		 */    
        public function frameAdd_send():AsyncToken
        {
        	return frameAdd(_FrameAdd_request.cameraID,_FrameAdd_request.content,_FrameAdd_request.marker);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _FrameAdd_request:FrameAdd_request;
		/**
		 * @see ICloudObserverService#FrameAdd_request_var
		 */
		[Bindable]
		public function get frameAdd_request_var():FrameAdd_request
		{
			return _FrameAdd_request;
		}
		
		/**
		 * @private
		 */
		public function set frameAdd_request_var(request:FrameAdd_request):void
		{
			_FrameAdd_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _frameAdd_lastResult:Number;
		[Bindable]
		/**
		 * @see ICloudObserverService#FrameAdd_lastResult
		 */	  
		public function get frameAdd_lastResult():Number
		{
			return _frameAdd_lastResult;
		}
		/**
		 * @private
		 */
		public function set frameAdd_lastResult(lastResult:Number):void
		{
			_frameAdd_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addFrameAdd()
		 */
		public function addframeAddEventListener(listener:Function):void
		{
			addEventListener(FrameAddResultEvent.FrameAdd_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _FrameAdd_populate_results(event:ResultEvent):void
		{
			var e:FrameAddResultEvent = new FrameAddResultEvent();
		            e.result = event.result as Number;
		                       e.headers = event.headers;
		             frameAdd_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the FrameRemove operation
          

        /**
         * @see ICloudObserverService#FrameRemove()
         */
        public function frameRemove(frameID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.frameRemove(frameID);
            _internal_token.addEventListener("result",_FrameRemove_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#FrameRemove_send()
		 */    
        public function frameRemove_send():AsyncToken
        {
        	return frameRemove(_FrameRemove_request.frameID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _FrameRemove_request:FrameRemove_request;
		/**
		 * @see ICloudObserverService#FrameRemove_request_var
		 */
		[Bindable]
		public function get frameRemove_request_var():FrameRemove_request
		{
			return _FrameRemove_request;
		}
		
		/**
		 * @private
		 */
		public function set frameRemove_request_var(request:FrameRemove_request):void
		{
			_FrameRemove_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _frameRemove_lastResult:Object;
		[Bindable]
		/**
		 * @see ICloudObserverService#FrameRemove_lastResult
		 */	  
		public function get frameRemove_lastResult():Object
		{
			return _frameRemove_lastResult;
		}
		/**
		 * @private
		 */
		public function set frameRemove_lastResult(lastResult:Object):void
		{
			_frameRemove_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addFrameRemove()
		 */
		public function addframeRemoveEventListener(listener:Function):void
		{
			addEventListener(FrameRemoveResultEvent.FrameRemove_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _FrameRemove_populate_results(event:ResultEvent):void
		{
			var e:FrameRemoveResultEvent = new FrameRemoveResultEvent();
		            e.result = event.result as Object;
		                       e.headers = event.headers;
		             frameRemove_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the FrameGetContent operation
          

        /**
         * @see ICloudObserverService#FrameGetContent()
         */
        public function frameGetContent(frameID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.frameGetContent(frameID);
            _internal_token.addEventListener("result",_FrameGetContent_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#FrameGetContent_send()
		 */    
        public function frameGetContent_send():AsyncToken
        {
        	return frameGetContent(_FrameGetContent_request.frameID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _FrameGetContent_request:FrameGetContent_request;
		/**
		 * @see ICloudObserverService#FrameGetContent_request_var
		 */
		[Bindable]
		public function get frameGetContent_request_var():FrameGetContent_request
		{
			return _FrameGetContent_request;
		}
		
		/**
		 * @private
		 */
		public function set frameGetContent_request_var(request:FrameGetContent_request):void
		{
			_FrameGetContent_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _frameGetContent_lastResult:flash.utils.ByteArray;
		[Bindable]
		/**
		 * @see ICloudObserverService#FrameGetContent_lastResult
		 */	  
		public function get frameGetContent_lastResult():flash.utils.ByteArray
		{
			return _frameGetContent_lastResult;
		}
		/**
		 * @private
		 */
		public function set frameGetContent_lastResult(lastResult:flash.utils.ByteArray):void
		{
			_frameGetContent_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addFrameGetContent()
		 */
		public function addframeGetContentEventListener(listener:Function):void
		{
			addEventListener(FrameGetContentResultEvent.FrameGetContent_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _FrameGetContent_populate_results(event:ResultEvent):void
		{
			var e:FrameGetContentResultEvent = new FrameGetContentResultEvent();
		            e.result = event.result as flash.utils.ByteArray;
		                       e.headers = event.headers;
		             frameGetContent_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the FrameGetMarker operation
          

        /**
         * @see ICloudObserverService#FrameGetMarker()
         */
        public function frameGetMarker(frameID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.frameGetMarker(frameID);
            _internal_token.addEventListener("result",_FrameGetMarker_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#FrameGetMarker_send()
		 */    
        public function frameGetMarker_send():AsyncToken
        {
        	return frameGetMarker(_FrameGetMarker_request.frameID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _FrameGetMarker_request:FrameGetMarker_request;
		/**
		 * @see ICloudObserverService#FrameGetMarker_request_var
		 */
		[Bindable]
		public function get frameGetMarker_request_var():FrameGetMarker_request
		{
			return _FrameGetMarker_request;
		}
		
		/**
		 * @private
		 */
		public function set frameGetMarker_request_var(request:FrameGetMarker_request):void
		{
			_FrameGetMarker_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _frameGetMarker_lastResult:String;
		[Bindable]
		/**
		 * @see ICloudObserverService#FrameGetMarker_lastResult
		 */	  
		public function get frameGetMarker_lastResult():String
		{
			return _frameGetMarker_lastResult;
		}
		/**
		 * @private
		 */
		public function set frameGetMarker_lastResult(lastResult:String):void
		{
			_frameGetMarker_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addFrameGetMarker()
		 */
		public function addframeGetMarkerEventListener(listener:Function):void
		{
			addEventListener(FrameGetMarkerResultEvent.FrameGetMarker_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _FrameGetMarker_populate_results(event:ResultEvent):void
		{
			var e:FrameGetMarkerResultEvent = new FrameGetMarkerResultEvent();
		            e.result = event.result as String;
		                       e.headers = event.headers;
		             frameGetMarker_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the UserIsEmailAvailable operation
          

        /**
         * @see ICloudObserverService#UserIsEmailAvailable()
         */
        public function userIsEmailAvailable(email:String):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.userIsEmailAvailable(email);
            _internal_token.addEventListener("result",_UserIsEmailAvailable_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#UserIsEmailAvailable_send()
		 */    
        public function userIsEmailAvailable_send():AsyncToken
        {
        	return userIsEmailAvailable(_UserIsEmailAvailable_request.email);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _UserIsEmailAvailable_request:UserIsEmailAvailable_request;
		/**
		 * @see ICloudObserverService#UserIsEmailAvailable_request_var
		 */
		[Bindable]
		public function get userIsEmailAvailable_request_var():UserIsEmailAvailable_request
		{
			return _UserIsEmailAvailable_request;
		}
		
		/**
		 * @private
		 */
		public function set userIsEmailAvailable_request_var(request:UserIsEmailAvailable_request):void
		{
			_UserIsEmailAvailable_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _userIsEmailAvailable_lastResult:Boolean;
		[Bindable]
		/**
		 * @see ICloudObserverService#UserIsEmailAvailable_lastResult
		 */	  
		public function get userIsEmailAvailable_lastResult():Boolean
		{
			return _userIsEmailAvailable_lastResult;
		}
		/**
		 * @private
		 */
		public function set userIsEmailAvailable_lastResult(lastResult:Boolean):void
		{
			_userIsEmailAvailable_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addUserIsEmailAvailable()
		 */
		public function adduserIsEmailAvailableEventListener(listener:Function):void
		{
			addEventListener(UserIsEmailAvailableResultEvent.UserIsEmailAvailable_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _UserIsEmailAvailable_populate_results(event:ResultEvent):void
		{
			var e:UserIsEmailAvailableResultEvent = new UserIsEmailAvailableResultEvent();
		            e.result = event.result as Boolean;
		                       e.headers = event.headers;
		             userIsEmailAvailable_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the UserLogin operation
          

        /**
         * @see ICloudObserverService#UserLogin()
         */
        public function userLogin(email:String,password:String):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.userLogin(email,password);
            _internal_token.addEventListener("result",_UserLogin_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#UserLogin_send()
		 */    
        public function userLogin_send():AsyncToken
        {
        	return userLogin(_UserLogin_request.email,_UserLogin_request.password);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _UserLogin_request:UserLogin_request;
		/**
		 * @see ICloudObserverService#UserLogin_request_var
		 */
		[Bindable]
		public function get userLogin_request_var():UserLogin_request
		{
			return _UserLogin_request;
		}
		
		/**
		 * @private
		 */
		public function set userLogin_request_var(request:UserLogin_request):void
		{
			_UserLogin_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _userLogin_lastResult:Boolean;
		[Bindable]
		/**
		 * @see ICloudObserverService#UserLogin_lastResult
		 */	  
		public function get userLogin_lastResult():Boolean
		{
			return _userLogin_lastResult;
		}
		/**
		 * @private
		 */
		public function set userLogin_lastResult(lastResult:Boolean):void
		{
			_userLogin_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addUserLogin()
		 */
		public function adduserLoginEventListener(listener:Function):void
		{
			addEventListener(UserLoginResultEvent.UserLogin_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _UserLogin_populate_results(event:ResultEvent):void
		{
			var e:UserLoginResultEvent = new UserLoginResultEvent();
		            e.result = event.result as Boolean;
		                       e.headers = event.headers;
		             userLogin_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the UserAdd operation
          

        /**
         * @see ICloudObserverService#UserAdd()
         */
        public function userAdd(email:String,password:String,name:String,description:String,icon:flash.utils.ByteArray):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.userAdd(email,password,name,description,icon);
            _internal_token.addEventListener("result",_UserAdd_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#UserAdd_send()
		 */    
        public function userAdd_send():AsyncToken
        {
        	return userAdd(_UserAdd_request.email,_UserAdd_request.password,_UserAdd_request.name,_UserAdd_request.description,_UserAdd_request.icon);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _UserAdd_request:UserAdd_request;
		/**
		 * @see ICloudObserverService#UserAdd_request_var
		 */
		[Bindable]
		public function get userAdd_request_var():UserAdd_request
		{
			return _UserAdd_request;
		}
		
		/**
		 * @private
		 */
		public function set userAdd_request_var(request:UserAdd_request):void
		{
			_UserAdd_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _userAdd_lastResult:Number;
		[Bindable]
		/**
		 * @see ICloudObserverService#UserAdd_lastResult
		 */	  
		public function get userAdd_lastResult():Number
		{
			return _userAdd_lastResult;
		}
		/**
		 * @private
		 */
		public function set userAdd_lastResult(lastResult:Number):void
		{
			_userAdd_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addUserAdd()
		 */
		public function adduserAddEventListener(listener:Function):void
		{
			addEventListener(UserAddResultEvent.UserAdd_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _UserAdd_populate_results(event:ResultEvent):void
		{
			var e:UserAddResultEvent = new UserAddResultEvent();
		            e.result = event.result as Number;
		                       e.headers = event.headers;
		             userAdd_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the UserRemove operation
          

        /**
         * @see ICloudObserverService#UserRemove()
         */
        public function userRemove(userID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.userRemove(userID);
            _internal_token.addEventListener("result",_UserRemove_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#UserRemove_send()
		 */    
        public function userRemove_send():AsyncToken
        {
        	return userRemove(_UserRemove_request.userID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _UserRemove_request:UserRemove_request;
		/**
		 * @see ICloudObserverService#UserRemove_request_var
		 */
		[Bindable]
		public function get userRemove_request_var():UserRemove_request
		{
			return _UserRemove_request;
		}
		
		/**
		 * @private
		 */
		public function set userRemove_request_var(request:UserRemove_request):void
		{
			_UserRemove_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _userRemove_lastResult:Object;
		[Bindable]
		/**
		 * @see ICloudObserverService#UserRemove_lastResult
		 */	  
		public function get userRemove_lastResult():Object
		{
			return _userRemove_lastResult;
		}
		/**
		 * @private
		 */
		public function set userRemove_lastResult(lastResult:Object):void
		{
			_userRemove_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addUserRemove()
		 */
		public function adduserRemoveEventListener(listener:Function):void
		{
			addEventListener(UserRemoveResultEvent.UserRemove_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _UserRemove_populate_results(event:ResultEvent):void
		{
			var e:UserRemoveResultEvent = new UserRemoveResultEvent();
		            e.result = event.result as Object;
		                       e.headers = event.headers;
		             userRemove_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the UserGetID operation
          

        /**
         * @see ICloudObserverService#UserGetID()
         */
        public function userGetID(email:String):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.userGetID(email);
            _internal_token.addEventListener("result",_UserGetID_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#UserGetID_send()
		 */    
        public function userGetID_send():AsyncToken
        {
        	return userGetID(_UserGetID_request.email);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _UserGetID_request:UserGetID_request;
		/**
		 * @see ICloudObserverService#UserGetID_request_var
		 */
		[Bindable]
		public function get userGetID_request_var():UserGetID_request
		{
			return _UserGetID_request;
		}
		
		/**
		 * @private
		 */
		public function set userGetID_request_var(request:UserGetID_request):void
		{
			_UserGetID_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _userGetID_lastResult:Number;
		[Bindable]
		/**
		 * @see ICloudObserverService#UserGetID_lastResult
		 */	  
		public function get userGetID_lastResult():Number
		{
			return _userGetID_lastResult;
		}
		/**
		 * @private
		 */
		public function set userGetID_lastResult(lastResult:Number):void
		{
			_userGetID_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addUserGetID()
		 */
		public function adduserGetIDEventListener(listener:Function):void
		{
			addEventListener(UserGetIDResultEvent.UserGetID_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _UserGetID_populate_results(event:ResultEvent):void
		{
			var e:UserGetIDResultEvent = new UserGetIDResultEvent();
		            e.result = event.result as Number;
		                       e.headers = event.headers;
		             userGetID_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the UserGetEmail operation
          

        /**
         * @see ICloudObserverService#UserGetEmail()
         */
        public function userGetEmail(userID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.userGetEmail(userID);
            _internal_token.addEventListener("result",_UserGetEmail_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#UserGetEmail_send()
		 */    
        public function userGetEmail_send():AsyncToken
        {
        	return userGetEmail(_UserGetEmail_request.userID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _UserGetEmail_request:UserGetEmail_request;
		/**
		 * @see ICloudObserverService#UserGetEmail_request_var
		 */
		[Bindable]
		public function get userGetEmail_request_var():UserGetEmail_request
		{
			return _UserGetEmail_request;
		}
		
		/**
		 * @private
		 */
		public function set userGetEmail_request_var(request:UserGetEmail_request):void
		{
			_UserGetEmail_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _userGetEmail_lastResult:String;
		[Bindable]
		/**
		 * @see ICloudObserverService#UserGetEmail_lastResult
		 */	  
		public function get userGetEmail_lastResult():String
		{
			return _userGetEmail_lastResult;
		}
		/**
		 * @private
		 */
		public function set userGetEmail_lastResult(lastResult:String):void
		{
			_userGetEmail_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addUserGetEmail()
		 */
		public function adduserGetEmailEventListener(listener:Function):void
		{
			addEventListener(UserGetEmailResultEvent.UserGetEmail_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _UserGetEmail_populate_results(event:ResultEvent):void
		{
			var e:UserGetEmailResultEvent = new UserGetEmailResultEvent();
		            e.result = event.result as String;
		                       e.headers = event.headers;
		             userGetEmail_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the UserGetPassword operation
          

        /**
         * @see ICloudObserverService#UserGetPassword()
         */
        public function userGetPassword(userID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.userGetPassword(userID);
            _internal_token.addEventListener("result",_UserGetPassword_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#UserGetPassword_send()
		 */    
        public function userGetPassword_send():AsyncToken
        {
        	return userGetPassword(_UserGetPassword_request.userID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _UserGetPassword_request:UserGetPassword_request;
		/**
		 * @see ICloudObserverService#UserGetPassword_request_var
		 */
		[Bindable]
		public function get userGetPassword_request_var():UserGetPassword_request
		{
			return _UserGetPassword_request;
		}
		
		/**
		 * @private
		 */
		public function set userGetPassword_request_var(request:UserGetPassword_request):void
		{
			_UserGetPassword_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _userGetPassword_lastResult:String;
		[Bindable]
		/**
		 * @see ICloudObserverService#UserGetPassword_lastResult
		 */	  
		public function get userGetPassword_lastResult():String
		{
			return _userGetPassword_lastResult;
		}
		/**
		 * @private
		 */
		public function set userGetPassword_lastResult(lastResult:String):void
		{
			_userGetPassword_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addUserGetPassword()
		 */
		public function adduserGetPasswordEventListener(listener:Function):void
		{
			addEventListener(UserGetPasswordResultEvent.UserGetPassword_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _UserGetPassword_populate_results(event:ResultEvent):void
		{
			var e:UserGetPasswordResultEvent = new UserGetPasswordResultEvent();
		            e.result = event.result as String;
		                       e.headers = event.headers;
		             userGetPassword_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the UserGetName operation
          

        /**
         * @see ICloudObserverService#UserGetName()
         */
        public function userGetName(userID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.userGetName(userID);
            _internal_token.addEventListener("result",_UserGetName_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#UserGetName_send()
		 */    
        public function userGetName_send():AsyncToken
        {
        	return userGetName(_UserGetName_request.userID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _UserGetName_request:UserGetName_request;
		/**
		 * @see ICloudObserverService#UserGetName_request_var
		 */
		[Bindable]
		public function get userGetName_request_var():UserGetName_request
		{
			return _UserGetName_request;
		}
		
		/**
		 * @private
		 */
		public function set userGetName_request_var(request:UserGetName_request):void
		{
			_UserGetName_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _userGetName_lastResult:String;
		[Bindable]
		/**
		 * @see ICloudObserverService#UserGetName_lastResult
		 */	  
		public function get userGetName_lastResult():String
		{
			return _userGetName_lastResult;
		}
		/**
		 * @private
		 */
		public function set userGetName_lastResult(lastResult:String):void
		{
			_userGetName_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addUserGetName()
		 */
		public function adduserGetNameEventListener(listener:Function):void
		{
			addEventListener(UserGetNameResultEvent.UserGetName_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _UserGetName_populate_results(event:ResultEvent):void
		{
			var e:UserGetNameResultEvent = new UserGetNameResultEvent();
		            e.result = event.result as String;
		                       e.headers = event.headers;
		             userGetName_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the UserGetDescription operation
          

        /**
         * @see ICloudObserverService#UserGetDescription()
         */
        public function userGetDescription(userID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.userGetDescription(userID);
            _internal_token.addEventListener("result",_UserGetDescription_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#UserGetDescription_send()
		 */    
        public function userGetDescription_send():AsyncToken
        {
        	return userGetDescription(_UserGetDescription_request.userID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _UserGetDescription_request:UserGetDescription_request;
		/**
		 * @see ICloudObserverService#UserGetDescription_request_var
		 */
		[Bindable]
		public function get userGetDescription_request_var():UserGetDescription_request
		{
			return _UserGetDescription_request;
		}
		
		/**
		 * @private
		 */
		public function set userGetDescription_request_var(request:UserGetDescription_request):void
		{
			_UserGetDescription_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _userGetDescription_lastResult:String;
		[Bindable]
		/**
		 * @see ICloudObserverService#UserGetDescription_lastResult
		 */	  
		public function get userGetDescription_lastResult():String
		{
			return _userGetDescription_lastResult;
		}
		/**
		 * @private
		 */
		public function set userGetDescription_lastResult(lastResult:String):void
		{
			_userGetDescription_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addUserGetDescription()
		 */
		public function adduserGetDescriptionEventListener(listener:Function):void
		{
			addEventListener(UserGetDescriptionResultEvent.UserGetDescription_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _UserGetDescription_populate_results(event:ResultEvent):void
		{
			var e:UserGetDescriptionResultEvent = new UserGetDescriptionResultEvent();
		            e.result = event.result as String;
		                       e.headers = event.headers;
		             userGetDescription_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the UserGetIcon operation
          

        /**
         * @see ICloudObserverService#UserGetIcon()
         */
        public function userGetIcon(userID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.userGetIcon(userID);
            _internal_token.addEventListener("result",_UserGetIcon_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#UserGetIcon_send()
		 */    
        public function userGetIcon_send():AsyncToken
        {
        	return userGetIcon(_UserGetIcon_request.userID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _UserGetIcon_request:UserGetIcon_request;
		/**
		 * @see ICloudObserverService#UserGetIcon_request_var
		 */
		[Bindable]
		public function get userGetIcon_request_var():UserGetIcon_request
		{
			return _UserGetIcon_request;
		}
		
		/**
		 * @private
		 */
		public function set userGetIcon_request_var(request:UserGetIcon_request):void
		{
			_UserGetIcon_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _userGetIcon_lastResult:flash.utils.ByteArray;
		[Bindable]
		/**
		 * @see ICloudObserverService#UserGetIcon_lastResult
		 */	  
		public function get userGetIcon_lastResult():flash.utils.ByteArray
		{
			return _userGetIcon_lastResult;
		}
		/**
		 * @private
		 */
		public function set userGetIcon_lastResult(lastResult:flash.utils.ByteArray):void
		{
			_userGetIcon_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addUserGetIcon()
		 */
		public function adduserGetIconEventListener(listener:Function):void
		{
			addEventListener(UserGetIconResultEvent.UserGetIcon_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _UserGetIcon_populate_results(event:ResultEvent):void
		{
			var e:UserGetIconResultEvent = new UserGetIconResultEvent();
		            e.result = event.result as flash.utils.ByteArray;
		                       e.headers = event.headers;
		             userGetIcon_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the UserGetRegistrationDate operation
          

        /**
         * @see ICloudObserverService#UserGetRegistrationDate()
         */
        public function userGetRegistrationDate(userID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.userGetRegistrationDate(userID);
            _internal_token.addEventListener("result",_UserGetRegistrationDate_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#UserGetRegistrationDate_send()
		 */    
        public function userGetRegistrationDate_send():AsyncToken
        {
        	return userGetRegistrationDate(_UserGetRegistrationDate_request.userID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _UserGetRegistrationDate_request:UserGetRegistrationDate_request;
		/**
		 * @see ICloudObserverService#UserGetRegistrationDate_request_var
		 */
		[Bindable]
		public function get userGetRegistrationDate_request_var():UserGetRegistrationDate_request
		{
			return _UserGetRegistrationDate_request;
		}
		
		/**
		 * @private
		 */
		public function set userGetRegistrationDate_request_var(request:UserGetRegistrationDate_request):void
		{
			_UserGetRegistrationDate_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _userGetRegistrationDate_lastResult:Date;
		[Bindable]
		/**
		 * @see ICloudObserverService#UserGetRegistrationDate_lastResult
		 */	  
		public function get userGetRegistrationDate_lastResult():Date
		{
			return _userGetRegistrationDate_lastResult;
		}
		/**
		 * @private
		 */
		public function set userGetRegistrationDate_lastResult(lastResult:Date):void
		{
			_userGetRegistrationDate_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addUserGetRegistrationDate()
		 */
		public function adduserGetRegistrationDateEventListener(listener:Function):void
		{
			addEventListener(UserGetRegistrationDateResultEvent.UserGetRegistrationDate_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _UserGetRegistrationDate_populate_results(event:ResultEvent):void
		{
			var e:UserGetRegistrationDateResultEvent = new UserGetRegistrationDateResultEvent();
		            e.result = event.result as Date;
		                       e.headers = event.headers;
		             userGetRegistrationDate_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the UserGetGroups operation
          

        /**
         * @see ICloudObserverService#UserGetGroups()
         */
        public function userGetGroups(userID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.userGetGroups(userID);
            _internal_token.addEventListener("result",_UserGetGroups_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#UserGetGroups_send()
		 */    
        public function userGetGroups_send():AsyncToken
        {
        	return userGetGroups(_UserGetGroups_request.userID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _UserGetGroups_request:UserGetGroups_request;
		/**
		 * @see ICloudObserverService#UserGetGroups_request_var
		 */
		[Bindable]
		public function get userGetGroups_request_var():UserGetGroups_request
		{
			return _UserGetGroups_request;
		}
		
		/**
		 * @private
		 */
		public function set userGetGroups_request_var(request:UserGetGroups_request):void
		{
			_UserGetGroups_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _userGetGroups_lastResult:ArrayOfint;
		[Bindable]
		/**
		 * @see ICloudObserverService#UserGetGroups_lastResult
		 */	  
		public function get userGetGroups_lastResult():ArrayOfint
		{
			return _userGetGroups_lastResult;
		}
		/**
		 * @private
		 */
		public function set userGetGroups_lastResult(lastResult:ArrayOfint):void
		{
			_userGetGroups_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addUserGetGroups()
		 */
		public function adduserGetGroupsEventListener(listener:Function):void
		{
			addEventListener(UserGetGroupsResultEvent.UserGetGroups_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _UserGetGroups_populate_results(event:ResultEvent):void
		{
			var e:UserGetGroupsResultEvent = new UserGetGroupsResultEvent();
		            e.result = event.result as ArrayOfint;
		                       e.headers = event.headers;
		             userGetGroups_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the UserSetPassword operation
          

        /**
         * @see ICloudObserverService#UserSetPassword()
         */
        public function userSetPassword(userID:Number,password:String):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.userSetPassword(userID,password);
            _internal_token.addEventListener("result",_UserSetPassword_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#UserSetPassword_send()
		 */    
        public function userSetPassword_send():AsyncToken
        {
        	return userSetPassword(_UserSetPassword_request.userID,_UserSetPassword_request.password);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _UserSetPassword_request:UserSetPassword_request;
		/**
		 * @see ICloudObserverService#UserSetPassword_request_var
		 */
		[Bindable]
		public function get userSetPassword_request_var():UserSetPassword_request
		{
			return _UserSetPassword_request;
		}
		
		/**
		 * @private
		 */
		public function set userSetPassword_request_var(request:UserSetPassword_request):void
		{
			_UserSetPassword_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _userSetPassword_lastResult:Object;
		[Bindable]
		/**
		 * @see ICloudObserverService#UserSetPassword_lastResult
		 */	  
		public function get userSetPassword_lastResult():Object
		{
			return _userSetPassword_lastResult;
		}
		/**
		 * @private
		 */
		public function set userSetPassword_lastResult(lastResult:Object):void
		{
			_userSetPassword_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addUserSetPassword()
		 */
		public function adduserSetPasswordEventListener(listener:Function):void
		{
			addEventListener(UserSetPasswordResultEvent.UserSetPassword_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _UserSetPassword_populate_results(event:ResultEvent):void
		{
			var e:UserSetPasswordResultEvent = new UserSetPasswordResultEvent();
		            e.result = event.result as Object;
		                       e.headers = event.headers;
		             userSetPassword_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the UserSetName operation
          

        /**
         * @see ICloudObserverService#UserSetName()
         */
        public function userSetName(userID:Number,name:String):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.userSetName(userID,name);
            _internal_token.addEventListener("result",_UserSetName_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#UserSetName_send()
		 */    
        public function userSetName_send():AsyncToken
        {
        	return userSetName(_UserSetName_request.userID,_UserSetName_request.name);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _UserSetName_request:UserSetName_request;
		/**
		 * @see ICloudObserverService#UserSetName_request_var
		 */
		[Bindable]
		public function get userSetName_request_var():UserSetName_request
		{
			return _UserSetName_request;
		}
		
		/**
		 * @private
		 */
		public function set userSetName_request_var(request:UserSetName_request):void
		{
			_UserSetName_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _userSetName_lastResult:Object;
		[Bindable]
		/**
		 * @see ICloudObserverService#UserSetName_lastResult
		 */	  
		public function get userSetName_lastResult():Object
		{
			return _userSetName_lastResult;
		}
		/**
		 * @private
		 */
		public function set userSetName_lastResult(lastResult:Object):void
		{
			_userSetName_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addUserSetName()
		 */
		public function adduserSetNameEventListener(listener:Function):void
		{
			addEventListener(UserSetNameResultEvent.UserSetName_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _UserSetName_populate_results(event:ResultEvent):void
		{
			var e:UserSetNameResultEvent = new UserSetNameResultEvent();
		            e.result = event.result as Object;
		                       e.headers = event.headers;
		             userSetName_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the UserSetDescription operation
          

        /**
         * @see ICloudObserverService#UserSetDescription()
         */
        public function userSetDescription(userID:Number,description:String):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.userSetDescription(userID,description);
            _internal_token.addEventListener("result",_UserSetDescription_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#UserSetDescription_send()
		 */    
        public function userSetDescription_send():AsyncToken
        {
        	return userSetDescription(_UserSetDescription_request.userID,_UserSetDescription_request.description);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _UserSetDescription_request:UserSetDescription_request;
		/**
		 * @see ICloudObserverService#UserSetDescription_request_var
		 */
		[Bindable]
		public function get userSetDescription_request_var():UserSetDescription_request
		{
			return _UserSetDescription_request;
		}
		
		/**
		 * @private
		 */
		public function set userSetDescription_request_var(request:UserSetDescription_request):void
		{
			_UserSetDescription_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _userSetDescription_lastResult:Object;
		[Bindable]
		/**
		 * @see ICloudObserverService#UserSetDescription_lastResult
		 */	  
		public function get userSetDescription_lastResult():Object
		{
			return _userSetDescription_lastResult;
		}
		/**
		 * @private
		 */
		public function set userSetDescription_lastResult(lastResult:Object):void
		{
			_userSetDescription_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addUserSetDescription()
		 */
		public function adduserSetDescriptionEventListener(listener:Function):void
		{
			addEventListener(UserSetDescriptionResultEvent.UserSetDescription_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _UserSetDescription_populate_results(event:ResultEvent):void
		{
			var e:UserSetDescriptionResultEvent = new UserSetDescriptionResultEvent();
		            e.result = event.result as Object;
		                       e.headers = event.headers;
		             userSetDescription_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the UserSetIcon operation
          

        /**
         * @see ICloudObserverService#UserSetIcon()
         */
        public function userSetIcon(userID:Number,icon:flash.utils.ByteArray):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.userSetIcon(userID,icon);
            _internal_token.addEventListener("result",_UserSetIcon_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#UserSetIcon_send()
		 */    
        public function userSetIcon_send():AsyncToken
        {
        	return userSetIcon(_UserSetIcon_request.userID,_UserSetIcon_request.icon);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _UserSetIcon_request:UserSetIcon_request;
		/**
		 * @see ICloudObserverService#UserSetIcon_request_var
		 */
		[Bindable]
		public function get userSetIcon_request_var():UserSetIcon_request
		{
			return _UserSetIcon_request;
		}
		
		/**
		 * @private
		 */
		public function set userSetIcon_request_var(request:UserSetIcon_request):void
		{
			_UserSetIcon_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _userSetIcon_lastResult:Object;
		[Bindable]
		/**
		 * @see ICloudObserverService#UserSetIcon_lastResult
		 */	  
		public function get userSetIcon_lastResult():Object
		{
			return _userSetIcon_lastResult;
		}
		/**
		 * @private
		 */
		public function set userSetIcon_lastResult(lastResult:Object):void
		{
			_userSetIcon_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addUserSetIcon()
		 */
		public function adduserSetIconEventListener(listener:Function):void
		{
			addEventListener(UserSetIconResultEvent.UserSetIcon_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _UserSetIcon_populate_results(event:ResultEvent):void
		{
			var e:UserSetIconResultEvent = new UserSetIconResultEvent();
		            e.result = event.result as Object;
		                       e.headers = event.headers;
		             userSetIcon_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the CameraIsPathAvailable operation
          

        /**
         * @see ICloudObserverService#CameraIsPathAvailable()
         */
        public function cameraIsPathAvailable(path:String):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.cameraIsPathAvailable(path);
            _internal_token.addEventListener("result",_CameraIsPathAvailable_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#CameraIsPathAvailable_send()
		 */    
        public function cameraIsPathAvailable_send():AsyncToken
        {
        	return cameraIsPathAvailable(_CameraIsPathAvailable_request.path);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _CameraIsPathAvailable_request:CameraIsPathAvailable_request;
		/**
		 * @see ICloudObserverService#CameraIsPathAvailable_request_var
		 */
		[Bindable]
		public function get cameraIsPathAvailable_request_var():CameraIsPathAvailable_request
		{
			return _CameraIsPathAvailable_request;
		}
		
		/**
		 * @private
		 */
		public function set cameraIsPathAvailable_request_var(request:CameraIsPathAvailable_request):void
		{
			_CameraIsPathAvailable_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _cameraIsPathAvailable_lastResult:Boolean;
		[Bindable]
		/**
		 * @see ICloudObserverService#CameraIsPathAvailable_lastResult
		 */	  
		public function get cameraIsPathAvailable_lastResult():Boolean
		{
			return _cameraIsPathAvailable_lastResult;
		}
		/**
		 * @private
		 */
		public function set cameraIsPathAvailable_lastResult(lastResult:Boolean):void
		{
			_cameraIsPathAvailable_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addCameraIsPathAvailable()
		 */
		public function addcameraIsPathAvailableEventListener(listener:Function):void
		{
			addEventListener(CameraIsPathAvailableResultEvent.CameraIsPathAvailable_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _CameraIsPathAvailable_populate_results(event:ResultEvent):void
		{
			var e:CameraIsPathAvailableResultEvent = new CameraIsPathAvailableResultEvent();
		            e.result = event.result as Boolean;
		                       e.headers = event.headers;
		             cameraIsPathAvailable_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the CameraAdd operation
          

        /**
         * @see ICloudObserverService#CameraAdd()
         */
        public function cameraAdd(name:String,description:String,icon:flash.utils.ByteArray):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.cameraAdd(name,description,icon);
            _internal_token.addEventListener("result",_CameraAdd_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#CameraAdd_send()
		 */    
        public function cameraAdd_send():AsyncToken
        {
        	return cameraAdd(_CameraAdd_request.name,_CameraAdd_request.description,_CameraAdd_request.icon);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _CameraAdd_request:CameraAdd_request;
		/**
		 * @see ICloudObserverService#CameraAdd_request_var
		 */
		[Bindable]
		public function get cameraAdd_request_var():CameraAdd_request
		{
			return _CameraAdd_request;
		}
		
		/**
		 * @private
		 */
		public function set cameraAdd_request_var(request:CameraAdd_request):void
		{
			_CameraAdd_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _cameraAdd_lastResult:Number;
		[Bindable]
		/**
		 * @see ICloudObserverService#CameraAdd_lastResult
		 */	  
		public function get cameraAdd_lastResult():Number
		{
			return _cameraAdd_lastResult;
		}
		/**
		 * @private
		 */
		public function set cameraAdd_lastResult(lastResult:Number):void
		{
			_cameraAdd_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addCameraAdd()
		 */
		public function addcameraAddEventListener(listener:Function):void
		{
			addEventListener(CameraAddResultEvent.CameraAdd_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _CameraAdd_populate_results(event:ResultEvent):void
		{
			var e:CameraAddResultEvent = new CameraAddResultEvent();
		            e.result = event.result as Number;
		                       e.headers = event.headers;
		             cameraAdd_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the CameraRemove operation
          

        /**
         * @see ICloudObserverService#CameraRemove()
         */
        public function cameraRemove(cameraID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.cameraRemove(cameraID);
            _internal_token.addEventListener("result",_CameraRemove_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#CameraRemove_send()
		 */    
        public function cameraRemove_send():AsyncToken
        {
        	return cameraRemove(_CameraRemove_request.cameraID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _CameraRemove_request:CameraRemove_request;
		/**
		 * @see ICloudObserverService#CameraRemove_request_var
		 */
		[Bindable]
		public function get cameraRemove_request_var():CameraRemove_request
		{
			return _CameraRemove_request;
		}
		
		/**
		 * @private
		 */
		public function set cameraRemove_request_var(request:CameraRemove_request):void
		{
			_CameraRemove_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _cameraRemove_lastResult:Object;
		[Bindable]
		/**
		 * @see ICloudObserverService#CameraRemove_lastResult
		 */	  
		public function get cameraRemove_lastResult():Object
		{
			return _cameraRemove_lastResult;
		}
		/**
		 * @private
		 */
		public function set cameraRemove_lastResult(lastResult:Object):void
		{
			_cameraRemove_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addCameraRemove()
		 */
		public function addcameraRemoveEventListener(listener:Function):void
		{
			addEventListener(CameraRemoveResultEvent.CameraRemove_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _CameraRemove_populate_results(event:ResultEvent):void
		{
			var e:CameraRemoveResultEvent = new CameraRemoveResultEvent();
		            e.result = event.result as Object;
		                       e.headers = event.headers;
		             cameraRemove_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the CameraGetID operation
          

        /**
         * @see ICloudObserverService#CameraGetID()
         */
        public function cameraGetID(path:String):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.cameraGetID(path);
            _internal_token.addEventListener("result",_CameraGetID_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#CameraGetID_send()
		 */    
        public function cameraGetID_send():AsyncToken
        {
        	return cameraGetID(_CameraGetID_request.path);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _CameraGetID_request:CameraGetID_request;
		/**
		 * @see ICloudObserverService#CameraGetID_request_var
		 */
		[Bindable]
		public function get cameraGetID_request_var():CameraGetID_request
		{
			return _CameraGetID_request;
		}
		
		/**
		 * @private
		 */
		public function set cameraGetID_request_var(request:CameraGetID_request):void
		{
			_CameraGetID_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _cameraGetID_lastResult:Number;
		[Bindable]
		/**
		 * @see ICloudObserverService#CameraGetID_lastResult
		 */	  
		public function get cameraGetID_lastResult():Number
		{
			return _cameraGetID_lastResult;
		}
		/**
		 * @private
		 */
		public function set cameraGetID_lastResult(lastResult:Number):void
		{
			_cameraGetID_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addCameraGetID()
		 */
		public function addcameraGetIDEventListener(listener:Function):void
		{
			addEventListener(CameraGetIDResultEvent.CameraGetID_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _CameraGetID_populate_results(event:ResultEvent):void
		{
			var e:CameraGetIDResultEvent = new CameraGetIDResultEvent();
		            e.result = event.result as Number;
		                       e.headers = event.headers;
		             cameraGetID_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the CameraGetPath operation
          

        /**
         * @see ICloudObserverService#CameraGetPath()
         */
        public function cameraGetPath(cameraID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.cameraGetPath(cameraID);
            _internal_token.addEventListener("result",_CameraGetPath_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#CameraGetPath_send()
		 */    
        public function cameraGetPath_send():AsyncToken
        {
        	return cameraGetPath(_CameraGetPath_request.cameraID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _CameraGetPath_request:CameraGetPath_request;
		/**
		 * @see ICloudObserverService#CameraGetPath_request_var
		 */
		[Bindable]
		public function get cameraGetPath_request_var():CameraGetPath_request
		{
			return _CameraGetPath_request;
		}
		
		/**
		 * @private
		 */
		public function set cameraGetPath_request_var(request:CameraGetPath_request):void
		{
			_CameraGetPath_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _cameraGetPath_lastResult:String;
		[Bindable]
		/**
		 * @see ICloudObserverService#CameraGetPath_lastResult
		 */	  
		public function get cameraGetPath_lastResult():String
		{
			return _cameraGetPath_lastResult;
		}
		/**
		 * @private
		 */
		public function set cameraGetPath_lastResult(lastResult:String):void
		{
			_cameraGetPath_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addCameraGetPath()
		 */
		public function addcameraGetPathEventListener(listener:Function):void
		{
			addEventListener(CameraGetPathResultEvent.CameraGetPath_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _CameraGetPath_populate_results(event:ResultEvent):void
		{
			var e:CameraGetPathResultEvent = new CameraGetPathResultEvent();
		            e.result = event.result as String;
		                       e.headers = event.headers;
		             cameraGetPath_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the CameraGetName operation
          

        /**
         * @see ICloudObserverService#CameraGetName()
         */
        public function cameraGetName(cameraID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.cameraGetName(cameraID);
            _internal_token.addEventListener("result",_CameraGetName_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#CameraGetName_send()
		 */    
        public function cameraGetName_send():AsyncToken
        {
        	return cameraGetName(_CameraGetName_request.cameraID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _CameraGetName_request:CameraGetName_request;
		/**
		 * @see ICloudObserverService#CameraGetName_request_var
		 */
		[Bindable]
		public function get cameraGetName_request_var():CameraGetName_request
		{
			return _CameraGetName_request;
		}
		
		/**
		 * @private
		 */
		public function set cameraGetName_request_var(request:CameraGetName_request):void
		{
			_CameraGetName_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _cameraGetName_lastResult:String;
		[Bindable]
		/**
		 * @see ICloudObserverService#CameraGetName_lastResult
		 */	  
		public function get cameraGetName_lastResult():String
		{
			return _cameraGetName_lastResult;
		}
		/**
		 * @private
		 */
		public function set cameraGetName_lastResult(lastResult:String):void
		{
			_cameraGetName_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addCameraGetName()
		 */
		public function addcameraGetNameEventListener(listener:Function):void
		{
			addEventListener(CameraGetNameResultEvent.CameraGetName_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _CameraGetName_populate_results(event:ResultEvent):void
		{
			var e:CameraGetNameResultEvent = new CameraGetNameResultEvent();
		            e.result = event.result as String;
		                       e.headers = event.headers;
		             cameraGetName_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the CameraGetDescription operation
          

        /**
         * @see ICloudObserverService#CameraGetDescription()
         */
        public function cameraGetDescription(cameraID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.cameraGetDescription(cameraID);
            _internal_token.addEventListener("result",_CameraGetDescription_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#CameraGetDescription_send()
		 */    
        public function cameraGetDescription_send():AsyncToken
        {
        	return cameraGetDescription(_CameraGetDescription_request.cameraID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _CameraGetDescription_request:CameraGetDescription_request;
		/**
		 * @see ICloudObserverService#CameraGetDescription_request_var
		 */
		[Bindable]
		public function get cameraGetDescription_request_var():CameraGetDescription_request
		{
			return _CameraGetDescription_request;
		}
		
		/**
		 * @private
		 */
		public function set cameraGetDescription_request_var(request:CameraGetDescription_request):void
		{
			_CameraGetDescription_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _cameraGetDescription_lastResult:String;
		[Bindable]
		/**
		 * @see ICloudObserverService#CameraGetDescription_lastResult
		 */	  
		public function get cameraGetDescription_lastResult():String
		{
			return _cameraGetDescription_lastResult;
		}
		/**
		 * @private
		 */
		public function set cameraGetDescription_lastResult(lastResult:String):void
		{
			_cameraGetDescription_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addCameraGetDescription()
		 */
		public function addcameraGetDescriptionEventListener(listener:Function):void
		{
			addEventListener(CameraGetDescriptionResultEvent.CameraGetDescription_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _CameraGetDescription_populate_results(event:ResultEvent):void
		{
			var e:CameraGetDescriptionResultEvent = new CameraGetDescriptionResultEvent();
		            e.result = event.result as String;
		                       e.headers = event.headers;
		             cameraGetDescription_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the CameraGetIcon operation
          

        /**
         * @see ICloudObserverService#CameraGetIcon()
         */
        public function cameraGetIcon(cameraID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.cameraGetIcon(cameraID);
            _internal_token.addEventListener("result",_CameraGetIcon_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#CameraGetIcon_send()
		 */    
        public function cameraGetIcon_send():AsyncToken
        {
        	return cameraGetIcon(_CameraGetIcon_request.cameraID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _CameraGetIcon_request:CameraGetIcon_request;
		/**
		 * @see ICloudObserverService#CameraGetIcon_request_var
		 */
		[Bindable]
		public function get cameraGetIcon_request_var():CameraGetIcon_request
		{
			return _CameraGetIcon_request;
		}
		
		/**
		 * @private
		 */
		public function set cameraGetIcon_request_var(request:CameraGetIcon_request):void
		{
			_CameraGetIcon_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _cameraGetIcon_lastResult:flash.utils.ByteArray;
		[Bindable]
		/**
		 * @see ICloudObserverService#CameraGetIcon_lastResult
		 */	  
		public function get cameraGetIcon_lastResult():flash.utils.ByteArray
		{
			return _cameraGetIcon_lastResult;
		}
		/**
		 * @private
		 */
		public function set cameraGetIcon_lastResult(lastResult:flash.utils.ByteArray):void
		{
			_cameraGetIcon_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addCameraGetIcon()
		 */
		public function addcameraGetIconEventListener(listener:Function):void
		{
			addEventListener(CameraGetIconResultEvent.CameraGetIcon_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _CameraGetIcon_populate_results(event:ResultEvent):void
		{
			var e:CameraGetIconResultEvent = new CameraGetIconResultEvent();
		            e.result = event.result as flash.utils.ByteArray;
		                       e.headers = event.headers;
		             cameraGetIcon_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the CameraGetRegistrationDate operation
          

        /**
         * @see ICloudObserverService#CameraGetRegistrationDate()
         */
        public function cameraGetRegistrationDate(cameraID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.cameraGetRegistrationDate(cameraID);
            _internal_token.addEventListener("result",_CameraGetRegistrationDate_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#CameraGetRegistrationDate_send()
		 */    
        public function cameraGetRegistrationDate_send():AsyncToken
        {
        	return cameraGetRegistrationDate(_CameraGetRegistrationDate_request.cameraID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _CameraGetRegistrationDate_request:CameraGetRegistrationDate_request;
		/**
		 * @see ICloudObserverService#CameraGetRegistrationDate_request_var
		 */
		[Bindable]
		public function get cameraGetRegistrationDate_request_var():CameraGetRegistrationDate_request
		{
			return _CameraGetRegistrationDate_request;
		}
		
		/**
		 * @private
		 */
		public function set cameraGetRegistrationDate_request_var(request:CameraGetRegistrationDate_request):void
		{
			_CameraGetRegistrationDate_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _cameraGetRegistrationDate_lastResult:Date;
		[Bindable]
		/**
		 * @see ICloudObserverService#CameraGetRegistrationDate_lastResult
		 */	  
		public function get cameraGetRegistrationDate_lastResult():Date
		{
			return _cameraGetRegistrationDate_lastResult;
		}
		/**
		 * @private
		 */
		public function set cameraGetRegistrationDate_lastResult(lastResult:Date):void
		{
			_cameraGetRegistrationDate_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addCameraGetRegistrationDate()
		 */
		public function addcameraGetRegistrationDateEventListener(listener:Function):void
		{
			addEventListener(CameraGetRegistrationDateResultEvent.CameraGetRegistrationDate_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _CameraGetRegistrationDate_populate_results(event:ResultEvent):void
		{
			var e:CameraGetRegistrationDateResultEvent = new CameraGetRegistrationDateResultEvent();
		            e.result = event.result as Date;
		                       e.headers = event.headers;
		             cameraGetRegistrationDate_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the CameraGetGroups operation
          

        /**
         * @see ICloudObserverService#CameraGetGroups()
         */
        public function cameraGetGroups(cameraID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.cameraGetGroups(cameraID);
            _internal_token.addEventListener("result",_CameraGetGroups_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#CameraGetGroups_send()
		 */    
        public function cameraGetGroups_send():AsyncToken
        {
        	return cameraGetGroups(_CameraGetGroups_request.cameraID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _CameraGetGroups_request:CameraGetGroups_request;
		/**
		 * @see ICloudObserverService#CameraGetGroups_request_var
		 */
		[Bindable]
		public function get cameraGetGroups_request_var():CameraGetGroups_request
		{
			return _CameraGetGroups_request;
		}
		
		/**
		 * @private
		 */
		public function set cameraGetGroups_request_var(request:CameraGetGroups_request):void
		{
			_CameraGetGroups_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _cameraGetGroups_lastResult:ArrayOfint;
		[Bindable]
		/**
		 * @see ICloudObserverService#CameraGetGroups_lastResult
		 */	  
		public function get cameraGetGroups_lastResult():ArrayOfint
		{
			return _cameraGetGroups_lastResult;
		}
		/**
		 * @private
		 */
		public function set cameraGetGroups_lastResult(lastResult:ArrayOfint):void
		{
			_cameraGetGroups_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addCameraGetGroups()
		 */
		public function addcameraGetGroupsEventListener(listener:Function):void
		{
			addEventListener(CameraGetGroupsResultEvent.CameraGetGroups_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _CameraGetGroups_populate_results(event:ResultEvent):void
		{
			var e:CameraGetGroupsResultEvent = new CameraGetGroupsResultEvent();
		            e.result = event.result as ArrayOfint;
		                       e.headers = event.headers;
		             cameraGetGroups_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the CameraGetFrames operation
          

        /**
         * @see ICloudObserverService#CameraGetFrames()
         */
        public function cameraGetFrames(cameraID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.cameraGetFrames(cameraID);
            _internal_token.addEventListener("result",_CameraGetFrames_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#CameraGetFrames_send()
		 */    
        public function cameraGetFrames_send():AsyncToken
        {
        	return cameraGetFrames(_CameraGetFrames_request.cameraID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _CameraGetFrames_request:CameraGetFrames_request;
		/**
		 * @see ICloudObserverService#CameraGetFrames_request_var
		 */
		[Bindable]
		public function get cameraGetFrames_request_var():CameraGetFrames_request
		{
			return _CameraGetFrames_request;
		}
		
		/**
		 * @private
		 */
		public function set cameraGetFrames_request_var(request:CameraGetFrames_request):void
		{
			_CameraGetFrames_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _cameraGetFrames_lastResult:ArrayOfint;
		[Bindable]
		/**
		 * @see ICloudObserverService#CameraGetFrames_lastResult
		 */	  
		public function get cameraGetFrames_lastResult():ArrayOfint
		{
			return _cameraGetFrames_lastResult;
		}
		/**
		 * @private
		 */
		public function set cameraGetFrames_lastResult(lastResult:ArrayOfint):void
		{
			_cameraGetFrames_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addCameraGetFrames()
		 */
		public function addcameraGetFramesEventListener(listener:Function):void
		{
			addEventListener(CameraGetFramesResultEvent.CameraGetFrames_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _CameraGetFrames_populate_results(event:ResultEvent):void
		{
			var e:CameraGetFramesResultEvent = new CameraGetFramesResultEvent();
		            e.result = event.result as ArrayOfint;
		                       e.headers = event.headers;
		             cameraGetFrames_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the CameraSetName operation
          

        /**
         * @see ICloudObserverService#CameraSetName()
         */
        public function cameraSetName(cameraID:Number,name:String):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.cameraSetName(cameraID,name);
            _internal_token.addEventListener("result",_CameraSetName_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#CameraSetName_send()
		 */    
        public function cameraSetName_send():AsyncToken
        {
        	return cameraSetName(_CameraSetName_request.cameraID,_CameraSetName_request.name);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _CameraSetName_request:CameraSetName_request;
		/**
		 * @see ICloudObserverService#CameraSetName_request_var
		 */
		[Bindable]
		public function get cameraSetName_request_var():CameraSetName_request
		{
			return _CameraSetName_request;
		}
		
		/**
		 * @private
		 */
		public function set cameraSetName_request_var(request:CameraSetName_request):void
		{
			_CameraSetName_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _cameraSetName_lastResult:Object;
		[Bindable]
		/**
		 * @see ICloudObserverService#CameraSetName_lastResult
		 */	  
		public function get cameraSetName_lastResult():Object
		{
			return _cameraSetName_lastResult;
		}
		/**
		 * @private
		 */
		public function set cameraSetName_lastResult(lastResult:Object):void
		{
			_cameraSetName_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addCameraSetName()
		 */
		public function addcameraSetNameEventListener(listener:Function):void
		{
			addEventListener(CameraSetNameResultEvent.CameraSetName_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _CameraSetName_populate_results(event:ResultEvent):void
		{
			var e:CameraSetNameResultEvent = new CameraSetNameResultEvent();
		            e.result = event.result as Object;
		                       e.headers = event.headers;
		             cameraSetName_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the CameraSetDescription operation
          

        /**
         * @see ICloudObserverService#CameraSetDescription()
         */
        public function cameraSetDescription(cameraID:Number,description:String):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.cameraSetDescription(cameraID,description);
            _internal_token.addEventListener("result",_CameraSetDescription_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#CameraSetDescription_send()
		 */    
        public function cameraSetDescription_send():AsyncToken
        {
        	return cameraSetDescription(_CameraSetDescription_request.cameraID,_CameraSetDescription_request.description);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _CameraSetDescription_request:CameraSetDescription_request;
		/**
		 * @see ICloudObserverService#CameraSetDescription_request_var
		 */
		[Bindable]
		public function get cameraSetDescription_request_var():CameraSetDescription_request
		{
			return _CameraSetDescription_request;
		}
		
		/**
		 * @private
		 */
		public function set cameraSetDescription_request_var(request:CameraSetDescription_request):void
		{
			_CameraSetDescription_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _cameraSetDescription_lastResult:Object;
		[Bindable]
		/**
		 * @see ICloudObserverService#CameraSetDescription_lastResult
		 */	  
		public function get cameraSetDescription_lastResult():Object
		{
			return _cameraSetDescription_lastResult;
		}
		/**
		 * @private
		 */
		public function set cameraSetDescription_lastResult(lastResult:Object):void
		{
			_cameraSetDescription_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addCameraSetDescription()
		 */
		public function addcameraSetDescriptionEventListener(listener:Function):void
		{
			addEventListener(CameraSetDescriptionResultEvent.CameraSetDescription_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _CameraSetDescription_populate_results(event:ResultEvent):void
		{
			var e:CameraSetDescriptionResultEvent = new CameraSetDescriptionResultEvent();
		            e.result = event.result as Object;
		                       e.headers = event.headers;
		             cameraSetDescription_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the CameraSetIcon operation
          

        /**
         * @see ICloudObserverService#CameraSetIcon()
         */
        public function cameraSetIcon(cameraID:Number,icon:flash.utils.ByteArray):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.cameraSetIcon(cameraID,icon);
            _internal_token.addEventListener("result",_CameraSetIcon_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#CameraSetIcon_send()
		 */    
        public function cameraSetIcon_send():AsyncToken
        {
        	return cameraSetIcon(_CameraSetIcon_request.cameraID,_CameraSetIcon_request.icon);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _CameraSetIcon_request:CameraSetIcon_request;
		/**
		 * @see ICloudObserverService#CameraSetIcon_request_var
		 */
		[Bindable]
		public function get cameraSetIcon_request_var():CameraSetIcon_request
		{
			return _CameraSetIcon_request;
		}
		
		/**
		 * @private
		 */
		public function set cameraSetIcon_request_var(request:CameraSetIcon_request):void
		{
			_CameraSetIcon_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _cameraSetIcon_lastResult:Object;
		[Bindable]
		/**
		 * @see ICloudObserverService#CameraSetIcon_lastResult
		 */	  
		public function get cameraSetIcon_lastResult():Object
		{
			return _cameraSetIcon_lastResult;
		}
		/**
		 * @private
		 */
		public function set cameraSetIcon_lastResult(lastResult:Object):void
		{
			_cameraSetIcon_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addCameraSetIcon()
		 */
		public function addcameraSetIconEventListener(listener:Function):void
		{
			addEventListener(CameraSetIconResultEvent.CameraSetIcon_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _CameraSetIcon_populate_results(event:ResultEvent):void
		{
			var e:CameraSetIconResultEvent = new CameraSetIconResultEvent();
		            e.result = event.result as Object;
		                       e.headers = event.headers;
		             cameraSetIcon_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the GroupAdd operation
          

        /**
         * @see ICloudObserverService#GroupAdd()
         */
        public function groupAdd(name:String,description:String,icon:flash.utils.ByteArray,privacy:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.groupAdd(name,description,icon,privacy);
            _internal_token.addEventListener("result",_GroupAdd_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#GroupAdd_send()
		 */    
        public function groupAdd_send():AsyncToken
        {
        	return groupAdd(_GroupAdd_request.name,_GroupAdd_request.description,_GroupAdd_request.icon,_GroupAdd_request.privacy);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _GroupAdd_request:GroupAdd_request;
		/**
		 * @see ICloudObserverService#GroupAdd_request_var
		 */
		[Bindable]
		public function get groupAdd_request_var():GroupAdd_request
		{
			return _GroupAdd_request;
		}
		
		/**
		 * @private
		 */
		public function set groupAdd_request_var(request:GroupAdd_request):void
		{
			_GroupAdd_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _groupAdd_lastResult:Number;
		[Bindable]
		/**
		 * @see ICloudObserverService#GroupAdd_lastResult
		 */	  
		public function get groupAdd_lastResult():Number
		{
			return _groupAdd_lastResult;
		}
		/**
		 * @private
		 */
		public function set groupAdd_lastResult(lastResult:Number):void
		{
			_groupAdd_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addGroupAdd()
		 */
		public function addgroupAddEventListener(listener:Function):void
		{
			addEventListener(GroupAddResultEvent.GroupAdd_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _GroupAdd_populate_results(event:ResultEvent):void
		{
			var e:GroupAddResultEvent = new GroupAddResultEvent();
		            e.result = event.result as Number;
		                       e.headers = event.headers;
		             groupAdd_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//stub functions for the GroupRemove operation
          

        /**
         * @see ICloudObserverService#GroupRemove()
         */
        public function groupRemove(groupID:Number):AsyncToken
        {
         	var _internal_token:AsyncToken = _baseService.groupRemove(groupID);
            _internal_token.addEventListener("result",_GroupRemove_populate_results);
            _internal_token.addEventListener("fault",throwFault); 
            return _internal_token;
		}
        /**
		 * @see ICloudObserverService#GroupRemove_send()
		 */    
        public function groupRemove_send():AsyncToken
        {
        	return groupRemove(_GroupRemove_request.groupID);
        }
              
		/**
		 * Internal representation of the request wrapper for the operation
		 * @private
		 */
		private var _GroupRemove_request:GroupRemove_request;
		/**
		 * @see ICloudObserverService#GroupRemove_request_var
		 */
		[Bindable]
		public function get groupRemove_request_var():GroupRemove_request
		{
			return _GroupRemove_request;
		}
		
		/**
		 * @private
		 */
		public function set groupRemove_request_var(request:GroupRemove_request):void
		{
			_GroupRemove_request = request;
		}
		
	  		/**
		 * Internal variable to store the operation's lastResult
		 * @private
		 */
        private var _groupRemove_lastResult:Object;
		[Bindable]
		/**
		 * @see ICloudObserverService#GroupRemove_lastResult
		 */	  
		public function get groupRemove_lastResult():Object
		{
			return _groupRemove_lastResult;
		}
		/**
		 * @private
		 */
		public function set groupRemove_lastResult(lastResult:Object):void
		{
			_groupRemove_lastResult = lastResult;
		}
		
		/**
		 * @see ICloudObserverService#addGroupRemove()
		 */
		public function addgroupRemoveEventListener(listener:Function):void
		{
			addEventListener(GroupRemoveResultEvent.GroupRemove_RESULT,listener);
		}
			
		/**
		 * @private
		 */
        private function _GroupRemove_populate_results(event:ResultEvent):void
		{
			var e:GroupRemoveResultEvent = new GroupRemoveResultEvent();
		            e.result = event.result as Object;
		                       e.headers = event.headers;
		             groupRemove_lastResult = e.result;
		             dispatchEvent(e);
	        		}
		
		//service-wide functions
		/**
		 * @see ICloudObserverService#getWebService()
		 */
		public function getWebService():BaseCloudObserverService
		{
			return _baseService;
		}
		
		/**
		 * Set the event listener for the fault event which can be triggered by each of the operations defined by the facade
		 */
		public function addCloudObserverServiceFaultEventListener(listener:Function):void
		{
			addEventListener("fault",listener);
		}
		
		/**
		 * Internal function to re-dispatch the fault event passed on by the base service implementation
		 * @private
		 */
		 
		 private function throwFault(event:FaultEvent):void
		 {
		 	dispatchEvent(event);
		 }
    }
}
