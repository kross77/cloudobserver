using System;
using System.Linq;
using System.ServiceModel;
using CloudObserver.Services;

namespace CloudObserver.Databases
{
    public class AccountsDatabase : Database
    {
        private new AccountsDataClassesDataContext database;

        private string controllerServiceUri;
        private ControllerServiceContract controllerService;

        private string storageServiceUri;
        private StorageServiceContract storageService;

        public AccountsDatabase(string controllerServiceUri)
        {
            database = new AccountsDataClassesDataContext();
            this.controllerServiceUri = controllerServiceUri;

            InitializeComponent();
        }

        public AccountsDatabase(string controllerServiceUri, string serverName, string databaseName)
        {
            database = new AccountsDataClassesDataContext(GetConnectionString(serverName, databaseName));
            this.controllerServiceUri = controllerServiceUri;

            InitializeComponent();
        }

        private void InitializeComponent()
        {
            if (!database.DatabaseExists())
                database.CreateDatabase();
            controllerService = ChannelFactory<ControllerServiceContract>.CreateChannel(new BasicHttpBinding(), new EndpointAddress(controllerServiceUri));
            storageServiceUri = controllerService.GetServiceUri(ServiceType.StorageService);
            storageService = ChannelFactory<StorageServiceContract>.CreateChannel(new BasicHttpBinding(), new EndpointAddress(storageServiceUri));
        }

        // users
        public bool UserCheckEmailAvailability(string email)
        {
            return (from u in database.Users where u.Email.Equals(email) select u).Count().Equals(0);
        }

        public bool UserLogin(string email, string password)
        {
            return ((from u in database.Users where u.Email.Equals(email) && u.Password.Equals(password) select u).Count() > 0);
        }

        public int UserRegister(string email, string password, string name, string description, byte[] icon)
        {
            User user = new User
            {
                Email = email,
                Password = password,
                Name = name,
                Description = description,
                IconPath = "",
                RegistrationDate = DateTime.Now
            };

            string iconPath = @"UserIcons\" + user.UserID;
            user.IconPath = iconPath;
            storageService.SaveIntoStorage(iconPath, icon);

            database.Users.InsertOnSubmit(user);
            database.SubmitChanges();
            return user.UserID;
        }

        public void UserRemove(int userID)
        {
            database.Users.DeleteOnSubmit((from u in database.Users where u.UserID.Equals(userID) select u).Single());
            database.SubmitChanges();
        }

        public int UserGetID(string email)
        {
            return (from u in database.Users where u.Email.Equals(email) select u.UserID).Single();
        }

        public string UserGetEmail(int userID)
        {
            return (from u in database.Users where u.UserID.Equals(userID) select u.Email).Single();
        }

        public string UserGetPassword(int userID)
        {
            return (from u in database.Users where u.UserID.Equals(userID) select u.Password).Single();
        }

        public string UserGetName(int userID)
        {
            return (from u in database.Users where u.UserID.Equals(userID) select u.Name).Single();
        }

        public string UserGetDescription(int userID)
        {
            return (from u in database.Users where u.UserID.Equals(userID) select u.Description).Single();
        }

        public byte[] UserGetIcon(int userID)
        {
            return storageService.LoadFromStorage((from u in database.Users where u.UserID.Equals(userID) select u.IconPath).Single());
        }

        public DateTime UserGetRegistrationDate(int userID)
        {
            return (from u in database.Users where u.UserID.Equals(userID) select u.RegistrationDate).Single();
        }

        public int[] UserGetGroups(int userID)
        {
            return (from gm in database.GroupMembers where gm.UserID.Equals(userID) select gm.GroupID).ToArray();
        }

        public void UserSetPassword(int userID, string password)
        {
            (from u in database.Users where u.UserID.Equals(userID) select u).Single().Password = password;
            database.SubmitChanges();
        }

        public void UserSetName(int userID, string name)
        {
            (from u in database.Users where u.UserID.Equals(userID) select u).Single().Name = name;
            database.SubmitChanges();
        }

        public void UserSetDescription(int userID, string description)
        {
            (from u in database.Users where u.UserID.Equals(userID) select u).Single().Description = description;
            database.SubmitChanges();
        }

        public void UserSetIcon(int userID, byte[] icon)
        {
            storageService.SaveIntoStorage(@"UserIcons\" + userID, icon);
        }

        // cameras
        public bool CameraCheckPathAvailability(string path)
        {
            return (from c in database.Cameras where c.Path.Equals(path) select c).Count().Equals(0);
        }

        public int CameraRegister(string name, string path, string description, byte[] icon)
        {
            Camera camera = new Camera
            {
                Path = path,
                Name = name,
                Description = description,
                IconPath = "",
                RegistrationDate = DateTime.Now
            };

            string iconPath = @"CameraIcons" + camera.CameraID;
            camera.IconPath = iconPath;
            storageService.SaveIntoStorage(iconPath, icon);

            database.Cameras.InsertOnSubmit(camera);
            database.SubmitChanges();
            return camera.CameraID;
        }

        public void CameraRemove(int cameraID)
        {
            database.Cameras.DeleteOnSubmit((from c in database.Cameras where c.CameraID.Equals(cameraID) select c).Single());
            database.SubmitChanges();
        }

        public int CameraGetID(string path)
        {
            return (from c in database.Cameras where c.Path.Equals(path) select c.CameraID).Single();
        }

        public string CameraGetPath(int cameraID)
        {
            return (from c in database.Cameras where c.CameraID.Equals(cameraID) select c.Path).Single();
        }

        public string CameraGetName(int cameraID)
        {
            return (from c in database.Cameras where c.CameraID.Equals(cameraID) select c.Name).Single();
        }

        public string CameraGetDescription(int cameraID)
        {
            return (from c in database.Cameras where c.CameraID.Equals(cameraID) select c.Description).Single();
        }

        public byte[] CameraGetIcon(int cameraID)
        {
            return storageService.LoadFromStorage((from c in database.Cameras where c.CameraID.Equals(cameraID) select c.IconPath).Single());
        }

        public DateTime CameraGetRegistrationDate(int cameraID)
        {
            return (from c in database.Cameras where c.CameraID.Equals(cameraID) select c.RegistrationDate).Single();
        }

        public int[] CameraGetGroups(int cameraID)
        {
            return (from gc in database.GroupCameras where gc.CameraID.Equals(cameraID) select gc.GroupID).ToArray();
        }

        public void CameraSetName(int cameraID, string name)
        {
            (from c in database.Cameras where c.CameraID.Equals(cameraID) select c).Single().Name = name;
            database.SubmitChanges();
        }

        public void CameraSetDescription(int cameraID, string description)
        {
            (from c in database.Cameras where c.CameraID.Equals(cameraID) select c).Single().Description = description;
            database.SubmitChanges();
        }

        public void CameraSetIcon(int cameraID, byte[] icon)
        {
            storageService.SaveIntoStorage(@"CameraIcons\" + cameraID, icon);
        }

        // groups
        public int GroupRegister(string name, string description, byte[] icon, int privacy)
        {
            Group group = new Group
            {
                Name = name,
                Description = description,
                IconPath = "",
                Privacy = privacy,
                RegistrationDate = DateTime.Now
            };

            string iconPath = @"GroupIcons\" + group.GroupID;
            group.IconPath = iconPath;
            storageService.SaveIntoStorage(iconPath, icon);

            database.Groups.InsertOnSubmit(group);
            database.SubmitChanges();
            return group.GroupID;
        }

        public void GroupRemove(int groupID)
        {
            database.Groups.DeleteOnSubmit((from g in database.Groups where g.GroupID.Equals(groupID) select g).Single());
            database.SubmitChanges();
        }

        public int GroupGetID(string name)
        {
            return (from g in database.Groups where g.Name.Equals(name) select g.GroupID).Single();
        }

        public string GroupGetName(int groupID)
        {
            return (from g in database.Groups where g.GroupID.Equals(groupID) select g.Name).Single();
        }

        public string GroupGetDescription(int groupID)
        {
            return (from g in database.Groups where g.GroupID.Equals(groupID) select g.Description).Single();
        }

        public byte[] GroupGetIcon(int groupID)
        {
            return storageService.LoadFromStorage((from g in database.Groups where g.GroupID.Equals(groupID) select g.IconPath).Single());
        }

        public int GroupGetPrivacy(int groupID)
        {
            return (from g in database.Groups where g.GroupID.Equals(groupID) select g.Privacy).Single();
        }

        public DateTime GroupGetRegistrationDate(int groupID)
        {
            return (from g in database.Groups where g.GroupID.Equals(groupID) select g.RegistrationDate).Single();
        }

        public int[] GroupGetMembers(int groupID)
        {
            return (from gm in database.GroupMembers where gm.GroupID.Equals(groupID) select gm.UserID).ToArray();
        }

        public int[] GroupGetCameras(int groupID)
        {
            return (from gc in database.GroupCameras where gc.GroupID.Equals(groupID) select gc.CameraID).ToArray();
        }

        public void GroupSetName(int groupID, string name)
        {
            (from g in database.Groups where g.GroupID.Equals(groupID) select g).Single().Name = name;
            database.SubmitChanges();
        }

        public void GroupSetDescription(int groupID, string description)
        {
            (from g in database.Groups where g.GroupID.Equals(groupID) select g).Single().Description = description;
            database.SubmitChanges();
        }

        public void GroupSetIcon(int groupID, byte[] icon)
        {
            storageService.SaveIntoStorage(@"GroupIcons\" + groupID, icon);
        }

        public void GroupSetPrivacy(int groupID, int privacy)
        {
            (from g in database.Groups where g.GroupID.Equals(groupID) select g).Single().Privacy = privacy;
            database.SubmitChanges();
        }

        // group members
        public void GroupMemberAdd(int userID, int groupID, int privileges)
        {
            database.GroupMembers.InsertOnSubmit(new GroupMember { UserID = userID, GroupID = groupID, Privileges = privileges });
            database.SubmitChanges();
        }

        public void GroupMemberRemove(int userID, int groupID)
        {
            database.GroupMembers.DeleteOnSubmit((from gm in database.GroupMembers where gm.UserID.Equals(userID) && gm.GroupID.Equals(groupID) select gm).Single());
            database.SubmitChanges();
        }

        public int GroupMemberGetPrivileges(int userID, int groupID)
        {
            return (from gm in database.GroupMembers where gm.UserID.Equals(userID) && gm.GroupID.Equals(groupID) select gm.Privileges).Single();
        }

        public void GroupMemberSetPrivileges(int userID, int groupID, int privileges)
        {
            (from gm in database.GroupMembers where gm.UserID.Equals(userID) && gm.GroupID.Equals(groupID) select gm).Single().Privileges = privileges;
            database.SubmitChanges();
        }

        // group cameras
        public void GroupCameraAdd(int cameraID, int groupID)
        {
            database.GroupCameras.InsertOnSubmit(new GroupCamera { CameraID = cameraID, GroupID = groupID });
            database.SubmitChanges();
        }

        public void GroupCameraRemove(int cameraID, int groupID)
        {
            database.GroupCameras.DeleteOnSubmit((from gc in database.GroupCameras where gc.CameraID.Equals(cameraID) && gc.GroupID.Equals(groupID) select gc).Single());
            database.SubmitChanges();
        }
    }
}