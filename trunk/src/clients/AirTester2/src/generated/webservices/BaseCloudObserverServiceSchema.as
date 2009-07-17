package generated.webservices
{
	 import mx.rpc.xml.Schema
	 public class BaseCloudObserverServiceSchema
	{
		 public var schemas:Array = new Array();
		 public var targetNamespaces:Array = new Array();
		 public function BaseCloudObserverServiceSchema():void
		{
			 var xsdXML2:XML = <xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:tns="http://schemas.microsoft.com/2003/10/Serialization/Arrays" attributeFormDefault="unqualified" elementFormDefault="qualified" targetNamespace="http://schemas.microsoft.com/2003/10/Serialization/Arrays">
    <xs:complexType name="ArrayOfint">
        <xs:sequence>
            <xs:element maxOccurs="unbounded" minOccurs="0" name="int" type="xs:int"/>
        </xs:sequence>
    </xs:complexType>
    <xs:element name="ArrayOfint" nillable="true" type="tns:ArrayOfint"/>
</xs:schema>
;
			 var xsdSchema2:Schema = new Schema(xsdXML2);
			schemas.push(xsdSchema2);
			targetNamespaces.push(new Namespace('','http://schemas.microsoft.com/2003/10/Serialization/Arrays'));
			 var xsdXML1:XML = <xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:ns0="http://schemas.microsoft.com/2003/10/Serialization/Arrays" xmlns:tns="http://tempuri.org/" attributeFormDefault="unqualified" elementFormDefault="qualified" targetNamespace="http://tempuri.org/">
    <xs:import namespace="http://schemas.microsoft.com/2003/10/Serialization/Arrays" schemaLocation="http://localhost:2101/CloudObserverWebsite/CloudObserverService.svc?xsd=xsd2"/>
    <xs:element name="CameraSetDescription">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="cameraID" type="xs:int"/>
                <xs:element minOccurs="0" name="description" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraSetDescriptionResponse">
        <xs:complexType>
            <xs:sequence/>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraSetIcon">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="cameraID" type="xs:int"/>
                <xs:element minOccurs="0" name="icon" nillable="true" type="xs:base64Binary"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraSetIconResponse">
        <xs:complexType>
            <xs:sequence/>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupAdd">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="name" nillable="true" type="xs:string"/>
                <xs:element minOccurs="0" name="description" nillable="true" type="xs:string"/>
                <xs:element minOccurs="0" name="icon" nillable="true" type="xs:base64Binary"/>
                <xs:element minOccurs="0" name="privacy" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupAddResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="GroupAddResult" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupRemove">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="groupID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupRemoveResponse">
        <xs:complexType>
            <xs:sequence/>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupGetID">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="name" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupGetIDResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="GroupGetIDResult" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupGetName">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="groupID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupGetNameResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="GroupGetNameResult" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupGetDescription">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="groupID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupGetDescriptionResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="GroupGetDescriptionResult" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupGetIcon">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="groupID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupGetIconResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="GroupGetIconResult" nillable="true" type="xs:base64Binary"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupGetPrivacy">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="groupID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupGetPrivacyResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="GroupGetPrivacyResult" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupGetRegistrationDate">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="groupID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupGetRegistrationDateResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="GroupGetRegistrationDateResult" type="xs:dateTime"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupGetMembers">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="groupID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupGetMembersResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element xmlns:q1="http://schemas.microsoft.com/2003/10/Serialization/Arrays" minOccurs="0" name="GroupGetMembersResult" nillable="true" type="ns0:ArrayOfint"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupGetCameras">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="groupID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupGetCamerasResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element xmlns:q2="http://schemas.microsoft.com/2003/10/Serialization/Arrays" minOccurs="0" name="GroupGetCamerasResult" nillable="true" type="ns0:ArrayOfint"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupSetName">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="groupID" type="xs:int"/>
                <xs:element minOccurs="0" name="name" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupSetNameResponse">
        <xs:complexType>
            <xs:sequence/>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupSetDescription">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="groupID" type="xs:int"/>
                <xs:element minOccurs="0" name="description" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupSetDescriptionResponse">
        <xs:complexType>
            <xs:sequence/>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupSetIcon">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="groupID" type="xs:int"/>
                <xs:element minOccurs="0" name="icon" nillable="true" type="xs:base64Binary"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupSetIconResponse">
        <xs:complexType>
            <xs:sequence/>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupSetPrivacy">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="groupID" type="xs:int"/>
                <xs:element minOccurs="0" name="privacy" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupSetPrivacyResponse">
        <xs:complexType>
            <xs:sequence/>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupMemberAdd">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="userID" type="xs:int"/>
                <xs:element minOccurs="0" name="groupID" type="xs:int"/>
                <xs:element minOccurs="0" name="privileges" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupMemberAddResponse">
        <xs:complexType>
            <xs:sequence/>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupMemberRemove">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="userID" type="xs:int"/>
                <xs:element minOccurs="0" name="groupID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupMemberRemoveResponse">
        <xs:complexType>
            <xs:sequence/>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupMemberGetPrivileges">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="userID" type="xs:int"/>
                <xs:element minOccurs="0" name="groupID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupMemberGetPrivilegesResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="GroupMemberGetPrivilegesResult" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupMemberSetPrivileges">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="userID" type="xs:int"/>
                <xs:element minOccurs="0" name="groupID" type="xs:int"/>
                <xs:element minOccurs="0" name="privileges" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupMemberSetPrivilegesResponse">
        <xs:complexType>
            <xs:sequence/>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupCameraAdd">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="cameraID" type="xs:int"/>
                <xs:element minOccurs="0" name="groupID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupCameraAddResponse">
        <xs:complexType>
            <xs:sequence/>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupCameraRemove">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="cameraID" type="xs:int"/>
                <xs:element minOccurs="0" name="groupID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="GroupCameraRemoveResponse">
        <xs:complexType>
            <xs:sequence/>
        </xs:complexType>
    </xs:element>
    <xs:element name="FrameAdd">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="cameraID" type="xs:int"/>
                <xs:element minOccurs="0" name="content" nillable="true" type="xs:base64Binary"/>
                <xs:element minOccurs="0" name="marker" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="FrameAddResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="FrameAddResult" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="FrameRemove">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="frameID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="FrameRemoveResponse">
        <xs:complexType>
            <xs:sequence/>
        </xs:complexType>
    </xs:element>
    <xs:element name="FrameGetContent">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="frameID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="FrameGetContentResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="FrameGetContentResult" nillable="true" type="xs:base64Binary"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="FrameGetMarker">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="frameID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="FrameGetMarkerResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="FrameGetMarkerResult" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserIsEmailAvailable">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="email" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserIsEmailAvailableResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="UserIsEmailAvailableResult" type="xs:boolean"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserLogin">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="email" nillable="true" type="xs:string"/>
                <xs:element minOccurs="0" name="password" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserLoginResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="UserLoginResult" type="xs:boolean"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserAdd">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="email" nillable="true" type="xs:string"/>
                <xs:element minOccurs="0" name="password" nillable="true" type="xs:string"/>
                <xs:element minOccurs="0" name="name" nillable="true" type="xs:string"/>
                <xs:element minOccurs="0" name="description" nillable="true" type="xs:string"/>
                <xs:element minOccurs="0" name="icon" nillable="true" type="xs:base64Binary"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserAddResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="UserAddResult" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserRemove">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="userID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserRemoveResponse">
        <xs:complexType>
            <xs:sequence/>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserGetID">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="email" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserGetIDResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="UserGetIDResult" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserGetEmail">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="userID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserGetEmailResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="UserGetEmailResult" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserGetPassword">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="userID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserGetPasswordResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="UserGetPasswordResult" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserGetName">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="userID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserGetNameResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="UserGetNameResult" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserGetDescription">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="userID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserGetDescriptionResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="UserGetDescriptionResult" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserGetIcon">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="userID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserGetIconResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="UserGetIconResult" nillable="true" type="xs:base64Binary"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserGetRegistrationDate">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="userID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserGetRegistrationDateResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="UserGetRegistrationDateResult" type="xs:dateTime"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserGetGroups">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="userID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserGetGroupsResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element xmlns:q3="http://schemas.microsoft.com/2003/10/Serialization/Arrays" minOccurs="0" name="UserGetGroupsResult" nillable="true" type="ns0:ArrayOfint"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserSetPassword">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="userID" type="xs:int"/>
                <xs:element minOccurs="0" name="password" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserSetPasswordResponse">
        <xs:complexType>
            <xs:sequence/>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserSetName">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="userID" type="xs:int"/>
                <xs:element minOccurs="0" name="name" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserSetNameResponse">
        <xs:complexType>
            <xs:sequence/>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserSetDescription">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="userID" type="xs:int"/>
                <xs:element minOccurs="0" name="description" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserSetDescriptionResponse">
        <xs:complexType>
            <xs:sequence/>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserSetIcon">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="userID" type="xs:int"/>
                <xs:element minOccurs="0" name="icon" nillable="true" type="xs:base64Binary"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="UserSetIconResponse">
        <xs:complexType>
            <xs:sequence/>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraIsPathAvailable">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="path" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraIsPathAvailableResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="CameraIsPathAvailableResult" type="xs:boolean"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraAdd">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="name" nillable="true" type="xs:string"/>
                <xs:element minOccurs="0" name="description" nillable="true" type="xs:string"/>
                <xs:element minOccurs="0" name="icon" nillable="true" type="xs:base64Binary"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraAddResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="CameraAddResult" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraRemove">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="cameraID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraRemoveResponse">
        <xs:complexType>
            <xs:sequence/>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraGetID">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="path" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraGetIDResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="CameraGetIDResult" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraGetPath">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="cameraID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraGetPathResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="CameraGetPathResult" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraGetName">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="cameraID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraGetNameResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="CameraGetNameResult" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraGetDescription">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="cameraID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraGetDescriptionResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="CameraGetDescriptionResult" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraGetIcon">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="cameraID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraGetIconResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="CameraGetIconResult" nillable="true" type="xs:base64Binary"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraGetRegistrationDate">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="cameraID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraGetRegistrationDateResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="CameraGetRegistrationDateResult" type="xs:dateTime"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraGetGroups">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="cameraID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraGetGroupsResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element xmlns:q4="http://schemas.microsoft.com/2003/10/Serialization/Arrays" minOccurs="0" name="CameraGetGroupsResult" nillable="true" type="ns0:ArrayOfint"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraGetFrames">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="cameraID" type="xs:int"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraGetFramesResponse">
        <xs:complexType>
            <xs:sequence>
                <xs:element xmlns:q5="http://schemas.microsoft.com/2003/10/Serialization/Arrays" minOccurs="0" name="CameraGetFramesResult" nillable="true" type="ns0:ArrayOfint"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraSetName">
        <xs:complexType>
            <xs:sequence>
                <xs:element minOccurs="0" name="cameraID" type="xs:int"/>
                <xs:element minOccurs="0" name="name" nillable="true" type="xs:string"/>
            </xs:sequence>
        </xs:complexType>
    </xs:element>
    <xs:element name="CameraSetNameResponse">
        <xs:complexType>
            <xs:sequence/>
        </xs:complexType>
    </xs:element>
</xs:schema>
;
			 var xsdSchema1:Schema = new Schema(xsdXML1);
			schemas.push(xsdSchema1);
			targetNamespaces.push(new Namespace('','http://tempuri.org/'));
			 var xsdXML3:XML = <xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:tns="http://schemas.microsoft.com/2003/10/Serialization/" attributeFormDefault="qualified" elementFormDefault="qualified" targetNamespace="http://schemas.microsoft.com/2003/10/Serialization/">
    <xs:element name="anyType" nillable="true" type="xs:anyType"/>
    <xs:element name="anyURI" nillable="true" type="xs:anyURI"/>
    <xs:element name="base64Binary" nillable="true" type="xs:base64Binary"/>
    <xs:element name="boolean" nillable="true" type="xs:boolean"/>
    <xs:element name="byte" nillable="true" type="xs:byte"/>
    <xs:element name="dateTime" nillable="true" type="xs:dateTime"/>
    <xs:element name="decimal" nillable="true" type="xs:decimal"/>
    <xs:element name="double" nillable="true" type="xs:double"/>
    <xs:element name="float" nillable="true" type="xs:float"/>
    <xs:element name="int" nillable="true" type="xs:int"/>
    <xs:element name="long" nillable="true" type="xs:long"/>
    <xs:element name="QName" nillable="true" type="xs:QName"/>
    <xs:element name="short" nillable="true" type="xs:short"/>
    <xs:element name="string" nillable="true" type="xs:string"/>
    <xs:element name="unsignedByte" nillable="true" type="xs:unsignedByte"/>
    <xs:element name="unsignedInt" nillable="true" type="xs:unsignedInt"/>
    <xs:element name="unsignedLong" nillable="true" type="xs:unsignedLong"/>
    <xs:element name="unsignedShort" nillable="true" type="xs:unsignedShort"/>
    <xs:element name="char" nillable="true" type="tns:char"/>
    <xs:simpleType name="char">
        <xs:restriction base="xs:int"/>
    </xs:simpleType>
    <xs:element name="duration" nillable="true" type="tns:duration"/>
    <xs:simpleType name="duration">
        <xs:restriction base="xs:duration">
            <xs:pattern value="\-?P(\d*D)?(T(\d*H)?(\d*M)?(\d*(\.\d*)?S)?)?"/>
            <xs:minInclusive value="-P10675199DT2H48M5.4775808S"/>
            <xs:maxInclusive value="P10675199DT2H48M5.4775807S"/>
        </xs:restriction>
    </xs:simpleType>
    <xs:element name="guid" nillable="true" type="tns:guid"/>
    <xs:simpleType name="guid">
        <xs:restriction base="xs:string">
            <xs:pattern value="[\da-fA-F]{8}-[\da-fA-F]{4}-[\da-fA-F]{4}-[\da-fA-F]{4}-[\da-fA-F]{12}"/>
        </xs:restriction>
    </xs:simpleType>
    <xs:attribute name="FactoryType" type="xs:QName"/>
    <xs:attribute name="Id" type="xs:ID"/>
    <xs:attribute name="Ref" type="xs:IDREF"/>
</xs:schema>
;
			 var xsdSchema3:Schema = new Schema(xsdXML3);
			schemas.push(xsdSchema3);
			targetNamespaces.push(new Namespace('','http://schemas.microsoft.com/2003/10/Serialization/'));
			 var xsdXML0:XML = <xsd:schema xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns="http://tempuri.org/Imports" xmlns:msc="http://schemas.microsoft.com/ws/2005/12/wsdl/contract" xmlns:soap="http://schemas.xmlsoap.org/wsdl/soap/" xmlns:soap12="http://schemas.xmlsoap.org/wsdl/soap12/" xmlns:soapenc="http://schemas.xmlsoap.org/soap/encoding/" xmlns:tns="http://tempuri.org/" xmlns:wsa="http://schemas.xmlsoap.org/ws/2004/08/addressing" xmlns:wsa10="http://www.w3.org/2005/08/addressing" xmlns:wsam="http://www.w3.org/2007/05/addressing/metadata" xmlns:wsap="http://schemas.xmlsoap.org/ws/2004/08/addressing/policy" xmlns:wsaw="http://www.w3.org/2006/05/addressing/wsdl" xmlns:wsdl="http://schemas.xmlsoap.org/wsdl/" xmlns:wsp="http://schemas.xmlsoap.org/ws/2004/09/policy" xmlns:wsu="http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd" xmlns:wsx="http://schemas.xmlsoap.org/ws/2004/09/mex" attributeFormDefault="unqualified" elementFormDefault="unqualified" targetNamespace="http://tempuri.org/Imports">
    <xsd:import namespace="http://tempuri.org/" schemaLocation="http://localhost:2101/CloudObserverWebsite/CloudObserverService.svc?xsd=xsd0"/>
    <xsd:import namespace="http://schemas.microsoft.com/2003/10/Serialization/" schemaLocation="http://localhost:2101/CloudObserverWebsite/CloudObserverService.svc?xsd=xsd1"/>
    <xsd:import namespace="http://schemas.microsoft.com/2003/10/Serialization/Arrays" schemaLocation="http://localhost:2101/CloudObserverWebsite/CloudObserverService.svc?xsd=xsd2"/>
</xsd:schema>
;
			 var xsdSchema0:Schema = new Schema(xsdXML0);
			schemas.push(xsdSchema0);
			targetNamespaces.push(new Namespace('','http://tempuri.org/Imports'));
			xsdSchema0.addImport(new Namespace("http://schemas.microsoft.com/2003/10/Serialization/"), xsdSchema3)
			xsdSchema0.addImport(new Namespace("http://schemas.microsoft.com/2003/10/Serialization/Arrays"), xsdSchema2)
			xsdSchema0.addImport(new Namespace("http://tempuri.org/"), xsdSchema1)
			xsdSchema1.addImport(new Namespace("http://schemas.microsoft.com/2003/10/Serialization/Arrays"), xsdSchema2)
		}
	}
}