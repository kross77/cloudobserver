using System;
using System.IO;
using System.ServiceModel;

namespace CloudObserver.Services.StreamingService
{
    /// <summary>
    /// Streaming service realization class.
    /// </summary>
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class StreamingService : IStreamingService
    {
        #region Fields

        /// <summary>
        /// Stores an internal buffer to store the data.
        /// </summary>
        private byte[] buffer;

        /// <summary>
        /// Stores the length (in bytes) of the internal buffer.
        /// </summary>
        private int bufferLength;

        /// <summary>
        /// Stores current internal buffer position.
        /// </summary>
        private int bufferPosition;

        /// <summary>
        /// Stores the instance of diagnostics object, associated with this service instance.
        /// </summary>
        private StreamingServiceDiagnostics diagnostics;

        #endregion

        #region Constants

        /// <summary>
        /// Default length (in bytes) of the internal buffer.
        /// </summary>
        public const int defaultBufferLength = 1048576; // 1 megabyte

        #endregion

        #region Constructors

        /// <summary>
        /// Default constructor. This contructor is always used when accessing service.
        /// </summary>
        public StreamingService() : this(defaultBufferLength) { }

        /// <summary>
        /// Parameterized constructor. Allows to specify the internal buffer length. 
        /// This constructor can only be used when specifying an instance of singleton service with ServiceHost object.
        /// </summary>
        /// <param name="bufferLength">Internal buffer length (in bytes).</param>
        public StreamingService(int bufferLength)
        {
            // Initialize default values of the fields.
            this.bufferLength = bufferLength;
            buffer = new byte[bufferLength];
            bufferPosition = 0;
            diagnostics = new StreamingServiceDiagnostics(bufferLength);
        }

        #endregion

        #region IStreamingService Members

        /// <summary>
        /// Returns the diagnostics object, associated with this service instance.
        /// </summary>
        /// <returns>The instance of diagnostics object, associated with this service instance.</returns>
        public StreamingServiceDiagnostics GetDiagnostics()
        {
            return diagnostics;
        }

        /// <summary>
        /// Reads a block of bytes from the internal buffer, starting from the specified position, and writes the data to buffer.
        /// </summary>
        /// <param name="buffer">When this method returns, contains the specified byte array with the values 
        /// between offset and (offset + count - 1) replaced by the characters read from the internal buffer.</param>
        /// <param name="offset">The byte offset in buffer at which to begin writing.</param>
        /// <param name="count">The maximum number of bytes to read.</param>
        /// <param name="position">The position in internal buffer at which to begin reading. When this method returns, 
        /// position is at the end of the read block.</param>
        /// <param name="synchronize">true to synchronize buffers before reading, otherwise false</param>
        /// <returns>The total number of bytes written into the buffer. This can be less than 
        /// the number of bytes requested if that number of bytes are not currently available.</returns>
        public int Read(out byte[] buffer, int offset, int count, ref int position, bool synchronize)
        {
            // Synchronize position if necessary.
            if (synchronize) position = Synchronize();

            // Define and initialize a variable to store the number of bytes read.
            int bytes = 0;

            // Initialize an output buffer.
            buffer = new byte[count];

            // While there are less than count bytes read and more bytes are available.
            while ((bytes < count) && (position != bufferPosition))
            {
                // Copy next byte in the result buffer.
                buffer[offset + bytes] = this.buffer[position];

                // Move to the next position.
                position = (position + 1) % bufferLength;

                // Increase the number of bytes read.
                bytes++;
            }

            // Notify diagnostics object about this read operation.
            diagnostics.ConfirmRead(position);

            // Return the total number of bytes written into the buffer.
            return bytes;
        }

        /// <summary>
        /// Writes the provided data stream into the internal buffer.
        /// </summary>
        /// <param name="dataStream">A stream to write data from.</param>
        public void Write(MemoryStream dataStream)
        {
            // Define and initialize a variable to store the number of bytes written.
            int bytes = 0;

            // Try to read the first byte from the input stream.
            int currentByte = dataStream.ReadByte();

            // While there are bytes in the input stream.
            while (currentByte != -1)
            {
                // Write the current byte in the internal buffer.
                buffer[bufferPosition] = (byte)currentByte;

                // Move to the next position.
                bufferPosition = (bufferPosition + 1) % bufferLength;

                // Increase the number of bytes written.
                bytes++;

                // Try to read the next byte from the input stream.
                currentByte = dataStream.ReadByte();
            }

            // Notify diagnostics object about this write operation.
            diagnostics.ConfirmWrite(bytes);
        }

        /// <summary>
        /// Synchronizes with the service internal buffer.
        /// </summary>
        /// <returns>Synchronized buffer position.</returns>
        public int Synchronize()
        {
            return bufferPosition;
        }

        #endregion
    }
}