using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AviLib
{
    public class AviFile
    {
        private int fileID;
        public int FileID
        {
            get { return fileID; }
        }

        private string fileName;
        public string FileName
        {
            get { return fileName; }
        }

        private AviFile(int fileID, string fileName)
        {
            this.fileID = fileID;
            this.fileName = fileName;
        }

        public static AviFile CreateFile(string fileName)
        {
            int fileID = 0;
            if (0 != AviWrapper.AVIFileOpen(ref fileID, fileName, AviWrapper.OF_WRITE | AviWrapper.OF_CREATE, 0))
            {
                return null;
            }
            return new AviFile(fileID, fileName);
        }

        public void CloseFile()
        {
            //TODO clear id and file name
            AviWrapper.AVIFileRelease(fileID);
        }
        
    }
}
