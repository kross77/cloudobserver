package org.bytearray.video.events
{
	import flash.events.Event;
	import org.bytearray.video.FLVSlice;
	
	public final class MergedEvent extends Event
	{
		public var time:Number;
		public var slice:FLVSlice;
		
		public static const COMPLETE:String = "mergeComplete";
		
		public function MergedEvent(type:String, slice:FLVSlice, duration:Number)
		{
			super(type, false, false);
			this.slice = slice;
			this.time = duration;
		}
		
		public override function toString ():String
		{	
			return "[MergedEvent duration="+time+"]";	
		} 
	}
}