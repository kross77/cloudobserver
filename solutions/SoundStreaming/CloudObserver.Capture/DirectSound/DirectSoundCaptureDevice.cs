using System;
using System.Collections.Generic;
using Microsoft.DirectX.DirectSound;

namespace CloudObserver.Capture.DirectSound
{
    /// <summary>
    /// Represents a sound capture device like a microphone or line-in.
    /// </summary>
    public struct DirectSoundCaptureDevice : IEquatable<DirectSoundCaptureDevice>
    {
        private string description;
        private Guid driverGuid;
        private string moduleName;

        /// <summary>
        /// Operating system default sound capture device.
        /// </summary>
        public static readonly DirectSoundCaptureDevice Default = new DirectSoundCaptureDevice("Default", Guid.Empty, "");

        /// <summary>
        /// Lists sound capture devices which are currently available in the operating system.
        /// </summary>
        public static IEnumerable<DirectSoundCaptureDevice> AllAvailable
        {
            get
            {
                CaptureDevicesCollection captureDevicesCollection = new CaptureDevicesCollection();
                foreach (DeviceInformation deviceInformation in captureDevicesCollection)
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

        public static bool operator ==(DirectSoundCaptureDevice device1, DirectSoundCaptureDevice device2)
        {
            return device1.Equals(device2);
        }

        public static bool operator !=(DirectSoundCaptureDevice device1, DirectSoundCaptureDevice device2)
        {
            return !(device1 == device2);
        }

        public bool Equals(DirectSoundCaptureDevice other)
        {
            return driverGuid == other.driverGuid;
        }

        public override bool Equals(object obj)
        {
            if (!(obj is DirectSoundCaptureDevice))
            {
                return false;
            }

            return base.Equals((DirectSoundCaptureDevice)obj);
        }

        public override int GetHashCode()
        {
            return driverGuid.GetHashCode();
        }

        public override string ToString()
        {
            return Description;
        }

        public DirectSoundCaptureDevice(string description, Guid driverGuid, string moduleName)
        {
            this.description = description;
            this.driverGuid = driverGuid;
            this.moduleName = moduleName;
        }
    }
}