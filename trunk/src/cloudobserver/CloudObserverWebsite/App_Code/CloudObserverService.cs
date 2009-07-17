using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using CloudObserverDatabaseLibrary;

public class CloudObserverService : ICloudObserverService
{
    CloudObserverDatabase database;

    private void CheckConnection()
    {
        if (database == null) database = new CloudObserverDatabase();
    }

    // users
    public bool UserIsEmailAvailable(string email)
    {
        CheckConnection();
        return database.UserIsEmailAvailable(email);
    }

    public bool UserLogin(string email, string password)
    {
        CheckConnection();
        return database.UserLogin(email, password);
    }

    public int UserAdd(string email, string password, string name, string description, byte[] icon)
    {
        CheckConnection();
        return database.UserAdd(email, password, name, description, icon);
    }

    public void UserRemove(int userID)
    {
        CheckConnection();
        database.UserRemove(userID);
    }

    public int UserGetID(string email)
    {
        CheckConnection();
        return database.UserGetID(email);
    }

    public string UserGetEmail(int userID)
    {
        CheckConnection();
        return database.UserGetEmail(userID);
    }

    public string UserGetPassword(int userID)
    {
        CheckConnection();
        return database.UserGetPassword(userID);
    }

    public string UserGetName(int userID)
    {
        CheckConnection();
        return database.UserGetName(userID);
    }

    public string UserGetDescription(int userID)
    {
        CheckConnection();
        return database.UserGetDescription(userID);
    }

    public byte[] UserGetIcon(int userID)
    {
        CheckConnection();
        return database.UserGetIcon(userID);
    }

    public DateTime UserGetRegistrationDate(int userID)
    {
        CheckConnection();
        return database.UserGetRegistrationDate(userID);
    }

    public int[] UserGetGroups(int userID)
    {
        CheckConnection();
        return database.UserGetGroups(userID);
    }

    public void UserSetPassword(int userID, string password)
    {
        CheckConnection();
        database.UserSetPassword(userID, password);
    }

    public void UserSetName(int userID, string name)
    {
        CheckConnection();
        database.UserSetName(userID, name);
    }

    public void UserSetDescription(int userID, string description)
    {
        CheckConnection();
        database.UserSetDescription(userID, description);
    }

    public void UserSetIcon(int userID, byte[] icon)
    {
        CheckConnection();
        database.UserSetIcon(userID, icon);
    }

    // cameras
    public bool CameraIsPathAvailable(string path)
    {
        CheckConnection();
        return database.CameraIsPathAvailable(path);
    }

    public int CameraAdd(string name, string description, byte[] icon)
    {
        CheckConnection();
        return database.CameraAdd(name, description, icon);
    }

    public void CameraRemove(int cameraID)
    {
        CheckConnection();
        database.CameraRemove(cameraID);
    }

    public int CameraGetID(string path)
    {
        CheckConnection();
        return database.CameraGetID(path);
    }

    public string CameraGetPath(int cameraID)
    {
        CheckConnection();
        return database.CameraGetPath(cameraID);
    }

    public string CameraGetName(int cameraID)
    {
        CheckConnection();
        return database.CameraGetName(cameraID);
    }

    public string CameraGetDescription(int cameraID)
    {
        CheckConnection();
        return database.CameraGetDescription(cameraID);
    }

    public byte[] CameraGetIcon(int cameraID)
    {
        CheckConnection();
        return database.CameraGetIcon(cameraID);
    }

    public DateTime CameraGetRegistrationDate(int cameraID)
    {
        CheckConnection();
        return database.CameraGetRegistrationDate(cameraID);
    }

    public int[] CameraGetGroups(int cameraID)
    {
        CheckConnection();
        return database.CameraGetGroups(cameraID);
    }

    public int[] CameraGetFrames(int cameraID)
    {
        CheckConnection();
        return database.CameraGetFrames(cameraID);
    }

    public void CameraSetName(int cameraID, string name)
    {
        CheckConnection();
        database.CameraSetName(cameraID, name);
    }

    public void CameraSetDescription(int cameraID, string description)
    {
        CheckConnection();
        database.CameraSetDescription(cameraID, description);
    }

    public void CameraSetIcon(int cameraID, byte[] icon)
    {
        CheckConnection();
        database.CameraSetIcon(cameraID, icon);
    }

    // groups
    public int GroupAdd(string name, string description, byte[] icon, int privacy)
    {
        CheckConnection();
        return database.GroupAdd(name, description, icon, privacy);
    }

    public void GroupRemove(int groupID)
    {
        CheckConnection();
        database.GroupRemove(groupID);
    }

    public int GroupGetID(string name)
    {
        CheckConnection();
        return database.GroupGetID(name);
    }

    public string GroupGetName(int groupID)
    {
        CheckConnection();
        return database.GroupGetName(groupID);
    }

    public string GroupGetDescription(int groupID)
    {
        CheckConnection();
        return database.GroupGetDescription(groupID);
    }

    public byte[] GroupGetIcon(int groupID)
    {
        CheckConnection();
        return database.GroupGetIcon(groupID);
    }

    public int GroupGetPrivacy(int groupID)
    {
        CheckConnection();
        return database.GroupGetPrivacy(groupID);
    }

    public DateTime GroupGetRegistrationDate(int groupID)
    {
        CheckConnection();
        return database.GroupGetRegistrationDate(groupID);
    }

    public int[] GroupGetMembers(int groupID)
    {
        CheckConnection();
        return database.GroupGetMembers(groupID);
    }

    public int[] GroupGetCameras(int groupID)
    {
        CheckConnection();
        return database.GroupGetCameras(groupID);
    }

    public void GroupSetName(int groupID, string name)
    {
        CheckConnection();
        database.GroupSetName(groupID, name);
    }

    public void GroupSetDescription(int groupID, string description)
    {
        CheckConnection();
        database.GroupSetDescription(groupID, description);
    }

    public void GroupSetIcon(int groupID, byte[] icon)
    {
        CheckConnection();
        database.GroupSetIcon(groupID, icon);
    }

    public void GroupSetPrivacy(int groupID, int privacy)
    {
        CheckConnection();
        database.GroupSetPrivacy(groupID, privacy);
    }

    // group members
    public void GroupMemberAdd(int userID, int groupID, int privileges)
    {
        CheckConnection();
        database.GroupMemberAdd(userID, groupID, privileges);
    }

    public void GroupMemberRemove(int userID, int groupID)
    {
        CheckConnection();
        database.GroupMemberRemove(userID, groupID);
    }

    public int GroupMemberGetPrivileges(int userID, int groupID)
    {
        CheckConnection();
        return database.GroupMemberGetPrivileges(userID, groupID);
    }

    public void GroupMemberSetPrivileges(int userID, int groupID, int privileges)
    {
        CheckConnection();
        database.GroupMemberSetPrivileges(userID, groupID, privileges);
    }

    // group cameras
    public void GroupCameraAdd(int cameraID, int groupID)
    {
        CheckConnection();
        database.GroupCameraAdd(cameraID, groupID);
    }

    public void GroupCameraRemove(int cameraID, int groupID)
    {
        CheckConnection();
        database.GroupCameraRemove(cameraID, groupID);
    }

    // frames
    public int FrameAdd(int cameraID, byte[] content, string marker)
    {
        CheckConnection();
        return database.FrameAdd(cameraID, content, marker);
    }

    public void FrameRemove(int frameID)
    {
        CheckConnection();
        database.FrameRemove(frameID);
    }

    public byte[] FrameGetContent(int frameID)
    {
        CheckConnection();
        return database.FrameGetContent(frameID);
    }

    public string FrameGetMarker(int frameID)
    {
        CheckConnection();
        return database.FrameGetMarker(frameID);
    }
}