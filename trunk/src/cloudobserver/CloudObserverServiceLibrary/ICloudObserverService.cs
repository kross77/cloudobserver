using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace CloudObserverServiceLibrary
{
    [ServiceContract]
    public interface ICloudObserverService
    {
        // users
        [OperationContract]
        bool UserIsEmailAvailable(string email);

        [OperationContract]
        bool UserLogin(string email, string password);

        [OperationContract]
        int UserAdd(string email, string password, string name, string description, byte[] icon);

        [OperationContract]
        void UserRemove(int userID);

        [OperationContract]
        int UserGetID(string email);

        [OperationContract]
        string UserGetEmail(int userID);

        [OperationContract]
        string UserGetPassword(int userID);

        [OperationContract]
        string UserGetName(int userID);

        [OperationContract]
        string UserGetDescription(int userID);

        [OperationContract]
        byte[] UserGetIcon(int userID);

        [OperationContract]
        DateTime UserGetRegistrationDate(int userID);

        [OperationContract]
        int[] UserGetGroups(int userID);

        [OperationContract]
        void UserSetPassword(int userID, string password);

        [OperationContract]
        void UserSetName(int userID, string name);

        [OperationContract]
        void UserSetDescription(int userID, string description);

        [OperationContract]
        void UserSetIcon(int userID, byte[] icon);

        // cameras
        [OperationContract]
        bool CameraIsPathAvailable(string path);

        [OperationContract]
        int CameraAdd(string name, string description, byte[] icon);

        [OperationContract]
        void CameraRemove(int cameraID);

        [OperationContract]
        int CameraGetID(string path);

        [OperationContract]
        string CameraGetPath(int cameraID);

        [OperationContract]
        string CameraGetName(int cameraID);

        [OperationContract]
        string CameraGetDescription(int cameraID);

        [OperationContract]
        byte[] CameraGetIcon(int cameraID);

        [OperationContract]
        DateTime CameraGetRegistrationDate(int cameraID);

        [OperationContract]
        int[] CameraGetGroups(int cameraID);

        [OperationContract]
        int[] CameraGetFrames(int cameraID);

        [OperationContract]
        void CameraSetName(int cameraID, string name);

        [OperationContract]
        void CameraSetDescription(int cameraID, string description);

        [OperationContract]
        void CameraSetIcon(int cameraID, byte[] icon);

        // groups
        [OperationContract]
        int GroupAdd(string name, string description, byte[] icon, int privacy);

        [OperationContract]
        void GroupRemove(int groupID);

        [OperationContract]
        int GroupGetID(string name);

        [OperationContract]
        string GroupGetName(int groupID);

        [OperationContract]
        string GroupGetDescription(int groupID);

        [OperationContract]
        byte[] GroupGetIcon(int groupID);

        [OperationContract]
        int GroupGetPrivacy(int groupID);

        [OperationContract]
        DateTime GroupGetRegistrationDate(int groupID);

        [OperationContract]
        int[] GroupGetMembers(int groupID);

        [OperationContract]
        int[] GroupGetCameras(int groupID);

        [OperationContract]
        void GroupSetName(int groupID, string name);

        [OperationContract]
        void GroupSetDescription(int groupID, string description);

        [OperationContract]
        void GroupSetIcon(int groupID, byte[] icon);

        [OperationContract]
        void GroupSetPrivacy(int groupID, int privacy);

        // group members
        [OperationContract]
        void GroupMemberAdd(int userID, int groupID, int privileges);

        [OperationContract]
        void GroupMemberRemove(int userID, int groupID);

        [OperationContract]
        int GroupMemberGetPrivileges(int userID, int groupID);

        [OperationContract]
        void GroupMemberSetPrivileges(int userID, int groupID, int privileges);

        // group cameras
        [OperationContract]
        void GroupCameraAdd(int cameraID, int groupID);

        [OperationContract]
        void GroupCameraRemove(int cameraID, int groupID);

        // frames
        [OperationContract]
        int FrameAdd(int cameraID, byte[] content, string marker);

        [OperationContract]
        void FrameRemove(int frameID);

        [OperationContract]
        byte[] FrameGetContent(int frameID);

        [OperationContract]
        string FrameGetMarker(int frameID);
    }
}