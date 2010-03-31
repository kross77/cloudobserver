using System.ServiceModel;
using System.Text;

namespace CloudObserver.Services
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class WorkBlock : Service, IWorkBlock
    {
        private const int port = 52503;

        public WorkBlock()
        {
            WorkBlockHttpServer server = new WorkBlockHttpServer(port);
            server.Start();
        }

        public string GetTcpStreamUriToRead(int[] contentIds)
        {
            StringBuilder stringBuilder = new StringBuilder(cloudControllerUri);
            stringBuilder.Replace("4773", port.ToString());
            stringBuilder.Replace("cc-0", "wb-0?action=read&ids=");
            for (int i = 0; i < contentIds.Length; i++)
            {
                stringBuilder.Append(contentIds[i]);
                if (i < contentIds.Length - 1)
                    stringBuilder.Append(',');
            }
            return stringBuilder.ToString();
        }

        public string GetTcpStreamUriToWrite(int contentId)
        {
            StringBuilder stringBuilder = new StringBuilder(cloudControllerUri);
            stringBuilder.Replace("4773", port.ToString());
            stringBuilder.Replace("cc-0", "wb-0?action=write&ids=");
            stringBuilder.Append(contentId);
            return stringBuilder.ToString();
        }
    }
}
