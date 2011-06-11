	import mx.controls.Alert;	
	import cmodule.stringecho.CLibInit;
	public var u:String;
	public function Echo():void
	{
		u=ui.text.toLowerCase();
		var loader:CLibInit = new CLibInit;
		var lib:Object = loader.init();	
		Alert.show(lib.echo(u),'C++ library compiled via Alchemy returned:');
	}