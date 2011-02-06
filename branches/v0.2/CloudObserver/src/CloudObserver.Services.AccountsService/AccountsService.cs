using System;
using System.ServiceModel;
using CloudObserver.Databases;

namespace CloudObserver.Services
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class AccountsService : AbstractService, AccountsServiceContract
    {
        private AccountsDatabase accountsDatabase;
        private string serverName;
        private string databaseName;
        private bool defaultConnection = true;

        public AccountsService() : base() { }

        public AccountsService(string serverName, string databaseName)
        {
            this.serverName = serverName;
            this.databaseName = databaseName;
            defaultConnection = false;
        }

        public new void SetControllerServiceUri(string controllerServiceUri)
        {
            base.SetControllerServiceUri(controllerServiceUri);
            if (defaultConnection) accountsDatabase = new AccountsDatabase(controllerServiceUri);
            else accountsDatabase = new AccountsDatabase(controllerServiceUri, serverName, databaseName);
        }

        // users
        public void UserRemove(int userID)
        {
            accountsDatabase.UserRemove(userID);
        }

        public int UserGetID(string email)
        {
            return accountsDatabase.UserGetID(email);
        }

        public string UserGetEmail(int userID)
        {
            return accountsDatabase.UserGetEmail(userID);
        }

        public string UserGetPassword(int userID)
        {
            return accountsDatabase.UserGetPassword(userID);
        }

        public string UserGetName(int userID)
        {
            return accountsDatabase.UserGetName(userID);
        }

        public string UserGetDescription(int userID)
        {
            return accountsDatabase.UserGetDescription(userID);
        }

        public byte[] UserGetIcon(int userID)
        {
            return accountsDatabase.UserGetIcon(userID);
        }

        public DateTime UserGetRegistrationDate(int userID)
        {
            return accountsDatabase.UserGetRegistrationDate(userID);
        }

        public int[] UserGetGroups(int userID)
        {
            return accountsDatabase.UserGetGroups(userID);
        }

        public void UserSetPassword(int userID, string password)
        {
            accountsDatabase.UserSetPassword(userID, password);
        }

        public void UserSetName(int userID, string name)
        {
            accountsDatabase.UserSetName(userID, name);
        }

        public void UserSetDescription(int userID, string description)
        {
            accountsDatabase.UserSetDescription(userID, description);
        }

        public void UserSetIcon(int userID, byte[] icon)
        {
            accountsDatabase.UserSetIcon(userID, icon);
        }

        // cameras
        public bool CameraCheckPathAvailability(string path)
        {
            return accountsDatabase.CameraCheckPathAvailability(path);
        }

        public int CameraRegister(string name, string path, string description, byte[] icon)
        {
            return accountsDatabase.CameraRegister(name, path, description, icon);
        }

        public void CameraRemove(int cameraID)
        {
            accountsDatabase.CameraRemove(cameraID);
        }

        public int CameraGetID(string path)
        {
            return accountsDatabase.CameraGetID(path);
        }

        public string CameraGetPath(int cameraID)
        {
            return accountsDatabase.CameraGetPath(cameraID);
        }

        public string CameraGetName(int cameraID)
        {
            return accountsDatabase.CameraGetName(cameraID);
        }

        public string CameraGetDescription(int cameraID)
        {
            return accountsDatabase.CameraGetDescription(cameraID);
        }

        public byte[] CameraGetIcon(int cameraID)
        {
            return accountsDatabase.CameraGetIcon(cameraID);
        }

        public DateTime CameraGetRegistrationDate(int cameraID)
        {
            return accountsDatabase.CameraGetRegistrationDate(cameraID);
        }

        public int[] CameraGetGroups(int cameraID)
        {
            return accountsDatabase.CameraGetGroups(cameraID);
        }

        public void CameraSetName(int cameraID, string name)
        {
            accountsDatabase.CameraSetName(cameraID, name);
        }

        public void CameraSetDescription(int cameraID, string description)
        {
            accountsDatabase.CameraSetDescription(cameraID, description);
        }

        public void CameraSetIcon(int cameraID, byte[] icon)
        {
            accountsDatabase.CameraSetIcon(cameraID, icon);
        }

        // groups
        public int GroupRegister(string name, string description, byte[] icon, int privacy)
        {
            return accountsDatabase.GroupRegister(name, description, icon, privacy);
        }

        public void GroupRemove(int groupID)
        {
            accountsDatabase.GroupRemove(groupID);
        }

        public int GroupGetID(string name)
        {
            return accountsDatabase.GroupGetID(name);
        }

        public string GroupGetName(int groupID)
        {
            return accountsDatabase.GroupGetName(groupID);
        }

        public string GroupGetDescription(int groupID)
        {
            return accountsDatabase.GroupGetDescription(groupID);
        }

        public byte[] GroupGetIcon(int groupID)
        {
            return accountsDatabase.GroupGetIcon(groupID);
        }

        public int GroupGetPrivacy(int groupID)
        {
            return accountsDatabase.GroupGetPrivacy(groupID);
        }

        public DateTime GroupGetRegistrationDate(int groupID)
        {
            return accountsDatabase.GroupGetRegistrationDate(groupID);
        }

        public int[] GroupGetMembers(int groupID)
        {
            return accountsDatabase.GroupGetMembers(groupID);
        }

        public int[] GroupGetCameras(int groupID)
        {
            return accountsDatabase.GroupGetCameras(groupID);
        }

        public void GroupSetName(int groupID, string name)
        {
            accountsDatabase.GroupSetName(groupID, name);
        }

        public void GroupSetDescription(int groupID, string description)
        {
            accountsDatabase.GroupSetDescription(groupID, description);
        }

        public void GroupSetIcon(int groupID, byte[] icon)
        {
            accountsDatabase.GroupSetIcon(groupID, icon);
        }

        public void GroupSetPrivacy(int groupID, int privacy)
        {
            accountsDatabase.GroupSetPrivacy(groupID, privacy);
        }

        // group members
        public void GroupMemberAdd(int userID, int groupID, int privileges)
        {
            accountsDatabase.GroupMemberAdd(userID, groupID, privileges);
        }

        public void GroupMemberRemove(int userID, int groupID)
        {
            accountsDatabase.GroupMemberRemove(userID, groupID);
        }

        public int GroupMemberGetPrivileges(int userID, int groupID)
        {
            return accountsDatabase.GroupMemberGetPrivileges(userID, groupID);
        }

        public void GroupMemberSetPrivileges(int userID, int groupID, int privileges)
        {
            accountsDatabase.GroupMemberSetPrivileges(userID, groupID, privileges);
        }

        // group cameras
        public void GroupCameraAdd(int cameraID, int groupID)
        {
            accountsDatabase.GroupCameraAdd(cameraID, groupID);
        }

        public void GroupCameraRemove(int cameraID, int groupID)
        {
            accountsDatabase.GroupCameraRemove(cameraID, groupID);
        }
    }
}