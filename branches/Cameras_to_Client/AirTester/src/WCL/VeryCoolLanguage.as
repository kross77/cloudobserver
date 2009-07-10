package WCL
{  
	 import flash.media.Camera;
	 import flash.media.Video;
	 
	 import mx.containers.Canvas;
	 import mx.core.UIComponent;
    
	public class VeryCoolLanguage extends Canvas
	{
	 protected var _cameraName:String;
	 
	 protected var _videoHolder:UIComponent = new UIComponent();
 	 
 	 protected var _video:Video;
    
     protected var _camera:Camera;
     
     
        //camera
          public function set cameraName(c:String):void {
            _cameraName = c;
            invalidateSize();
	       	invalidateDisplayList();
            
            }
          
        
           public function set camera(ca:Camera):void {
            _camera = ca;
            invalidateSize();
	       	invalidateDisplayList();
          
        }
        public function get cameraName():String {
            return _cameraName;
        }
        
        
        	public function VeryCoolLanguage()
		{	
			super();
	   _video = new Video(this.width ,this.height);
         _camera = Camera.getCamera(cameraName);
 	        _video.attachCamera(_camera);                
 	        _videoHolder.addChild(_video);
 	        this.addChild(_videoHolder);
		}
		
		
	}
}