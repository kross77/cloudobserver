using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Data.Linq;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;

namespace CloudObserverDatabaseLibrary
{
    public class CloudObserverDatabase : ICloudObserverDatabase
    {
        private readonly CloudObserverDBDataContext database;

        // constructors
        public CloudObserverDatabase()
        {
             database = new CloudObserverDBDataContext(global::CloudObserverDatabaseLibrary.Properties.Settings.Default.CloudObserverDatabaseConnectionString);
            if (!database.DatabaseExists())
                database.CreateDatabase();
        }

        public CloudObserverDatabase(string connection)
        {
            database = new CloudObserverDBDataContext(connection);
        }

        // database management functions
        public void ClearDatabase()
        {
            database.Users.DeleteAllOnSubmit(from u in database.Users select u);
            database.Groups.DeleteAllOnSubmit(from g in database.Groups select g);
            database.GroupMembers.DeleteAllOnSubmit(from gm in database.GroupMembers select gm);
            database.GroupCameras.DeleteAllOnSubmit(from gc in database.GroupCameras select gc);
            database.Cameras.DeleteAllOnSubmit(from c in database.Cameras select c);
            database.Frames.DeleteAllOnSubmit(from f in database.Frames select f);
            database.SubmitChanges();
        }

        // user manipulation functions
        public bool IsEmailRegistered(string email)
        {
            return ((from u in database.Users where u.Email.Equals(email) select u).Count() > 0);
        }

        public bool IsUserRegistered(string email, string password)
        {
            return ((from u in database.Users where u.Email.Equals(email) && u.Password.Equals(password) select u).Count() > 0);
        }

        public int RegisterUser(string email, string password, string name)
        {
            database.Users.InsertOnSubmit(new User
            {
                Email = email,
                Password = password,
                Name = name,
                Description = "DefaultUserDescription",
                IconPath = "DefaultUserIconPath",
                RegistrationDate = DateTime.Now
            });
            database.SubmitChanges();
            return (from u in database.Users where u.Email.Equals(email) select u.UserID).Single();
        }

        public void RemoveUser(int userID)
        {
            database.Users.DeleteOnSubmit((from u in database.Users where u.UserID.Equals(userID) select u).Single());
            database.SubmitChanges();
        }

        public int GetUserID(string email)
        {
            return (from u in database.Users where u.Email.Equals(email) select u.UserID).Single();
        }

        public string GetUserEmail(int userID)
        {
            return (from u in database.Users where u.UserID.Equals(userID) select u.Email).Single();
        }

        public string GetUserPassword(int userID)
        {
            return (from u in database.Users where u.UserID.Equals(userID) select u.Password).Single();
        }

        public string GetUserName(int userID)
        {
            return (from u in database.Users where u.UserID.Equals(userID) select u.Name).Single();
        }

        public string GetUserDescription(int userID)
        {
            return (from u in database.Users where u.UserID.Equals(userID) select u.Description).Single();
        }

        public byte[] GetUserIcon(int userID)
        {
            return null; // read from local storage
        }

        public DateTime GetUserRegistrationDate(int userID)
        {
            return (from u in database.Users where u.UserID.Equals(userID) select u.RegistrationDate).Single();
        }

        public int[] GetUserGroups(int userID)
        {
            return (from gm in database.GroupMembers where gm.UserID.Equals(userID) select gm.GroupID).ToArray();
        }

        public void SetUserPassword(int userID, string password)
        {
            (from u in database.Users where u.UserID.Equals(userID) select u).Single().Password = password;
            database.SubmitChanges();
        }

        public void SetUserName(int userID, string name)
        {
            (from u in database.Users where u.UserID.Equals(userID) select u).Single().Name = name;
            database.SubmitChanges();
        }

        public void SetUserDescription(int userID, string description)
        {
            (from u in database.Users where u.UserID.Equals(userID) select u).Single().Description = description;
            database.SubmitChanges();
        }

        public void SetUserIcon(int userID, byte[] icon)
        {
            // save or replace icon in local storage
        }

        // group manipulation functions
        public bool IsGroupRegistered(string name)
        {
            return ((from g in database.Groups where g.Name.Equals(name) select g).Count() > 0);
        }

        public int RegisterGroup(string name, int privacy)
        {
            database.Groups.InsertOnSubmit(new Group
            {
                Name = name,
                Description = "DefaultGroupDescription",
                IconPath = "DefaultGroupIconPath",
                Privacy = privacy,
                RegistrationDate = DateTime.Now
            });
            database.SubmitChanges();
            return (from g in database.Groups where g.Name.Equals(name) select g.GroupID).Single();
        }

        public void RemoveGroup(int groupID)
        {
            database.Groups.DeleteOnSubmit((from g in database.Groups where g.GroupID.Equals(groupID) select g).Single());
            database.SubmitChanges();
        }

        public int GetGroupID(string name)
        {
            return (from g in database.Groups where g.Name.Equals(name) select g.GroupID).Single();
        }

        public string GetGroupName(int groupID)
        {
            return (from g in database.Groups where g.GroupID.Equals(groupID) select g.Name).Single();
        }

        public string GetGroupDescription(int groupID)
        {
            return (from g in database.Groups where g.GroupID.Equals(groupID) select g.Description).Single();
        }

        public byte[] GetGroupIcon(int groupID)
        {
            return null; // read from local storage
        }

        public int GetGroupPrivacy(int groupID)
        {
            return (from g in database.Groups where g.GroupID.Equals(groupID) select g.Privacy).Single();
        }

        public DateTime GetGroupRegistrationDate(int groupID)
        {
            return (from g in database.Groups where g.GroupID.Equals(groupID) select g.RegistrationDate).Single();
        }

        public int[] GetGroupMembers(int groupID)
        {
            return (from gm in database.GroupMembers where gm.GroupID.Equals(groupID) select gm.UserID).ToArray();
        }

        public int[] GetGroupCameras(int groupID)
        {
            return (from gc in database.GroupCameras where gc.GroupID.Equals(groupID) select gc.CameraID).ToArray();
        }

        public void SetGroupName(int groupID, string name)
        {
            (from g in database.Groups where g.GroupID.Equals(groupID) select g).Single().Name = name;
            database.SubmitChanges();
        }

        public void SetGroupDescription(int groupID, string description)
        {
            (from g in database.Groups where g.GroupID.Equals(groupID) select g).Single().Description = description;
            database.SubmitChanges();
        }

        public void SetGroupIcon(int groupID, byte[] icon)
        {
            // save or replace icon in local storage
        }

        public void SetGroupPrivacy(int groupID, int privacy)
        {
            (from g in database.Groups where g.GroupID.Equals(groupID) select g).Single().Privacy = privacy;
            database.SubmitChanges();
        }

        public void AddGroupMember(int userID, int groupID, int privileges)
        {
            database.GroupMembers.InsertOnSubmit(new GroupMember { UserID = userID, GroupID = groupID, Privileges = privileges });
            database.SubmitChanges();
        }

        public void SetGroupMemberPrivileges(int userID, int groupID, int privileges)
        {
            (from gm in database.GroupMembers where gm.UserID.Equals(userID) && gm.GroupID.Equals(groupID) select gm).Single().Privileges = privileges;
            database.SubmitChanges();
        }

        public void RemoveGroupMember(int userID, int groupID)
        {
            database.GroupMembers.DeleteOnSubmit((from gm in database.GroupMembers where gm.UserID.Equals(userID) && gm.GroupID.Equals(groupID) select gm).Single());
            database.SubmitChanges();
        }

        public void AddGroupCamera(int cameraID, int groupID)
        {
            database.GroupCameras.InsertOnSubmit(new GroupCamera { CameraID = cameraID, GroupID = groupID });
            database.SubmitChanges();
        }

        public void RemoveGroupCamera(int cameraID, int groupID)
        {
            database.GroupCameras.DeleteOnSubmit((from gc in database.GroupCameras where gc.CameraID.Equals(cameraID) && gc.GroupID.Equals(groupID) select gc).Single());
            database.SubmitChanges();
        }

        // camera manipulations functions
        public bool IsCameraRegistered(string path)
        {
            return ((from c in database.Cameras where c.Path.Equals(path) select c).Count() > 0);
        }

        public int RegisterCamera(string name)
        {
            database.Cameras.InsertOnSubmit(new Camera
            {
                Path = "TempPath",
                Name = name,
                Description = "DefaultCameraDescription",
                IconPath = "DefaultCameraIconPath",
                RegistrationDate = DateTime.Now
            });
            database.SubmitChanges();
            Camera camera = (from c in database.Cameras where c.Path.Equals("TempPath") select c).Single();
            string path = camera.Name + camera.CameraID;
            camera.Path = path;
            database.SubmitChanges();
            return (from c in database.Cameras where c.Path.Equals(path) select c.CameraID).Single();
        }

        public void RemoveCamera(int cameraID)
        {
            database.Cameras.DeleteOnSubmit((from c in database.Cameras where c.CameraID.Equals(cameraID) select c).Single());
            database.SubmitChanges();
        }

        public int GetCameraID(string path)
        {
            return (from c in database.Cameras where c.Path.Equals(path) select c.CameraID).Single();
        }

        public string GetCameraPath(int cameraID)
        {
            return (from c in database.Cameras where c.CameraID.Equals(cameraID) select c.Path).Single();
        }

        public string GetCameraName(int cameraID)
        {
            return (from c in database.Cameras where c.CameraID.Equals(cameraID) select c.Name).Single();
        }

        public string GetCameraDescription(int cameraID)
        {
            return (from c in database.Cameras where c.CameraID.Equals(cameraID) select c.Description).Single();
        }

        public byte[] GetCameraIcon(int cameraID)
        {
            return null; // read from local storage
        }

        public DateTime GetCameraRegistrationDate(int cameraID)
        {
            return (from c in database.Cameras where c.CameraID.Equals(cameraID) select c.RegistrationDate).Single();
        }

        public int[] GetCameraGroups(int cameraID)
        {
            return (from gc in database.GroupCameras where gc.CameraID.Equals(cameraID) select gc.GroupID).ToArray();
        }

        public int[] GetCameraFrames(int cameraID)
        {
            return (from f in database.Frames where f.CameraID.Equals(cameraID) select f.FrameID).ToArray();
        }

        public void SetCameraName(int cameraID, string name)
        {
            (from c in database.Cameras where c.CameraID.Equals(cameraID) select c).Single().Name = name;
            database.SubmitChanges();
        }

        public void SetCameraDescription(int cameraID, string description)
        {
            (from c in database.Cameras where c.CameraID.Equals(cameraID) select c).Single().Description = description;
            database.SubmitChanges();
        }

        public void SetCameraIcon(int cameraID, byte[] icon)
        {
            // save or replace icon in local storage
        }

        // frame manipulations functions
        public void AddFrame(int cameraID, byte[] content, string marker)
        {
            database.Frames.InsertOnSubmit(new Frame
            {
                CameraID = cameraID,
                ContentPath = "", // save frame in local storage
                Marker = marker
            });
            database.SubmitChanges();
        }

        public void RemoveFrame(int frameID)
        {
            database.Frames.DeleteOnSubmit((from f in database.Frames where f.FrameID.Equals(frameID) select f).Single());
            database.SubmitChanges();
        }

        public byte[] GetFrameContent(int frameID)
        {
            return null; // read from local storage
        }

        public string GetFrameMarker(int frameID)
        {
            return (from f in database.Frames where f.FrameID.Equals(frameID) select f.Marker).Single();
        }
    }
}
