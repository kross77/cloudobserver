package
{
	import flash.display.Graphics;
	import flash.events.Event;
	import flash.events.IOErrorEvent;
	import flash.media.Sound;
	import flash.media.SoundChannel;
	import flash.media.SoundMixer;
	import flash.media.SoundTransform;
	import flash.net.URLRequest;
	import flash.utils.ByteArray;
	import mx.core.UIComponent;
	public class CloudSuperSound extends UIComponent
	{

		public function CloudSuperSound()
		{
			super();
			addEventListener(Event.ENTER_FRAME, onEnterFrame);
			channel.addEventListener(Event.SOUND_COMPLETE, onPlaybackComplete);
			snd.addEventListener(IOErrorEvent.IO_ERROR, errorfun);
		}
		[Bindable]
		public var channel:SoundChannel=new SoundChannel;

		[Bindable]
		public var snd:Sound=new Sound();

		public function startfun(urlstr:String):void
		{
			stopfun();
			var req:URLRequest=new URLRequest(urlstr);
			snd=new Sound();
			snd.load(req);
			channel=snd.play();
			snd.addEventListener(IOErrorEvent.IO_ERROR, errorfun);
		}

		public function stopfun():void
		{
			SoundMixer.stopAll();
		}

		public function volumefun(volnumber:Number):void
		{
			var transform:SoundTransform=new SoundTransform(volnumber, 0);
			channel.soundTransform=transform;
		}


		private function errorfun(e:IOErrorEvent):void
		{
			stopfun();
		}

		private function onEnterFrame(event:Event):void
		{
			var bytes:ByteArray=new ByteArray();
			const PLOT_HEIGHT:int=200;
			const CHANNEL_LENGTH:int=256;

			SoundMixer.computeSpectrum(bytes, false, 0);

			var g:Graphics=this.graphics;

			g.clear();

			g.lineStyle(0, 0x6600CC);
			g.beginFill(0x6600CC);
			g.moveTo(0, PLOT_HEIGHT);

			var n:Number=0;

			for (var i:int=0; i < CHANNEL_LENGTH; i++)
			{
				n=(bytes.readFloat() * PLOT_HEIGHT);
				g.lineTo(i * 2, PLOT_HEIGHT - n);
			}

			g.lineTo(CHANNEL_LENGTH * 2, PLOT_HEIGHT);
			g.endFill();

			g.lineStyle(0, 0xCC0066);
			g.beginFill(0xCC0066, 0.5);
			g.moveTo(CHANNEL_LENGTH * 2, PLOT_HEIGHT);

			for (i=CHANNEL_LENGTH; i > 0; i--)
			{
				n=(bytes.readFloat() * PLOT_HEIGHT);
				g.lineTo(i * 2, PLOT_HEIGHT - n);
			}

			g.lineTo(0, PLOT_HEIGHT);
			g.endFill();
		}

		private function onPlaybackComplete(event:Event):void
		{
			removeEventListener(Event.ENTER_FRAME, onEnterFrame);
		}
	}
}
