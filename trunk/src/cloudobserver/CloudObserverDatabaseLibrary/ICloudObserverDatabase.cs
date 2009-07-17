using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CloudObserverDatabaseLibrary
{
    interface ICloudObserverDatabase
    {
        // users
        bool UserIsEmailAvailable(string email);
        bool UserLogin(string email, string password);
        int UserAdd(string email, string password, string name, string description, byte[] icon);
        void UserRemove(int userID);
        int UserGetID(string email);
        string UserGetEmail(int userID);
        string UserGetPassword(int userID);
        string UserGetName(int userID);
        string UserGetDescription(int userID);
        byte[] UserGetIcon(int userID);
        DateTime UserGetRegistrationDate(int userID);
        int[] UserGetGroups(int userID);
        void UserSetPassword(int userID, string password);
        void UserSetName(int userID, string name);
        void UserSetDescription(int userID, string description);
        void UserSetIcon(int userID, byte[] icon);

        // cameras
        bool CameraIsPathAvailable(string path);
        int CameraAdd(string name, string description, byte[] icon);
        void CameraRemove(int cameraID);
        int CameraGetID(string path);
        string CameraGetPath(int cameraID);
        string CameraGetName(int cameraID);
        string CameraGetDescription(int cameraID);
        byte[] CameraGetIcon(int cameraID);
        DateTime CameraGetRegistrationDate(int cameraID);
        int[] CameraGetGroups(int cameraID);
        int[] CameraGetFrames(int cameraID);
        void CameraSetName(int cameraID, string name);
        void CameraSetDescription(int cameraID, string description);
        void CameraSetIcon(int cameraID, byte[] icon);

        // groups
        int GroupAdd(string name, string description, byte[] icon, int privacy);
        void GroupRemove(int groupID);
        int GroupGetID(string name);
        string GroupGetName(int groupID);
        string GroupGetDescription(int groupID);
        byte[] GroupGetIcon(int groupID);
        int GroupGetPrivacy(int groupID);
        DateTime GroupGetRegistrationDate(int groupID);
        int[] GroupGetMembers(int groupID);
        int[] GroupGetCameras(int groupID);
        void GroupSetName(int groupID, string name);
        void GroupSetDescription(int groupID, string description);
        void GroupSetIcon(int groupID, byte[] icon);
        void GroupSetPrivacy(int groupID, int privacy);

        // group members
        void GroupMemberAdd(int userID, int groupID, int privileges);
        void GroupMemberRemove(int userID, int groupID);
        int GroupMemberGetPrivileges(int userID, int groupID);
        void GroupMemberSetPrivileges(int userID, int groupID, int privileges);

        // group cameras
        void GroupCameraAdd(int cameraID, int groupID);
        void GroupCameraRemove(int cameraID, int groupID);

        // frames
        int FrameAdd(int cameraID, byte[] content, string marker);
        void FrameRemove(int frameID);
        byte[] FrameGetContent(int frameID);
        string FrameGetMarker(int frameID);

        // database management
        void DatabaseClear();
    }
}