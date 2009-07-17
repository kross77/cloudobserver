
/**
 * Service.as
 * This file was auto-generated from WSDL by the Apache Axis2 generator modified by Adobe
 * Any change made to this file will be overwritten when the code is re-generated.
 */
package generated.webservices{
	import mx.rpc.AsyncToken;
	import flash.utils.ByteArray;
	import mx.rpc.soap.types.*;
               
    public interface ICloudObserverService
    {
    	//Stub functions for the GroupGetID operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param name
    	 * @return An AsyncToken
    	 */
    	function groupGetID(name:String):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function groupGetID_send():AsyncToken;
        
        /**
         * The groupGetID operation lastResult property
         */
        function get groupGetID_lastResult():Number;
		/**
		 * @private
		 */
        function set groupGetID_lastResult(lastResult:Number):void;
       /**
        * Add a listener for the groupGetID operation successful result event
        * @param The listener function
        */
       function addgroupGetIDEventListener(listener:Function):void;
       
       
        /**
         * The groupGetID operation request wrapper
         */
        function get groupGetID_request_var():GroupGetID_request;
        
        /**
         * @private
         */
        function set groupGetID_request_var(request:GroupGetID_request):void;
                   
    	//Stub functions for the GroupGetName operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param groupID
    	 * @return An AsyncToken
    	 */
    	function groupGetName(groupID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function groupGetName_send():AsyncToken;
        
        /**
         * The groupGetName operation lastResult property
         */
        function get groupGetName_lastResult():String;
		/**
		 * @private
		 */
        function set groupGetName_lastResult(lastResult:String):void;
       /**
        * Add a listener for the groupGetName operation successful result event
        * @param The listener function
        */
       function addgroupGetNameEventListener(listener:Function):void;
       
       
        /**
         * The groupGetName operation request wrapper
         */
        function get groupGetName_request_var():GroupGetName_request;
        
        /**
         * @private
         */
        function set groupGetName_request_var(request:GroupGetName_request):void;
                   
    	//Stub functions for the GroupGetDescription operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param groupID
    	 * @return An AsyncToken
    	 */
    	function groupGetDescription(groupID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function groupGetDescription_send():AsyncToken;
        
        /**
         * The groupGetDescription operation lastResult property
         */
        function get groupGetDescription_lastResult():String;
		/**
		 * @private
		 */
        function set groupGetDescription_lastResult(lastResult:String):void;
       /**
        * Add a listener for the groupGetDescription operation successful result event
        * @param The listener function
        */
       function addgroupGetDescriptionEventListener(listener:Function):void;
       
       
        /**
         * The groupGetDescription operation request wrapper
         */
        function get groupGetDescription_request_var():GroupGetDescription_request;
        
        /**
         * @private
         */
        function set groupGetDescription_request_var(request:GroupGetDescription_request):void;
                   
    	//Stub functions for the GroupGetIcon operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param groupID
    	 * @return An AsyncToken
    	 */
    	function groupGetIcon(groupID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function groupGetIcon_send():AsyncToken;
        
        /**
         * The groupGetIcon operation lastResult property
         */
        function get groupGetIcon_lastResult():flash.utils.ByteArray;
		/**
		 * @private
		 */
        function set groupGetIcon_lastResult(lastResult:flash.utils.ByteArray):void;
       /**
        * Add a listener for the groupGetIcon operation successful result event
        * @param The listener function
        */
       function addgroupGetIconEventListener(listener:Function):void;
       
       
        /**
         * The groupGetIcon operation request wrapper
         */
        function get groupGetIcon_request_var():GroupGetIcon_request;
        
        /**
         * @private
         */
        function set groupGetIcon_request_var(request:GroupGetIcon_request):void;
                   
    	//Stub functions for the GroupGetPrivacy operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param groupID
    	 * @return An AsyncToken
    	 */
    	function groupGetPrivacy(groupID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function groupGetPrivacy_send():AsyncToken;
        
        /**
         * The groupGetPrivacy operation lastResult property
         */
        function get groupGetPrivacy_lastResult():Number;
		/**
		 * @private
		 */
        function set groupGetPrivacy_lastResult(lastResult:Number):void;
       /**
        * Add a listener for the groupGetPrivacy operation successful result event
        * @param The listener function
        */
       function addgroupGetPrivacyEventListener(listener:Function):void;
       
       
        /**
         * The groupGetPrivacy operation request wrapper
         */
        function get groupGetPrivacy_request_var():GroupGetPrivacy_request;
        
        /**
         * @private
         */
        function set groupGetPrivacy_request_var(request:GroupGetPrivacy_request):void;
                   
    	//Stub functions for the GroupGetRegistrationDate operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param groupID
    	 * @return An AsyncToken
    	 */
    	function groupGetRegistrationDate(groupID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function groupGetRegistrationDate_send():AsyncToken;
        
        /**
         * The groupGetRegistrationDate operation lastResult property
         */
        function get groupGetRegistrationDate_lastResult():Date;
		/**
		 * @private
		 */
        function set groupGetRegistrationDate_lastResult(lastResult:Date):void;
       /**
        * Add a listener for the groupGetRegistrationDate operation successful result event
        * @param The listener function
        */
       function addgroupGetRegistrationDateEventListener(listener:Function):void;
       
       
        /**
         * The groupGetRegistrationDate operation request wrapper
         */
        function get groupGetRegistrationDate_request_var():GroupGetRegistrationDate_request;
        
        /**
         * @private
         */
        function set groupGetRegistrationDate_request_var(request:GroupGetRegistrationDate_request):void;
                   
    	//Stub functions for the GroupGetMembers operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param groupID
    	 * @return An AsyncToken
    	 */
    	function groupGetMembers(groupID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function groupGetMembers_send():AsyncToken;
        
        /**
         * The groupGetMembers operation lastResult property
         */
        function get groupGetMembers_lastResult():ArrayOfint;
		/**
		 * @private
		 */
        function set groupGetMembers_lastResult(lastResult:ArrayOfint):void;
       /**
        * Add a listener for the groupGetMembers operation successful result event
        * @param The listener function
        */
       function addgroupGetMembersEventListener(listener:Function):void;
       
       
        /**
         * The groupGetMembers operation request wrapper
         */
        function get groupGetMembers_request_var():GroupGetMembers_request;
        
        /**
         * @private
         */
        function set groupGetMembers_request_var(request:GroupGetMembers_request):void;
                   
    	//Stub functions for the GroupGetCameras operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param groupID
    	 * @return An AsyncToken
    	 */
    	function groupGetCameras(groupID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function groupGetCameras_send():AsyncToken;
        
        /**
         * The groupGetCameras operation lastResult property
         */
        function get groupGetCameras_lastResult():ArrayOfint;
		/**
		 * @private
		 */
        function set groupGetCameras_lastResult(lastResult:ArrayOfint):void;
       /**
        * Add a listener for the groupGetCameras operation successful result event
        * @param The listener function
        */
       function addgroupGetCamerasEventListener(listener:Function):void;
       
       
        /**
         * The groupGetCameras operation request wrapper
         */
        function get groupGetCameras_request_var():GroupGetCameras_request;
        
        /**
         * @private
         */
        function set groupGetCameras_request_var(request:GroupGetCameras_request):void;
                   
    	//Stub functions for the GroupSetName operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param groupID
    	 * @param name
    	 * @return An AsyncToken
    	 */
    	function groupSetName(groupID:Number,name:String):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function groupSetName_send():AsyncToken;
        
        /**
         * The groupSetName operation lastResult property
         */
        function get groupSetName_lastResult():Object;
		/**
		 * @private
		 */
        function set groupSetName_lastResult(lastResult:Object):void;
       /**
        * Add a listener for the groupSetName operation successful result event
        * @param The listener function
        */
       function addgroupSetNameEventListener(listener:Function):void;
       
       
        /**
         * The groupSetName operation request wrapper
         */
        function get groupSetName_request_var():GroupSetName_request;
        
        /**
         * @private
         */
        function set groupSetName_request_var(request:GroupSetName_request):void;
                   
    	//Stub functions for the GroupSetDescription operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param groupID
    	 * @param description
    	 * @return An AsyncToken
    	 */
    	function groupSetDescription(groupID:Number,description:String):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function groupSetDescription_send():AsyncToken;
        
        /**
         * The groupSetDescription operation lastResult property
         */
        function get groupSetDescription_lastResult():Object;
		/**
		 * @private
		 */
        function set groupSetDescription_lastResult(lastResult:Object):void;
       /**
        * Add a listener for the groupSetDescription operation successful result event
        * @param The listener function
        */
       function addgroupSetDescriptionEventListener(listener:Function):void;
       
       
        /**
         * The groupSetDescription operation request wrapper
         */
        function get groupSetDescription_request_var():GroupSetDescription_request;
        
        /**
         * @private
         */
        function set groupSetDescription_request_var(request:GroupSetDescription_request):void;
                   
    	//Stub functions for the GroupSetIcon operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param groupID
    	 * @param icon
    	 * @return An AsyncToken
    	 */
    	function groupSetIcon(groupID:Number,icon:flash.utils.ByteArray):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function groupSetIcon_send():AsyncToken;
        
        /**
         * The groupSetIcon operation lastResult property
         */
        function get groupSetIcon_lastResult():Object;
		/**
		 * @private
		 */
        function set groupSetIcon_lastResult(lastResult:Object):void;
       /**
        * Add a listener for the groupSetIcon operation successful result event
        * @param The listener function
        */
       function addgroupSetIconEventListener(listener:Function):void;
       
       
        /**
         * The groupSetIcon operation request wrapper
         */
        function get groupSetIcon_request_var():GroupSetIcon_request;
        
        /**
         * @private
         */
        function set groupSetIcon_request_var(request:GroupSetIcon_request):void;
                   
    	//Stub functions for the GroupSetPrivacy operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param groupID
    	 * @param privacy
    	 * @return An AsyncToken
    	 */
    	function groupSetPrivacy(groupID:Number,privacy:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function groupSetPrivacy_send():AsyncToken;
        
        /**
         * The groupSetPrivacy operation lastResult property
         */
        function get groupSetPrivacy_lastResult():Object;
		/**
		 * @private
		 */
        function set groupSetPrivacy_lastResult(lastResult:Object):void;
       /**
        * Add a listener for the groupSetPrivacy operation successful result event
        * @param The listener function
        */
       function addgroupSetPrivacyEventListener(listener:Function):void;
       
       
        /**
         * The groupSetPrivacy operation request wrapper
         */
        function get groupSetPrivacy_request_var():GroupSetPrivacy_request;
        
        /**
         * @private
         */
        function set groupSetPrivacy_request_var(request:GroupSetPrivacy_request):void;
                   
    	//Stub functions for the GroupMemberAdd operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param userID
    	 * @param groupID
    	 * @param privileges
    	 * @return An AsyncToken
    	 */
    	function groupMemberAdd(userID:Number,groupID:Number,privileges:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function groupMemberAdd_send():AsyncToken;
        
        /**
         * The groupMemberAdd operation lastResult property
         */
        function get groupMemberAdd_lastResult():Object;
		/**
		 * @private
		 */
        function set groupMemberAdd_lastResult(lastResult:Object):void;
       /**
        * Add a listener for the groupMemberAdd operation successful result event
        * @param The listener function
        */
       function addgroupMemberAddEventListener(listener:Function):void;
       
       
        /**
         * The groupMemberAdd operation request wrapper
         */
        function get groupMemberAdd_request_var():GroupMemberAdd_request;
        
        /**
         * @private
         */
        function set groupMemberAdd_request_var(request:GroupMemberAdd_request):void;
                   
    	//Stub functions for the GroupMemberRemove operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param userID
    	 * @param groupID
    	 * @return An AsyncToken
    	 */
    	function groupMemberRemove(userID:Number,groupID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function groupMemberRemove_send():AsyncToken;
        
        /**
         * The groupMemberRemove operation lastResult property
         */
        function get groupMemberRemove_lastResult():Object;
		/**
		 * @private
		 */
        function set groupMemberRemove_lastResult(lastResult:Object):void;
       /**
        * Add a listener for the groupMemberRemove operation successful result event
        * @param The listener function
        */
       function addgroupMemberRemoveEventListener(listener:Function):void;
       
       
        /**
         * The groupMemberRemove operation request wrapper
         */
        function get groupMemberRemove_request_var():GroupMemberRemove_request;
        
        /**
         * @private
         */
        function set groupMemberRemove_request_var(request:GroupMemberRemove_request):void;
                   
    	//Stub functions for the GroupMemberGetPrivileges operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param userID
    	 * @param groupID
    	 * @return An AsyncToken
    	 */
    	function groupMemberGetPrivileges(userID:Number,groupID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function groupMemberGetPrivileges_send():AsyncToken;
        
        /**
         * The groupMemberGetPrivileges operation lastResult property
         */
        function get groupMemberGetPrivileges_lastResult():Number;
		/**
		 * @private
		 */
        function set groupMemberGetPrivileges_lastResult(lastResult:Number):void;
       /**
        * Add a listener for the groupMemberGetPrivileges operation successful result event
        * @param The listener function
        */
       function addgroupMemberGetPrivilegesEventListener(listener:Function):void;
       
       
        /**
         * The groupMemberGetPrivileges operation request wrapper
         */
        function get groupMemberGetPrivileges_request_var():GroupMemberGetPrivileges_request;
        
        /**
         * @private
         */
        function set groupMemberGetPrivileges_request_var(request:GroupMemberGetPrivileges_request):void;
                   
    	//Stub functions for the GroupMemberSetPrivileges operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param userID
    	 * @param groupID
    	 * @param privileges
    	 * @return An AsyncToken
    	 */
    	function groupMemberSetPrivileges(userID:Number,groupID:Number,privileges:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function groupMemberSetPrivileges_send():AsyncToken;
        
        /**
         * The groupMemberSetPrivileges operation lastResult property
         */
        function get groupMemberSetPrivileges_lastResult():Object;
		/**
		 * @private
		 */
        function set groupMemberSetPrivileges_lastResult(lastResult:Object):void;
       /**
        * Add a listener for the groupMemberSetPrivileges operation successful result event
        * @param The listener function
        */
       function addgroupMemberSetPrivilegesEventListener(listener:Function):void;
       
       
        /**
         * The groupMemberSetPrivileges operation request wrapper
         */
        function get groupMemberSetPrivileges_request_var():GroupMemberSetPrivileges_request;
        
        /**
         * @private
         */
        function set groupMemberSetPrivileges_request_var(request:GroupMemberSetPrivileges_request):void;
                   
    	//Stub functions for the GroupCameraAdd operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param cameraID
    	 * @param groupID
    	 * @return An AsyncToken
    	 */
    	function groupCameraAdd(cameraID:Number,groupID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function groupCameraAdd_send():AsyncToken;
        
        /**
         * The groupCameraAdd operation lastResult property
         */
        function get groupCameraAdd_lastResult():Object;
		/**
		 * @private
		 */
        function set groupCameraAdd_lastResult(lastResult:Object):void;
       /**
        * Add a listener for the groupCameraAdd operation successful result event
        * @param The listener function
        */
       function addgroupCameraAddEventListener(listener:Function):void;
       
       
        /**
         * The groupCameraAdd operation request wrapper
         */
        function get groupCameraAdd_request_var():GroupCameraAdd_request;
        
        /**
         * @private
         */
        function set groupCameraAdd_request_var(request:GroupCameraAdd_request):void;
                   
    	//Stub functions for the GroupCameraRemove operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param cameraID
    	 * @param groupID
    	 * @return An AsyncToken
    	 */
    	function groupCameraRemove(cameraID:Number,groupID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function groupCameraRemove_send():AsyncToken;
        
        /**
         * The groupCameraRemove operation lastResult property
         */
        function get groupCameraRemove_lastResult():Object;
		/**
		 * @private
		 */
        function set groupCameraRemove_lastResult(lastResult:Object):void;
       /**
        * Add a listener for the groupCameraRemove operation successful result event
        * @param The listener function
        */
       function addgroupCameraRemoveEventListener(listener:Function):void;
       
       
        /**
         * The groupCameraRemove operation request wrapper
         */
        function get groupCameraRemove_request_var():GroupCameraRemove_request;
        
        /**
         * @private
         */
        function set groupCameraRemove_request_var(request:GroupCameraRemove_request):void;
                   
    	//Stub functions for the FrameAdd operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param cameraID
    	 * @param content
    	 * @param marker
    	 * @return An AsyncToken
    	 */
    	function frameAdd(cameraID:Number,content:flash.utils.ByteArray,marker:String):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function frameAdd_send():AsyncToken;
        
        /**
         * The frameAdd operation lastResult property
         */
        function get frameAdd_lastResult():Number;
		/**
		 * @private
		 */
        function set frameAdd_lastResult(lastResult:Number):void;
       /**
        * Add a listener for the frameAdd operation successful result event
        * @param The listener function
        */
       function addframeAddEventListener(listener:Function):void;
       
       
        /**
         * The frameAdd operation request wrapper
         */
        function get frameAdd_request_var():FrameAdd_request;
        
        /**
         * @private
         */
        function set frameAdd_request_var(request:FrameAdd_request):void;
                   
    	//Stub functions for the FrameRemove operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param frameID
    	 * @return An AsyncToken
    	 */
    	function frameRemove(frameID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function frameRemove_send():AsyncToken;
        
        /**
         * The frameRemove operation lastResult property
         */
        function get frameRemove_lastResult():Object;
		/**
		 * @private
		 */
        function set frameRemove_lastResult(lastResult:Object):void;
       /**
        * Add a listener for the frameRemove operation successful result event
        * @param The listener function
        */
       function addframeRemoveEventListener(listener:Function):void;
       
       
        /**
         * The frameRemove operation request wrapper
         */
        function get frameRemove_request_var():FrameRemove_request;
        
        /**
         * @private
         */
        function set frameRemove_request_var(request:FrameRemove_request):void;
                   
    	//Stub functions for the FrameGetContent operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param frameID
    	 * @return An AsyncToken
    	 */
    	function frameGetContent(frameID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function frameGetContent_send():AsyncToken;
        
        /**
         * The frameGetContent operation lastResult property
         */
        function get frameGetContent_lastResult():flash.utils.ByteArray;
		/**
		 * @private
		 */
        function set frameGetContent_lastResult(lastResult:flash.utils.ByteArray):void;
       /**
        * Add a listener for the frameGetContent operation successful result event
        * @param The listener function
        */
       function addframeGetContentEventListener(listener:Function):void;
       
       
        /**
         * The frameGetContent operation request wrapper
         */
        function get frameGetContent_request_var():FrameGetContent_request;
        
        /**
         * @private
         */
        function set frameGetContent_request_var(request:FrameGetContent_request):void;
                   
    	//Stub functions for the FrameGetMarker operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param frameID
    	 * @return An AsyncToken
    	 */
    	function frameGetMarker(frameID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function frameGetMarker_send():AsyncToken;
        
        /**
         * The frameGetMarker operation lastResult property
         */
        function get frameGetMarker_lastResult():String;
		/**
		 * @private
		 */
        function set frameGetMarker_lastResult(lastResult:String):void;
       /**
        * Add a listener for the frameGetMarker operation successful result event
        * @param The listener function
        */
       function addframeGetMarkerEventListener(listener:Function):void;
       
       
        /**
         * The frameGetMarker operation request wrapper
         */
        function get frameGetMarker_request_var():FrameGetMarker_request;
        
        /**
         * @private
         */
        function set frameGetMarker_request_var(request:FrameGetMarker_request):void;
                   
    	//Stub functions for the UserIsEmailAvailable operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param email
    	 * @return An AsyncToken
    	 */
    	function userIsEmailAvailable(email:String):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function userIsEmailAvailable_send():AsyncToken;
        
        /**
         * The userIsEmailAvailable operation lastResult property
         */
        function get userIsEmailAvailable_lastResult():Boolean;
		/**
		 * @private
		 */
        function set userIsEmailAvailable_lastResult(lastResult:Boolean):void;
       /**
        * Add a listener for the userIsEmailAvailable operation successful result event
        * @param The listener function
        */
       function adduserIsEmailAvailableEventListener(listener:Function):void;
       
       
        /**
         * The userIsEmailAvailable operation request wrapper
         */
        function get userIsEmailAvailable_request_var():UserIsEmailAvailable_request;
        
        /**
         * @private
         */
        function set userIsEmailAvailable_request_var(request:UserIsEmailAvailable_request):void;
                   
    	//Stub functions for the UserLogin operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param email
    	 * @param password
    	 * @return An AsyncToken
    	 */
    	function userLogin(email:String,password:String):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function userLogin_send():AsyncToken;
        
        /**
         * The userLogin operation lastResult property
         */
        function get userLogin_lastResult():Boolean;
		/**
		 * @private
		 */
        function set userLogin_lastResult(lastResult:Boolean):void;
       /**
        * Add a listener for the userLogin operation successful result event
        * @param The listener function
        */
       function adduserLoginEventListener(listener:Function):void;
       
       
        /**
         * The userLogin operation request wrapper
         */
        function get userLogin_request_var():UserLogin_request;
        
        /**
         * @private
         */
        function set userLogin_request_var(request:UserLogin_request):void;
                   
    	//Stub functions for the UserAdd operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param email
    	 * @param password
    	 * @param name
    	 * @param description
    	 * @param icon
    	 * @return An AsyncToken
    	 */
    	function userAdd(email:String,password:String,name:String,description:String,icon:flash.utils.ByteArray):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function userAdd_send():AsyncToken;
        
        /**
         * The userAdd operation lastResult property
         */
        function get userAdd_lastResult():Number;
		/**
		 * @private
		 */
        function set userAdd_lastResult(lastResult:Number):void;
       /**
        * Add a listener for the userAdd operation successful result event
        * @param The listener function
        */
       function adduserAddEventListener(listener:Function):void;
       
       
        /**
         * The userAdd operation request wrapper
         */
        function get userAdd_request_var():UserAdd_request;
        
        /**
         * @private
         */
        function set userAdd_request_var(request:UserAdd_request):void;
                   
    	//Stub functions for the UserRemove operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param userID
    	 * @return An AsyncToken
    	 */
    	function userRemove(userID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function userRemove_send():AsyncToken;
        
        /**
         * The userRemove operation lastResult property
         */
        function get userRemove_lastResult():Object;
		/**
		 * @private
		 */
        function set userRemove_lastResult(lastResult:Object):void;
       /**
        * Add a listener for the userRemove operation successful result event
        * @param The listener function
        */
       function adduserRemoveEventListener(listener:Function):void;
       
       
        /**
         * The userRemove operation request wrapper
         */
        function get userRemove_request_var():UserRemove_request;
        
        /**
         * @private
         */
        function set userRemove_request_var(request:UserRemove_request):void;
                   
    	//Stub functions for the UserGetID operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param email
    	 * @return An AsyncToken
    	 */
    	function userGetID(email:String):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function userGetID_send():AsyncToken;
        
        /**
         * The userGetID operation lastResult property
         */
        function get userGetID_lastResult():Number;
		/**
		 * @private
		 */
        function set userGetID_lastResult(lastResult:Number):void;
       /**
        * Add a listener for the userGetID operation successful result event
        * @param The listener function
        */
       function adduserGetIDEventListener(listener:Function):void;
       
       
        /**
         * The userGetID operation request wrapper
         */
        function get userGetID_request_var():UserGetID_request;
        
        /**
         * @private
         */
        function set userGetID_request_var(request:UserGetID_request):void;
                   
    	//Stub functions for the UserGetEmail operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param userID
    	 * @return An AsyncToken
    	 */
    	function userGetEmail(userID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function userGetEmail_send():AsyncToken;
        
        /**
         * The userGetEmail operation lastResult property
         */
        function get userGetEmail_lastResult():String;
		/**
		 * @private
		 */
        function set userGetEmail_lastResult(lastResult:String):void;
       /**
        * Add a listener for the userGetEmail operation successful result event
        * @param The listener function
        */
       function adduserGetEmailEventListener(listener:Function):void;
       
       
        /**
         * The userGetEmail operation request wrapper
         */
        function get userGetEmail_request_var():UserGetEmail_request;
        
        /**
         * @private
         */
        function set userGetEmail_request_var(request:UserGetEmail_request):void;
                   
    	//Stub functions for the UserGetPassword operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param userID
    	 * @return An AsyncToken
    	 */
    	function userGetPassword(userID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function userGetPassword_send():AsyncToken;
        
        /**
         * The userGetPassword operation lastResult property
         */
        function get userGetPassword_lastResult():String;
		/**
		 * @private
		 */
        function set userGetPassword_lastResult(lastResult:String):void;
       /**
        * Add a listener for the userGetPassword operation successful result event
        * @param The listener function
        */
       function adduserGetPasswordEventListener(listener:Function):void;
       
       
        /**
         * The userGetPassword operation request wrapper
         */
        function get userGetPassword_request_var():UserGetPassword_request;
        
        /**
         * @private
         */
        function set userGetPassword_request_var(request:UserGetPassword_request):void;
                   
    	//Stub functions for the UserGetName operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param userID
    	 * @return An AsyncToken
    	 */
    	function userGetName(userID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function userGetName_send():AsyncToken;
        
        /**
         * The userGetName operation lastResult property
         */
        function get userGetName_lastResult():String;
		/**
		 * @private
		 */
        function set userGetName_lastResult(lastResult:String):void;
       /**
        * Add a listener for the userGetName operation successful result event
        * @param The listener function
        */
       function adduserGetNameEventListener(listener:Function):void;
       
       
        /**
         * The userGetName operation request wrapper
         */
        function get userGetName_request_var():UserGetName_request;
        
        /**
         * @private
         */
        function set userGetName_request_var(request:UserGetName_request):void;
                   
    	//Stub functions for the UserGetDescription operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param userID
    	 * @return An AsyncToken
    	 */
    	function userGetDescription(userID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function userGetDescription_send():AsyncToken;
        
        /**
         * The userGetDescription operation lastResult property
         */
        function get userGetDescription_lastResult():String;
		/**
		 * @private
		 */
        function set userGetDescription_lastResult(lastResult:String):void;
       /**
        * Add a listener for the userGetDescription operation successful result event
        * @param The listener function
        */
       function adduserGetDescriptionEventListener(listener:Function):void;
       
       
        /**
         * The userGetDescription operation request wrapper
         */
        function get userGetDescription_request_var():UserGetDescription_request;
        
        /**
         * @private
         */
        function set userGetDescription_request_var(request:UserGetDescription_request):void;
                   
    	//Stub functions for the UserGetIcon operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param userID
    	 * @return An AsyncToken
    	 */
    	function userGetIcon(userID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function userGetIcon_send():AsyncToken;
        
        /**
         * The userGetIcon operation lastResult property
         */
        function get userGetIcon_lastResult():flash.utils.ByteArray;
		/**
		 * @private
		 */
        function set userGetIcon_lastResult(lastResult:flash.utils.ByteArray):void;
       /**
        * Add a listener for the userGetIcon operation successful result event
        * @param The listener function
        */
       function adduserGetIconEventListener(listener:Function):void;
       
       
        /**
         * The userGetIcon operation request wrapper
         */
        function get userGetIcon_request_var():UserGetIcon_request;
        
        /**
         * @private
         */
        function set userGetIcon_request_var(request:UserGetIcon_request):void;
                   
    	//Stub functions for the UserGetRegistrationDate operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param userID
    	 * @return An AsyncToken
    	 */
    	function userGetRegistrationDate(userID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function userGetRegistrationDate_send():AsyncToken;
        
        /**
         * The userGetRegistrationDate operation lastResult property
         */
        function get userGetRegistrationDate_lastResult():Date;
		/**
		 * @private
		 */
        function set userGetRegistrationDate_lastResult(lastResult:Date):void;
       /**
        * Add a listener for the userGetRegistrationDate operation successful result event
        * @param The listener function
        */
       function adduserGetRegistrationDateEventListener(listener:Function):void;
       
       
        /**
         * The userGetRegistrationDate operation request wrapper
         */
        function get userGetRegistrationDate_request_var():UserGetRegistrationDate_request;
        
        /**
         * @private
         */
        function set userGetRegistrationDate_request_var(request:UserGetRegistrationDate_request):void;
                   
    	//Stub functions for the UserGetGroups operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param userID
    	 * @return An AsyncToken
    	 */
    	function userGetGroups(userID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function userGetGroups_send():AsyncToken;
        
        /**
         * The userGetGroups operation lastResult property
         */
        function get userGetGroups_lastResult():ArrayOfint;
		/**
		 * @private
		 */
        function set userGetGroups_lastResult(lastResult:ArrayOfint):void;
       /**
        * Add a listener for the userGetGroups operation successful result event
        * @param The listener function
        */
       function adduserGetGroupsEventListener(listener:Function):void;
       
       
        /**
         * The userGetGroups operation request wrapper
         */
        function get userGetGroups_request_var():UserGetGroups_request;
        
        /**
         * @private
         */
        function set userGetGroups_request_var(request:UserGetGroups_request):void;
                   
    	//Stub functions for the UserSetPassword operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param userID
    	 * @param password
    	 * @return An AsyncToken
    	 */
    	function userSetPassword(userID:Number,password:String):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function userSetPassword_send():AsyncToken;
        
        /**
         * The userSetPassword operation lastResult property
         */
        function get userSetPassword_lastResult():Object;
		/**
		 * @private
		 */
        function set userSetPassword_lastResult(lastResult:Object):void;
       /**
        * Add a listener for the userSetPassword operation successful result event
        * @param The listener function
        */
       function adduserSetPasswordEventListener(listener:Function):void;
       
       
        /**
         * The userSetPassword operation request wrapper
         */
        function get userSetPassword_request_var():UserSetPassword_request;
        
        /**
         * @private
         */
        function set userSetPassword_request_var(request:UserSetPassword_request):void;
                   
    	//Stub functions for the UserSetName operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param userID
    	 * @param name
    	 * @return An AsyncToken
    	 */
    	function userSetName(userID:Number,name:String):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function userSetName_send():AsyncToken;
        
        /**
         * The userSetName operation lastResult property
         */
        function get userSetName_lastResult():Object;
		/**
		 * @private
		 */
        function set userSetName_lastResult(lastResult:Object):void;
       /**
        * Add a listener for the userSetName operation successful result event
        * @param The listener function
        */
       function adduserSetNameEventListener(listener:Function):void;
       
       
        /**
         * The userSetName operation request wrapper
         */
        function get userSetName_request_var():UserSetName_request;
        
        /**
         * @private
         */
        function set userSetName_request_var(request:UserSetName_request):void;
                   
    	//Stub functions for the UserSetDescription operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param userID
    	 * @param description
    	 * @return An AsyncToken
    	 */
    	function userSetDescription(userID:Number,description:String):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function userSetDescription_send():AsyncToken;
        
        /**
         * The userSetDescription operation lastResult property
         */
        function get userSetDescription_lastResult():Object;
		/**
		 * @private
		 */
        function set userSetDescription_lastResult(lastResult:Object):void;
       /**
        * Add a listener for the userSetDescription operation successful result event
        * @param The listener function
        */
       function adduserSetDescriptionEventListener(listener:Function):void;
       
       
        /**
         * The userSetDescription operation request wrapper
         */
        function get userSetDescription_request_var():UserSetDescription_request;
        
        /**
         * @private
         */
        function set userSetDescription_request_var(request:UserSetDescription_request):void;
                   
    	//Stub functions for the UserSetIcon operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param userID
    	 * @param icon
    	 * @return An AsyncToken
    	 */
    	function userSetIcon(userID:Number,icon:flash.utils.ByteArray):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function userSetIcon_send():AsyncToken;
        
        /**
         * The userSetIcon operation lastResult property
         */
        function get userSetIcon_lastResult():Object;
		/**
		 * @private
		 */
        function set userSetIcon_lastResult(lastResult:Object):void;
       /**
        * Add a listener for the userSetIcon operation successful result event
        * @param The listener function
        */
       function adduserSetIconEventListener(listener:Function):void;
       
       
        /**
         * The userSetIcon operation request wrapper
         */
        function get userSetIcon_request_var():UserSetIcon_request;
        
        /**
         * @private
         */
        function set userSetIcon_request_var(request:UserSetIcon_request):void;
                   
    	//Stub functions for the CameraIsPathAvailable operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param path
    	 * @return An AsyncToken
    	 */
    	function cameraIsPathAvailable(path:String):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function cameraIsPathAvailable_send():AsyncToken;
        
        /**
         * The cameraIsPathAvailable operation lastResult property
         */
        function get cameraIsPathAvailable_lastResult():Boolean;
		/**
		 * @private
		 */
        function set cameraIsPathAvailable_lastResult(lastResult:Boolean):void;
       /**
        * Add a listener for the cameraIsPathAvailable operation successful result event
        * @param The listener function
        */
       function addcameraIsPathAvailableEventListener(listener:Function):void;
       
       
        /**
         * The cameraIsPathAvailable operation request wrapper
         */
        function get cameraIsPathAvailable_request_var():CameraIsPathAvailable_request;
        
        /**
         * @private
         */
        function set cameraIsPathAvailable_request_var(request:CameraIsPathAvailable_request):void;
                   
    	//Stub functions for the CameraAdd operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param name
    	 * @param description
    	 * @param icon
    	 * @return An AsyncToken
    	 */
    	function cameraAdd(name:String,description:String,icon:flash.utils.ByteArray):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function cameraAdd_send():AsyncToken;
        
        /**
         * The cameraAdd operation lastResult property
         */
        function get cameraAdd_lastResult():Number;
		/**
		 * @private
		 */
        function set cameraAdd_lastResult(lastResult:Number):void;
       /**
        * Add a listener for the cameraAdd operation successful result event
        * @param The listener function
        */
       function addcameraAddEventListener(listener:Function):void;
       
       
        /**
         * The cameraAdd operation request wrapper
         */
        function get cameraAdd_request_var():CameraAdd_request;
        
        /**
         * @private
         */
        function set cameraAdd_request_var(request:CameraAdd_request):void;
                   
    	//Stub functions for the CameraRemove operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param cameraID
    	 * @return An AsyncToken
    	 */
    	function cameraRemove(cameraID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function cameraRemove_send():AsyncToken;
        
        /**
         * The cameraRemove operation lastResult property
         */
        function get cameraRemove_lastResult():Object;
		/**
		 * @private
		 */
        function set cameraRemove_lastResult(lastResult:Object):void;
       /**
        * Add a listener for the cameraRemove operation successful result event
        * @param The listener function
        */
       function addcameraRemoveEventListener(listener:Function):void;
       
       
        /**
         * The cameraRemove operation request wrapper
         */
        function get cameraRemove_request_var():CameraRemove_request;
        
        /**
         * @private
         */
        function set cameraRemove_request_var(request:CameraRemove_request):void;
                   
    	//Stub functions for the CameraGetID operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param path
    	 * @return An AsyncToken
    	 */
    	function cameraGetID(path:String):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function cameraGetID_send():AsyncToken;
        
        /**
         * The cameraGetID operation lastResult property
         */
        function get cameraGetID_lastResult():Number;
		/**
		 * @private
		 */
        function set cameraGetID_lastResult(lastResult:Number):void;
       /**
        * Add a listener for the cameraGetID operation successful result event
        * @param The listener function
        */
       function addcameraGetIDEventListener(listener:Function):void;
       
       
        /**
         * The cameraGetID operation request wrapper
         */
        function get cameraGetID_request_var():CameraGetID_request;
        
        /**
         * @private
         */
        function set cameraGetID_request_var(request:CameraGetID_request):void;
                   
    	//Stub functions for the CameraGetPath operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param cameraID
    	 * @return An AsyncToken
    	 */
    	function cameraGetPath(cameraID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function cameraGetPath_send():AsyncToken;
        
        /**
         * The cameraGetPath operation lastResult property
         */
        function get cameraGetPath_lastResult():String;
		/**
		 * @private
		 */
        function set cameraGetPath_lastResult(lastResult:String):void;
       /**
        * Add a listener for the cameraGetPath operation successful result event
        * @param The listener function
        */
       function addcameraGetPathEventListener(listener:Function):void;
       
       
        /**
         * The cameraGetPath operation request wrapper
         */
        function get cameraGetPath_request_var():CameraGetPath_request;
        
        /**
         * @private
         */
        function set cameraGetPath_request_var(request:CameraGetPath_request):void;
                   
    	//Stub functions for the CameraGetName operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param cameraID
    	 * @return An AsyncToken
    	 */
    	function cameraGetName(cameraID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function cameraGetName_send():AsyncToken;
        
        /**
         * The cameraGetName operation lastResult property
         */
        function get cameraGetName_lastResult():String;
		/**
		 * @private
		 */
        function set cameraGetName_lastResult(lastResult:String):void;
       /**
        * Add a listener for the cameraGetName operation successful result event
        * @param The listener function
        */
       function addcameraGetNameEventListener(listener:Function):void;
       
       
        /**
         * The cameraGetName operation request wrapper
         */
        function get cameraGetName_request_var():CameraGetName_request;
        
        /**
         * @private
         */
        function set cameraGetName_request_var(request:CameraGetName_request):void;
                   
    	//Stub functions for the CameraGetDescription operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param cameraID
    	 * @return An AsyncToken
    	 */
    	function cameraGetDescription(cameraID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function cameraGetDescription_send():AsyncToken;
        
        /**
         * The cameraGetDescription operation lastResult property
         */
        function get cameraGetDescription_lastResult():String;
		/**
		 * @private
		 */
        function set cameraGetDescription_lastResult(lastResult:String):void;
       /**
        * Add a listener for the cameraGetDescription operation successful result event
        * @param The listener function
        */
       function addcameraGetDescriptionEventListener(listener:Function):void;
       
       
        /**
         * The cameraGetDescription operation request wrapper
         */
        function get cameraGetDescription_request_var():CameraGetDescription_request;
        
        /**
         * @private
         */
        function set cameraGetDescription_request_var(request:CameraGetDescription_request):void;
                   
    	//Stub functions for the CameraGetIcon operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param cameraID
    	 * @return An AsyncToken
    	 */
    	function cameraGetIcon(cameraID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function cameraGetIcon_send():AsyncToken;
        
        /**
         * The cameraGetIcon operation lastResult property
         */
        function get cameraGetIcon_lastResult():flash.utils.ByteArray;
		/**
		 * @private
		 */
        function set cameraGetIcon_lastResult(lastResult:flash.utils.ByteArray):void;
       /**
        * Add a listener for the cameraGetIcon operation successful result event
        * @param The listener function
        */
       function addcameraGetIconEventListener(listener:Function):void;
       
       
        /**
         * The cameraGetIcon operation request wrapper
         */
        function get cameraGetIcon_request_var():CameraGetIcon_request;
        
        /**
         * @private
         */
        function set cameraGetIcon_request_var(request:CameraGetIcon_request):void;
                   
    	//Stub functions for the CameraGetRegistrationDate operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param cameraID
    	 * @return An AsyncToken
    	 */
    	function cameraGetRegistrationDate(cameraID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function cameraGetRegistrationDate_send():AsyncToken;
        
        /**
         * The cameraGetRegistrationDate operation lastResult property
         */
        function get cameraGetRegistrationDate_lastResult():Date;
		/**
		 * @private
		 */
        function set cameraGetRegistrationDate_lastResult(lastResult:Date):void;
       /**
        * Add a listener for the cameraGetRegistrationDate operation successful result event
        * @param The listener function
        */
       function addcameraGetRegistrationDateEventListener(listener:Function):void;
       
       
        /**
         * The cameraGetRegistrationDate operation request wrapper
         */
        function get cameraGetRegistrationDate_request_var():CameraGetRegistrationDate_request;
        
        /**
         * @private
         */
        function set cameraGetRegistrationDate_request_var(request:CameraGetRegistrationDate_request):void;
                   
    	//Stub functions for the CameraGetGroups operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param cameraID
    	 * @return An AsyncToken
    	 */
    	function cameraGetGroups(cameraID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function cameraGetGroups_send():AsyncToken;
        
        /**
         * The cameraGetGroups operation lastResult property
         */
        function get cameraGetGroups_lastResult():ArrayOfint;
		/**
		 * @private
		 */
        function set cameraGetGroups_lastResult(lastResult:ArrayOfint):void;
       /**
        * Add a listener for the cameraGetGroups operation successful result event
        * @param The listener function
        */
       function addcameraGetGroupsEventListener(listener:Function):void;
       
       
        /**
         * The cameraGetGroups operation request wrapper
         */
        function get cameraGetGroups_request_var():CameraGetGroups_request;
        
        /**
         * @private
         */
        function set cameraGetGroups_request_var(request:CameraGetGroups_request):void;
                   
    	//Stub functions for the CameraGetFrames operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param cameraID
    	 * @return An AsyncToken
    	 */
    	function cameraGetFrames(cameraID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function cameraGetFrames_send():AsyncToken;
        
        /**
         * The cameraGetFrames operation lastResult property
         */
        function get cameraGetFrames_lastResult():ArrayOfint;
		/**
		 * @private
		 */
        function set cameraGetFrames_lastResult(lastResult:ArrayOfint):void;
       /**
        * Add a listener for the cameraGetFrames operation successful result event
        * @param The listener function
        */
       function addcameraGetFramesEventListener(listener:Function):void;
       
       
        /**
         * The cameraGetFrames operation request wrapper
         */
        function get cameraGetFrames_request_var():CameraGetFrames_request;
        
        /**
         * @private
         */
        function set cameraGetFrames_request_var(request:CameraGetFrames_request):void;
                   
    	//Stub functions for the CameraSetName operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param cameraID
    	 * @param name
    	 * @return An AsyncToken
    	 */
    	function cameraSetName(cameraID:Number,name:String):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function cameraSetName_send():AsyncToken;
        
        /**
         * The cameraSetName operation lastResult property
         */
        function get cameraSetName_lastResult():Object;
		/**
		 * @private
		 */
        function set cameraSetName_lastResult(lastResult:Object):void;
       /**
        * Add a listener for the cameraSetName operation successful result event
        * @param The listener function
        */
       function addcameraSetNameEventListener(listener:Function):void;
       
       
        /**
         * The cameraSetName operation request wrapper
         */
        function get cameraSetName_request_var():CameraSetName_request;
        
        /**
         * @private
         */
        function set cameraSetName_request_var(request:CameraSetName_request):void;
                   
    	//Stub functions for the CameraSetDescription operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param cameraID
    	 * @param description
    	 * @return An AsyncToken
    	 */
    	function cameraSetDescription(cameraID:Number,description:String):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function cameraSetDescription_send():AsyncToken;
        
        /**
         * The cameraSetDescription operation lastResult property
         */
        function get cameraSetDescription_lastResult():Object;
		/**
		 * @private
		 */
        function set cameraSetDescription_lastResult(lastResult:Object):void;
       /**
        * Add a listener for the cameraSetDescription operation successful result event
        * @param The listener function
        */
       function addcameraSetDescriptionEventListener(listener:Function):void;
       
       
        /**
         * The cameraSetDescription operation request wrapper
         */
        function get cameraSetDescription_request_var():CameraSetDescription_request;
        
        /**
         * @private
         */
        function set cameraSetDescription_request_var(request:CameraSetDescription_request):void;
                   
    	//Stub functions for the CameraSetIcon operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param cameraID
    	 * @param icon
    	 * @return An AsyncToken
    	 */
    	function cameraSetIcon(cameraID:Number,icon:flash.utils.ByteArray):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function cameraSetIcon_send():AsyncToken;
        
        /**
         * The cameraSetIcon operation lastResult property
         */
        function get cameraSetIcon_lastResult():Object;
		/**
		 * @private
		 */
        function set cameraSetIcon_lastResult(lastResult:Object):void;
       /**
        * Add a listener for the cameraSetIcon operation successful result event
        * @param The listener function
        */
       function addcameraSetIconEventListener(listener:Function):void;
       
       
        /**
         * The cameraSetIcon operation request wrapper
         */
        function get cameraSetIcon_request_var():CameraSetIcon_request;
        
        /**
         * @private
         */
        function set cameraSetIcon_request_var(request:CameraSetIcon_request):void;
                   
    	//Stub functions for the GroupAdd operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param name
    	 * @param description
    	 * @param icon
    	 * @param privacy
    	 * @return An AsyncToken
    	 */
    	function groupAdd(name:String,description:String,icon:flash.utils.ByteArray,privacy:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function groupAdd_send():AsyncToken;
        
        /**
         * The groupAdd operation lastResult property
         */
        function get groupAdd_lastResult():Number;
		/**
		 * @private
		 */
        function set groupAdd_lastResult(lastResult:Number):void;
       /**
        * Add a listener for the groupAdd operation successful result event
        * @param The listener function
        */
       function addgroupAddEventListener(listener:Function):void;
       
       
        /**
         * The groupAdd operation request wrapper
         */
        function get groupAdd_request_var():GroupAdd_request;
        
        /**
         * @private
         */
        function set groupAdd_request_var(request:GroupAdd_request):void;
                   
    	//Stub functions for the GroupRemove operation
    	/**
    	 * Call the operation on the server passing in the arguments defined in the WSDL file
    	 * @param groupID
    	 * @return An AsyncToken
    	 */
    	function groupRemove(groupID:Number):AsyncToken;
        /**
         * Method to call the operation on the server without passing the arguments inline.
         * You must however set the _request property for the operation before calling this method
         * Should use it in MXML context mostly
         * @return An AsyncToken
         */
        function groupRemove_send():AsyncToken;
        
        /**
         * The groupRemove operation lastResult property
         */
        function get groupRemove_lastResult():Object;
		/**
		 * @private
		 */
        function set groupRemove_lastResult(lastResult:Object):void;
       /**
        * Add a listener for the groupRemove operation successful result event
        * @param The listener function
        */
       function addgroupRemoveEventListener(listener:Function):void;
       
       
        /**
         * The groupRemove operation request wrapper
         */
        function get groupRemove_request_var():GroupRemove_request;
        
        /**
         * @private
         */
        function set groupRemove_request_var(request:GroupRemove_request):void;
                   
        /**
         * Get access to the underlying web service that the stub uses to communicate with the server
         * @return The base service that the facade implements
         */
        function getWebService():BaseCloudObserverService;
	}
}