using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using CMS;

namespace EXAMPLE
{
    class Program
    {
        static void Main(string[] args)
        {
            API ap = new API();
            
            Random random = new Random();
            int ran = random.Next(1, 100000);
            String str = ran.ToString();

            Console.WindowWidth = 120;
            Console.WindowHeight = 50;
            // Ready to go

            ap.setResponseEncoding(API.DataFormat.PRINTR); // I tested on API.DataFormat.XML and API.DataFormat.JSON if not specified is set to API default (XML) 
            
            Console.WriteLine("\n Create Methods");
           
            Console.WriteLine("create user with NO pass and NO email but with Stream! Key Returned for further operations: " + ap.createUserWithStream(random.Next(1, 100000), "userWithNoPass"));
            Console.WriteLine("create user with pass and email and with Stream! Key Returned for further operations: " + ap.createUserWithStream(random.Next(1, 100000), "userRegistred" , "suk" + random.Next(1, 100000).ToString() + "@suchok.su", "pass"));
            Console.WriteLine("create user with pass and email. Key Returned for further operations: " + ap.createUser("userRegistred", "suk" + random.Next(1, 100000).ToString() + "@suchok.su", "pass"));
            Console.WriteLine("create password for a user with NO password and NO email " + ap.createPassword(ap.createUserWithStream(random.Next(1, 100000), "userWithNoPass" + str), "myRealEmail" + str + "@real.su", "myPass"));
         
            Console.WriteLine("\n Log Methods");
            Console.WriteLine("log In " + ap.logIn("myRealEmail" + str + "@real.su", "myPass"));
            Console.WriteLine("log Out " + ap.logOut(ap.logIn("myRealEmail" + str + "@real.su", "myPass")));

            Console.WriteLine("\n Set Methods");
            Console.WriteLine("set a new user name: " + ap.setMyName(ap.logIn("myRealEmail" + str + "@real.su", "myPass"), "myName"));
            Console.WriteLine("add a stream to users streams collection: " + ap.setStream(ap.logIn("myRealEmail" + str + "@real.su", "myPass"), ran));

            Console.WriteLine("\n Get Methods");
            Console.WriteLine("get Kernel Gateway Address (Yes! you should get Kernel address by calling CMS) " + ap.getGatewayAddress(ap.logIn("myRealEmail" + str + "@real.su", "myPass")));
            Console.WriteLine("get user name by KEY " + ap.getMyName(ap.logIn("myRealEmail" + str + "@real.su", "myPass")));
            Console.WriteLine("get users streams (KEY, AMMOUNT, ORDER (none = default, DO NOT CHANGE until CMS v3.5)) \n " + ap.getMyStreams(ap.logIn("myRealEmail" + str + "@real.su", "myPass"), 30, "none"));
            Console.WriteLine("get NOT user streams  (KEY, AMMOUNT, ORDER (none = default, DO NOT CHANGE until CMS v3.4)) \n " + ap.getStreamsFromAll(ap.logIn("myRealEmail" + str + "@real.su", "myPass"), 35, "none"));
      
            Console.WriteLine("\n Delete Methods");
            Console.WriteLine("delete stream from users streams collection " + ap.deleteStream(ap.logIn("myRealEmail" + str + "@real.su", "myPass"), ran));
            Console.WriteLine("delete a user " + ap.deleteUser(ap.logIn("myRealEmail" + str + "@real.su", "myPass"), "myName", "myRealEmail" + str + "@real.su", "myPass"));
            
            Console.Read();
        }
    }
}