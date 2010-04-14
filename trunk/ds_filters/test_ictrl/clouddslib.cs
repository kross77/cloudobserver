using System;
using System.Runtime.InteropServices;
using System.Security;

namespace CloudDirectShowLib
{
    [SuppressUnmanagedCodeSecurity]
    [Guid("80AE3F22-17DE-4d6c-BC3E-F2A38AFC53CC")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface ICloudInetControl
    {
        int SetAddress(out string pszAddress, int port);
    }
}
