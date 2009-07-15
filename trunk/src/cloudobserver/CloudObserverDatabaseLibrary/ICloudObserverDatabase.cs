using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CloudObserverDatabaseLibrary
{
    interface ICloudObserverDatabase
    {
        // database management functions
        void ClearDatabase();

        // user manipulation functions
        bool IsEmailRegistered(string email);
        bool IsUserRegistered(string email, string password);
        int RegisterUser(string email, string password, string name);
        void RemoveUser(int userID);
        int GetUserID(string email);
        string GetUserEmail(int userID);
        string GetUserPassword(int userID);
        string GetUserName(int userID);
        string GetUserDescription(int userID);
        byte[] GetUserIcon(int userID);
        DateTime GetUserRegistrationDate(int userID);
        int[] GetUserGroups(int userID);
        void SetUserPassword(int userID, string password);
        void SetUserName(int userID, string name);
        void SetUserDescription(int userID, string description);
        void SetUserIcon(int userID, byte[] icon);

        // group manipulation functions
        bool IsGroupRegistered(string name);
        int RegisterGroup(string name, int privacy);
        void RemoveGroup(int groupID);
        int GetGroupID(string name);
        string GetGroupName(int groupID);
        string GetGroupDescription(int groupID);
        byte[] GetGroupIcon(int groupID);
        int GetGroupPrivacy(int groupID);
        DateTime GetGroupRegistrationDate(int groupID);
        int[] GetGroupMembers(int groupID);
        int[] GetGroupCameras(int groupID);
        void SetGroupName(int groupID, string name);
        void SetGroupDescription(int groupID, string description);
        void SetGroupIcon(int groupID, byte[] icon);
        void SetGroupPrivacy(int groupID, int privacy);        
        void AddGroupMember(int userID, int groupID, int privileges);
        void SetGroupMemberPrivileges(int userID, int groupID, int privileges);
        void RemoveGroupMember(int userID, int groupID);
        void AddGroupCamera(int cameraID, int groupID);
        void RemoveGroupCamera(int cameraID, int groupID);

        // camera manipulations functions
        bool IsCameraRegistered(string path);
        int RegisterCamera(string name);
        void RemoveCamera(int cameraID);
        int GetCameraID(string path);
        string GetCameraPath(int cameraID);
        string GetCameraName(int cameraID);
        string GetCameraDescription(int cameraID);
        byte[] GetCameraIcon(int cameraID);
        DateTime GetCameraRegistrationDate(int cameraID);
        int[] GetCameraGroups(int cameraID);
        int[] GetCameraFrames(int cameraID);
        void SetCameraName(int cameraID, string name);
        void SetCameraDescription(int cameraID, string description);
        void SetCameraIcon(int cameraID, byte[] icon);

        // frame manipulations functions
        void AddFrame(int cameraID, byte[] content, string marker);
        void RemoveFrame(int frameID);
        byte[] GetFrameContent(int frameID);
        string GetFrameMarker(int frameID);
    }
}
