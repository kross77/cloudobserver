package org.bytearray.video
{
	import flash.utils.ByteArray;

	public final class FLVSlice
	{
		public var duration:Number;
		public var stream:ByteArray = new ByteArray();
		
		public function FLVSlice ( stream:ByteArray, duration:Number )
		{
			this.stream.writeBytes(stream);
			this.duration = duration;
		}
		
		public function toString ():String
		{
			return "[FLVSlice duration="+duration+" size="+stream.length+"]";	
		}
	}
}