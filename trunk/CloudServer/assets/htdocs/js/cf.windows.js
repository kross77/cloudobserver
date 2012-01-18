var prepareWindow_called = 0;

function prepareWindow()
{
	if(prepareWindow_called == 0)
	{
		$('.alert').remove();
		$('body').append("<div class=\"alert\"><div class=\"overlay\"></div><div id=\"demo4_box\" class=\"box message nifty\" data-minwidth=\"75\" data-minheight=\"50\"><div class=\"handle bar\" id=\"alert_name\"><h2 class=\"handle bar\">Handle</h2></div><div class=\"contents\" id=\"alert_content\"><h1>demo box</h1></div><div class=\"handle resize\"></div></div></div></div></div>");
	
		$(".resize").bind('dragstart', function(event) {
			var $box = $(this).closest(".box");
	
			$box.data("width", $box.width());
			$box.data("height", $box.height());
			$box.data("x", event.offsetX);
			$box.data("y", event.offsetY);
	
		}).bind("drag", function(event) {
			var $box = $(this).closest(".box");
	
			$box.width(Math.max($box.data("width") - $box.data("x") + event.offsetX, $box.data("minwidth")));
			$box.height(Math.max($box.data("height") - $box.data("y") + event.offsetY, $box.data("minheight")));
		});
		
		$('#demo4_box').bind('dragstart', function(event) {
			return $(event.target).is('.handle');
		}).bind('drag', function(event) {
			$(this).css({
				top: event.offsetY,
				left: event.offsetX
			});
		});
		prepareWindow_called = 1;
	}
}

function showAlert(w, h, name, body_text) {
	prepareWindow();
	$("#alert_name").html(name);
	$("#alert_content").html(body_text);
	$(".box").width = w;
	$(".box").height = h;
	$(".alert").show();
}

function showForm(sourceElement, PopupName, w, h) {
	prepareWindow();
	$("#alert_name").html(PopupName);
	$("#alert_content").html(sourceElement.html());
	$(".alert").show();
	$("#demo4_box").width(w);
	$("#demo4_box").height(h);
	$('#demo4_box').center();
	$(window).bind('resize', function() {
		$(".alert").zindex('up');
		$('#demo4_box').center();
	});
}

function doStuff() {
	showAlert(200, 50, '<h2 class="handle bar">Alert</h2>', '<div onClick=$(".alert").hide()><h1>Contents</h1><h3>click to hide alert</h3></div>');
}