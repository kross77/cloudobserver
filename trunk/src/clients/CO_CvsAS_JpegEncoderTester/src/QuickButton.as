package
{
	import flash.display.*;
	import flash.events.*;
	import flash.text.*;

	public class QuickButton extends Sprite
	{
		public function QuickButton(theText:String):void
		{
			graphics.beginFill(0xCCCCCC);
			graphics.drawRect(0, 0, 100, 30);
			var tf:TextField = new TextField();
			tf.y = 5;
			var format:TextFormat = new TextFormat();
			format.font = "Verdana";
			format.color = 0x000000;
			format.size = 12;
			format.align = "center";
			tf.defaultTextFormat = format;
			tf.selectable = false;
			tf.text = theText;
			tf.width = 100;
			addChild(tf);
		}
	}
}

