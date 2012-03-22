$.wait = function( callback, seconds){
   return window.setTimeout( callback, seconds * 1000 );
}
$(window).load(function() {    
	$('body').prepend("<div id='bgFix' style='z-index:-1;  pointer-events:none; position: fixed; top: 0; left: 0; width: 100%; height: 100%;'><div>")
	var theWindow        = $(window),
	    $bg              = $("#bgFix"),
	    aspectRatio      = $bg.width() / $bg.height();

	function resizeBg() {

		if ( (theWindow.width() / theWindow.height()) < aspectRatio ) {
		    $bg
		    	.removeClass()
		    	.addClass('bgheight');
		} else {
		    $bg
		    	.removeClass()
		    	.addClass('bgwidth');
		}

	}

	theWindow.resize(function() {
		resizeBg();
	}).trigger("resize");

});
String.prototype.folderOf=function(no_slash){ 
	return this.slice(0,this.lastIndexOf('/',this.length-(/\/$/.test(this)?2:0))+(no_slash?0:1)) 
}; 

var user = null;
function readCookie(name) {
	var nameEQ = name + "=";
	var ca = document.cookie.split(';');
	for (var i = 0; i < ca.length; i++) {
		var c = ca[i];
		while (c.charAt(0) == ' ') c = c.substring(1, c.length);
		if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length, c.length);
	}
	return null;
}

// if error ,run it again.
function onerror(url, func){
	setTimeout(function(){getFromServer(url, func);},500);
}

function getJSONFromServer(url, func){
  $.getJSON(url, function(data) {
		  // Verify your data, if it's not you want run error function 
		  if(!data){ onerror(url, func); return; }
		  func(data);
  }).error(function() { onerror(url, func); });
}

(function($) {
	$.fn.extend({
		center: function() {
			return this.each(function() {
				var top = ($(window).height() - $(this).outerHeight()) / 2;
				var left = ($(window).width() - $(this).outerWidth()) / 2;
				$(this).css({
					position: 'absolute',
					margin: 0,
					top: (top > 0 ? top : 0) + 'px',
					left: (left > 0 ? left : 0) + 'px'
				});
			});
		}
	});
})(jQuery);

var page_update = page_update || {};
	page_update.functions = [];
	page_update.add = function(fn){
				  page_update.functions.push(fn);
				  page_update.run();
				};
	page_update.remove = function(fn){
					 page_update.functions.splice(page_update.functions.indexOf(fn), 1);
				   };
	page_update.run = function(){
				 $.each(page_update.functions, function(index, val){ 
					if (typeof val == "function") {
					  val.call(); 
				}
				  });
				};

function updateBodyWidth()
{
	$('body').css("width", "" + ($('html').width() ) + "px" );
}

$(document).ready(function() {
	$('body').append("<div id=\"cf-footer\" style='color:white; position:fixed;min-height:20px;height:auto !important;height:20px;background-color:#3f3b8d;background-color:rgba(4,4,0,0.9);bottom:0; width:100%;'><p id=\"cf-footer-paragraph\" style='font-size: 8pt'> Copyright &copy; 2012 <a id='rol' href='#cloudobserver' onclick=\"{	newwindow=window.open(\'http://code.google.com/p/cloudobserver/\',\'CloudObserver\',\'height=750,width=900\');	if (window.focus) {newwindow.focus()}}\">Cloud Forever</a>. Some rights reserved. </p><div>");

	$(".butt").live('mousedown', function(){
		$(this).addClass("hilight2");
	}).live('mouseup', function(){
		$(this).removeClass("hilight2");
	}).live('mouseover', function(){
		$(this).addClass("border2");
	}).live('mouseout', function(eventObj){
		$(this).removeClass("border2");
		$(this).removeClass("hilight2");
	});
	
	page_update.add(updateBodyWidth);
	
	$(window).bind('resize', function() {
		$('html', 'body').css("background-size", "cover");
		 page_update.run();
	});	
});

var _gaq = _gaq || [];
_gaq.push(['_setAccount', 'UA-21524436-1']);
_gaq.push(['_trackPageview']);

(function() {
	var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
	ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
	var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
})();