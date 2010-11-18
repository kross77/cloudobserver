using System;
using System.Collections;
using System.IO;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Web;

namespace CloudObserverLite
{
    public class CloudClient
    {
        private CloudServer server;
        private uint clientNumber;
        private TcpClient client;
        private HttpRequestStruct httpRequest;
        private HttpResponseStruct httpResponse;

        private LogWriter logWriter;

        public CloudClient(CloudServer server, uint clientNumber, TcpClient client)
        {
            this.server = server;
            this.clientNumber = clientNumber;
            this.client = client;

            this.logWriter = LogWriter.GetInstance();
        }

        public void Process()
        {
            this.logWriter.WriteLog("Client " + this.clientNumber.ToString() + " connected.");

            FileStream fileStream = File.Create("client-" + this.clientNumber.ToString() + ".dat");
            NetworkStream networkStream = this.client.GetStream();

            int totalBytesReceived = 0;
            byte[] buffer = new byte[this.client.ReceiveBufferSize];

            ParserState parserState = ParserState.METHOD;

            string key = "";
            string value = "";
            int bodyDataIndex = 0;

            try
            {
                do
                {
                    int bytesReceived = 0;
                    do
                    {
                        int bytesRead = networkStream.Read(buffer, 0, buffer.Length);
                        bytesReceived += bytesRead;

                        int index = 0;
                        do
                        {
                            switch (parserState)
                            {
                                case ParserState.METHOD:
                                    if (buffer[index] != ' ')
                                        this.httpRequest.method += (char)buffer[index++];
                                    else
                                    {
                                        index++;
                                        parserState = ParserState.URL;
                                    }
                                    break;
                                case ParserState.URL:
                                    if (buffer[index] == '?')
                                    {
                                        index++;
                                        key = "";
                                        this.httpRequest.execute = true;
                                        this.httpRequest.arguments = new Hashtable();
                                        parserState = ParserState.URLPARAM;
                                    }
                                    else if (buffer[index] != ' ')
                                        this.httpRequest.url += (char)buffer[index++];
                                    else
                                    {
                                        index++;
                                        this.httpRequest.url = HttpUtility.UrlDecode(this.httpRequest.url);
                                        parserState = ParserState.VERSION;
                                    }
                                    break;
                                case ParserState.URLPARAM:
                                    if (buffer[index] == '=')
                                    {
                                        index++;
                                        value = "";
                                        parserState = ParserState.URLVALUE;
                                    }
                                    else if (buffer[index] == ' ')
                                    {
                                        index++;

                                        this.httpRequest.url = HttpUtility.UrlDecode(this.httpRequest.url);
                                        parserState = ParserState.VERSION;
                                    }
                                    else
                                    {
                                        key += (char)buffer[index++];
                                    }
                                    break;
                                case ParserState.URLVALUE:
                                    if (buffer[index] == '&')
                                    {
                                        index++;
                                        key = HttpUtility.UrlDecode(key);
                                        value = HttpUtility.UrlDecode(value);
                                        this.httpRequest.arguments[key] = this.httpRequest.arguments[key] != null ? this.httpRequest.arguments[key] + ", " + value : value;
                                        key = "";
                                        parserState = ParserState.URLPARAM;
                                    }
                                    else if (buffer[index] == ' ')
                                    {
                                        index++;
                                        key = HttpUtility.UrlDecode(key);
                                        value = HttpUtility.UrlDecode(value);
                                        this.httpRequest.arguments[key] = this.httpRequest.arguments[key] != null ? this.httpRequest.arguments[key] + ", " + value : value;

                                        this.httpRequest.url = HttpUtility.UrlDecode(this.httpRequest.url);
                                        parserState = ParserState.VERSION;
                                    }
                                    else
                                    {
                                        value += (char)buffer[index++];
                                    }
                                    break;
                                case ParserState.VERSION:
                                    if (buffer[index] == '\r')
                                        index++;
                                    else if (buffer[index] != '\n')
                                        this.httpRequest.version += (char)buffer[index++];
                                    else
                                    {
                                        index++;
                                        key = "";
                                        this.httpRequest.headers = new Hashtable();
                                        parserState = ParserState.HEADERKEY;
                                    }
                                    break;
                                case ParserState.HEADERKEY:
                                    if (buffer[index] == '\r')
                                        index++;
                                    else if (buffer[index] == '\n')
                                    {
                                        index++;
                                        if (this.httpRequest.headers["Content-Length"] != null)
                                        {
                                            if (Convert.ToString(this.httpRequest.headers["Content-Length"]) == "stream")
                                                parserState = ParserState.STREAM;
                                            else
                                            {
                                                this.httpRequest.bodySize = Convert.ToInt32(this.httpRequest.headers["Content-Length"]);
                                                this.httpRequest.bodyData = new byte[this.httpRequest.bodySize];
                                                parserState = ParserState.BODY;
                                            }

                                        }
                                        else
                                            parserState = ParserState.OK;

                                    }
                                    else if (buffer[index] == ':')
                                        index++;
                                    else if (buffer[index] != ' ')
                                        key += (char)buffer[index++];
                                    else
                                    {
                                        index++;
                                        value = "";
                                        parserState = ParserState.HEADERVALUE;
                                    }
                                    break;
                                case ParserState.HEADERVALUE:
                                    if (buffer[index] == '\r')
                                        index++;
                                    else if (buffer[index] != '\n')
                                        value += (char)buffer[index++];
                                    else
                                    {
                                        index++;
                                        this.httpRequest.headers.Add(key, value);
                                        key = "";
                                        parserState = ParserState.HEADERKEY;
                                    }
                                    break;
                                case ParserState.BODY:
                                    Array.Copy(buffer, index, this.httpRequest.bodyData, bodyDataIndex, bytesRead - index);
                                    bodyDataIndex += bytesRead - index;
                                    index = bytesRead;
                                    if (this.httpRequest.bodySize <= bodyDataIndex)
                                        parserState = ParserState.OK;
                                    break;
                                case ParserState.STREAM:
                                    fileStream.Write(buffer, index, bytesRead - index);
                                    index = bytesRead;
                                    break;
                                case ParserState.OK:
                                    index = bytesRead;
                                    break;
                            }
                        }
                        while (index < bytesRead);
                    }
                    while (networkStream.DataAvailable);

                    if (bytesReceived > 0)
                    {
                        this.logWriter.WriteLog("Client " + this.clientNumber.ToString() + " received " + bytesReceived.ToString() + ((bytesReceived == 1) ? " byte" : " bytes"));
                        totalBytesReceived += bytesReceived;
                    }
                    else
                        this.client.Close();

                    if (parserState != ParserState.STREAM)
                    {
                        this.httpResponse.version = "HTTP/1.1";
                        this.httpResponse.status = (int)((parserState == ParserState.OK) ? ResponseState.OK : ResponseState.BAD_REQUEST);


                        this.httpResponse.headers = new Hashtable();
                        this.httpResponse.headers.Add("Server", server.Name);
                        this.httpResponse.headers.Add("Date", DateTime.Now.ToString("r"));

                        if (httpResponse.status == (int)ResponseState.OK)
                            this.server.OnResponse(ref this.httpRequest, ref this.httpResponse);

                        string headersString = this.httpResponse.version + " " + ResponseStatus.GetInstance()[this.httpResponse.status] + "\n";
                        foreach (DictionaryEntry header in this.httpResponse.headers)
                            headersString += header.Key + ": " + header.Value + "\n";
                        headersString += "\n";
                        byte[] bHeadersString = Encoding.ASCII.GetBytes(headersString);
                        networkStream.Write(bHeadersString, 0, bHeadersString.Length);

                        if (this.httpResponse.bodyData != null)
                            networkStream.Write(this.httpResponse.bodyData, 0, this.httpResponse.bodyData.Length);

                        if (this.httpResponse.fileStream != null)
                            using (this.httpResponse.fileStream)
                            {
                                byte[] b = new byte[client.SendBufferSize];
                                int bytesRead;
                                while ((bytesRead = this.httpResponse.fileStream.Read(b, 0, b.Length)) > 0)
                                    networkStream.Write(b, 0, bytesRead);

                                this.httpResponse.fileStream.Close();
                            }

                        break;
                    }
                } while (this.client.Connected);
            }
            catch (IOException)
            {
            }
            catch (Exception e)
            {
                this.logWriter.WriteLog("Client " + this.clientNumber.ToString() + " caught " + e.ToString());
            }
            finally
            {
                this.logWriter.WriteLog("Client " + this.clientNumber.ToString() + " disconnected. Total bytes received: " + totalBytesReceived.ToString());

                networkStream.Close();
                fileStream.Close();
                this.client.Close();
                if (this.httpResponse.fileStream != null)
                    this.httpResponse.fileStream.Close();
                Thread.CurrentThread.Abort();
            }
        }
    }
}
