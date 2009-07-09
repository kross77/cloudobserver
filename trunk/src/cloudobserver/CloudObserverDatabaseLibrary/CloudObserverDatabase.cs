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
using System.Xml.Linq;

namespace CloudObserverDatabaseLibrary
{
    public class CloudObserverDatabase : ICloudObserverDatabase
    {
        private readonly CloudObserverDBDataContext database;

        public readonly XElement DefaultUserDescription = XElement.Parse(global::CloudObserverDatabaseLibrary.Properties.Resources.DefaultUserDescription);
        public readonly XElement DefaultGroupDescription = XElement.Parse(global::CloudObserverDatabaseLibrary.Properties.Resources.DefaultGroupDescription);
        public readonly XElement DefaultCameraDescription = XElement.Parse(global::CloudObserverDatabaseLibrary.Properties.Resources.DefaultCameraDescription);

        public readonly Bitmap DefaultUserIcon = global::CloudObserverDatabaseLibrary.Properties.Resources.DefaultUserIcon;
        public readonly Bitmap DefaultGroupIcon = global::CloudObserverDatabaseLibrary.Properties.Resources.DefaultGroupIcon;
        public readonly Bitmap DefaultCameraIcon = global::CloudObserverDatabaseLibrary.Properties.Resources.DefaultCameraIcon;

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
                RegistrationDate = DateTime.Now,
                Description = DefaultUserDescription,
                Icon = BitmapToBinary(DefaultUserIcon)
            });
            database.SubmitChanges();
            return (from u in database.Users where u.Email.Equals(email) select u.UserID).Single();
        }

        public int RegisterUser(string email, string password, string name, XElement description, Bitmap icon)
        {
            database.Users.InsertOnSubmit(new User
            {
                Email = email,
                Password = password,
                Name = name,
                RegistrationDate = DateTime.Now,
                Description = description,
                Icon = BitmapToBinary(icon)
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

        public XElement GetUserDescription(int userID)
        {
            return (from u in database.Users where u.UserID.Equals(userID) select u.Description).Single();
        }

        public Bitmap GetUserIcon(int userID)
        {
            return BinaryToBitmap((from u in database.Users where u.UserID.Equals(userID) select u.Icon).Single());
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

        public void SetUserDescription(int userID, XElement description)
        {
            (from u in database.Users where u.UserID.Equals(userID) select u).Single().Description = description;
            database.SubmitChanges();
        }

        public void SetUserIcon(int userID, Bitmap icon)
        {
            (from u in database.Users where u.UserID.Equals(userID) select u).Single().Icon = BitmapToBinary(icon);
            database.SubmitChanges();
        }

        // group manipulation functions
        public bool IsGroupRegistered(string name)
        {
            return ((from g in database.Groups where g.Name.Equals(name) select g).Count() > 0);
        }

        public int RegisterGroup(string name, bool privacy)
        {
            database.Groups.InsertOnSubmit(new Group
            {
                Name = name,
                Description = DefaultGroupDescription,
                Icon = BitmapToBinary(DefaultGroupIcon),
                Privacy = privacy,
                RegistrationDate = DateTime.Now
            });
            database.SubmitChanges();
            return (from g in database.Groups where g.Name.Equals(name) select g.GroupID).Single();
        }

        public int RegisterGroup(string name, XElement description, Bitmap icon, bool privacy)
        {
            database.Groups.InsertOnSubmit(new Group
            {
                Name = name,
                Description = description,
                Icon = BitmapToBinary(icon),
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

        public XElement GetGroupDescription(int groupID)
        {
            return (from g in database.Groups where g.GroupID.Equals(groupID) select g.Description).Single();
        }

        public Bitmap GetGroupIcon(int groupID)
        {
            return BinaryToBitmap((from g in database.Groups where g.GroupID.Equals(groupID) select g.Icon).Single());
        }

        public bool GetGroupPrivacy(int groupID)
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

        public void SetGroupDescription(int groupID, XElement description)
        {
            (from g in database.Groups where g.GroupID.Equals(groupID) select g).Single().Description = description;
            database.SubmitChanges();
        }

        public void SetGroupIcon(int groupID, Bitmap icon)
        {
            (from g in database.Groups where g.GroupID.Equals(groupID) select g).Single().Icon = BitmapToBinary(icon);
            database.SubmitChanges();
        }

        public void SetGroupPrivacy(int groupID, bool privacy)
        {
            (from g in database.Groups where g.GroupID.Equals(groupID) select g).Single().Privacy = privacy;
            database.SubmitChanges();
        }

        public void AddGroupMember(int userID, int groupID, int privileges)
        {
            database.GroupMembers.InsertOnSubmit(new GroupMember { UserID = userID, GroupID = groupID, Privileges = privileges });
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

        public int RegisterCamera(string path, string name)
        {
            database.Cameras.InsertOnSubmit(new Camera
            {
                Path = path,
                Name = name,
                Description = DefaultCameraDescription,
                Icon = BitmapToBinary(DefaultCameraIcon),
                RegistrationDate = DateTime.Now
            });
            database.SubmitChanges();
            return (from c in database.Cameras where c.Path.Equals(path) select c.CameraID).Single();
        }

        public int RegisterCamera(string path, string name, XElement description, Bitmap icon)
        {
            database.Cameras.InsertOnSubmit(new Camera
            {
                Path = path,
                Name = name,
                Description = description,
                Icon = BitmapToBinary(icon),
                RegistrationDate = DateTime.Now
            });
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

        public XElement GetCameraDescription(int cameraID)
        {
            return (from c in database.Cameras where c.CameraID.Equals(cameraID) select c.Description).Single();
        }

        public Bitmap GetCameraIcon(int cameraID)
        {
            return BinaryToBitmap((from c in database.Cameras where c.CameraID.Equals(cameraID) select c.Icon).Single());
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

        public void SetCameraDescription(int cameraID, XElement description)
        {
            (from c in database.Cameras where c.CameraID.Equals(cameraID) select c).Single().Description = description;
            database.SubmitChanges();
        }

        public void SetCameraIcon(int cameraID, Bitmap icon)
        {
            (from c in database.Cameras where c.CameraID.Equals(cameraID) select c).Single().Icon = BitmapToBinary(icon);
            database.SubmitChanges();
        }

        // frame manipulations functions
        public int SaveFrame(int cameraID, Bitmap content, XElement marker)
        {
            database.Frames.InsertOnSubmit(new Frame
            {
                CameraID = cameraID,
                Content = BitmapToBinary(content),
                Marker = marker
            });
            database.SubmitChanges();
            return (from f in database.Frames where f.Content.Equals(content) select f.FrameID).Single();
        }

        public void RemoveFrame(int frameID)
        {
            database.Frames.DeleteOnSubmit((from f in database.Frames where f.FrameID.Equals(frameID) select f).Single());
            database.SubmitChanges();
        }

        public Bitmap GetFrameContent(int frameID)
        {
            return BinaryToBitmap((from f in database.Frames where f.FrameID.Equals(frameID) select f.Content).Single());
        }

        public XElement GetFrameMarker(int frameID)
        {
            return (from f in database.Frames where f.FrameID.Equals(frameID) select f.Marker).Single();
        }

        // auxiliary functions
        private static Binary BitmapToBinary(Bitmap bitmap)
        {
            var memoryStream = new MemoryStream();
            bitmap.Save(memoryStream, ImageFormat.Jpeg);
            byte[] bitmapData = memoryStream.ToArray();
            return new Binary(bitmapData);
        }

        private static Bitmap BinaryToBitmap(Binary binary)
        {
            var memoryStream = new MemoryStream();
            var bitmapData = binary.ToArray();
            memoryStream.Write(bitmapData, 0, bitmapData.Count());
            return new Bitmap(Image.FromStream(memoryStream));
        }
    }
}
