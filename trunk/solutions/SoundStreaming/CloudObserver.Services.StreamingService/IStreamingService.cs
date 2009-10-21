using System;
using System.IO;
using System.ServiceModel;

namespace CloudObserver.Services.StreamingService
{
    /// <summary>
    /// Streaming service contract interface.
    /// </summary>
    [ServiceContract]
    public interface IStreamingService
    {
        /// <summary>
        /// Returns the diagnostics object, associated with this service instance.
        /// </summary>
        /// <returns>The instance of diagnostics object, associated with this service instance.</returns>
        [OperationContract]
        StreamingServiceDiagnostics GetDiagnostics();

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
        [OperationContract]
        int Read(out byte[] buffer, int offset, int count, ref int position, bool synchronize);

        /// <summary>
        /// Writes the provided data stream into the internal buffer.
        /// </summary>
        /// <param name="dataStream">A stream to write data from.</param>
        [OperationContract]
        void Write(MemoryStream dataStream);

        /// <summary>
        /// Synchronizes with the service internal buffer.
        /// </summary>
        /// <returns>Synchronized buffer position.</returns>
        [OperationContract]
        int Synchronize();
    }
}