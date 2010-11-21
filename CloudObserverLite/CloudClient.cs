using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Web;
//using Microsoft.Win32;
using CloudObserverLite.Properties;

namespace CloudObserverLite
{
    public class CloudClient
    {
        private CloudServer server;
        private uint clientNumber;
        private TcpClient client;
        private HttpRequestStruct httpRequest;
        private HttpResponseStruct httpResponse;

        private ClientType clientType = ClientType.GeneralClient;

        private string nickname;

        private List<FLVReader> readers;
        private List<FLVReader> disconnectedReaders;

        private byte[] header;
        private List<byte[]> scriptData;
        private List<byte[]> tagsBuffer;
        private uint bufferedTimestamp;

        private object locker = new Object();

        private const int HEADER_LENGTH = 13;
        private const byte SIGNATURE1 = 0x46;
        private const byte SIGNATURE2 = 0x4C;
        private const byte SIGNATURE3 = 0x56;
        private const byte VERSION = 1;
        private const int TAG_HEADER_LENGTH = 11;
        private const byte TAGTYPE_AUDIO = 8;
        private const byte TAGTYPE_VIDEO = 9;
        private const byte TAGTYPE_DATA = 18;

        private LogWriter logWriter;

        public CloudClient(CloudServer server, uint clientNumber, TcpClient client)
        {
            this.server = server;
            this.clientNumber = clientNumber;
            this.client = client;

            this.readers = new List<FLVReader>();
            this.disconnectedReaders = new List<FLVReader>();
            this.scriptData = new List<byte[]>();
            this.tagsBuffer = new List<byte[]>();
            this.bufferedTimestamp = 0;

            this.logWriter = LogWriter.GetInstance();
        }

        public void Process()
        {
            this.logWriter.WriteLog("Client " + this.clientNumber.ToString() + " connected.");

            NetworkStream networkStream = this.client.GetStream();

            byte[] buffer = new byte[this.client.ReceiveBufferSize];

            ParserState parserState = ParserState.METHOD;

            string key = "";
            string value = "";
            int bodyDataIndex = 0;

            try
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
                                        this.httpRequest.bodySize = Convert.ToInt32(this.httpRequest.headers["Content-Length"]);
                                        this.httpRequest.bodyData = new byte[this.httpRequest.bodySize];
                                        parserState = ParserState.BODY;
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
                            case ParserState.OK:
                                index = bytesRead;
                                break;
                        }
                    }
                    while (index < bytesRead);
                }
                while (networkStream.DataAvailable);

                this.httpResponse.version = "HTTP/1.1";
                this.httpResponse.status = (int)((parserState == ParserState.OK) ? ResponseState.OK : ResponseState.BAD_REQUEST);

                this.httpResponse.headers = new Hashtable();
                this.httpResponse.headers.Add("Server", server.Name);
                this.httpResponse.headers.Add("Date", DateTime.Now.ToString("r"));

                if (httpResponse.status == (int)ResponseState.OK)
                    this.OnResponse(ref this.httpRequest, ref this.httpResponse);

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

                if (httpResponse.status == (int)ResponseState.OK)
                {
                    if (clientType == ClientType.ReaderClient)
                        ((CloudClient)server.streams[nickname]).ConnectReader(networkStream);

                    if (clientType == ClientType.WriterClient)
                    {
                        // FLV header
                        header = ReadBytes(networkStream, HEADER_LENGTH);
                        // Signature
                        if ((SIGNATURE1 != header[0]) || (SIGNATURE2 != header[1]) || (SIGNATURE3 != header[2]))
                            throw new InvalidDataException("Not a valid FLV file!.");
                        // Version
                        if (VERSION != header[3])
                            throw new InvalidDataException("Not a valid FLV file!.");
                        // TypeFlags
                        if (0 != (header[4] >> 3))
                            throw new InvalidDataException("Not a valid FLV file!.");
                        //audio = (((header[4] & 0x4) >> 2) == 1);
                        if (0 != ((header[4] & 0x2) >> 1))
                            throw new InvalidDataException("Not a valid FLV file!.");
                        //video = ((header[4] & 0x1) == 1);
                        // DataOffset
                        uint dataOffset = ToUI32(header, 5);
                        // PreviousTagSize0
                        if (0 != ToUI32(header, 9))
                            throw new InvalidDataException("Not a valid FLV file!.");

                        // FLV body
                        while (this.client.Connected)
                        {
                            // FLV tag header
                            byte[] tagHeader = ReadBytes(networkStream, TAG_HEADER_LENGTH);
                            // TagType
                            if ((tagHeader[0] != TAGTYPE_AUDIO) && (tagHeader[0] != TAGTYPE_VIDEO) && (tagHeader[0] != TAGTYPE_DATA))
                                throw new InvalidDataException("Not a valid FLV file!.");
                            // DataSize
                            uint dataSize = ToUI24(tagHeader, 1);
                            // Timestamp
                            uint timestamp = ToUI24(tagHeader, 4);
                            // TimestampExtended
                            //uint timestampExtended = tagHeader[7];
                            // StreamID
                            if (0 != ToUI24(tagHeader, 8))
                                throw new InvalidDataException("Not a valid FLV file!.");
                            // Data
                            byte[] tagData = ReadBytes(networkStream, (int)dataSize + 4);

                            lock (locker)
                            {
                                if ((tagHeader[0] == TAGTYPE_VIDEO) && (1 == (tagData[0] & 0xF0) >> 4))
                                {
                                    tagsBuffer.Clear();
                                    bufferedTimestamp = timestamp;
                                }

                                if (tagHeader[0] == TAGTYPE_DATA)
                                {
                                    scriptData.Add(tagHeader);
                                    scriptData.Add(tagData);
                                }

                                tagsBuffer.Add(tagHeader);
                                tagsBuffer.Add(tagData);

                                foreach (FLVReader reader in readers)
                                {
                                    // Update timestamp.
                                    byte[] newTimestampValue = BitConverter.GetBytes(timestamp - reader.timestampDelta);
                                    tagHeader[4] = newTimestampValue[2];
                                    tagHeader[5] = newTimestampValue[1];
                                    tagHeader[6] = newTimestampValue[0];

                                    // Write tag.
                                    try
                                    {
                                        reader.stream.Write(tagHeader, 0, tagHeader.Length);
                                        reader.stream.Write(tagData, 0, tagData.Length);
                                    }
                                    catch (IOException)
                                    {
                                        disconnectedReaders.Add(reader);
                                    }
                                }

                                foreach (FLVReader disconnectedReader in disconnectedReaders)
                                    readers.Remove(disconnectedReader);
                                disconnectedReaders.Clear();
                            }
                        }
                    }
                }
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
                if (clientType != ClientType.ReaderClient)
                {
                    this.logWriter.WriteLog("Client " + this.clientNumber.ToString() + " disconnected.");

                    networkStream.Close();
                    this.client.Close();
                    if (this.httpResponse.fileStream != null)
                        this.httpResponse.fileStream.Close();
                }
                if (clientType == ClientType.WriterClient)
                {
                    foreach (FLVReader reader in readers)
                        reader.stream.Close();
                    server.streams.Remove(nickname);
                }
                Thread.CurrentThread.Abort();
            }
        }

        private bool CheckNickname(string nickname)
        {
            if (nickname == String.Empty)
                return false;

            bool result = true;
            for (int i = 0; i < nickname.Length; i++)
                if (!Char.IsLetterOrDigit(nickname, i))
                    result = false;

            return result;
        }

        private string GetSafeDateTime()
        {
            string result = DateTime.Now.ToString();
            result = result.Replace(' ', '-');
            result = result.Replace('.', '-');
            result = result.Replace(':', '-');
            return result;
        }

        private void OnResponse(ref HttpRequestStruct httpRequest, ref HttpResponseStruct httpResponse)
        {
            if ((httpRequest.execute) && (httpRequest.arguments["action"] != null))
            {
                string action = Convert.ToString(httpRequest.arguments["action"]);
                string bodyString = "";
                this.nickname = httpRequest.url.Substring(1);
                switch (action)
                {
                    case "write":
                        if (!CheckNickname(this.nickname))
                        {
                            httpResponse.status = (int)ResponseState.BAD_REQUEST;
                            bodyString = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\n";
                            bodyString += "<HTML><HEAD>\n";
                            bodyString += "<META http-equiv=Content-Type content=\"text/html; charset=windows-1252\">\n";
                            bodyString += "</HEAD>\n";
                            bodyString += "<BODY>Nickname \"";
                            bodyString += this.nickname;
                            bodyString += "\" is not valid! Nickname must contain only alphabetic characters and decimal digits.</BODY></HTML>\n";
                        }
                        else if (server.streams[this.nickname] != null)
                        {
                            httpResponse.status = (int)ResponseState.FORBIDDEN;
                            bodyString = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\n";
                            bodyString += "<HTML><HEAD>\n";
                            bodyString += "<META http-equiv=Content-Type content=\"text/html; charset=windows-1252\">\n";
                            bodyString += "</HEAD>\n";
                            bodyString += "<BODY>Nickname \"";
                            bodyString += this.nickname;
                            bodyString += "\" is already in use!</BODY></HTML>\n";
                        }
                        else if (server.streams.Count >= CloudServer.MAX_STREAMS_COUNT)
                        {
                            httpResponse.status = (int)ResponseState.FORBIDDEN;
                            bodyString = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\n";
                            bodyString += "<HTML><HEAD>\n";
                            bodyString += "<META http-equiv=Content-Type content=\"text/html; charset=windows-1252\">\n";
                            bodyString += "</HEAD>\n";
                            bodyString += "<BODY>You have reached the maximum number of streams available in this demo. Try stopping some streams to create the new ones.</BODY></HTML>\n";
                        }
                        else
                        {
                            server.streams[this.nickname] = this;
                            bodyString = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\n";
                            bodyString += "<HTML><HEAD>\n";
                            bodyString += "<META http-equiv=Content-Type content=\"text/html; charset=windows-1252\">\n";
                            bodyString += "</HEAD>\n";
                            bodyString += "<BODY>Ready to receive stream from user with nickname \"";
                            bodyString += this.nickname;
                            bodyString += "\".</BODY></HTML>\n";
                            this.clientType = ClientType.WriterClient;
                        }
                        break;
                    case "read":
                        if (nickname.EndsWith(".flv"))
                            nickname = nickname.Substring(0, nickname.Length - 4);
                        if (server.streams[this.nickname] == null)
                        {
                            httpResponse.status = (int)ResponseState.NOT_FOUND;
                            bodyString = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\n";
                            bodyString += "<HTML><HEAD>\n";
                            bodyString += "<META http-equiv=Content-Type content=\"text/html; charset=windows-1252\">\n";
                            bodyString += "</HEAD>\n";
                            bodyString += "<BODY>User with nickname \"";
                            bodyString += this.nickname;
                            bodyString += "\" is not found!</BODY></HTML>\n";
                        }
                        else
                        {
                            httpResponse.headers.Add("Content-type", "video/x-flv");
                            httpResponse.headers.Add("Cache-Control", "no-cache");
                            this.clientType = ClientType.ReaderClient;
                        }
                        break;
                    default:
                        httpResponse.status = (int)ResponseState.BAD_REQUEST;
                        bodyString = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\n";
                        bodyString += "<HTML><HEAD>\n";
                        bodyString += "<META http-equiv=Content-Type content=\"text/html; charset=windows-1252\">\n";
                        bodyString += "</HEAD>\n";
                        bodyString += "<BODY>Unknown action \"";
                        bodyString += action;
                        bodyString += "\"!</BODY></HTML>\n";
                        break;
                    case "play":
                        bodyString = Resources.player_html.Replace("_NICKNAME_", nickname);
                        break;
                }
                httpResponse.bodyData = Encoding.ASCII.GetBytes(bodyString);
                return;
            }

            switch (httpRequest.url)
            {
                case "/":
                    string onlineUsers = "";
                    foreach (string nickname in server.streams.Keys)
                        onlineUsers += "<li><FORM><INPUT class=\"eButton\" type=\"button\" value=\"" + nickname + "\" onClick=\"window.open('./" + nickname + "?action=play','" + nickname + "','width=400,height=200,left=400,top=100,screenX=400,screenY=100')\"></FORM></li>\n";
                    httpResponse.bodyData = Encoding.ASCII.GetBytes(Resources.index_html.Replace("_ONLINE_USERS_", onlineUsers));
                    break;
                case "/history/history.css":
                    httpResponse.bodyData = Resources.history_history_css;
                    break;
                case "/history/history.js":
                    httpResponse.bodyData = Resources.history_history_js;
                    break;
                case "/history/historyFrame.html":
                    httpResponse.bodyData = Resources.history_historyFrame_html;
                    break;
                case "/AC_OETags.js":
                    httpResponse.bodyData = Resources.AC_OETags_js;
                    break;
                case "/framework_4.5.0.17689.swz":
                    httpResponse.bodyData = Resources.framework_4_5_0_17689_swz;
                    break;
                case "/osmf_1.0.0.16316.swz":
                    httpResponse.bodyData = Resources.osmf_1_0_0_16316_swz;
                    break;
                case "/playerProductInstall.swf":
                    httpResponse.bodyData = Resources.playerProductInstall_swf;
                    break;
                case "/rpc_4.5.0.17689.swz":
                    httpResponse.bodyData = Resources.rpc_4_5_0_17689_swz;
                    break;
                case "/spark_4.5.0.17689.swz":
                    httpResponse.bodyData = Resources.spark_4_5_0_17689_swz;
                    break;
                case "/sparkskins_4.5.0.17689.swz":
                    httpResponse.bodyData = Resources.sparkskins_4_5_0_17689_swz;
                    break;
                case "/swfobject.js":
                    httpResponse.bodyData = Resources.swfobject_js;
                    break;
                case "/textLayout_2.0.0.139.swz":
                    httpResponse.bodyData = Resources.textLayout_2_0_0_139_swz;
                    break;
                case "/window.swf":
                    httpResponse.bodyData = Resources.player_swf;
                    break;
                default:
                    httpResponse.status = (int)ResponseState.NOT_FOUND;

                    string bodyString = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\n";
                    bodyString += "<HTML><HEAD>\n";
                    bodyString += "<META http-equiv=Content-Type content=\"text/html; charset=windows-1252\">\n";
                    bodyString += "</HEAD>\n";
                    bodyString += "<BODY>File not found!</BODY></HTML>\n";

                    httpResponse.bodyData = Encoding.ASCII.GetBytes(bodyString);
                    break;
            }

            //string path = Directory.GetCurrentDirectory() + "\\" + httpRequest.url.Replace("/", "\\");

            //if (Directory.Exists(path))
            //{
            //    if (File.Exists(path + "index.html"))
            //        path += "\\index.html";
            //    else
            //    {
            //        string[] directories = Directory.GetDirectories(path);
            //        string[] files = Directory.GetFiles(path);

            //        string bodyString = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\n";
            //        bodyString += "<HTML><HEAD>\n";
            //        bodyString += "<META http-equiv=Content-Type content=\"text/html; charset=windows-1252\">\n";
            //        bodyString += "</HEAD>\n";
            //        bodyString += "<BODY><p>Folder listing, to do not see this add a 'index.html' document\n<p>\n";
            //        for (int i = 0; i < directories.Length; i++)
            //            bodyString += "<br><a href = \"" + httpRequest.url + Path.GetFileName(directories[i]) + "/\">[" + Path.GetFileName(directories[i]) + "]</a>\n";
            //        for (int i = 0; i < files.Length; i++)
            //            bodyString += "<br><a href = \"" + httpRequest.url + Path.GetFileName(files[i]) + "\">" + Path.GetFileName(files[i]) + "</a>\n";
            //        bodyString += "</BODY></HTML>\n";

            //        httpResponse.bodyData = Encoding.ASCII.GetBytes(bodyString);
            //        return;
            //    }
            //}

            //if (File.Exists(path))
            //{
            //    RegistryKey registryKey = Registry.ClassesRoot.OpenSubKey(Path.GetExtension(path), true);
            //    string registryValue = (string)registryKey.GetValue("Content Type");

            //    httpResponse.fileStream = File.Open(path, FileMode.Open);
            //    if (registryValue != "")
            //        httpResponse.headers["Content-type"] = registryValue;

            //    httpResponse.headers["Content-Length"] = httpResponse.fileStream.Length;
            //}
        }

        public void ConnectReader(Stream stream)
        {
            lock (locker)
            {
                stream.Write(header, 0, header.Length);
                foreach (byte[] data in scriptData)
                    stream.Write(data, 0, data.Length);

                bool tagHeader = true;
                foreach (byte[] data in tagsBuffer)
                {
                    if (tagHeader)
                    {
                        // Get timestamp.
                        uint timestamp = ToUI24(data, 4);
                        // Update timestamp.
                        byte[] newTimestampValue = BitConverter.GetBytes(timestamp - bufferedTimestamp);
                        data[4] = newTimestampValue[2];
                        data[5] = newTimestampValue[1];
                        data[6] = newTimestampValue[0];
                    }
                    stream.Write(data, 0, data.Length);
                    tagHeader = !tagHeader;
                }
                readers.Add(new FLVReader(stream, bufferedTimestamp));
            }
        }

        private static byte[] ReadBytes(Stream stream, int bytesToRead)
        {
            byte[] result = new byte[bytesToRead];
            int bytesRead = 0;
            while (bytesToRead > 0)
            {
                int read = stream.Read(result, bytesRead, bytesToRead);
                if (read == 0)
                    throw new EndOfStreamException("End of stream reached.");
                bytesRead += read;
                bytesToRead -= read;
            }
            return result;
        }

        private static ushort ToUI16(byte[] value, int startIndex)
        {
            return (ushort)(value[startIndex] << 8 | value[startIndex + 1]);
        }

        private static uint ToUI24(byte[] value, int startIndex)
        {
            return (uint)(value[startIndex] << 16 | value[startIndex + 1] << 8 | value[startIndex + 2]);
        }

        private static uint ToUI32(byte[] value, int startIndex)
        {
            return (uint)(value[startIndex] << 24 | value[startIndex + 1] << 16 | value[startIndex + 2] << 8 | value[startIndex + 3]);
        }
    }
}
