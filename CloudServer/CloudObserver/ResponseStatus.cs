using System.Collections;

namespace CloudObserver
{
    public class ResponseStatus
    {
        private static ResponseStatus instance = null;

        private Hashtable responseStatus;

        private ResponseStatus()
        {
            responseStatus = new Hashtable();

            responseStatus.Add(200, "200 Ok");
            responseStatus.Add(201, "201 Created");
            responseStatus.Add(202, "202 Accepted");
            responseStatus.Add(204, "204 No Content");

            responseStatus.Add(301, "301 Moved Permanently");
            responseStatus.Add(302, "302 Redirection");
            responseStatus.Add(304, "304 Not Modified");

            responseStatus.Add(400, "400 Bad Request");
            responseStatus.Add(401, "401 Unauthorized");
            responseStatus.Add(403, "403 Forbidden");
            responseStatus.Add(404, "404 Not Found");

            responseStatus.Add(500, "500 Internal Server Error");
            responseStatus.Add(501, "501 Not Implemented");
            responseStatus.Add(502, "502 Bad Gateway");
            responseStatus.Add(503, "503 Service Unavailable");
        }

        public string this[int key]
        {
            get
            {
                return (string)responseStatus[key];
            }
        }

        public static ResponseStatus GetInstance()
        {
            if (instance == null)
                instance = new ResponseStatus();

            return instance;
        }
    }
}
