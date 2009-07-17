/**
 * ArrayOfint.as
 * This file was auto-generated from WSDL by the Apache Axis2 generator modified by Adobe
 * Any change made to this file will be overwritten when the code is re-generated.
 */
package generated.webservices
{
	import mx.utils.ObjectProxy;
	import mx.collections.ArrayCollection;
	import mx.collections.IList;
	import mx.collections.ICollectionView;
	import mx.rpc.soap.types.*;
	/**
	 * Typed array collection
	 */

	public class ArrayOfint extends ArrayCollection
	{
		/**
		 * Constructor - initializes the array collection based on a source array
		 */
        
		public function ArrayOfint(source:Array = null)
		{
			super(source);
		}
        
        
		public function addNumberAt(item:Number,index:int):void 
		{
			addItemAt(item,index);
		}

		public function addNumber(item:Number):void 
		{
			addItem(item);
		} 

		public function getNumberAt(index:int):Number 
		{
			return getItemAt(index) as Number;
		}

		public function getNumberIndex(item:Number):int 
		{
			return getItemIndex(item);
		}

		public function setNumberAt(item:Number,index:int):void 
		{
			setItemAt(item,index);
		}

		public function asIList():IList 
		{
			return this as IList;
		}
        
		public function asICollectionView():ICollectionView 
		{
			return this as ICollectionView;
		}
	}
}
