/**
 * GroupGetRegistrationDateResultEvent.as
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
    
	public class GroupGetRegistrationDateResultEvent extends Event
	{
		/**
		 * The event type value
		 */
		public static var GroupGetRegistrationDate_RESULT:String="GroupGetRegistrationDate_result";
		/**
		 * Constructor for the new event type
		 */
		public function GroupGetRegistrationDateResultEvent()
		{
			super(GroupGetRegistrationDate_RESULT,false,false);
		}
        
		private var _headers:Object;
		private var _result:Date;
		public function get result():Date
		{
			return _result;
		}

		public function set result(value:Date):void
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