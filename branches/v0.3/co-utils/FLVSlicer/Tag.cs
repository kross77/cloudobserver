namespace CloudObserver.Utils.FLVSlicer
{
    public class FLVTag
    {
        public uint Timestamp;
		public long Offset;

        public FLVTag(uint timestamp, long offset)
        {
            Timestamp = timestamp;
            Offset = offset;
        }
    }
}
