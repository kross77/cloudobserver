using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using CloudObserverDataClasses;

namespace CloudObserverServiceLibrary
{
    [ServiceContract]
    public interface ICloudObserverService
    {
        // user manipulation functions
        [OperationContract]
        bool IsEmailRegistered(string email);

        [OperationContract]
        bool IsUserRegistered(string email, string password);

        [OperationContract]
        int RegisterUser(string email, string password, string name);

        [OperationContract]
        void RemoveUser(int userID);

        [OperationContract]
        int GetUserID(string email);

        [OperationContract]
        string GetUserEmail(int userID);

        [OperationContract]
        string GetUserPassword(int userID);

        [OperationContract]
        string GetUserName(int userID);

        [OperationContract]
        string GetUserDescription(int userID);

        [OperationContract]
        byte[] GetUserIcon(int userID);

        [OperationContract]
        DateTime GetUserRegistrationDate(int userID);

        [OperationContract]
        int[] GetUserGroups(int userID);

        [OperationContract]
        void SetUserPassword(int userID, string password);

        [OperationContract]
        void SetUserName(int userID, string name);

        [OperationContract]
        void SetUserDescription(int userID, string description);

        [OperationContract]
        void SetUserIcon(int userID, byte[] icon);

        // group manipulation functions
        [OperationContract]
        bool IsGroupRegistered(string name);

        [OperationContract]
        int RegisterGroup(string name, int privacy);

        [OperationContract]
        void RemoveGroup(int groupID);

        [OperationContract]
        int GetGroupID(string name);

        [OperationContract]
        string GetGroupName(int groupID);

        [OperationContract]
        string GetGroupDescription(int groupID);

        [OperationContract]
        byte[] GetGroupIcon(int groupID);

        [OperationContract]
        int GetGroupPrivacy(int groupID);

        [OperationContract]
        DateTime GetGroupRegistrationDate(int groupID);

        [OperationContract]
        int[] GetGroupMembers(int groupID);

        [OperationContract]
        int[] GetGroupCameras(int groupID);

        [OperationContract]
        void SetGroupName(int groupID, string name);

        [OperationContract]
        void SetGroupDescription(int groupID, string description);

        [OperationContract]
        void SetGroupIcon(int groupID, byte[] icon);

        [OperationContract]
        void SetGroupPrivacy(int groupID, int privacy);

        [OperationContract]
        void AddGroupMember(int userID, int groupID, int privileges);

        [OperationContract]
        void SetGroupMemberPrivileges(int userID, int groupID, int privileges);

        [OperationContract]
        void RemoveGroupMember(int userID, int groupID);

        [OperationContract]
        void AddGroupCamera(int cameraID, int groupID);

        [OperationContract]
        void RemoveGroupCamera(int cameraID, int groupID);

        // camera manipulations functions
        [OperationContract]
        bool IsCameraRegistered(string path);

        [OperationContract]
        int RegisterCamera(string name);

        [OperationContract]
        void RemoveCamera(int cameraID);

        [OperationContract]
        int GetCameraID(string path);

        [OperationContract]
        string GetCameraPath(int cameraID);

        [OperationContract]
        string GetCameraName(int cameraID);

        [OperationContract]
        string GetCameraDescription(int cameraID);

        [OperationContract]
        byte[] GetCameraIcon(int cameraID);

        [OperationContract]
        DateTime GetCameraRegistrationDate(int cameraID);

        [OperationContract]
        int[] GetCameraGroups(int cameraID);

        [OperationContract]
        int[] GetCameraFrames(int cameraID);

        [OperationContract]
        void SetCameraName(int cameraID, string name);

        [OperationContract]
        void SetCameraDescription(int cameraID, string description);

        [OperationContract]
        void SetCameraIcon(int cameraID, byte[] icon);

        // frame manipulations functions
        [OperationContract]
        void AddFrame(int cameraID, byte[] content, string marker);

        [OperationContract]
        void RemoveFrame(int frameID);

        [OperationContract]
        byte[] GetFrameContent(int frameID);

        [OperationContract]
        string GetFrameMarker(int frameID);
    }
}
