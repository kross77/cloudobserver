using System;
using System.IO;
using Microsoft.Win32;

namespace CloudObserver
{
    public class Settings
    {
        public const string RegistryPath = "Software\\Cloud Forever\\Cloud Observer";

        private static string installLocation = Directory.GetCurrentDirectory() + "/";
        private static string serverName = "Cloud Observer";
        private static ushort serverPort = 4773;
        private static uint maxStreams = 10;

        public static string InstallLocation
        {
            get
            {
                return installLocation;
            }
        }

        public static string ServerName
        {
            get
            {
                return serverName;
            }
        }

        public static ushort ServerPort
        {
            get
            {
                return serverPort;
            }
        }

        public static uint MaxStreams
        {
            get
            {
                return maxStreams;
            }
        }

        static Settings()
        {
            RegistryKey registryKey = Registry.LocalMachine.OpenSubKey(RegistryPath);
            if (registryKey == null)
            {
                registryKey = Registry.LocalMachine.CreateSubKey(RegistryPath);
                registryKey.SetValue("InstallLocation", installLocation);
                registryKey.SetValue("ServerName", serverName);
                registryKey.SetValue("ServerPort", (int)serverPort, RegistryValueKind.DWord);
                registryKey.SetValue("MaxStreams", (int)maxStreams, RegistryValueKind.DWord);
            }

            installLocation = (string)registryKey.GetValue("InstallLocation");
            serverName = (string)registryKey.GetValue("ServerName");
            serverPort = (ushort)(int)registryKey.GetValue("ServerPort");
            maxStreams = (uint)(int)registryKey.GetValue("MaxStreams");
        }
    }
}
