/*
  ^    ^    ^    ^    ^    ^    ^    ^    ^  
 /F\  /L\  /V\  /S\  /l\  /i\  /c\  /e\  /r\ 
<___><___><___><___><___><___><___><___><___>

* Copyright (c) 2009 Thibault Imbert
*
* This program is distributed under the terms of the MIT License as found 
* in a file called LICENSE. If it is not present, the license
* is always available at http://www.opensource.org/licenses/mit-license.php.
*
* This program is distributed in the hope that it will be useful, but
* without any waranty; without even the implied warranty of merchantability
* or fitness for a particular purpose. See the MIT License for full details.
*/

/**
 * This library lets you slice an FLV file with the Adobe Flash Player 10. FLVSlicer also allows you to extract audio or video only from an FLV.
 * Since version 0.3, the merge method() allows you to merge multiple FLVSlice objects into a single FLV stream.
 * @version 0.6
 * @url http://code.google.com/p/flvslicer/
 * @url http://bytearray.org
 */
	
package org.bytearray.video 
{
	import flash.events.Event;
	import flash.events.EventDispatcher;
	import flash.events.IEventDispatcher;
	import flash.utils.ByteArray;
	
	import org.bytearray.video.events.MergedEvent;
	import org.bytearray.video.events.SlicedEvent;
	import org.bytearray.video.tags.Tag;
	
	/**
	 * Dispatched when the FLV slice has been cutted
	 *
	 * @eventType SlicedEvent.COMPLETE
	 *
	 * * @example
	 * This example shows how to listen for such an event :
	 * <div class="listing">
	 * <pre>
	 *
	 * mySlicer.addEventListener ( SlicedEvent.COMPLETE, onTrimmed );
	 * </pre>
	 * </div>
	 */
	[Event(name='sliceComplete', type='SlicedEvent')]
	
	/**
	 * Dispatched when the FLV slices have been merged
	 *
	 * @eventType MergedEvent.COMPLETE
	 *
	 * * @example
	 * This example shows how to listen for such an event :
	 * <div class="listing">
	 * <pre>
	 *
	 * mySlicer.addEventListener ( MergedEvent.COMPLETE, onMerged );
	 * </pre>
	 * </div>
	 */
	[Event(name='mergeComplete', type='MergedEvent')]
	
	public class FLVSlicer implements IEventDispatcher
	{
		public var input:ByteArray;
		private var metaData:ByteArray = new ByteArray();
		
		private var _slice:ByteArray = new ByteArray();
		private var _sound:ByteArray = new ByteArray();
		private var _video:ByteArray = new ByteArray();
		
		private var slices:Vector.<FLVSlice>;
		
		private var memory:int;
		private var signature:String;
		private var version:int;
		private var typeFlagsReserved1:int;
		private var typeFlagsReserved2:int;
		private var typeFlagsAudio:int;
		private var typeFlagsVideo:int;
		private var dataOffset:int;
		
		private var startTag:Tag;
		private var endTag:Tag;
		
		private var dispatcher:EventDispatcher;
		
		private var seekableFramesDictionary:Vector.<Tag> = new Vector.<Tag>();
		private var framesDictionary:Vector.<Tag> = new Vector.<Tag>();
		
		private static const AUDIO_TAG:int = 0x08;
		private static const VIDEO_TAG:int = 0x09;
		private static const SCRIPT_TAG:int = 0x12;
		private static const SECOND_TAG:int = 0xD;
		private static const SIGNATURE:String = "FLV";
		
		private static const SHORT:int = 0x3;
		private static const METADATA:String = "onMetaData";
		private static const DURATION:String = "duration";
		
		/**
		 * An FLVSlice object.
		 * @param streamщ
		 * 
		 */		
		public function FLVSlicer( stream:ByteArray )
		{
			dispatcher = new EventDispatcher(this);
			init( stream );
		}
		
		private function init ( buffer:ByteArray ):void
		{
			input = buffer;
			input.position = 0;
			signature = input.readUTFBytes(3);
			if ( signature != FLVSlicer.SIGNATURE ) throw new Error("Not a valid FLV file!.");
			version = input.readByte();
			var infos:int = input.readByte();
			typeFlagsReserved1 = (infos >> 3);
			typeFlagsAudio = ((infos & 0x4 ) >> 2);
			typeFlagsReserved2 = ((infos & 0x2 ) >> 1);
			typeFlagsVideo = (infos & 0x1);
			dataOffset = input.readUnsignedInt();
			input.position += 4;
			
			var currentPos:int = input.position;
	
			_slice.writeBytes(input, 0, currentPos );
			_sound.writeBytes(input, 0, currentPos );
			_video.writeBytes(input, 0, currentPos );
			
			var offset:int; 
			var end:int;
			var tagLength:int;
			var currentTag:int;
			var step:int;
			var fb:int;
			var time:int;
			var keyframe:int;
			var timestampExtended:int;
			var streamID:int;
			var soundFormat:int;
			var soundRate:int;
			var soundSize:int;
			var soundType:int;
			var codecID:int;
			var frameTag:Tag;
			
			while ( input.bytesAvailable > 0 )
			{		
				offset = input.position; 
				currentTag = input.readByte();
				step = (input.readUnsignedShort() << 8) | input.readUnsignedByte();
				time = (input.readUnsignedShort() << 8) | input.readUnsignedByte();
				timestampExtended = input.readUnsignedByte();
				streamID = ((input.readUnsignedShort() << 8) | input.readUnsignedByte());
				fb = input.readByte();
				end = input.position + step + 3;
				tagLength = end-offset;
				
				if ( currentTag == FLVSlicer.AUDIO_TAG ) 
				{
					soundFormat = (fb & 0xF0) >> 4;
					soundRate = (fb & 0xC) >> 2;
					soundSize = (fb & 0x2) >> 1;
					soundType = (fb & 0x1);
					_sound.writeBytes(input, offset, tagLength);
					
				} else if ( currentTag == FLVSlicer.VIDEO_TAG )
				{
					keyframe = (fb & 0xF0) >> 4;
					codecID = (fb & 0xF0) >> 4;
					frameTag = new Tag ( time, offset );
					if ( keyframe == 1 ) seekableFramesDictionary.push ( frameTag );
				 	framesDictionary.push ( frameTag );
					_video.writeBytes(input, offset, tagLength);
					
				} else if ( currentTag == FLVSlicer.SCRIPT_TAG )
				{
					_slice.writeBytes(input, offset, tagLength);	
					_sound.writeBytes(input, offset, tagLength);	
					_video.writeBytes(input, offset, tagLength);
				}
				input.position = end;
			}
			memory = _slice.position;
		}
		
		/**
		 * Returns the full-length video only from the FLV
		 * @return ByteArray
		 * 
		 */		
		public function get video():ByteArray
		{
			return _video;
		}
		
		/**
		 * Returns the full-length audio track from the FLV
		 * @return ByteArray
		 * 
		 */		
		public function get sound():ByteArray
		{
			return _sound;
		}
		
		/**
		 * Slices the video with the specified starting time and ending time (in ms)
		 * @param start
		 * @param end
		 * 
		 */		
		public function slice ( start:int, end:int ):FLVSlice
		{
			if ( end <= start ) throw new Error ("End timing cannot be below or equal to starting time.");
			startTag = findTag(start);
			endTag = findTag(end, false);
			var startTime:Number = startTag.time;
			var endTime:Number = endTag.time;
			var duration:Number = endTime - startTime;
			_slice.length = memory;
			_slice.writeBytes(input, startTag.offset, endTag.offset-startTag.offset);
			updateMetaData(duration*.001);
			updateTimeStamp(_slice, startTime);
			var slice:FLVSlice = new FLVSlice ( _slice, duration );
			dispatchEvent( new SlicedEvent ( SlicedEvent.COMPLETE, slice, startTime, endTime ) );
			return slice;
		}
		
		/**
		 * Merges muliple FLVSlice objects into a single FLV stream.
		 * Make sure the different slices come from the same incoming FLV.
		 * @param slices
		 * 
		 */		
		public function merge( slices:Vector.<FLVSlice> ):FLVSlice
		{	
			if ( slices.length > 0 )
			{
				_slice.length = memory;
				var duration:Number = 0;
				var startTime:Number = 0;
				var bytes:ByteArray;
				var stream:ByteArray;
				for each ( var slice:FLVSlice in slices )
				{	
					stream = slice.stream;
					startTime += updateTimeStamp(stream, startTime, true);
					_slice.writeBytes(stream, memory);
					duration += slice.duration;
				}
				updateMetaData(duration*.001);
				slice = new FLVSlice ( _slice, duration );
				dispatchEvent( new MergedEvent ( MergedEvent.COMPLETE, slice, duration ) );
				return slice;
			}
			return null;
		}
		
		private function updateTimeStamp ( stream:ByteArray, starting:Number, merging:Boolean=false ):Number
		{
			stream.position = FLVSlicer.SECOND_TAG;
			
			var currentTag:int;
			var step:int;
			var time:Number;
			var newTimeStamp:Number;
			
			while ( stream.bytesAvailable > 0 )
			{	
				currentTag = stream.readByte();
				step = (stream.readUnsignedShort() << 8) | stream.readUnsignedByte();
				time = (stream.readUnsignedShort() << 8) | stream.readUnsignedByte();
				
				newTimeStamp = ( false == merging ) ? time - starting : time + starting;
				
				stream.position -= FLVSlicer.SHORT;
				
				if ( currentTag == FLVSlicer.VIDEO_TAG || currentTag == FLVSlicer.AUDIO_TAG )
				{
					stream.writeShort(newTimeStamp >> 8);
					stream.writeByte(newTimeStamp & 0xFF);
					
				} else if ( currentTag == FLVSlicer.SCRIPT_TAG )
				{
					stream.writeShort(0);
					stream.writeByte(0);
				}
				stream.position += step + 8;
			}
			return time;
		}
		
		private function updateMetaData(timing:Number):void
		{
			var pos:int = _slice.position;
			_slice.position = 25;
			var gap:int = _slice.readUnsignedShort();
			var objectName:String = _slice.readUTFBytes( gap );
			if ( objectName == FLVSlicer.METADATA )
			{	
				_slice.position += 5;
				gap = _slice.readUnsignedShort();
				objectName = _slice.readUTFBytes( gap );
				if ( objectName == FLVSlicer.DURATION )
				{
					_slice.position += 1;
					_slice.writeDouble(timing);
				} else throw new Error("Could not find duration field.");
			} else throw new Error("Could not find onMetaData tag.");
			_slice.position = pos;
		}
		
		private function findTag ( timing:int, seekable:Boolean=true ):Tag
		{	
			if ( seekableFramesDictionary.length )	
			{
				var firstTag:Tag = seekableFramesDictionary[0];
				var lastTag:Tag = seekableFramesDictionary[seekableFramesDictionary.length-1];
				var minTime:Number = firstTag.time;
				var maxTime:Number = lastTag.time;
				
				if ( seekable )
					if ( timing < minTime ) 
						return firstTag;
		
				if ( timing > lastTag.time ) 
					return lastTag;
			
				var previousItem:Tag;
				
				for each ( var item:Tag in seekable ? seekableFramesDictionary : framesDictionary )
				{
					if ( previousItem != null )
					{					
						if ( previousItem.time <= timing && item.time >= timing )
							return previousItem;
					}	
					previousItem = item;
				}
			} else throw new Error("Could not find any seekable frame as a starting point.");
			
			return null;
		}

		public function addEventListener( type:String, listener:Function, useCapture:Boolean=false, priority:int=0, useWeakReference:Boolean=false ):void
		{
			dispatcher.addEventListener( type, listener, useCapture, priority, useWeakReference );
		}
		
		public function dispatchEvent( event:Event ):Boolean
		{
			return dispatcher.dispatchEvent( event );
		}
		
		public function hasEventListener( type:String ):Boolean
		{
			return dispatcher.hasEventListener( type );
		}
		
		public function removeEventListener( type:String, listener:Function, useCapture:Boolean=false ):void
		{
			dispatcher.removeEventListener( type, listener, useCapture );
		}
		
		public function willTrigger( type:String ):Boolean
		{
			return dispatcher.willTrigger( type );
		}
	}
}