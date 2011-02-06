using System;
using System.Collections.Generic;

namespace CloudObserver.Clients.Auxiliaries.Capture.DirectSound
{
    /// <summary>
    /// Represents an audio capture device like a microphone or line-in in terms of Microsoft DirectSound API.
    /// </summary>
    public struct DirectSoundCaptureDevice : IEquatable<DirectSoundCaptureDevice>
    {
        /// <summary>
        /// A textual description of the Microsoft DirectSound device.
        /// </summary>
        private string description;

        /// <summary>
        /// The globally unique identifier (GUID) of a Microsoft DirectSound driver.
        /// </summary>
        private Guid driverGuid;

        /// <summary>
        /// The module name of the Microsoft DirectSound driver corresponding to this device.
        /// </summary>
        private string moduleName;

        /// <summary>
        /// Operating system default audio capture device.
        /// </summary>
        public static readonly DirectSoundCaptureDevice Default = new DirectSoundCaptureDevice("Default", Guid.Empty, "");

        /// <summary>
        /// Lists audio capture devices which are currently available in the operating system.
        /// </summary>
        public static IEnumerable<DirectSoundCaptureDevice> AllAvailable
        {
            get
            {
                Microsoft.DirectX.DirectSound.CaptureDevicesCollection captureDevicesCollection =
                    new Microsoft.DirectX.DirectSound.CaptureDevicesCollection();
                foreach (Microsoft.DirectX.DirectSound.DeviceInformation deviceInformation in captureDevicesCollection)
                {
                    yield return new DirectSoundCaptureDevice(
                        deviceInformation.Description,
                        deviceInformation.DriverGuid,
                        deviceInformation.ModuleName);
                }
            }
        }

        /// <summary>
        /// Retrieves a textual description of the Microsoft DirectSound device.
        /// </summary>
        public string Description { get { return description; } }

        /// <summary>
        /// Retrieves the globally unique identifier (GUID) of a Microsoft DirectSound driver.
        /// </summary>
        public Guid DriverGuid { get { return driverGuid; } }

        /// <summary>
        /// Retrieves the module name of the Microsoft DirectSound driver corresponding to this device.
        /// </summary>
        public string ModuleName { get { return moduleName; } }

        /// <summary>
        /// Initializes a new instance of the CloudObserver.Capture.DirectSound.DirectSoundCaptureDevice class.
        /// </summary>
        /// <param name="description">A textual description of the Microsoft DirectSound device.</param>
        /// <param name="driverGuid">The globally unique identifier (GUID) of a Microsoft DirectSound driver.</param>
        /// <param name="moduleName">The module name of the Microsoft DirectSound driver corresponding to this device.</param>
        public DirectSoundCaptureDevice(string description, Guid driverGuid, string moduleName)
        {
            this.description = description;
            this.driverGuid = driverGuid;
            this.moduleName = moduleName;
        }

        /// <summary>
        /// Compares two CloudObserver.Capture.DirectSound.DirectSoundCaptureDevice objects.
        /// </summary>
        /// <param name="device1">A CloudObserver.Capture.DirectSound.DirectSoundCaptureDevice to compare.</param>
        /// <param name="device2">A CloudObserver.Capture.DirectSound.DirectSoundCaptureDevice to compare.</param>
        /// <returns>true if the device1 and device2 values are not equal; otherwise, false.</returns>
        public static bool operator !=(DirectSoundCaptureDevice device1, DirectSoundCaptureDevice device2)
        {
            return !(device1 == device2);
        }

        /// <summary>
        /// Compares two CloudObserver.Capture.DirectSound.DirectSoundCaptureDevice objects.
        /// </summary>
        /// <param name="device1">A CloudObserver.Capture.DirectSound.DirectSoundCaptureDevice to compare.</param>
        /// <param name="device2">A CloudObserver.Capture.DirectSound.DirectSoundCaptureDevice to compare.</param>
        /// <returns>true if the device1 and device2 values are equal; otherwise, false.</returns>
        public static bool operator ==(DirectSoundCaptureDevice device1, DirectSoundCaptureDevice device2)
        {
            return device1.Equals(device2);
        }

        /// <summary>
        /// Determines whether the specified System.Object is equal to the current System.Object.
        /// </summary>
        /// <param name="obj">The System.Object to compare with the current System.Object.</param>
        /// <returns>true if the specified System.Object is equal to the current System.Object; otherwise, false.</returns>
        public override bool Equals(object obj)
        {
            if (!(obj is DirectSoundCaptureDevice)) { return false; }
            return base.Equals((DirectSoundCaptureDevice)obj);
        }

        /// <summary>
        /// Serves as a hash function for a CloudObserver.Capture.DirectSound.DirectSoundCaptureDevice type.
        /// </summary>
        /// <returns>A hash code for the current CloudObserver.Capture.DirectSound.DirectSoundCaptureDevice.</returns>
        public override int GetHashCode()
        {
            return driverGuid.GetHashCode();
        }

        /// <summary>
        /// Returns a System.String that represents the current CloudObserver.Capture.DirectSound.DirectSoundCaptureDevice.
        /// </summary>
        /// <returns>A System.String that represents the current CloudObserver.Capture.DirectSound.DirectSoundCaptureDevice.</returns>
        public override string ToString()
        {
            return Description;
        }

        /// <summary>
        /// Indicates whether the current object represents the same Microsoft DirectSound device as the another one.
        /// </summary>
        /// <param name="other">An CloudObserver.Capture.DirectSound.DirectSoundCaptureDevice object to compare with this object.</param>
        /// <returns>true if the current object represents the same Microsoft DirectSound device as the another one; otherwise, false.</returns>
        public bool Equals(DirectSoundCaptureDevice other)
        {
            return driverGuid == other.driverGuid;
        }
    }
}
