/**
 * BaseCloudObserverServiceService.as
 * This file was auto-generated from WSDL by the Apache Axis2 generator modified by Adobe
 * Any change made to this file will be overwritten when the code is re-generated.
 */
package generated.webservices
{
	import flash.events.Event;
	import flash.events.EventDispatcher;
	import flash.net.URLLoader;
	import flash.net.URLRequest;
	import flash.utils.getDefinitionByName;
	import flash.utils.getQualifiedClassName;
	import mx.controls.treeClasses.DefaultDataDescriptor;
	import mx.utils.ObjectUtil;
	import mx.utils.ObjectProxy;
	import mx.messaging.events.MessageFaultEvent;
	import mx.messaging.MessageResponder;
	import mx.messaging.messages.SOAPMessage;
	import mx.messaging.messages.ErrorMessage;
   	import mx.messaging.ChannelSet;
	import mx.messaging.channels.DirectHTTPChannel;
	import mx.rpc.*;
	import mx.rpc.events.*;
	import mx.rpc.soap.*;
	import mx.rpc.wsdl.*;
	import mx.rpc.xml.*;
	import mx.rpc.soap.types.*;
	import mx.collections.ArrayCollection;
	
	/**
	 * Base service implementation, extends the AbstractWebService and adds specific functionality for the selected WSDL
	 * It defines the options and properties for each of the WSDL's operations
	 */ 
	public class BaseCloudObserverService extends AbstractWebService
    {
		private var results:Object;
		private var schemaMgr:SchemaManager;
		private var BaseCloudObserverServiceService:WSDLService;
		private var BaseCloudObserverServicePortType:WSDLPortType;
		private var BaseCloudObserverServiceBinding:WSDLBinding;
		private var BaseCloudObserverServicePort:WSDLPort;
		private var currentOperation:WSDLOperation;
		private var internal_schema:BaseCloudObserverServiceSchema;
	
		/**
		 * Constructor for the base service, initializes all of the WSDL's properties
		 * @param [Optional] The LCDS destination (if available) to use to contact the server
		 * @param [Optional] The URL to the WSDL end-point
		 */
		public function BaseCloudObserverService(destination:String=null, rootURL:String=null)
		{
			super(destination, rootURL);
			if(destination == null)
			{
				//no destination available; must set it to go directly to the target
				this.useProxy = false;
			}
			else
			{
				//specific destination requested; must set proxying to true
				this.useProxy = true;
			}
			
			if(rootURL != null)
			{
				this.endpointURI = rootURL;
			} 
			else 
			{
				this.endpointURI = null;
			}
			internal_schema = new BaseCloudObserverServiceSchema();
			schemaMgr = new SchemaManager();
			for(var i:int;i<internal_schema.schemas.length;i++)
			{
				internal_schema.schemas[i].targetNamespace=internal_schema.targetNamespaces[i];
				schemaMgr.addSchema(internal_schema.schemas[i]);
			}
BaseCloudObserverServiceService = new WSDLService("BaseCloudObserverServiceService");
			BaseCloudObserverServicePort = new WSDLPort("BaseCloudObserverServicePort",BaseCloudObserverServiceService);
        	BaseCloudObserverServiceBinding = new WSDLBinding("BaseCloudObserverServiceBinding");
	        BaseCloudObserverServicePortType = new WSDLPortType("BaseCloudObserverServicePortType");
       		BaseCloudObserverServiceBinding.portType = BaseCloudObserverServicePortType;
       		BaseCloudObserverServicePort.binding = BaseCloudObserverServiceBinding;
       		BaseCloudObserverServiceService.addPort(BaseCloudObserverServicePort);
       		BaseCloudObserverServicePort.endpointURI = "http://localhost:2101/CloudObserverWebsite/CloudObserverService.svc";
       		if(this.endpointURI == null)
       		{
       			this.endpointURI = BaseCloudObserverServicePort.endpointURI; 
       		} 
       		
			var requestMessage:WSDLMessage;
			var responseMessage:WSDLMessage;
			//define the WSDLOperation: new WSDLOperation(methodName)
            var groupGetID:WSDLOperation = new WSDLOperation("GroupGetID");
				//input message for the operation
    	        requestMessage = new WSDLMessage("GroupGetID");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","name"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","GroupGetID");
                
                responseMessage = new WSDLMessage("GroupGetIDResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","GroupGetIDResult"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","GroupGetIDResponse");
			groupGetID.inputMessage = requestMessage;
	        groupGetID.outputMessage = responseMessage;
            groupGetID.schemaManager = this.schemaMgr;
            groupGetID.soapAction = "http://tempuri.org/ICloudObserverService/GroupGetID";
            groupGetID.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(groupGetID);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var groupGetName:WSDLOperation = new WSDLOperation("GroupGetName");
				//input message for the operation
    	        requestMessage = new WSDLMessage("GroupGetName");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","groupID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","GroupGetName");
                
                responseMessage = new WSDLMessage("GroupGetNameResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","GroupGetNameResult"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","GroupGetNameResponse");
			groupGetName.inputMessage = requestMessage;
	        groupGetName.outputMessage = responseMessage;
            groupGetName.schemaManager = this.schemaMgr;
            groupGetName.soapAction = "http://tempuri.org/ICloudObserverService/GroupGetName";
            groupGetName.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(groupGetName);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var groupGetDescription:WSDLOperation = new WSDLOperation("GroupGetDescription");
				//input message for the operation
    	        requestMessage = new WSDLMessage("GroupGetDescription");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","groupID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","GroupGetDescription");
                
                responseMessage = new WSDLMessage("GroupGetDescriptionResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","GroupGetDescriptionResult"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","GroupGetDescriptionResponse");
			groupGetDescription.inputMessage = requestMessage;
	        groupGetDescription.outputMessage = responseMessage;
            groupGetDescription.schemaManager = this.schemaMgr;
            groupGetDescription.soapAction = "http://tempuri.org/ICloudObserverService/GroupGetDescription";
            groupGetDescription.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(groupGetDescription);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var groupGetIcon:WSDLOperation = new WSDLOperation("GroupGetIcon");
				//input message for the operation
    	        requestMessage = new WSDLMessage("GroupGetIcon");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","groupID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","GroupGetIcon");
                
                responseMessage = new WSDLMessage("GroupGetIconResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","GroupGetIconResult"),null,new QName("http://www.w3.org/2001/XMLSchema","base64Binary")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","GroupGetIconResponse");
			groupGetIcon.inputMessage = requestMessage;
	        groupGetIcon.outputMessage = responseMessage;
            groupGetIcon.schemaManager = this.schemaMgr;
            groupGetIcon.soapAction = "http://tempuri.org/ICloudObserverService/GroupGetIcon";
            groupGetIcon.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(groupGetIcon);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var groupGetPrivacy:WSDLOperation = new WSDLOperation("GroupGetPrivacy");
				//input message for the operation
    	        requestMessage = new WSDLMessage("GroupGetPrivacy");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","groupID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","GroupGetPrivacy");
                
                responseMessage = new WSDLMessage("GroupGetPrivacyResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","GroupGetPrivacyResult"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","GroupGetPrivacyResponse");
			groupGetPrivacy.inputMessage = requestMessage;
	        groupGetPrivacy.outputMessage = responseMessage;
            groupGetPrivacy.schemaManager = this.schemaMgr;
            groupGetPrivacy.soapAction = "http://tempuri.org/ICloudObserverService/GroupGetPrivacy";
            groupGetPrivacy.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(groupGetPrivacy);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var groupGetRegistrationDate:WSDLOperation = new WSDLOperation("GroupGetRegistrationDate");
				//input message for the operation
    	        requestMessage = new WSDLMessage("GroupGetRegistrationDate");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","groupID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","GroupGetRegistrationDate");
                
                responseMessage = new WSDLMessage("GroupGetRegistrationDateResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","GroupGetRegistrationDateResult"),null,new QName("http://www.w3.org/2001/XMLSchema","dateTime")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","GroupGetRegistrationDateResponse");
			groupGetRegistrationDate.inputMessage = requestMessage;
	        groupGetRegistrationDate.outputMessage = responseMessage;
            groupGetRegistrationDate.schemaManager = this.schemaMgr;
            groupGetRegistrationDate.soapAction = "http://tempuri.org/ICloudObserverService/GroupGetRegistrationDate";
            groupGetRegistrationDate.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(groupGetRegistrationDate);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var groupGetMembers:WSDLOperation = new WSDLOperation("GroupGetMembers");
				//input message for the operation
    	        requestMessage = new WSDLMessage("GroupGetMembers");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","groupID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","GroupGetMembers");
                
                responseMessage = new WSDLMessage("GroupGetMembersResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","GroupGetMembersResult"),null,new QName("http://schemas.microsoft.com/2003/10/Serialization/Arrays","ArrayOfint")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","GroupGetMembersResponse");
			groupGetMembers.inputMessage = requestMessage;
	        groupGetMembers.outputMessage = responseMessage;
            groupGetMembers.schemaManager = this.schemaMgr;
            groupGetMembers.soapAction = "http://tempuri.org/ICloudObserverService/GroupGetMembers";
            groupGetMembers.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(groupGetMembers);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var groupGetCameras:WSDLOperation = new WSDLOperation("GroupGetCameras");
				//input message for the operation
    	        requestMessage = new WSDLMessage("GroupGetCameras");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","groupID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","GroupGetCameras");
                
                responseMessage = new WSDLMessage("GroupGetCamerasResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","GroupGetCamerasResult"),null,new QName("http://schemas.microsoft.com/2003/10/Serialization/Arrays","ArrayOfint")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","GroupGetCamerasResponse");
			groupGetCameras.inputMessage = requestMessage;
	        groupGetCameras.outputMessage = responseMessage;
            groupGetCameras.schemaManager = this.schemaMgr;
            groupGetCameras.soapAction = "http://tempuri.org/ICloudObserverService/GroupGetCameras";
            groupGetCameras.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(groupGetCameras);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var groupSetName:WSDLOperation = new WSDLOperation("GroupSetName");
				//input message for the operation
    	        requestMessage = new WSDLMessage("GroupSetName");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","groupID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","name"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","GroupSetName");
                
                responseMessage = new WSDLMessage("GroupSetNameResponse");
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				groupSetName.inputMessage = requestMessage;
	        groupSetName.outputMessage = responseMessage;
            groupSetName.schemaManager = this.schemaMgr;
            groupSetName.soapAction = "http://tempuri.org/ICloudObserverService/GroupSetName";
            groupSetName.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(groupSetName);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var groupSetDescription:WSDLOperation = new WSDLOperation("GroupSetDescription");
				//input message for the operation
    	        requestMessage = new WSDLMessage("GroupSetDescription");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","groupID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","description"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","GroupSetDescription");
                
                responseMessage = new WSDLMessage("GroupSetDescriptionResponse");
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				groupSetDescription.inputMessage = requestMessage;
	        groupSetDescription.outputMessage = responseMessage;
            groupSetDescription.schemaManager = this.schemaMgr;
            groupSetDescription.soapAction = "http://tempuri.org/ICloudObserverService/GroupSetDescription";
            groupSetDescription.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(groupSetDescription);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var groupSetIcon:WSDLOperation = new WSDLOperation("GroupSetIcon");
				//input message for the operation
    	        requestMessage = new WSDLMessage("GroupSetIcon");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","groupID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","icon"),null,new QName("http://www.w3.org/2001/XMLSchema","base64Binary")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","GroupSetIcon");
                
                responseMessage = new WSDLMessage("GroupSetIconResponse");
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				groupSetIcon.inputMessage = requestMessage;
	        groupSetIcon.outputMessage = responseMessage;
            groupSetIcon.schemaManager = this.schemaMgr;
            groupSetIcon.soapAction = "http://tempuri.org/ICloudObserverService/GroupSetIcon";
            groupSetIcon.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(groupSetIcon);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var groupSetPrivacy:WSDLOperation = new WSDLOperation("GroupSetPrivacy");
				//input message for the operation
    	        requestMessage = new WSDLMessage("GroupSetPrivacy");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","groupID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","privacy"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","GroupSetPrivacy");
                
                responseMessage = new WSDLMessage("GroupSetPrivacyResponse");
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				groupSetPrivacy.inputMessage = requestMessage;
	        groupSetPrivacy.outputMessage = responseMessage;
            groupSetPrivacy.schemaManager = this.schemaMgr;
            groupSetPrivacy.soapAction = "http://tempuri.org/ICloudObserverService/GroupSetPrivacy";
            groupSetPrivacy.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(groupSetPrivacy);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var groupMemberAdd:WSDLOperation = new WSDLOperation("GroupMemberAdd");
				//input message for the operation
    	        requestMessage = new WSDLMessage("GroupMemberAdd");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","userID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","groupID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","privileges"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","GroupMemberAdd");
                
                responseMessage = new WSDLMessage("GroupMemberAddResponse");
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				groupMemberAdd.inputMessage = requestMessage;
	        groupMemberAdd.outputMessage = responseMessage;
            groupMemberAdd.schemaManager = this.schemaMgr;
            groupMemberAdd.soapAction = "http://tempuri.org/ICloudObserverService/GroupMemberAdd";
            groupMemberAdd.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(groupMemberAdd);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var groupMemberRemove:WSDLOperation = new WSDLOperation("GroupMemberRemove");
				//input message for the operation
    	        requestMessage = new WSDLMessage("GroupMemberRemove");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","userID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","groupID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","GroupMemberRemove");
                
                responseMessage = new WSDLMessage("GroupMemberRemoveResponse");
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				groupMemberRemove.inputMessage = requestMessage;
	        groupMemberRemove.outputMessage = responseMessage;
            groupMemberRemove.schemaManager = this.schemaMgr;
            groupMemberRemove.soapAction = "http://tempuri.org/ICloudObserverService/GroupMemberRemove";
            groupMemberRemove.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(groupMemberRemove);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var groupMemberGetPrivileges:WSDLOperation = new WSDLOperation("GroupMemberGetPrivileges");
				//input message for the operation
    	        requestMessage = new WSDLMessage("GroupMemberGetPrivileges");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","userID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","groupID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","GroupMemberGetPrivileges");
                
                responseMessage = new WSDLMessage("GroupMemberGetPrivilegesResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","GroupMemberGetPrivilegesResult"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","GroupMemberGetPrivilegesResponse");
			groupMemberGetPrivileges.inputMessage = requestMessage;
	        groupMemberGetPrivileges.outputMessage = responseMessage;
            groupMemberGetPrivileges.schemaManager = this.schemaMgr;
            groupMemberGetPrivileges.soapAction = "http://tempuri.org/ICloudObserverService/GroupMemberGetPrivileges";
            groupMemberGetPrivileges.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(groupMemberGetPrivileges);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var groupMemberSetPrivileges:WSDLOperation = new WSDLOperation("GroupMemberSetPrivileges");
				//input message for the operation
    	        requestMessage = new WSDLMessage("GroupMemberSetPrivileges");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","userID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","groupID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","privileges"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","GroupMemberSetPrivileges");
                
                responseMessage = new WSDLMessage("GroupMemberSetPrivilegesResponse");
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				groupMemberSetPrivileges.inputMessage = requestMessage;
	        groupMemberSetPrivileges.outputMessage = responseMessage;
            groupMemberSetPrivileges.schemaManager = this.schemaMgr;
            groupMemberSetPrivileges.soapAction = "http://tempuri.org/ICloudObserverService/GroupMemberSetPrivileges";
            groupMemberSetPrivileges.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(groupMemberSetPrivileges);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var groupCameraAdd:WSDLOperation = new WSDLOperation("GroupCameraAdd");
				//input message for the operation
    	        requestMessage = new WSDLMessage("GroupCameraAdd");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","cameraID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","groupID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","GroupCameraAdd");
                
                responseMessage = new WSDLMessage("GroupCameraAddResponse");
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				groupCameraAdd.inputMessage = requestMessage;
	        groupCameraAdd.outputMessage = responseMessage;
            groupCameraAdd.schemaManager = this.schemaMgr;
            groupCameraAdd.soapAction = "http://tempuri.org/ICloudObserverService/GroupCameraAdd";
            groupCameraAdd.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(groupCameraAdd);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var groupCameraRemove:WSDLOperation = new WSDLOperation("GroupCameraRemove");
				//input message for the operation
    	        requestMessage = new WSDLMessage("GroupCameraRemove");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","cameraID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","groupID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","GroupCameraRemove");
                
                responseMessage = new WSDLMessage("GroupCameraRemoveResponse");
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				groupCameraRemove.inputMessage = requestMessage;
	        groupCameraRemove.outputMessage = responseMessage;
            groupCameraRemove.schemaManager = this.schemaMgr;
            groupCameraRemove.soapAction = "http://tempuri.org/ICloudObserverService/GroupCameraRemove";
            groupCameraRemove.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(groupCameraRemove);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var frameAdd:WSDLOperation = new WSDLOperation("FrameAdd");
				//input message for the operation
    	        requestMessage = new WSDLMessage("FrameAdd");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","cameraID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","content"),null,new QName("http://www.w3.org/2001/XMLSchema","base64Binary")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","marker"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","FrameAdd");
                
                responseMessage = new WSDLMessage("FrameAddResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","FrameAddResult"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","FrameAddResponse");
			frameAdd.inputMessage = requestMessage;
	        frameAdd.outputMessage = responseMessage;
            frameAdd.schemaManager = this.schemaMgr;
            frameAdd.soapAction = "http://tempuri.org/ICloudObserverService/FrameAdd";
            frameAdd.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(frameAdd);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var frameRemove:WSDLOperation = new WSDLOperation("FrameRemove");
				//input message for the operation
    	        requestMessage = new WSDLMessage("FrameRemove");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","frameID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","FrameRemove");
                
                responseMessage = new WSDLMessage("FrameRemoveResponse");
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				frameRemove.inputMessage = requestMessage;
	        frameRemove.outputMessage = responseMessage;
            frameRemove.schemaManager = this.schemaMgr;
            frameRemove.soapAction = "http://tempuri.org/ICloudObserverService/FrameRemove";
            frameRemove.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(frameRemove);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var frameGetContent:WSDLOperation = new WSDLOperation("FrameGetContent");
				//input message for the operation
    	        requestMessage = new WSDLMessage("FrameGetContent");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","frameID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","FrameGetContent");
                
                responseMessage = new WSDLMessage("FrameGetContentResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","FrameGetContentResult"),null,new QName("http://www.w3.org/2001/XMLSchema","base64Binary")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","FrameGetContentResponse");
			frameGetContent.inputMessage = requestMessage;
	        frameGetContent.outputMessage = responseMessage;
            frameGetContent.schemaManager = this.schemaMgr;
            frameGetContent.soapAction = "http://tempuri.org/ICloudObserverService/FrameGetContent";
            frameGetContent.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(frameGetContent);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var frameGetMarker:WSDLOperation = new WSDLOperation("FrameGetMarker");
				//input message for the operation
    	        requestMessage = new WSDLMessage("FrameGetMarker");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","frameID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","FrameGetMarker");
                
                responseMessage = new WSDLMessage("FrameGetMarkerResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","FrameGetMarkerResult"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","FrameGetMarkerResponse");
			frameGetMarker.inputMessage = requestMessage;
	        frameGetMarker.outputMessage = responseMessage;
            frameGetMarker.schemaManager = this.schemaMgr;
            frameGetMarker.soapAction = "http://tempuri.org/ICloudObserverService/FrameGetMarker";
            frameGetMarker.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(frameGetMarker);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var userIsEmailAvailable:WSDLOperation = new WSDLOperation("UserIsEmailAvailable");
				//input message for the operation
    	        requestMessage = new WSDLMessage("UserIsEmailAvailable");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","email"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","UserIsEmailAvailable");
                
                responseMessage = new WSDLMessage("UserIsEmailAvailableResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","UserIsEmailAvailableResult"),null,new QName("http://www.w3.org/2001/XMLSchema","boolean")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","UserIsEmailAvailableResponse");
			userIsEmailAvailable.inputMessage = requestMessage;
	        userIsEmailAvailable.outputMessage = responseMessage;
            userIsEmailAvailable.schemaManager = this.schemaMgr;
            userIsEmailAvailable.soapAction = "http://tempuri.org/ICloudObserverService/UserIsEmailAvailable";
            userIsEmailAvailable.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(userIsEmailAvailable);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var userLogin:WSDLOperation = new WSDLOperation("UserLogin");
				//input message for the operation
    	        requestMessage = new WSDLMessage("UserLogin");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","email"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","password"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","UserLogin");
                
                responseMessage = new WSDLMessage("UserLoginResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","UserLoginResult"),null,new QName("http://www.w3.org/2001/XMLSchema","boolean")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","UserLoginResponse");
			userLogin.inputMessage = requestMessage;
	        userLogin.outputMessage = responseMessage;
            userLogin.schemaManager = this.schemaMgr;
            userLogin.soapAction = "http://tempuri.org/ICloudObserverService/UserLogin";
            userLogin.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(userLogin);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var userAdd:WSDLOperation = new WSDLOperation("UserAdd");
				//input message for the operation
    	        requestMessage = new WSDLMessage("UserAdd");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","email"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","password"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","name"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","description"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","icon"),null,new QName("http://www.w3.org/2001/XMLSchema","base64Binary")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","UserAdd");
                
                responseMessage = new WSDLMessage("UserAddResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","UserAddResult"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","UserAddResponse");
			userAdd.inputMessage = requestMessage;
	        userAdd.outputMessage = responseMessage;
            userAdd.schemaManager = this.schemaMgr;
            userAdd.soapAction = "http://tempuri.org/ICloudObserverService/UserAdd";
            userAdd.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(userAdd);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var userRemove:WSDLOperation = new WSDLOperation("UserRemove");
				//input message for the operation
    	        requestMessage = new WSDLMessage("UserRemove");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","userID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","UserRemove");
                
                responseMessage = new WSDLMessage("UserRemoveResponse");
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				userRemove.inputMessage = requestMessage;
	        userRemove.outputMessage = responseMessage;
            userRemove.schemaManager = this.schemaMgr;
            userRemove.soapAction = "http://tempuri.org/ICloudObserverService/UserRemove";
            userRemove.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(userRemove);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var userGetID:WSDLOperation = new WSDLOperation("UserGetID");
				//input message for the operation
    	        requestMessage = new WSDLMessage("UserGetID");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","email"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","UserGetID");
                
                responseMessage = new WSDLMessage("UserGetIDResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","UserGetIDResult"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","UserGetIDResponse");
			userGetID.inputMessage = requestMessage;
	        userGetID.outputMessage = responseMessage;
            userGetID.schemaManager = this.schemaMgr;
            userGetID.soapAction = "http://tempuri.org/ICloudObserverService/UserGetID";
            userGetID.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(userGetID);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var userGetEmail:WSDLOperation = new WSDLOperation("UserGetEmail");
				//input message for the operation
    	        requestMessage = new WSDLMessage("UserGetEmail");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","userID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","UserGetEmail");
                
                responseMessage = new WSDLMessage("UserGetEmailResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","UserGetEmailResult"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","UserGetEmailResponse");
			userGetEmail.inputMessage = requestMessage;
	        userGetEmail.outputMessage = responseMessage;
            userGetEmail.schemaManager = this.schemaMgr;
            userGetEmail.soapAction = "http://tempuri.org/ICloudObserverService/UserGetEmail";
            userGetEmail.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(userGetEmail);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var userGetPassword:WSDLOperation = new WSDLOperation("UserGetPassword");
				//input message for the operation
    	        requestMessage = new WSDLMessage("UserGetPassword");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","userID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","UserGetPassword");
                
                responseMessage = new WSDLMessage("UserGetPasswordResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","UserGetPasswordResult"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","UserGetPasswordResponse");
			userGetPassword.inputMessage = requestMessage;
	        userGetPassword.outputMessage = responseMessage;
            userGetPassword.schemaManager = this.schemaMgr;
            userGetPassword.soapAction = "http://tempuri.org/ICloudObserverService/UserGetPassword";
            userGetPassword.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(userGetPassword);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var userGetName:WSDLOperation = new WSDLOperation("UserGetName");
				//input message for the operation
    	        requestMessage = new WSDLMessage("UserGetName");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","userID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","UserGetName");
                
                responseMessage = new WSDLMessage("UserGetNameResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","UserGetNameResult"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","UserGetNameResponse");
			userGetName.inputMessage = requestMessage;
	        userGetName.outputMessage = responseMessage;
            userGetName.schemaManager = this.schemaMgr;
            userGetName.soapAction = "http://tempuri.org/ICloudObserverService/UserGetName";
            userGetName.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(userGetName);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var userGetDescription:WSDLOperation = new WSDLOperation("UserGetDescription");
				//input message for the operation
    	        requestMessage = new WSDLMessage("UserGetDescription");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","userID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","UserGetDescription");
                
                responseMessage = new WSDLMessage("UserGetDescriptionResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","UserGetDescriptionResult"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","UserGetDescriptionResponse");
			userGetDescription.inputMessage = requestMessage;
	        userGetDescription.outputMessage = responseMessage;
            userGetDescription.schemaManager = this.schemaMgr;
            userGetDescription.soapAction = "http://tempuri.org/ICloudObserverService/UserGetDescription";
            userGetDescription.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(userGetDescription);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var userGetIcon:WSDLOperation = new WSDLOperation("UserGetIcon");
				//input message for the operation
    	        requestMessage = new WSDLMessage("UserGetIcon");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","userID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","UserGetIcon");
                
                responseMessage = new WSDLMessage("UserGetIconResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","UserGetIconResult"),null,new QName("http://www.w3.org/2001/XMLSchema","base64Binary")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","UserGetIconResponse");
			userGetIcon.inputMessage = requestMessage;
	        userGetIcon.outputMessage = responseMessage;
            userGetIcon.schemaManager = this.schemaMgr;
            userGetIcon.soapAction = "http://tempuri.org/ICloudObserverService/UserGetIcon";
            userGetIcon.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(userGetIcon);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var userGetRegistrationDate:WSDLOperation = new WSDLOperation("UserGetRegistrationDate");
				//input message for the operation
    	        requestMessage = new WSDLMessage("UserGetRegistrationDate");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","userID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","UserGetRegistrationDate");
                
                responseMessage = new WSDLMessage("UserGetRegistrationDateResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","UserGetRegistrationDateResult"),null,new QName("http://www.w3.org/2001/XMLSchema","dateTime")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","UserGetRegistrationDateResponse");
			userGetRegistrationDate.inputMessage = requestMessage;
	        userGetRegistrationDate.outputMessage = responseMessage;
            userGetRegistrationDate.schemaManager = this.schemaMgr;
            userGetRegistrationDate.soapAction = "http://tempuri.org/ICloudObserverService/UserGetRegistrationDate";
            userGetRegistrationDate.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(userGetRegistrationDate);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var userGetGroups:WSDLOperation = new WSDLOperation("UserGetGroups");
				//input message for the operation
    	        requestMessage = new WSDLMessage("UserGetGroups");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","userID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","UserGetGroups");
                
                responseMessage = new WSDLMessage("UserGetGroupsResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","UserGetGroupsResult"),null,new QName("http://schemas.microsoft.com/2003/10/Serialization/Arrays","ArrayOfint")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","UserGetGroupsResponse");
			userGetGroups.inputMessage = requestMessage;
	        userGetGroups.outputMessage = responseMessage;
            userGetGroups.schemaManager = this.schemaMgr;
            userGetGroups.soapAction = "http://tempuri.org/ICloudObserverService/UserGetGroups";
            userGetGroups.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(userGetGroups);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var userSetPassword:WSDLOperation = new WSDLOperation("UserSetPassword");
				//input message for the operation
    	        requestMessage = new WSDLMessage("UserSetPassword");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","userID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","password"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","UserSetPassword");
                
                responseMessage = new WSDLMessage("UserSetPasswordResponse");
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				userSetPassword.inputMessage = requestMessage;
	        userSetPassword.outputMessage = responseMessage;
            userSetPassword.schemaManager = this.schemaMgr;
            userSetPassword.soapAction = "http://tempuri.org/ICloudObserverService/UserSetPassword";
            userSetPassword.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(userSetPassword);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var userSetName:WSDLOperation = new WSDLOperation("UserSetName");
				//input message for the operation
    	        requestMessage = new WSDLMessage("UserSetName");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","userID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","name"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","UserSetName");
                
                responseMessage = new WSDLMessage("UserSetNameResponse");
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				userSetName.inputMessage = requestMessage;
	        userSetName.outputMessage = responseMessage;
            userSetName.schemaManager = this.schemaMgr;
            userSetName.soapAction = "http://tempuri.org/ICloudObserverService/UserSetName";
            userSetName.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(userSetName);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var userSetDescription:WSDLOperation = new WSDLOperation("UserSetDescription");
				//input message for the operation
    	        requestMessage = new WSDLMessage("UserSetDescription");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","userID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","description"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","UserSetDescription");
                
                responseMessage = new WSDLMessage("UserSetDescriptionResponse");
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				userSetDescription.inputMessage = requestMessage;
	        userSetDescription.outputMessage = responseMessage;
            userSetDescription.schemaManager = this.schemaMgr;
            userSetDescription.soapAction = "http://tempuri.org/ICloudObserverService/UserSetDescription";
            userSetDescription.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(userSetDescription);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var userSetIcon:WSDLOperation = new WSDLOperation("UserSetIcon");
				//input message for the operation
    	        requestMessage = new WSDLMessage("UserSetIcon");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","userID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","icon"),null,new QName("http://www.w3.org/2001/XMLSchema","base64Binary")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","UserSetIcon");
                
                responseMessage = new WSDLMessage("UserSetIconResponse");
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				userSetIcon.inputMessage = requestMessage;
	        userSetIcon.outputMessage = responseMessage;
            userSetIcon.schemaManager = this.schemaMgr;
            userSetIcon.soapAction = "http://tempuri.org/ICloudObserverService/UserSetIcon";
            userSetIcon.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(userSetIcon);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var cameraIsPathAvailable:WSDLOperation = new WSDLOperation("CameraIsPathAvailable");
				//input message for the operation
    	        requestMessage = new WSDLMessage("CameraIsPathAvailable");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","path"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","CameraIsPathAvailable");
                
                responseMessage = new WSDLMessage("CameraIsPathAvailableResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","CameraIsPathAvailableResult"),null,new QName("http://www.w3.org/2001/XMLSchema","boolean")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","CameraIsPathAvailableResponse");
			cameraIsPathAvailable.inputMessage = requestMessage;
	        cameraIsPathAvailable.outputMessage = responseMessage;
            cameraIsPathAvailable.schemaManager = this.schemaMgr;
            cameraIsPathAvailable.soapAction = "http://tempuri.org/ICloudObserverService/CameraIsPathAvailable";
            cameraIsPathAvailable.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(cameraIsPathAvailable);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var cameraAdd:WSDLOperation = new WSDLOperation("CameraAdd");
				//input message for the operation
    	        requestMessage = new WSDLMessage("CameraAdd");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","name"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","description"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","icon"),null,new QName("http://www.w3.org/2001/XMLSchema","base64Binary")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","CameraAdd");
                
                responseMessage = new WSDLMessage("CameraAddResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","CameraAddResult"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","CameraAddResponse");
			cameraAdd.inputMessage = requestMessage;
	        cameraAdd.outputMessage = responseMessage;
            cameraAdd.schemaManager = this.schemaMgr;
            cameraAdd.soapAction = "http://tempuri.org/ICloudObserverService/CameraAdd";
            cameraAdd.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(cameraAdd);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var cameraRemove:WSDLOperation = new WSDLOperation("CameraRemove");
				//input message for the operation
    	        requestMessage = new WSDLMessage("CameraRemove");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","cameraID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","CameraRemove");
                
                responseMessage = new WSDLMessage("CameraRemoveResponse");
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				cameraRemove.inputMessage = requestMessage;
	        cameraRemove.outputMessage = responseMessage;
            cameraRemove.schemaManager = this.schemaMgr;
            cameraRemove.soapAction = "http://tempuri.org/ICloudObserverService/CameraRemove";
            cameraRemove.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(cameraRemove);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var cameraGetID:WSDLOperation = new WSDLOperation("CameraGetID");
				//input message for the operation
    	        requestMessage = new WSDLMessage("CameraGetID");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","path"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","CameraGetID");
                
                responseMessage = new WSDLMessage("CameraGetIDResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","CameraGetIDResult"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","CameraGetIDResponse");
			cameraGetID.inputMessage = requestMessage;
	        cameraGetID.outputMessage = responseMessage;
            cameraGetID.schemaManager = this.schemaMgr;
            cameraGetID.soapAction = "http://tempuri.org/ICloudObserverService/CameraGetID";
            cameraGetID.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(cameraGetID);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var cameraGetPath:WSDLOperation = new WSDLOperation("CameraGetPath");
				//input message for the operation
    	        requestMessage = new WSDLMessage("CameraGetPath");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","cameraID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","CameraGetPath");
                
                responseMessage = new WSDLMessage("CameraGetPathResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","CameraGetPathResult"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","CameraGetPathResponse");
			cameraGetPath.inputMessage = requestMessage;
	        cameraGetPath.outputMessage = responseMessage;
            cameraGetPath.schemaManager = this.schemaMgr;
            cameraGetPath.soapAction = "http://tempuri.org/ICloudObserverService/CameraGetPath";
            cameraGetPath.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(cameraGetPath);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var cameraGetName:WSDLOperation = new WSDLOperation("CameraGetName");
				//input message for the operation
    	        requestMessage = new WSDLMessage("CameraGetName");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","cameraID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","CameraGetName");
                
                responseMessage = new WSDLMessage("CameraGetNameResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","CameraGetNameResult"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","CameraGetNameResponse");
			cameraGetName.inputMessage = requestMessage;
	        cameraGetName.outputMessage = responseMessage;
            cameraGetName.schemaManager = this.schemaMgr;
            cameraGetName.soapAction = "http://tempuri.org/ICloudObserverService/CameraGetName";
            cameraGetName.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(cameraGetName);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var cameraGetDescription:WSDLOperation = new WSDLOperation("CameraGetDescription");
				//input message for the operation
    	        requestMessage = new WSDLMessage("CameraGetDescription");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","cameraID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","CameraGetDescription");
                
                responseMessage = new WSDLMessage("CameraGetDescriptionResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","CameraGetDescriptionResult"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","CameraGetDescriptionResponse");
			cameraGetDescription.inputMessage = requestMessage;
	        cameraGetDescription.outputMessage = responseMessage;
            cameraGetDescription.schemaManager = this.schemaMgr;
            cameraGetDescription.soapAction = "http://tempuri.org/ICloudObserverService/CameraGetDescription";
            cameraGetDescription.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(cameraGetDescription);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var cameraGetIcon:WSDLOperation = new WSDLOperation("CameraGetIcon");
				//input message for the operation
    	        requestMessage = new WSDLMessage("CameraGetIcon");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","cameraID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","CameraGetIcon");
                
                responseMessage = new WSDLMessage("CameraGetIconResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","CameraGetIconResult"),null,new QName("http://www.w3.org/2001/XMLSchema","base64Binary")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","CameraGetIconResponse");
			cameraGetIcon.inputMessage = requestMessage;
	        cameraGetIcon.outputMessage = responseMessage;
            cameraGetIcon.schemaManager = this.schemaMgr;
            cameraGetIcon.soapAction = "http://tempuri.org/ICloudObserverService/CameraGetIcon";
            cameraGetIcon.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(cameraGetIcon);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var cameraGetRegistrationDate:WSDLOperation = new WSDLOperation("CameraGetRegistrationDate");
				//input message for the operation
    	        requestMessage = new WSDLMessage("CameraGetRegistrationDate");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","cameraID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","CameraGetRegistrationDate");
                
                responseMessage = new WSDLMessage("CameraGetRegistrationDateResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","CameraGetRegistrationDateResult"),null,new QName("http://www.w3.org/2001/XMLSchema","dateTime")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","CameraGetRegistrationDateResponse");
			cameraGetRegistrationDate.inputMessage = requestMessage;
	        cameraGetRegistrationDate.outputMessage = responseMessage;
            cameraGetRegistrationDate.schemaManager = this.schemaMgr;
            cameraGetRegistrationDate.soapAction = "http://tempuri.org/ICloudObserverService/CameraGetRegistrationDate";
            cameraGetRegistrationDate.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(cameraGetRegistrationDate);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var cameraGetGroups:WSDLOperation = new WSDLOperation("CameraGetGroups");
				//input message for the operation
    	        requestMessage = new WSDLMessage("CameraGetGroups");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","cameraID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","CameraGetGroups");
                
                responseMessage = new WSDLMessage("CameraGetGroupsResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","CameraGetGroupsResult"),null,new QName("http://schemas.microsoft.com/2003/10/Serialization/Arrays","ArrayOfint")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","CameraGetGroupsResponse");
			cameraGetGroups.inputMessage = requestMessage;
	        cameraGetGroups.outputMessage = responseMessage;
            cameraGetGroups.schemaManager = this.schemaMgr;
            cameraGetGroups.soapAction = "http://tempuri.org/ICloudObserverService/CameraGetGroups";
            cameraGetGroups.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(cameraGetGroups);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var cameraGetFrames:WSDLOperation = new WSDLOperation("CameraGetFrames");
				//input message for the operation
    	        requestMessage = new WSDLMessage("CameraGetFrames");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","cameraID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","CameraGetFrames");
                
                responseMessage = new WSDLMessage("CameraGetFramesResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","CameraGetFramesResult"),null,new QName("http://schemas.microsoft.com/2003/10/Serialization/Arrays","ArrayOfint")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","CameraGetFramesResponse");
			cameraGetFrames.inputMessage = requestMessage;
	        cameraGetFrames.outputMessage = responseMessage;
            cameraGetFrames.schemaManager = this.schemaMgr;
            cameraGetFrames.soapAction = "http://tempuri.org/ICloudObserverService/CameraGetFrames";
            cameraGetFrames.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(cameraGetFrames);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var cameraSetName:WSDLOperation = new WSDLOperation("CameraSetName");
				//input message for the operation
    	        requestMessage = new WSDLMessage("CameraSetName");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","cameraID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","name"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","CameraSetName");
                
                responseMessage = new WSDLMessage("CameraSetNameResponse");
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				cameraSetName.inputMessage = requestMessage;
	        cameraSetName.outputMessage = responseMessage;
            cameraSetName.schemaManager = this.schemaMgr;
            cameraSetName.soapAction = "http://tempuri.org/ICloudObserverService/CameraSetName";
            cameraSetName.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(cameraSetName);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var cameraSetDescription:WSDLOperation = new WSDLOperation("CameraSetDescription");
				//input message for the operation
    	        requestMessage = new WSDLMessage("CameraSetDescription");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","cameraID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","description"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","CameraSetDescription");
                
                responseMessage = new WSDLMessage("CameraSetDescriptionResponse");
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				cameraSetDescription.inputMessage = requestMessage;
	        cameraSetDescription.outputMessage = responseMessage;
            cameraSetDescription.schemaManager = this.schemaMgr;
            cameraSetDescription.soapAction = "http://tempuri.org/ICloudObserverService/CameraSetDescription";
            cameraSetDescription.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(cameraSetDescription);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var cameraSetIcon:WSDLOperation = new WSDLOperation("CameraSetIcon");
				//input message for the operation
    	        requestMessage = new WSDLMessage("CameraSetIcon");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","cameraID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","icon"),null,new QName("http://www.w3.org/2001/XMLSchema","base64Binary")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","CameraSetIcon");
                
                responseMessage = new WSDLMessage("CameraSetIconResponse");
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				cameraSetIcon.inputMessage = requestMessage;
	        cameraSetIcon.outputMessage = responseMessage;
            cameraSetIcon.schemaManager = this.schemaMgr;
            cameraSetIcon.soapAction = "http://tempuri.org/ICloudObserverService/CameraSetIcon";
            cameraSetIcon.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(cameraSetIcon);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var groupAdd:WSDLOperation = new WSDLOperation("GroupAdd");
				//input message for the operation
    	        requestMessage = new WSDLMessage("GroupAdd");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","name"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","description"),null,new QName("http://www.w3.org/2001/XMLSchema","string")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","icon"),null,new QName("http://www.w3.org/2001/XMLSchema","base64Binary")));
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","privacy"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","GroupAdd");
                
                responseMessage = new WSDLMessage("GroupAddResponse");
            				responseMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","GroupAddResult"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				
	            responseMessage.isWrapped = true;
	            responseMessage.wrappedQName = new QName("http://tempuri.org/","GroupAddResponse");
			groupAdd.inputMessage = requestMessage;
	        groupAdd.outputMessage = responseMessage;
            groupAdd.schemaManager = this.schemaMgr;
            groupAdd.soapAction = "http://tempuri.org/ICloudObserverService/GroupAdd";
            groupAdd.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(groupAdd);
			//define the WSDLOperation: new WSDLOperation(methodName)
            var groupRemove:WSDLOperation = new WSDLOperation("GroupRemove");
				//input message for the operation
    	        requestMessage = new WSDLMessage("GroupRemove");
            				requestMessage.addPart(new WSDLMessagePart(new QName("http://tempuri.org/","groupID"),null,new QName("http://www.w3.org/2001/XMLSchema","int")));
                requestMessage.encoding = new WSDLEncoding();
                requestMessage.encoding.namespaceURI="http://tempuri.org/";
			requestMessage.encoding.useStyle="literal";
	            requestMessage.isWrapped = true;
	            requestMessage.wrappedQName = new QName("http://tempuri.org/","GroupRemove");
                
                responseMessage = new WSDLMessage("GroupRemoveResponse");
                responseMessage.encoding = new WSDLEncoding();
                responseMessage.encoding.namespaceURI="http://tempuri.org/";
                responseMessage.encoding.useStyle="literal";				
				groupRemove.inputMessage = requestMessage;
	        groupRemove.outputMessage = responseMessage;
            groupRemove.schemaManager = this.schemaMgr;
            groupRemove.soapAction = "http://tempuri.org/ICloudObserverService/GroupRemove";
            groupRemove.style = "document";
            BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.addOperation(groupRemove);
							SchemaTypeRegistry.getInstance().registerClass(new QName("http://schemas.microsoft.com/2003/10/Serialization/","char"),generated.webservices.Char);
							SchemaTypeRegistry.getInstance().registerClass(new QName("http://schemas.microsoft.com/2003/10/Serialization/","guid"),generated.webservices.Guid);
							SchemaTypeRegistry.getInstance().registerCollectionClass(new QName("http://schemas.microsoft.com/2003/10/Serialization/Arrays","ArrayOfint"),generated.webservices.ArrayOfint);
							SchemaTypeRegistry.getInstance().registerClass(new QName("http://schemas.microsoft.com/2003/10/Serialization/","duration"),generated.webservices.Duration);
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param name
		 * @return Asynchronous token
		 */
		public function groupGetID(name:String):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["name"] = name;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("GroupGetID");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param groupID
		 * @return Asynchronous token
		 */
		public function groupGetName(groupID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["groupID"] = groupID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("GroupGetName");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param groupID
		 * @return Asynchronous token
		 */
		public function groupGetDescription(groupID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["groupID"] = groupID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("GroupGetDescription");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param groupID
		 * @return Asynchronous token
		 */
		public function groupGetIcon(groupID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["groupID"] = groupID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("GroupGetIcon");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param groupID
		 * @return Asynchronous token
		 */
		public function groupGetPrivacy(groupID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["groupID"] = groupID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("GroupGetPrivacy");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param groupID
		 * @return Asynchronous token
		 */
		public function groupGetRegistrationDate(groupID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["groupID"] = groupID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("GroupGetRegistrationDate");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param groupID
		 * @return Asynchronous token
		 */
		public function groupGetMembers(groupID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["groupID"] = groupID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("GroupGetMembers");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param groupID
		 * @return Asynchronous token
		 */
		public function groupGetCameras(groupID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["groupID"] = groupID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("GroupGetCameras");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param groupID* @param name
		 * @return Asynchronous token
		 */
		public function groupSetName(groupID:Number,name:String):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["groupID"] = groupID;
	            out["name"] = name;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("GroupSetName");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param groupID* @param description
		 * @return Asynchronous token
		 */
		public function groupSetDescription(groupID:Number,description:String):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["groupID"] = groupID;
	            out["description"] = description;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("GroupSetDescription");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param groupID* @param icon
		 * @return Asynchronous token
		 */
		public function groupSetIcon(groupID:Number,icon:flash.utils.ByteArray):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["groupID"] = groupID;
	            out["icon"] = icon;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("GroupSetIcon");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param groupID* @param privacy
		 * @return Asynchronous token
		 */
		public function groupSetPrivacy(groupID:Number,privacy:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["groupID"] = groupID;
	            out["privacy"] = privacy;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("GroupSetPrivacy");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param userID* @param groupID* @param privileges
		 * @return Asynchronous token
		 */
		public function groupMemberAdd(userID:Number,groupID:Number,privileges:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["userID"] = userID;
	            out["groupID"] = groupID;
	            out["privileges"] = privileges;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("GroupMemberAdd");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param userID* @param groupID
		 * @return Asynchronous token
		 */
		public function groupMemberRemove(userID:Number,groupID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["userID"] = userID;
	            out["groupID"] = groupID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("GroupMemberRemove");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param userID* @param groupID
		 * @return Asynchronous token
		 */
		public function groupMemberGetPrivileges(userID:Number,groupID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["userID"] = userID;
	            out["groupID"] = groupID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("GroupMemberGetPrivileges");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param userID* @param groupID* @param privileges
		 * @return Asynchronous token
		 */
		public function groupMemberSetPrivileges(userID:Number,groupID:Number,privileges:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["userID"] = userID;
	            out["groupID"] = groupID;
	            out["privileges"] = privileges;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("GroupMemberSetPrivileges");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param cameraID* @param groupID
		 * @return Asynchronous token
		 */
		public function groupCameraAdd(cameraID:Number,groupID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["cameraID"] = cameraID;
	            out["groupID"] = groupID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("GroupCameraAdd");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param cameraID* @param groupID
		 * @return Asynchronous token
		 */
		public function groupCameraRemove(cameraID:Number,groupID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["cameraID"] = cameraID;
	            out["groupID"] = groupID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("GroupCameraRemove");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param cameraID* @param content* @param marker
		 * @return Asynchronous token
		 */
		public function frameAdd(cameraID:Number,content:flash.utils.ByteArray,marker:String):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["cameraID"] = cameraID;
	            out["content"] = content;
	            out["marker"] = marker;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("FrameAdd");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param frameID
		 * @return Asynchronous token
		 */
		public function frameRemove(frameID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["frameID"] = frameID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("FrameRemove");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param frameID
		 * @return Asynchronous token
		 */
		public function frameGetContent(frameID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["frameID"] = frameID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("FrameGetContent");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param frameID
		 * @return Asynchronous token
		 */
		public function frameGetMarker(frameID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["frameID"] = frameID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("FrameGetMarker");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param email
		 * @return Asynchronous token
		 */
		public function userIsEmailAvailable(email:String):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["email"] = email;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("UserIsEmailAvailable");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param email* @param password
		 * @return Asynchronous token
		 */
		public function userLogin(email:String,password:String):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["email"] = email;
	            out["password"] = password;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("UserLogin");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param email* @param password* @param name* @param description* @param icon
		 * @return Asynchronous token
		 */
		public function userAdd(email:String,password:String,name:String,description:String,icon:flash.utils.ByteArray):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["email"] = email;
	            out["password"] = password;
	            out["name"] = name;
	            out["description"] = description;
	            out["icon"] = icon;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("UserAdd");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param userID
		 * @return Asynchronous token
		 */
		public function userRemove(userID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["userID"] = userID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("UserRemove");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param email
		 * @return Asynchronous token
		 */
		public function userGetID(email:String):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["email"] = email;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("UserGetID");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param userID
		 * @return Asynchronous token
		 */
		public function userGetEmail(userID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["userID"] = userID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("UserGetEmail");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param userID
		 * @return Asynchronous token
		 */
		public function userGetPassword(userID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["userID"] = userID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("UserGetPassword");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param userID
		 * @return Asynchronous token
		 */
		public function userGetName(userID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["userID"] = userID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("UserGetName");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param userID
		 * @return Asynchronous token
		 */
		public function userGetDescription(userID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["userID"] = userID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("UserGetDescription");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param userID
		 * @return Asynchronous token
		 */
		public function userGetIcon(userID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["userID"] = userID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("UserGetIcon");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param userID
		 * @return Asynchronous token
		 */
		public function userGetRegistrationDate(userID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["userID"] = userID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("UserGetRegistrationDate");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param userID
		 * @return Asynchronous token
		 */
		public function userGetGroups(userID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["userID"] = userID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("UserGetGroups");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param userID* @param password
		 * @return Asynchronous token
		 */
		public function userSetPassword(userID:Number,password:String):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["userID"] = userID;
	            out["password"] = password;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("UserSetPassword");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param userID* @param name
		 * @return Asynchronous token
		 */
		public function userSetName(userID:Number,name:String):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["userID"] = userID;
	            out["name"] = name;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("UserSetName");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param userID* @param description
		 * @return Asynchronous token
		 */
		public function userSetDescription(userID:Number,description:String):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["userID"] = userID;
	            out["description"] = description;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("UserSetDescription");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param userID* @param icon
		 * @return Asynchronous token
		 */
		public function userSetIcon(userID:Number,icon:flash.utils.ByteArray):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["userID"] = userID;
	            out["icon"] = icon;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("UserSetIcon");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param path
		 * @return Asynchronous token
		 */
		public function cameraIsPathAvailable(path:String):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["path"] = path;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("CameraIsPathAvailable");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param name* @param description* @param icon
		 * @return Asynchronous token
		 */
		public function cameraAdd(name:String,description:String,icon:flash.utils.ByteArray):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["name"] = name;
	            out["description"] = description;
	            out["icon"] = icon;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("CameraAdd");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param cameraID
		 * @return Asynchronous token
		 */
		public function cameraRemove(cameraID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["cameraID"] = cameraID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("CameraRemove");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param path
		 * @return Asynchronous token
		 */
		public function cameraGetID(path:String):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["path"] = path;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("CameraGetID");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param cameraID
		 * @return Asynchronous token
		 */
		public function cameraGetPath(cameraID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["cameraID"] = cameraID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("CameraGetPath");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param cameraID
		 * @return Asynchronous token
		 */
		public function cameraGetName(cameraID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["cameraID"] = cameraID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("CameraGetName");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param cameraID
		 * @return Asynchronous token
		 */
		public function cameraGetDescription(cameraID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["cameraID"] = cameraID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("CameraGetDescription");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param cameraID
		 * @return Asynchronous token
		 */
		public function cameraGetIcon(cameraID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["cameraID"] = cameraID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("CameraGetIcon");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param cameraID
		 * @return Asynchronous token
		 */
		public function cameraGetRegistrationDate(cameraID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["cameraID"] = cameraID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("CameraGetRegistrationDate");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param cameraID
		 * @return Asynchronous token
		 */
		public function cameraGetGroups(cameraID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["cameraID"] = cameraID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("CameraGetGroups");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param cameraID
		 * @return Asynchronous token
		 */
		public function cameraGetFrames(cameraID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["cameraID"] = cameraID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("CameraGetFrames");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param cameraID* @param name
		 * @return Asynchronous token
		 */
		public function cameraSetName(cameraID:Number,name:String):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["cameraID"] = cameraID;
	            out["name"] = name;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("CameraSetName");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param cameraID* @param description
		 * @return Asynchronous token
		 */
		public function cameraSetDescription(cameraID:Number,description:String):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["cameraID"] = cameraID;
	            out["description"] = description;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("CameraSetDescription");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param cameraID* @param icon
		 * @return Asynchronous token
		 */
		public function cameraSetIcon(cameraID:Number,icon:flash.utils.ByteArray):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["cameraID"] = cameraID;
	            out["icon"] = icon;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("CameraSetIcon");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param name* @param description* @param icon* @param privacy
		 * @return Asynchronous token
		 */
		public function groupAdd(name:String,description:String,icon:flash.utils.ByteArray,privacy:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["name"] = name;
	            out["description"] = description;
	            out["icon"] = icon;
	            out["privacy"] = privacy;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("GroupAdd");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
		/**
		 * Performs the low level call to the server for the operation
		 * It passes along the headers and the operation arguments
		 * @param groupID
		 * @return Asynchronous token
		 */
		public function groupRemove(groupID:Number):AsyncToken
		{
			var headerArray:Array = new Array();
            var out:Object = new Object();
            out["groupID"] = groupID;
	            currentOperation = BaseCloudObserverServiceService.getPort("BaseCloudObserverServicePort").binding.portType.getOperation("GroupRemove");
            var pc:PendingCall = new PendingCall(out,headerArray);
            call(currentOperation,out,pc.token,pc.headers);
            return pc.token;
		}
        /**
         * Performs the actual call to the remove server
         * It SOAP-encodes the message using the schema and WSDL operation options set above and then calls the server using 
         * an async invoker
         * It also registers internal event handlers for the result / fault cases
         * @private
         */
        private function call(operation:WSDLOperation,args:Object,token:AsyncToken,headers:Array=null):void
        {
	    	var enc:SOAPEncoder = new SOAPEncoder();
	        var soap:Object = new Object;
	        var message:SOAPMessage = new SOAPMessage();
	        enc.wsdlOperation = operation;
	        soap = enc.encodeRequest(args,headers);
	        message.setSOAPAction(operation.soapAction);
	        message.body = soap.toString();
	        message.url=endpointURI;
            var inv:AsyncRequest = new AsyncRequest();
            inv.destination = super.destination;
            //we need this to handle multiple asynchronous calls 
            var wrappedData:Object = new Object();
            wrappedData.operation = currentOperation;
            wrappedData.returnToken = token;
            if(!this.useProxy)
            {
            	var dcs:ChannelSet = new ChannelSet();	
	        	dcs.addChannel(new DirectHTTPChannel("direct_http_channel"));
            	inv.channelSet = dcs;
            }                
            var processRes:AsyncResponder = new AsyncResponder(processResult,faultResult,wrappedData);
            inv.invoke(message,processRes);
		}
        
        /**
         * Internal event handler to process a successful operation call from the server
         * The result is decoded using the schema and operation settings and then the events get passed on to the actual facade that the user employs in the application 
         * @private
         */
		private function processResult(result:Object,wrappedData:Object):void
           {
           		var headers:Object;
           		var token:AsyncToken = wrappedData.returnToken;
                var currentOperation:WSDLOperation = wrappedData.operation;
                var decoder:SOAPDecoder = new SOAPDecoder();
                decoder.resultFormat = "object";
                decoder.headerFormat = "object";
                decoder.multiplePartsFormat = "object";
                decoder.ignoreWhitespace = true;
                decoder.makeObjectsBindable=false;
                decoder.wsdlOperation = currentOperation;
                decoder.schemaManager = currentOperation.schemaManager;
                var body:Object = result.message.body;
                var stringResult:String = String(body);
                if(stringResult == null  || stringResult == "")
                	return;
                var soapResult:SOAPResult = decoder.decodeResponse(result.message.body);
                if(soapResult.isFault)
                {
	                var faults:Array = soapResult.result as Array;
	                for each (var soapFault:Fault in faults)
	                {
		                var soapFaultEvent:FaultEvent = FaultEvent.createEvent(soapFault,token,null);
		                token.dispatchEvent(soapFaultEvent);
	                }
                } else {
	                result = soapResult.result;
	                headers = soapResult.headers;
	                var event:ResultEvent = ResultEvent.createEvent(result,token,null);
	                event.headers = headers;
	                token.dispatchEvent(event);
                }
           }
           	/**
           	 * Handles the cases when there are errors calling the operation on the server
           	 * This is not the case for SOAP faults, which is handled by the SOAP decoder in the result handler
           	 * but more critical errors, like network outage or the impossibility to connect to the server
           	 * The fault is dispatched upwards to the facade so that the user can do something meaningful 
           	 * @private
           	 */
			private function faultResult(error:MessageFaultEvent,token:Object):void
			{
				//when there is a network error the token is actually the wrappedData object from above	
				if(!(token is AsyncToken))
					token = token.returnToken;
				token.dispatchEvent(new FaultEvent(FaultEvent.FAULT,true,true,new Fault(error.faultCode,error.faultString,error.faultDetail)));
			}
		}
	}

	import mx.rpc.AsyncToken;
	import mx.rpc.AsyncResponder;
	import mx.rpc.wsdl.WSDLBinding;
                
    /**
     * Internal class to handle multiple operation call scheduling
     * It allows us to pass data about the operation being encoded / decoded to and from the SOAP encoder / decoder units. 
     * @private
     */
    class PendingCall
    {
		public var args:*;
		public var headers:Array;
		public var token:AsyncToken;
		
		public function PendingCall(args:Object, headers:Array=null)
		{
			this.args = args;
			this.headers = headers;
			this.token = new AsyncToken(null);
		}
	}