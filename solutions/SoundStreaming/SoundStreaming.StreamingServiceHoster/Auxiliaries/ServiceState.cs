using System;

namespace SoundStreaming.StreamingServiceHoster
{
    /// <summary>
    /// Defines the states in which a service object can exist.
    /// </summary>
    public enum ServiceState
    {
        /// <summary>
        /// Indicates that the service object has been instantiated and is configurable, but not yet ready for use.
        /// </summary>
        Created = 0,

        /// <summary>
        /// Indicates that the service object is being transitioned from the Created or Faulted state to the Started state.
        /// </summary>
        Starting = 1,

        /// <summary>
        /// Indicates that the service object is now started and ready to be used.
        /// </summary>
        Started = 2,

        /// <summary>
        ///  Indicates that the service object is being transitioned to the Stopped state.
        /// </summary>
        Stopping = 3,

        /// <summary>
        /// Indicates that the service object has been stopped.
        /// </summary>
        Stopped = 4,

        /// <summary>
        /// Indicates that the service object has encountered an error or fault.
        /// </summary>
        Faulted = 5,
    }
}