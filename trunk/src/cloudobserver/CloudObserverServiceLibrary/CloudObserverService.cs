using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using CloudObserverDatabaseLibrary;

namespace CloudObserverServiceLibrary
{
    public class CloudObserverService : ICloudObserverService
    {
        CloudObserverDatabase database;

        // auxiliary functions
        private void CheckConnection()
        {
            if (database == null) database = new CloudObserverDatabase();
        }

        // user manipulation functions
        public bool IsEmailRegistered(string email)
        {
            CheckConnection();
            return database.IsEmailRegistered(email);
        }

        public bool IsUserRegistered(string email, string password)
        {
            CheckConnection();
            return database.IsUserRegistered(email, password);
        }

        public int RegisterUser(string email, string password, string name)
        {
            CheckConnection();
            return database.RegisterUser(email, password, name);
        }

        public void RemoveUser(int userID)
        {
            CheckConnection();
            database.RemoveUser(userID);
        }

        public int GetUserID(string email)
        {
            CheckConnection();
            return database.GetUserID(email);
        }

        public string GetUserEmail(int userID)
        {
            CheckConnection();
            return database.GetUserEmail(userID);
        }

        public string GetUserPassword(int userID)
        {
            CheckConnection();
            return database.GetUserPassword(userID);
        }

        public string GetUserName(int userID)
        {
            CheckConnection();
            return database.GetUserName(userID);
        }

        public string GetUserDescription(int userID)
        {
            CheckConnection();
            return database.GetUserDescription(userID);
        }

        public byte[] GetUserIcon(int userID)
        {
            CheckConnection();
            return database.GetUserIcon(userID);
        }

        public DateTime GetUserRegistrationDate(int userID)
        {
            CheckConnection();
            return database.GetUserRegistrationDate(userID);
        }

        public int[] GetUserGroups(int userID)
        {
            CheckConnection();
            return database.GetUserGroups(userID);
        }

        public void SetUserPassword(int userID, string password)
        {
            CheckConnection();
            database.SetUserPassword(userID, password);
        }

        public void SetUserName(int userID, string name)
        {
            CheckConnection();
            database.SetUserName(userID, name);
        }

        public void SetUserDescription(int userID, string description)
        {
            CheckConnection();
            database.SetUserDescription(userID, description);
        }

        public void SetUserIcon(int userID, byte[] icon)
        {
            CheckConnection();
            database.SetUserIcon(userID, icon);
        }

        // group manipulation functions
        public bool IsGroupRegistered(string name)
        {
            CheckConnection();
            return database.IsGroupRegistered(name);
        }

        public int RegisterGroup(string name, int privacy)
        {
            CheckConnection();
            return database.RegisterGroup(name, privacy);
        }

        public void RemoveGroup(int groupID)
        {
            CheckConnection();
            database.RemoveGroup(groupID);
        }

        public int GetGroupID(string name)
        {
            CheckConnection();
            return database.GetGroupID(name);
        }

        public string GetGroupName(int groupID)
        {
            CheckConnection();
            return database.GetGroupName(groupID);
        }

        public string GetGroupDescription(int groupID)
        {
            CheckConnection();
            return database.GetGroupDescription(groupID);
        }

        public byte[] GetGroupIcon(int groupID)
        {
            CheckConnection();
            return database.GetGroupIcon(groupID);
        }

        public int GetGroupPrivacy(int groupID)
        {
            CheckConnection();
            return database.GetGroupPrivacy(groupID);
        }

        public DateTime GetGroupRegistrationDate(int groupID)
        {
            CheckConnection();
            return database.GetGroupRegistrationDate(groupID);
        }

        public int[] GetGroupMembers(int groupID)
        {
            CheckConnection();
            return database.GetGroupMembers(groupID);
        }

        public int[] GetGroupCameras(int groupID)
        {
            CheckConnection();
            return database.GetGroupCameras(groupID);
        }

        public void SetGroupName(int groupID, string name)
        {
            CheckConnection();
            database.SetGroupName(groupID, name);
        }

        public void SetGroupDescription(int groupID, string description)
        {
            CheckConnection();
            database.SetGroupDescription(groupID, description);
        }

        public void SetGroupIcon(int groupID, byte[] icon)
        {
            CheckConnection();
            database.SetGroupIcon(groupID, icon);
        }

        public void SetGroupPrivacy(int groupID, int privacy)
        {
            CheckConnection();
            database.SetGroupPrivacy(groupID, privacy);
        }

        public void AddGroupMember(int userID, int groupID, int privileges)
        {
            CheckConnection();
            database.AddGroupMember(userID, groupID, privileges);
        }

        public void SetGroupMemberPrivileges(int userID, int groupID, int privileges)
        {
            CheckConnection();
            database.SetGroupMemberPrivileges(userID, groupID, privileges);
        }

        public void RemoveGroupMember(int userID, int groupID)
        {
            CheckConnection();
            database.RemoveGroupMember(userID, groupID);
        }

        public void AddGroupCamera(int cameraID, int groupID)
        {
            CheckConnection();
            database.AddGroupCamera(cameraID, groupID);
        }

        public void RemoveGroupCamera(int cameraID, int groupID)
        {
            CheckConnection();
            database.RemoveGroupCamera(cameraID, groupID);
        }

        // camera manipulations functions
        public bool IsCameraRegistered(string path)
        {
            CheckConnection();
            return database.IsCameraRegistered(path);
        }

        public int RegisterCamera(string name)
        {
            CheckConnection();
            return database.RegisterCamera(name);
        }

        public void RemoveCamera(int cameraID)
        {
            CheckConnection();
            database.RemoveCamera(cameraID);
        }

        public int GetCameraID(string path)
        {
            CheckConnection();
            return database.GetCameraID(path);
        }

        public string GetCameraPath(int cameraID)
        {
            CheckConnection();
            return database.GetCameraPath(cameraID);
        }

        public string GetCameraName(int cameraID)
        {
            CheckConnection();
            return database.GetCameraName(cameraID);
        }

        public string GetCameraDescription(int cameraID)
        {
            CheckConnection();
            return database.GetCameraDescription(cameraID);
        }

        public byte[] GetCameraIcon(int cameraID)
        {
            CheckConnection();
            return database.GetCameraIcon(cameraID);
        }

        public DateTime GetCameraRegistrationDate(int cameraID)
        {
            CheckConnection();
            return database.GetCameraRegistrationDate(cameraID);
        }

        public int[] GetCameraGroups(int cameraID)
        {
            CheckConnection();
            return database.GetCameraGroups(cameraID);
        }

        public int[] GetCameraFrames(int cameraID)
        {
            CheckConnection();
            return database.GetCameraFrames(cameraID);
        }

        public void SetCameraName(int cameraID, string name)
        {
            CheckConnection();
            database.SetCameraName(cameraID, name);
        }

        public void SetCameraDescription(int cameraID, string description)
        {
            CheckConnection();
            database.SetCameraDescription(cameraID, description);
        }

        public void SetCameraIcon(int cameraID, byte[] icon)
        {
            CheckConnection();
            database.SetCameraIcon(cameraID, icon);
        }

        // frame manipulations functions
        public void AddFrame(int cameraID, byte[] content, string marker)
        {
            CheckConnection();
            database.AddFrame(cameraID, content, marker);
        }

        public void RemoveFrame(int frameID)
        {
            CheckConnection();
            database.RemoveFrame(frameID);
        }

        public byte[] GetFrameContent(int frameID)
        {
            CheckConnection();
            return database.GetFrameContent(frameID);
        }

        public string GetFrameMarker(int frameID)
        {
            CheckConnection();
            return database.GetFrameMarker(frameID);
        }
    }
}
