$.wait = function( callback, seconds){
   return window.setTimeout( callback, seconds * 1000 );
}
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
                };
    page_update.remove = function(fn){
                     page_update.functions.splice(page_update.functions.indexOf(fn), 1);
                   };
    page_update.run = function(){
                  page_update.functions.forEach(function(cb){ 
                    if (typeof cb == "function") {
                      cb.call(); 
                    }
                  });
                };

$(document).ready(function() {
	$('body').append("<div id=\"cf-footer\" style='position:fixed;min-height:20px;height:auto !important;height:20px;background-color:#3f3b8d;background-color:rgba(0,0,0,0.6);bottom:0; width:100%'><p id=\"cf-footer-paragraph\" style='font-size: 8pt'> Copyright &copy; 2012 <a id='rol' href='#cloudobserver' onclick=\"{	newwindow=window.open(\'http://code.google.com/p/cloudobserver/\',\'CloudObserver\',\'height=750,width=900\');	if (window.focus) {newwindow.focus()}}\">Cloud Forever</a>. Some rights reserved. </p><div>");

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

	var _gaq = _gaq || [];
	_gaq.push(['_setAccount', 'UA-21524436-1']);
	_gaq.push(['_setDomainName', 'none']);
	_gaq.push(['_setAllowLinker', true]);
	_gaq.push(['_trackPageview']);

	(function()
	{
		var ga = document.createElement('script');
		ga.type = 'text/javascript';
		ga.async = true;
		ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
		var s = document.getElementsByTagName('script')[0];
		s.parentNode.insertBefore(ga, s);
	})();
	_gaq.push(['_setCustomVar', 1, // This custom var is set to slot #1
	'URL', // The name acts as a kind of category for the user activity
	window.location.toString(), // This value of the custom variable
	1]);
	_gaq.push(['_trackEvent', 'Visit on page', // category of activity
	window.location.toString() // Action
	]);
	
	$(window).bind('resize', function() {
		$('html', 'body').css("background-size", "cover");
		 page_update.run();
	});	
});