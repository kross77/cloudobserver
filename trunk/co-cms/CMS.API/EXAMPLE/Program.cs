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

            Console.WindowWidth = 120;
            Console.WindowHeight = 50;

            Console.WriteLine("\n Create Methods");
            // Ready to go
            Console.WriteLine("create user with NO pass and NO email but with Stream! Key Returned for further operations: " + ap.createUserWithStream(random.Next(1, 100000), "userWithNoPass"));
            Console.WriteLine("create user with pass and email and with Stream! Key Returned for further operations: " + ap.createUserWithStream(random.Next(1, 100000), "userRegistred" , "suk" + random.Next(1, 100000).ToString() + "@suchok.su", "pass"));
            Console.WriteLine("create user with pass and email. Key Returned for further operations: " + ap.createUser("userRegistred", "suk" + random.Next(1, 100000).ToString() + "@suchok.su", "pass"));
            Console.WriteLine("create password for a user with NO password and NO email " + ap.createPassword(ap.createUserWithStream(random.Next(1, 100000), "userWithNoPass2"), "myRealEmail@real.su", "myPass"));
            // Not ready to go =(  
            Console.WriteLine("\n Log Methods");
            Console.WriteLine("log In" + ap.logIn("myRealEmail@real.life", "myPass"));
            Console.WriteLine("log Out" + ap.logOut("myRealEmail@real.life", ap.logIn("myRealEmail@real.life", "myPass")));
        
            Console.WriteLine("\n Get Methods");
            Console.WriteLine("get Kernel Gateway Address (Yes! you should get Kernel address by calling CMS)" + ap.getGatewayAddress(ap.logIn("myRealEmail@real.life", "myPass")));
            Console.WriteLine("get user name by KEY" + ap.getMyName(ap.logIn("myRealEmail@real.life", "myPass")));
            Console.WriteLine("get users streams (KEY, AMMOUNT, ORDER (none = default, DO NOT CHANGE until CMS v3.5))" + ap.getMyStreams(ap.logIn("myRealEmail@real.life", "myPass"), 30, "none"));
            Console.WriteLine("get NOT user streams  (KEY, AMMOUNT, ORDER (none = default, DO NOT CHANGE until CMS v3.4))" + ap.getStreamsFromAll(ap.logIn("myRealEmail@real.life", "myPass"), 35, "none"));
      
            Console.WriteLine("\n Set Methods");   
            Console.WriteLine("set a new user name" + ap.setMyName(ap.logIn("myRealEmail@real.life", "myPass"), "myName"));
            Console.WriteLine("set new password to user" + ap.setMyNewPassword(ap.logIn("myRealEmail@real.life", "myPass"), "myRealEmail@real.life", "myPass", "iHaveNewPass"));
            Console.WriteLine("add a stream to users streams collection" + ap.setStream(ap.logIn("myRealEmail@real.life", "iHaveNewPass"), 4663));
          
            Console.WriteLine("\n Delete Methods");   
            Console.WriteLine("delete stream from users streams collection" + ap.deleteStream(ap.logIn("myRealEmail@real.life", "iHaveNewPass"), 4663));
            Console.WriteLine("delete a user" + ap.deleteUser(ap.logIn("myRealEmail@real.life", "iHaveNewPass"), "myName", "myRealEmail@real.life", "iHaveNewPass"));
            
            Console.Read();
        }
    }
}