using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.ComTypes;
using DirectShowLib;

using CloudDirectShowLib;

namespace test_ictrl
{
    class GraphBuilder
    {
        //private IGraphBuilder graph;
        private Guid CLSID_CloudStreamRenderer = new Guid("{37AC047C-BED1-49ef-AB43-BB906A158DD6}");

        public GraphBuilder()
        {
            IBaseFilter cloudRenderer = (IBaseFilter)Activator.CreateInstance(Type.GetTypeFromCLSID(CLSID_CloudStreamRenderer));
            if (cloudRenderer == null)
                return;
            ICloudInetControl cloudCtrl = cloudRenderer as ICloudInetControl;
            if (cloudCtrl == null)
                return;
        }
    }
}
