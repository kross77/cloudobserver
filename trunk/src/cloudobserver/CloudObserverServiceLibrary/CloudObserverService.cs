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

        public CloudObserverService()
        {
            database = new CloudObserverDatabase();
        }

        // users
        public bool UserIsEmailAvailable(string email)
        {
            return database.UserIsEmailAvailable(email);
        }

        public bool UserLogin(string email, string password)
        {
            return database.UserLogin(email, password);
        }

        public int UserAdd(string email, string password, string name, string description, byte[] icon)
        {
            return database.UserAdd(email, password, name, description, icon);
        }

        public void UserRemove(int userID)
        {
            database.UserRemove(userID);
        }

        public int UserGetID(string email)
        {
            return database.UserGetID(email);
        }

        public string UserGetEmail(int userID)
        {
            return database.UserGetEmail(userID);
        }

        public string UserGetPassword(int userID)
        {
            return database.UserGetPassword(userID);
        }

        public string UserGetName(int userID)
        {
            return database.UserGetName(userID);
        }

        public string UserGetDescription(int userID)
        {
            return database.UserGetDescription(userID);
        }

        public byte[] UserGetIcon(int userID)
        {
            return database.UserGetIcon(userID);
        }

        public DateTime UserGetRegistrationDate(int userID)
        {
            return database.UserGetRegistrationDate(userID);
        }

        public int[] UserGetGroups(int userID)
        {
            return database.UserGetGroups(userID);
        }

        public void UserSetPassword(int userID, string password)
        {
            database.UserSetPassword(userID, password);
        }

        public void UserSetName(int userID, string name)
        {
            database.UserSetName(userID, name);
        }

        public void UserSetDescription(int userID, string description)
        {
            database.UserSetDescription(userID, description);
        }

        public void UserSetIcon(int userID, byte[] icon)
        {
            database.UserSetIcon(userID, icon);
        }

        // cameras
        public bool CameraIsPathAvailable(string path)
        {
            return database.CameraIsPathAvailable(path);
        }

        public int CameraAdd(string name, string description, byte[] icon)
        {
            return database.CameraAdd(name, description, icon);
        }

        public void CameraRemove(int cameraID)
        {
            database.CameraRemove(cameraID);
        }

        public int CameraGetID(string path)
        {
            return database.CameraGetID(path);
        }

        public string CameraGetPath(int cameraID)
        {
            return database.CameraGetPath(cameraID);
        }

        public string CameraGetName(int cameraID)
        {
            return database.CameraGetName(cameraID);
        }

        public string CameraGetDescription(int cameraID)
        {
            return database.CameraGetDescription(cameraID);
        }

        public byte[] CameraGetIcon(int cameraID)
        {
            return database.CameraGetIcon(cameraID);
        }

        public DateTime CameraGetRegistrationDate(int cameraID)
        {
            return database.CameraGetRegistrationDate(cameraID);
        }

        public int[] CameraGetGroups(int cameraID)
        {
            return database.CameraGetGroups(cameraID);
        }

        public int[] CameraGetFrames(int cameraID)
        {
            return database.CameraGetFrames(cameraID);
        }

        public void CameraSetName(int cameraID, string name)
        {
            database.CameraSetName(cameraID, name);
        }

        public void CameraSetDescription(int cameraID, string description)
        {
            database.CameraSetDescription(cameraID, description);
        }

        public void CameraSetIcon(int cameraID, byte[] icon)
        {
            database.CameraSetIcon(cameraID, icon);
        }

        // groups
        public int GroupAdd(string name, string description, byte[] icon, int privacy)
        {
            return database.GroupAdd(name, description, icon, privacy);
        }

        public void GroupRemove(int groupID)
        {
            database.GroupRemove(groupID);
        }

        public int GroupGetID(string name)
        {
            return database.GroupGetID(name);
        }

        public string GroupGetName(int groupID)
        {
            return database.GroupGetName(groupID);
        }

        public string GroupGetDescription(int groupID)
        {
            return database.GroupGetDescription(groupID);
        }

        public byte[] GroupGetIcon(int groupID)
        {
            return database.GroupGetIcon(groupID);
        }

        public int GroupGetPrivacy(int groupID)
        {
            return database.GroupGetPrivacy(groupID);
        }

        public DateTime GroupGetRegistrationDate(int groupID)
        {
            return database.GroupGetRegistrationDate(groupID);
        }

        public int[] GroupGetMembers(int groupID)
        {
            return database.GroupGetMembers(groupID);
        }

        public int[] GroupGetCameras(int groupID)
        {
            return database.GroupGetCameras(groupID);
        }

        public void GroupSetName(int groupID, string name)
        {
            database.GroupSetName(groupID, name);
        }

        public void GroupSetDescription(int groupID, string description)
        {
            database.GroupSetDescription(groupID, description);
        }

        public void GroupSetIcon(int groupID, byte[] icon)
        {
            database.GroupSetIcon(groupID, icon);
        }

        public void GroupSetPrivacy(int groupID, int privacy)
        {
            database.GroupSetPrivacy(groupID, privacy);
        }

        // group members
        public void GroupMemberAdd(int userID, int groupID, int privileges)
        {
            database.GroupMemberAdd(userID, groupID, privileges);
        }

        public void GroupMemberRemove(int userID, int groupID)
        {
            database.GroupMemberRemove(userID, groupID);
        }

        public int GroupMemberGetPrivileges(int userID, int groupID)
        {
            return database.GroupMemberGetPrivileges(userID, groupID);
        }

        public void GroupMemberSetPrivileges(int userID, int groupID, int privileges)
        {
            database.GroupMemberSetPrivileges(userID, groupID, privileges);
        }

        // group cameras
        public void GroupCameraAdd(int cameraID, int groupID)
        {
            database.GroupCameraAdd(cameraID, groupID);
        }

        public void GroupCameraRemove(int cameraID, int groupID)
        {
            database.GroupCameraRemove(cameraID, groupID);
        }

        // frames
        public int FrameAdd(int cameraID, byte[] content, string marker)
        {
            return database.FrameAdd(cameraID, content, marker);
        }

        public void FrameRemove(int frameID)
        {
            database.FrameRemove(frameID);
        }

        public byte[] FrameGetContent(int frameID)
        {
            return database.FrameGetContent(frameID);
        }

        public string FrameGetMarker(int frameID)
        {
            return database.FrameGetMarker(frameID);
        }
    }
}