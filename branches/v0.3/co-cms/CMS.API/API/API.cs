using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;

///////////////////////////////////////.
// THIS IS  C# .NET WRAPPER FOR CO-CMS API BY OJ in 2010
// IDEA -  to provide C# programmers way to interact with CMS PHP API
// 14 methods for using CMS 3.* methods. Methods are divided into GET SET DELETE LOG and CREATE regions
////////////////////////////////////////

////////////////////////////////////////
// PHP API READS ESCAPED STRINGS FROM C# CORRECTLY? only god knows... so go test IT! (To Do)
////////////////////////////////////////

///////////////////////////////////////
// there are 2 methods that return objects in JSON , XML or PRINT_R  : getStreamsFromAll and getMyStreams
// Default return tupe is set in Constants.php CLOUD_OBSERVER_CMS_API_RETURN_FORMAT by default XML.
// To change Return Format for one C# class instance use Wrapper's function setResponseEncoding()
// To parse XML use your head
// To pars PRINT_R use for example such method (REG exps) (**)
// TO PARSE RETURNED JSON STRINGS USE(***)
//////////////////////////////////////

////////////////////////////////////
// (ToDo) Check this out If it does not  http://stackoverflow.com/questions/2760035/how-to-turn-string-into-readable-by-php-server-way if it steel will not tell OJ
//  (*) JSON is nice string; referense http://www.json.org/
//  (**) referense: http://stackoverflow.com/questions/2757239/how-to-turn-such-string-into-a-data-grid-c-net 
// (***) referense http://stackoverflow.com/questions/2859753/what-is-simpliest-c-function-to-parse-json-string-into-object
/////////////////////////////////

namespace CMS
{
    public class API
    {
  #region Fields
        /// <summary>
        /// An address at which API methods can be called.
        /// </summary>
        private string address;
      
        #endregion

        #region Properties
        /// <summary>
        /// Gets or sets an address at which API methods can be called.
        /// </summary>
        public string Address
        {
            get { return address; }
            set
            {
                address = value;
            }
        }
        #endregion

        #region Constructors
        /// <summary>
        /// Initializes a new instance of the CMS.API class with the localhost/cms/api.php address.
        /// </summary>
        public API() : this("http://localhost/cms/api.php?") { }

        /// <summary>
        /// Initializes a new instance of the CMS.API class with the provided address. NOTE! all returns are Strings
        /// </summary>
        /// <param name="address">An address at which API methods can be called.</param>
   
        public API(string address)
        {
            this.address = address;

        }
        #endregion

        #region ApiSetUp Methods
        public enum DataFormat { JSON = 0, XML = 1, PRINTR = 2 }
        public void setResponseEncoding(DataFormat format){
          if( DataFormat.JSON == format ) {  this.address = address + "returnFormat=JSON&" ; }
          if( DataFormat.XML == format ) {   this.address = address + "returnFormat=XML&" ;}
          if( DataFormat.PRINTR == format ) { this.address = address + "returnFormat=PRINT_R&" ;}
        }
        #endregion

        #region Public Methods

        #region Create Methods
        //.......................cuws
        /// <summary>
        /// Creates a User with Stream for temporary use; Use createPassword to 
        /// </summary>
        /// <param name="streamId">Represents CloudObserver streamId which should be obtained by calling CO.Kernel</param>
        /// <param name="userName">User name</param>
        /// <returns>Key for calling further methods of CMS; or error</returns>
    public string createUserWithStream(int streamId, string userName)
    {
        WebClient client = new WebClient();
        var result = client.DownloadString((address + string.Format("method=createUserWithStream&streamId={0}&userName={1}", streamId.ToString(), userName)).ToString());
        return result;
    }
    /// <summary>
    /// Creates a User with Stream
    /// </summary>
    /// <param name="streamId">Represents CloudObserver streamId which should be obtained by calling CO.Kernel</param>
    /// <param name="userName">User name</param>
    /// <param name="userEmail">User Email</param>
    /// <param name="userPass">User Password</param>
    /// <returns>Key for calling further methods of CMS; or error</returns>
    public string createUserWithStream(int streamId, string userName, string userEmail, string userPass)
    {
        WebClient client = new WebClient();
        var result = client.DownloadString((address + string.Format("method=createUserWithStream&streamId={0}&userName={1}&userEmail={2}&userPass={3}", streamId.ToString(), userName, userEmail, userPass)).ToString());
        return result;
    }
        //........................................................cu
        /// <summary>
        /// 
        /// </summary>
        /// <param name="userName"></param>
        /// <param name="userEmail"></param>
        /// <param name="userPass"></param>
        /// <returns></returns>
    public string createUser(string userName, string userEmail, string userPass)
    {
        WebClient client = new WebClient();
        var result = client.DownloadString((address + string.Format("method=createUser&userName={0}&userEmail={1}&userPass={2}", userName, userEmail, userPass)).ToString());
        return result;
    }
    //........................................................cp
    public string createPassword(string key, string userEmail, string newUserPass)
    {
        WebClient client = new WebClient();
        var result = client.DownloadString((address + string.Format("method=createPassword&key={0}&userEmail={1}&newUserPass={2}", key, userEmail, newUserPass)).ToString());
        return result;
    }
        #endregion
        #region Log Methods
    //.......................................................li
        /// <summary>
        /// 
        /// </summary>
        /// <param name="userEmail"></param>
        /// <param name="userPass"></param>
        /// <returns></returns>
    public string logIn(string userEmail, string userPass)
    {
        WebClient client = new WebClient();
        var result = client.DownloadString((address + string.Format("method=logIn&userEmail={0}&userPass={1}", userEmail, userPass)).ToString());
        return result;
    }
        //.......................................................lo
        /// <summary>
        /// 
        /// </summary>
        /// <param name="userEmail"></param>
        /// <param name="key"></param>
        /// <returns></returns>
    public string logOut(string key)
    {
        WebClient client = new WebClient();
        var result = client.DownloadString((address + string.Format("method=logOut&key={0}",  key)).ToString());
        return result;
    }
    #endregion
        #region Get Methods
    //.......................................................gmn
        /// <summary>
        /// 
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
    public string getMyName(string key)
    {
        WebClient client = new WebClient();
        var result = client.DownloadString((address + string.Format("method=getMyName&key={0}", key)).ToString());
        return result;
    }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
    public string getGatewayAddress(string key)
    {
        WebClient client = new WebClient();
        var result = client.DownloadString((address + string.Format("method=getGatewayAddress&key={0}", key)).ToString());
        return result;
    }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="key"></param>
        /// <param name="count"></param>
        /// <param name="order"></param>
        /// <returns></returns>
    public string getStreamsFromAll(string key, int count, string order)
    {
        WebClient client = new WebClient();
        var result = client.DownloadString((address + string.Format("method=getStreamsFromAll&key={0}&count={1}&order={2}", key, count, order)).ToString());
        return result;
    }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="key"></param>
        /// <param name="count"></param>
        /// <param name="order"></param>
        /// <returns></returns>
    public string getMyStreams(string key, int count, string order)
    {
        WebClient client = new WebClient();
        var result = client.DownloadString((address + string.Format("method=getMyStreams&key={0}&count={1}&order={2}", key, count, order)).ToString());
        return result;
    }
        #endregion
        #region Set Methods
        /// <summary>
        /// 
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
    public string setMyName(string key, string userName)
    {
        WebClient client = new WebClient();
        var result = client.DownloadString((address + string.Format("method=setMyName&key={0}&newUserName={1}", key, userName)).ToString());
        return result;
    }
  /* // method canceled - not part of 3.1 spec.
   * public string setMyNewPassword(string key, string userEmail, string curentUserPass, string newUserPass)
    {
        WebClient client = new WebClient();
        var result = client.DownloadString((address + string.Format("method=setMyNewPassword&key={0}&userEmail={1}&curentUserPass={2}&newUserPass={3}", key, userEmail, curentUserPass, newUserPass)).ToString());
        return result;
    } */

    public string setStream(string key, int streamId)
    {
        WebClient client = new WebClient();
        var result = client.DownloadString((address + string.Format("method=setStream&key={0}&streamId={1}", key, streamId)).ToString());
        return result;
    }
        #endregion       
        #region Delete Methods
        /// <summary>
        /// 
        /// </summary>
        /// <param name="key"></param>
        /// <param name="streamId"></param>
        /// <returns></returns>
    public string deleteStream(string key, int streamId)
    {
        WebClient client = new WebClient();
        var result = client.DownloadString((address + string.Format("method=deleteStream&key={0}&streamId={1}", key, streamId)).ToString());
        return result;
    }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="key"></param>
        /// <param name="userName"></param>
        /// <param name="userEmail"></param>
        /// <param name="userPass"></param>
        /// <returns></returns>
    public string deleteUser(string key, string userName, string userEmail, string userPass)
    {
        WebClient client = new WebClient();
        var result = client.DownloadString((address + string.Format("method=deleteUser&key={0}&userName={1}&userEmail={2}&userPass={3}", key, userName, userEmail, userPass)).ToString());
        return result;
    }
        #endregion
        //..........................................................
       
        #endregion
    }
}
