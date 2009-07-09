using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Xml.Linq;

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
        int RegisterUser(string email, string password, string name, XElement description, Bitmap icon);
        void RemoveUser(int userID);
        int GetUserID(string email);
        string GetUserEmail(int userID);
        string GetUserPassword(int userID);
        string GetUserName(int userID);
        XElement GetUserDescription(int userID);
        Bitmap GetUserIcon(int userID);
        DateTime GetUserRegistrationDate(int userID);
        int[] GetUserGroups(int userID);
        void SetUserPassword(int userID, string password);
        void SetUserName(int userID, string name);
        void SetUserDescription(int userID, XElement description);
        void SetUserIcon(int userID, Bitmap icon);

        // group manipulation functions
        bool IsGroupRegistered(string name);
        int RegisterGroup(string name, bool privacy);
        int RegisterGroup(string name, XElement description, Bitmap icon, bool privacy);
        void RemoveGroup(int groupID);
        int GetGroupID(string name);
        string GetGroupName(int groupID);
        XElement GetGroupDescription(int groupID);
        Bitmap GetGroupIcon(int groupID);
        bool GetGroupPrivacy(int groupID);
        DateTime GetGroupRegistrationDate(int groupID);
        int[] GetGroupMembers(int groupID);
        int[] GetGroupCameras(int groupID);
        void SetGroupName(int groupID, string name);
        void SetGroupDescription(int groupID, XElement description);
        void SetGroupIcon(int groupID, Bitmap icon);
        void SetGroupPrivacy(int groupID, bool privacy);        
        void AddGroupMember(int userID, int groupID, int privileges);
        void RemoveGroupMember(int userID, int groupID);
        void AddGroupCamera(int cameraID, int groupID);
        void RemoveGroupCamera(int cameraID, int groupID);

        // camera manipulations functions
        bool IsCameraRegistered(string path);
        int RegisterCamera(string path, string name);
        int RegisterCamera(string path, string name, XElement description, Bitmap icon);
        void RemoveCamera(int cameraID);
        int GetCameraID(string path);
        string GetCameraPath(int cameraID);
        string GetCameraName(int cameraID);
        XElement GetCameraDescription(int cameraID);
        Bitmap GetCameraIcon(int cameraID);
        DateTime GetCameraRegistrationDate(int cameraID);
        int[] GetCameraGroups(int cameraID);
        int[] GetCameraFrames(int cameraID);
        void SetCameraName(int cameraID, string name);
        void SetCameraDescription(int cameraID, XElement description);
        void SetCameraIcon(int cameraID, Bitmap icon);

        // frame manipulations functions
        int SaveFrame(int cameraID, Bitmap content, XElement marker);
        void RemoveFrame(int frameID);
        Bitmap GetFrameContent(int frameID);
        XElement GetFrameMarker(int frameID);
    }
}
