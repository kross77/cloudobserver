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


function showAlert(w, h, name, body_text) {
	$("#alert_name").html(name);
	$("#alert_content").html(body_text);
	$(".box").width = w;
	$(".box").height = h;
	$(".alert").show();
}

function showForm(sourceElement, PopupName, w, h) {
	$("#alert_name").html(PopupName);
	$("#alert_content").html(sourceElement.html());
	$(".alert").show();
	$("#demo4_box").width(w);
	$("#demo4_box").height(h);
	$('#demo4_box').center();
	$(window).bind('resize', function() {
		$('#demo4_box').center();
	});
}

function showUpdate(fileEU, name) {
	$("#tabs-ufs-update-file_eu").html(fileEU);
	$("#tabs-ufs-update-file_name").html(name);
	showForm($("#tabs-ufs-update"), "Files update form", 350, 295);

}

function showEdit(ue, name) {
	showUpdate("eu", "name");
}

function doStuff() {
	showAlert(200, 50, '<h2 class="handle bar">Alert</h2>', '<div onClick=$(".alert").hide()><h1>Contents</h1><h3>click to hide alert</h3></div>');
}

$(document).ready(function() {
$('body').append("<div style='position:fixed;min-height:20px;height:auto !important;height:20px;background-color:#3f3b8d;background-color:rgba(0,0,0,0.6);bottom:0; width:100%'><p style='font-size: 8pt'> Copyright &copy; 2012 <a id='rol' href='#cloudobserver' onclick=\"{	newwindow=window.open(\'http://code.google.com/p/cloudobserver/\',\'CloudObserver\',\'height=750,width=900\');	if (window.focus) {newwindow.focus()}}\">Cloud Forever</a>. All rights reserved. </p><div>");

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
});