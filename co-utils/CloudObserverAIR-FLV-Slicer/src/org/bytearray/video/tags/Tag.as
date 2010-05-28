package org.bytearray.video.tags
{	
	public final class Tag 
	{
		public var time:Number;
		public var offset:int;
		
		public function Tag( time:int, offset:int )
		{
			this.time = time;
			this.offset = offset;
		}
	}
}