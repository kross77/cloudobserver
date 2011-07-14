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
        private static string dumpsLocation = installLocation + "dumps/";
        private static bool dumpWriters = false;
        private static bool dumpReaders = false;

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

        public static string DumpsLocation
        {
            get
            {
                return dumpsLocation;
            }
        }

        public static bool DumpWriters
        {
            get
            {
                return dumpWriters;
            }
        }

        public static bool DumpReaders
        {
            get
            {
                return dumpReaders;
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
                registryKey.SetValue("DumpsLocation", dumpsLocation);
                registryKey.SetValue("DumpWriters", dumpWriters ? 1 : 0, RegistryValueKind.DWord);
                registryKey.SetValue("DumpReaders", dumpReaders ? 1 : 0, RegistryValueKind.DWord);
            }

            object temp = null;

            temp = registryKey.GetValue("InstallLocation");
            if (temp == null)
                registryKey.SetValue("InstallLocation", installLocation);
            else
                installLocation = (string)temp;

            temp = registryKey.GetValue("ServerName");
            if (temp == null)
                registryKey.SetValue("ServerName", serverName);
            else
                serverName = (string)temp;

            temp = registryKey.GetValue("ServerPort");
            if (temp == null)
                registryKey.SetValue("ServerPort", (int)serverPort, RegistryValueKind.DWord);
            else
                try
                {
                    serverPort = (ushort)(int)temp;
                }
                catch (Exception)
                {
                    registryKey.SetValue("ServerPort", (int)serverPort, RegistryValueKind.DWord);
                }

            temp = registryKey.GetValue("MaxStreams");
            if (temp == null)
                registryKey.SetValue("MaxStreams", (int)maxStreams, RegistryValueKind.DWord);
            else
                try
                {
                    maxStreams = (uint)(int)temp;
                }
                catch (Exception)
                {
                    registryKey.SetValue("MaxStreams", (int)maxStreams, RegistryValueKind.DWord);
                }

            temp = registryKey.GetValue("DumpsLocation");
            if (temp == null)
                registryKey.SetValue("DumpsLocation", dumpsLocation);
            else
                dumpsLocation = (string)temp;

            temp = registryKey.GetValue("DumpWriters");
            if (temp == null)
                registryKey.SetValue("DumpWriters", dumpWriters ? 1 : 0, RegistryValueKind.DWord);
            else
                try
                {
                    dumpWriters = ((int)temp != 0);
                }
                catch (Exception)
                {
                    registryKey.SetValue("DumpWriters", dumpWriters ? 1 : 0, RegistryValueKind.DWord);
                }

            temp = registryKey.GetValue("DumpReaders");
            if (temp == null)
                registryKey.SetValue("DumpReaders", dumpReaders ? 1 : 0, RegistryValueKind.DWord);
            else
                try
                {
                    dumpReaders = ((int)temp != 0);
                }
                catch (Exception)
                {
                    registryKey.SetValue("DumpReaders", dumpReaders ? 1 : 0, RegistryValueKind.DWord);
                }
        }
    }
}
