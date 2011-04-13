﻿using System;
using System.IO;
using System.Net;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.Collections.Generic;

namespace CloudObserver.Services
{
    public class IPCameraMJpegFormat : IPCamera
    {
        private int cameraID;
        private string sourceUri;
        private string userName = null;
        private string password = null;
        private object userData = null;
        private int framesReceived;
        private int bytesReceived;
        private bool useSeparateConnectionGroup = true;

        private const int bufSize = 512 * 1024;	// buffer size
        private const int readSize = 1024;		// portion size to read

        private Thread thread = null;
        private ManualResetEvent stopEvent = null;
        private ManualResetEvent reloadEvent = null;
        private BroadcastServiceContract broadcastServiceClient;

        //Constructor
        public IPCameraMJpegFormat(int cameraID, string broadcastServiceUri)
        {
            this.cameraID = cameraID;

            broadcastServiceClient = ChannelFactory<BroadcastServiceContract>.CreateChannel(new BasicHttpBinding(), new EndpointAddress(broadcastServiceUri));
        }

        // SeparateConnectioGroup property
        // indicates to open WebRequest in separate connection group
        public bool SeparateConnectionGroup
        {
            get { return useSeparateConnectionGroup; }
            set { useSeparateConnectionGroup = value; }
        }

        //Here we set what camera we are
        public int CameraID
        {
            get { return cameraID; }
            set { cameraID = value; }
        }

        // VideoSource property
        public string VideoSource
        {
            get { return sourceUri; }
            set
            {
                sourceUri = value;
                // signal to reload
                if (thread != null)
                    reloadEvent.Set();
            }
        }

        // Login property
        public string Login
        {
            get { return userName; }
            set { userName = value; }
        }

        // Password property 
        public string Password
        {
            get { return password; }
            set { password = value; }
        }

        // FramesReceived property
        public int FramesReceived
        {
            get
            {
                int frames = framesReceived;
                framesReceived = 0;
                return frames;
            }
        }

        // BytesReceived property
        public int BytesReceived
        {
            get
            {
                int bytes = bytesReceived;
                bytesReceived = 0;
                return bytes;
            }
        }

        // UserData property
        public object UserData
        {
            get { return userData; }
            set { userData = value; }
        }

        // Get state of the video source thread
        public bool Running
        {
            get
            {
                if (thread != null)
                {
                    if (thread.Join(0) == false)
                        return true;

                    // the thread is not running, so free resources
                    Free();
                }
                return false;
            }
        }

        public override void SetSource(string sourceUri)
        {
            this.sourceUri = sourceUri;
        }

        //To  know how much frames transfered
        public override int GetFramesCounter()
        {
            return FramesReceived;
        }

        //Without realisation
        public override void SetFPSLimit(int fpsLimit)
        {
            ;
        }

        // Start work
        public override void StartBroadcasting()
        {
            if (thread == null)
            {
                framesReceived = 0;
                bytesReceived = 0;

                // create events
                stopEvent = new ManualResetEvent(false);
                reloadEvent = new ManualResetEvent(false);

                // create and start new thread
                thread = new Thread(new ThreadStart(WorkerThread));
                thread.Name = sourceUri;
                thread.Start();
            }
        }

        // Signal thread to stop work
        public override void StopBroadcasting()
        {
            // stop thread
            if (thread != null)
            {
                // signal to stop
                stopEvent.Set();
            }
        }

        // Wait for thread stop
        public void WaitForStop()
        {
            if (thread != null)
            {
                // wait for thread stop
                thread.Join();

                Free();
            }
        }

        //set  information for https connection
        public override void SetCredentials(string userName, string password)
        {
            this.userName = userName;
            this.password = password;
        }

        // Abort thread
        public void Stop()
        {
            if (this.Running)
            {
                thread.Abort();
                WaitForStop();
            }
        }

        // Free resources
        private void Free()
        {
            thread = null;

            // release events
            stopEvent.Close();
            stopEvent = null;
            reloadEvent.Close();
            reloadEvent = null;
        }

        // Thread entry point
        public void WorkerThread()
        {
            byte[] buffer = new byte[bufSize];	// buffer to read stream

            while (true)
            {
                // reset reload event
                reloadEvent.Reset();

                HttpWebRequest req = null;
                WebResponse resp = null;
                Stream stream = null;
                byte[] delimiter = null;
                byte[] delimiter2 = null;
                byte[] boundary = null;
                int boundaryLen, delimiterLen = 0, delimiter2Len = 0;
                int read, todo = 0, total = 0, pos = 0, align = 1;
                int start = 0, stop = 0;

                // align
                //  1 = searching for image start
                //  2 = searching for image end
                try
                {
                    // create request
                    req = (HttpWebRequest)WebRequest.Create(sourceUri);
                    // set login and password
                    if ((userName != null) && (password != null) && (userName != ""))
                        req.Credentials = new NetworkCredential(userName, password);
                    // set connection group name
                    if (useSeparateConnectionGroup)
                        req.ConnectionGroupName = GetHashCode().ToString();
                    // get response
                    resp = req.GetResponse();

                    // check content type
                    string ct = resp.ContentType;
                    if (ct.IndexOf("multipart/x-mixed-replace") == -1)
                        throw new ApplicationException("Invalid URL");

                    // get boundary
                    ASCIIEncoding encoding = new ASCIIEncoding();
                    boundary = encoding.GetBytes(ct.Substring(ct.IndexOf("boundary=", 0) + 9));
                    boundaryLen = boundary.Length;

                    // get response stream
                    stream = resp.GetResponseStream();

                    // loop
                    while ((!stopEvent.WaitOne(0, true)) && (!reloadEvent.WaitOne(0, true)))
                    {
                        // check total read
                        if (total > bufSize - readSize)
                        {
                            System.Diagnostics.Debug.WriteLine("flushing");
                            total = pos = todo = 0;
                        }

                        // read next portion from stream
                        if ((read = stream.Read(buffer, total, readSize)) == 0)
                            throw new ApplicationException();

                        total += read;
                        todo += read;

                        // increment received bytes counter
                        bytesReceived += read;

                        // does we know the delimiter ?
                        if (delimiter == null)
                        {
                            // find boundary
                            pos = Find(buffer, boundary, pos, todo);

                            if (pos == -1)
                            {
                                // was not found
                                todo = boundaryLen - 1;
                                pos = total - todo;
                                continue;
                            }

                            todo = total - pos;

                            if (todo < 2)
                                continue;

                            // check new line delimiter type
                            if (buffer[pos + boundaryLen] == 10)
                            {
                                delimiterLen = 2;
                                delimiter = new byte[2] { 10, 10 };
                                delimiter2Len = 1;
                                delimiter2 = new byte[1] { 10 };
                            }
                            else
                            {
                                delimiterLen = 4;
                                delimiter = new byte[4] { 13, 10, 13, 10 };
                                delimiter2Len = 2;
                                delimiter2 = new byte[2] { 13, 10 };
                            }

                            pos += boundaryLen + delimiter2Len;
                            todo = total - pos;
                        }

                        // boundary aligned
                        /*						if ((align == 0) && (todo >= boundaryLen))
                                                {
                                                    if (ByteArrayUtils.Compare(buffer, boundary, pos))
                                                    {
                                                        // boundary located
                                                        align = 1;
                                                        todo -= boundaryLen;
                                                        pos += boundaryLen;
                                                    }
                                                    else
                                                        align = 2;
                                                }*/

                        // search for image
                        if (align == 1)
                        {
                            start = Find(buffer, delimiter, pos, todo);
                            if (start != -1)
                            {
                                // found delimiter
                                start += delimiterLen;
                                pos = start;
                                todo = total - pos;
                                align = 2;
                            }
                            else
                            {
                                // delimiter not found
                                todo = delimiterLen - 1;
                                pos = total - todo;
                            }
                        }

                        // search for image end
                        while ((align == 2) && (todo >= boundaryLen))
                        {
                            stop = Find(buffer, boundary, pos, todo);
                            if (stop != -1)
                            {
                                pos = stop;
                                todo = total - pos;

                                // increment frames counter
                                framesReceived++;
                                byte[] picture;
                                picture = (new MemoryStream(buffer, start, stop - start)).ToArray();
                                broadcastServiceClient.WriteFrame(cameraID, picture);

                                /*Bitmap bmp = (Bitmap)Bitmap.FromStream(new MemoryStream(buffer, start, stop - start));
                                pictureBox1.Image = bmp;
                                pictureBox1.Refresh();*/

                                //here byte[] is to be done..

                                // image at stop
                                /*if (NewFrame != null)
                                {
                                    Bitmap	bmp = (Bitmap) Bitmap.FromStream(new MemoryStream(buffer, start, stop - start));
                                    // notify client
                                    NewFrame(this, new CameraEventArgs(bmp));
                                    // release the image
                                    bmp.Dispose();
                                    bmp = null;
                                } */
                                //								System.Diagnostics.Debug.WriteLine("found image end, size = " + (stop - start));

                                // shift array
                                pos = stop + boundaryLen;
                                todo = total - pos;
                                Array.Copy(buffer, pos, buffer, 0, todo);

                                total = todo;
                                pos = 0;
                                align = 1;
                            }
                            else
                            {
                                // delimiter not found
                                todo = boundaryLen - 1;
                                pos = total - todo;
                            }
                        }
                    }
                }
                catch (Exception)
                {
                    // wait for a while before the next try
                    Thread.Sleep(250);
                }
                finally
                {
                    // abort request
                    if (req != null)
                    {
                        req.Abort();
                        req = null;
                    }
                    // close response stream
                    if (stream != null)
                    {
                        stream.Close();
                        stream = null;
                    }
                    // close response
                    if (resp != null)
                    {
                        resp.Close();
                        resp = null;
                    }
                }

                // need to stop ?
                if (stopEvent.WaitOne(0, true))
                    break;
            }
        }

        // Find subarray in array
        public static int Find(byte[] array, byte[] needle, int startIndex, int count)
        {
            int needleLen = needle.Length;
            int index;

            while (count >= needleLen)
            {
                index = Array.IndexOf(array, needle[0], startIndex, count - needleLen + 1);

                if (index == -1)
                    return -1;

                int i, p;
                // check for needle
                for (i = 0, p = index; i < needleLen; i++, p++)
                {
                    if (array[p] != needle[i])
                        break;
                }

                if (i == needleLen)
                {
                    // found needle
                    return index;
                }

                count -= (index - startIndex + 1);
                startIndex = index + 1;
            }
            return -1;
        }
    }
}