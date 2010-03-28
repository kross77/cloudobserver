using System;
using System.IO;
using System.Collections;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Web;

namespace HttpServerPrototype.HttpServer
{
    public enum ParserState
    {
        METHOD, URL, URLPARM, URLVALUE, VERSION,
        HEADERKEY, HEADERVALUE, BODY, OK
    }

    public enum ResponseState
    {
        OK = 200,
        BAD_REQUEST = 400,
        NOT_FOUND = 404
    }

    public struct HttpRequest
    {
        public string Method;
        public string Url;
        public string Version;
        public Hashtable Arguments;
        public bool Execute;
        public Hashtable Headers;
        public int BodySize;
        public byte[] BodyData;
    }

    public struct HttpResponse
    {
        public int Status;
        public string Version;
        public Hashtable Headers;
        public int BodySize;
        public byte[] BodyData;
    }

    public class TestHttpRequest
    {
        private TcpClient client;
        private TestHttpServer parent;

        private ParserState parserState;
        private HttpRequest httpRequest;
        private HttpResponse httpResponse;

        private byte[] readBuffer;

        public TestHttpRequest(TcpClient client, TestHttpServer parent)
        {
            this.client = client;
            this.parent = parent;
        }

        public void Process()
        {
            readBuffer = new byte[client.ReceiveBufferSize];
            NetworkStream networkStream = client.GetStream();

            int read = 0;
            string hValue = "";
            string hKey = "";

            try
            {
                int bfndx = 0;

                do
                {
                    read = networkStream.Read(readBuffer, 0, readBuffer.Length);

                    int index = 0;
                    do
                    {
                        switch (parserState)
                        {
                            case ParserState.METHOD:
                                if (readBuffer[index] != ' ')
                                    httpRequest.Method += (char)readBuffer[index++];
                                else
                                {
                                    index++;
                                    parserState = ParserState.URL;
                                }
                                break;
                            case ParserState.URL:
                                if (readBuffer[index] == '?')
                                {
                                    index++;
                                    hKey = "";
                                    httpRequest.Execute = true;
                                    httpRequest.Arguments = new Hashtable();
                                    parserState = ParserState.URLPARM;
                                }
                                else if (readBuffer[index] != ' ')
                                    httpRequest.Url += (char)readBuffer[index++];
                                else
                                {
                                    index++;
                                    httpRequest.Url = HttpUtility.UrlDecode(httpRequest.Url);
                                    parserState = ParserState.VERSION;
                                }
                                break;
                            case ParserState.URLPARM:
                                if (readBuffer[index] == '=')
                                {
                                    index++;
                                    hValue = "";
                                    parserState = ParserState.URLVALUE;
                                }
                                else if (readBuffer[index] == ' ')
                                {
                                    index++;

                                    httpRequest.Url = HttpUtility.UrlDecode(httpRequest.Url);
                                    parserState = ParserState.VERSION;
                                }
                                else
                                {
                                    hKey += (char)readBuffer[index++];
                                }
                                break;
                            case ParserState.URLVALUE:
                                if (readBuffer[index] == '&')
                                {
                                    index++;
                                    hKey = HttpUtility.UrlDecode(hKey);
                                    hValue = HttpUtility.UrlDecode(hValue);
                                    httpRequest.Arguments[hKey] = httpRequest.Arguments[hKey] != null ? httpRequest.Arguments[hKey] + ", " + hValue : hValue;
                                    hKey = "";
                                    parserState = ParserState.URLPARM;
                                }
                                else if (readBuffer[index] == ' ')
                                {
                                    index++;
                                    hKey = HttpUtility.UrlDecode(hKey);
                                    hValue = HttpUtility.UrlDecode(hValue);
                                    httpRequest.Arguments[hKey] = httpRequest.Arguments[hKey] != null ? httpRequest.Arguments[hKey] + ", " + hValue : hValue;

                                    httpRequest.Url = HttpUtility.UrlDecode(httpRequest.Url);
                                    parserState = ParserState.VERSION;
                                }
                                else
                                {
                                    hValue += (char)readBuffer[index++];
                                }
                                break;
                            case ParserState.VERSION:
                                if (readBuffer[index] == '\r')
                                    index++;
                                else if (readBuffer[index] != '\n')
                                    httpRequest.Version += (char)readBuffer[index++];
                                else
                                {
                                    index++;
                                    hKey = "";
                                    httpRequest.Headers = new Hashtable();
                                    parserState = ParserState.HEADERKEY;
                                }
                                break;
                            case ParserState.HEADERKEY:
                                if (readBuffer[index] == '\r')
                                    index++;
                                else if (readBuffer[index] == '\n')
                                {
                                    index++;
                                    if (httpRequest.Headers["Content-Length"] != null)
                                    {
                                        httpRequest.BodySize = Convert.ToInt32(httpRequest.Headers["Content-Length"]);
                                        this.httpRequest.BodyData = new byte[httpRequest.BodySize];
                                        parserState = ParserState.BODY;
                                    }
                                    else
                                        parserState = ParserState.OK;

                                }
                                else if (readBuffer[index] == ':')
                                    index++;
                                else if (readBuffer[index] != ' ')
                                    hKey += (char)readBuffer[index++];
                                else
                                {
                                    index++;
                                    hValue = "";
                                    parserState = ParserState.HEADERVALUE;
                                }
                                break;
                            case ParserState.HEADERVALUE:
                                if (readBuffer[index] == '\r')
                                    index++;
                                else if (readBuffer[index] != '\n')
                                    hValue += (char)readBuffer[index++];
                                else
                                {
                                    index++;
                                    httpRequest.Headers.Add(hKey, hValue);
                                    hKey = "";
                                    parserState = ParserState.HEADERKEY;
                                }
                                break;
                            case ParserState.BODY:
                                Array.Copy(readBuffer, index, httpRequest.BodyData, bfndx, read - index);
                                bfndx += read - index;
                                index = read;
                                if (httpRequest.BodySize <= bfndx)
                                {
                                    parserState = ParserState.OK;
                                }
                                break;
                        }
                    }
                    while (index < read);
                }
                while (networkStream.DataAvailable);

                httpResponse.Version = "HTTP/1.1";

                if (parserState != ParserState.OK)
                    httpResponse.Status = (int)ResponseState.BAD_REQUEST;
                else
                    httpResponse.Status = (int)ResponseState.OK;

                httpResponse.Headers = new Hashtable();
                if (!String.IsNullOrEmpty(parent.Name))
                    httpResponse.Headers.Add("Server", parent.Name);
                httpResponse.Headers.Add("Date", DateTime.Now.ToString("r"));
                httpResponse.Headers.Add("Content-Type", "audio/mpeg");

                string headersString = httpResponse.Version + " " + parent.ResponseStatuses[httpResponse.Status] + "\n";
                foreach (DictionaryEntry header in httpResponse.Headers)
                    headersString += header.Key + ": " + header.Value + "\n";
                headersString += "\n";

                byte[] headersStringData = Encoding.ASCII.GetBytes(headersString);
                networkStream.Write(headersStringData, 0, headersStringData.Length);

                // Send infinite random body (emulate 44kHz pcm audio)
                int chunkSize = 44100 * 2 * 2;
                byte[] randomChunk = new byte[chunkSize];
                Random random = new Random();

                while (true)
                {
                    random.NextBytes(randomChunk);
                    networkStream.Write(randomChunk, 0, chunkSize);
                    Thread.Sleep(1000);
                }
            }
            catch (Exception)
            {
            }
            finally
            {
                networkStream.Close();
                client.Close();
                Thread.CurrentThread.Abort();
            }
        }
    }
}
