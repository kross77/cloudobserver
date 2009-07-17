/**
 * GroupGetCamerasResultEvent.as
 * This file was auto-generated from WSDL
 * Any change made to this file will be overwritten when the code is re-generated.
*/
package generated.webservices
{
	import mx.utils.ObjectProxy;
	import flash.events.Event;
	import flash.utils.ByteArray;
	import mx.rpc.soap.types.*;
	/**
	 * Typed event handler for the result of the operation
	 */
    
	public class GroupGetCamerasResultEvent extends Event
	{
		/**
		 * The event type value
		 */
		public static var GroupGetCameras_RESULT:String="GroupGetCameras_result";
		/**
		 * Constructor for the new event type
		 */
		public function GroupGetCamerasResultEvent()
		{
			super(GroupGetCameras_RESULT,false,false);
		}
        
		private var _headers:Object;
		private var _result:ArrayOfint;
		public function get result():ArrayOfint
		{
			return _result;
		}

		public function set result(value:ArrayOfint):void
		{
			_result = value;
		}

		public function get headers():Object
		{
			return _headers;
		}

		public function set headers(value:Object):void
		{
			_headers = value;
		}
	}
}