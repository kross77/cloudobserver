using System;
using System.Runtime.Serialization;

namespace CloudObserver.Services.StreamingService
{
    /// <summary>
    /// Represents streaming service diagnostics information.
    /// </summary>
    public class StreamingServiceDiagnostics
    {
        #region Fields

        /// <summary>
        /// Stores the length (in bytes) of the internal buffer.
        /// </summary>
        private int bufferLength;

        /// <summary>
        /// Stores current internal buffer position.
        /// </summary>
        private int bufferPosition;

        /// <summary>
        /// Stores end position of the last read operation.
        /// </summary>
        private int lastReadPosition;

        #endregion

        #region Events

        /// <summary>
        /// Occurs when diagnostic data is updated.
        /// </summary>
        public event EventHandler DiagnosticsUpdated;

        #endregion

        #region Properties

        /// <summary>
        /// The length (in bytes) of the internal buffer.
        /// </summary>
        public int BufferLength
        {
            get { return bufferLength; }
        }

        /// <summary>
        /// Current internal buffer position.
        /// </summary>
        public int BufferPosition
        {
            get { return bufferPosition; }
        }

        /// <summary>
        /// End position of the last read operation.
        /// </summary>
        public int LastReadPosition
        {
            get { return lastReadPosition; }
        }

        #endregion

        #region Constructors

        /// <summary>
        /// Default constructor.
        /// </summary>
        /// <param name="bufferLength">The length (in bytes) of the internal buffer.</param>
        public StreamingServiceDiagnostics(int bufferLength)
        {
            this.bufferLength = bufferLength;
            bufferPosition = 0;
            lastReadPosition = 0;
        }

        #endregion

        #region Public Methods

        /// <summary>
        /// Confirms write operation.
        /// </summary>
        /// <param name="bytes">Number of bytes written.</param>
        public void ConfirmWrite(int bytes)
        {
            bufferPosition = (bufferPosition + bytes) % bufferLength;
            DiagnosticsUpdated.Invoke(this, EventArgs.Empty);
        }

        /// <summary>
        /// Confirms read operation.
        /// </summary>
        /// <param name="readPosition"></param>
        public void ConfirmRead(int readPosition)
        {
            lastReadPosition = readPosition;
            DiagnosticsUpdated.Invoke(this, EventArgs.Empty);
        }

        #endregion
    }
}