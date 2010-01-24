<?php

class Index {
	public function __construct(){}
	static function main() {
		haxe_Log::trace("Hello World !", _hx_anonymous(array("fileName" => "Index.hx", "lineNumber" => 14, "className" => "Index", "methodName" => "main")));
	}
	function __toString() { return 'Index'; }
}
