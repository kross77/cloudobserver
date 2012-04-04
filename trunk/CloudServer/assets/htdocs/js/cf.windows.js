var prepareWindow_called = 0;


function windowsBase(id)
{
		var alert = "alert" + id;
		var class_alert = '.' + alert;
		var id_alert_name = "#" + alert + "_name";
		var id_alert_content = "#" + alert + "_content";
		
		var demo_box = "demo_box" + id;
		var id_demo_box = '#' + demo_box;
		
		$(class_alert).remove();
		var html_alert_text = "<div class=\"" + alert + "\" style=\"display: none;\"><div class=\"overlay\"></div><div id=\""+ demo_box +"\" class=\"box message nifty\" data-minwidth=\"75\" data-minheight=\"50\"><div class=\"handle bar\" id=\""+ alert +"_name\"><h2 class=\"handle bar\">Handle</h2></div><div class=\"contents\" id=\"" + alert + "_content\"><h1>demo box</h1></div><div class=\"handle resize\" style=\"position: absolute;\"></div></div></div></div></div>";
		$('body').append(html_alert_text);
	
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
		
		$(id_demo_box).bind('dragstart', function(event) {
			return $(this).closest('.handle');
		}).bind('drag', function(event) {
			$(this).css({
				top: event.offsetY,
				left: event.offsetX
			});
		});
		
	$(window).bind('resize', function() {
		$(id_demo_box).center();
	});
}

function hideDialog(dialog)
{
	dialog.hide();
}

function prepareWindow()
{
	if(prepareWindow_called == 0)
	{
		windowsBase("");
		prepareWindow_called = 1;
	}
}

function showAlertBase(w, h, name)
{
	prepareWindow();
	$("#alert_name").html(name);
	$(".alert").show();
	$("#demo_box").width(w);
	$("#demo_box").height(h);
	$('#demo_box').center();
	$(window).bind('resize', function() {
		$('#demo_box').center();
	});
}

function showAlert(w, h, name, body_text)
{
	prepareWindow();
	$("#alert_content").html(body_text + '<br/>' + '<input type=\"button\" class=\"eButton\" value=\"OK\" onClick=$(\".alert\").hide() />');
	showAlertBase(w, h, name);
}

function showAlertWithCallback(w, h, name, body_text, functionToCallOnOk) {
	prepareWindow();
	var ran_alert_number=Math.floor(Math.random()*50000);
	$("#alert_content").html(body_text + '<br/>' + '<input type=\"button\" class=\"eButton\" value=\"Cancel\" onClick=$(\".alert\").hide() />' + '<input id=\"general-alert-'+ ran_alert_number +'\" type=\"button\" class=\"eButton\" value=\"OK\" onClick=\"$(\'.alert\').hide();\"/>');
	$('#general-alert-' + ran_alert_number).click(function(){functionToCallOnOk();});
	showAlertBase(w, h, name);
}

function showForm(sourceElement, PopupName, w, h) {
	prepareWindow();
	$("#alert_name").html(PopupName);
	$("#alert_content").html(sourceElement.html());
	$(".alert").show();
	$("#demo_box").width(w);
	$("#demo_box").height(h);
	$('#demo_box').center();
	$(window).bind('resize', function() {
		$('#demo_box').center();
	});
}

function prepareWindowWithStaticObject(id, flag, html_code, PopupName)
{	
	windowsBase(id);
	
	var alert = "alert" + id;
	var id_alert_name = "#" + alert + "_name";
	var id_alert_content = "#" + alert + "_content";
	
	$(id_alert_content).html(html_code);
	$(id_alert_name).html(PopupName);
	
	flag = 1;
	
}

function showStaticForm(id, w, h) {
	var alert = "alert" + id;
	var class_alert = '.' + alert;
	var id_alert_name = "#" + alert + "_name";
	var id_alert_content = "#" + alert + "_content";
	
	var demo_box = "demo_box" + id;
	var id_demo_box = '#' + demo_box;

	$(class_alert).show();
	$(id_demo_box).width(w);
	$(id_demo_box).height(h);
	$(id_demo_box).center();
	$(window).bind('resize', function() {
		$(id_demo_box).center();
	});
}

function doStuff() {
	showAlert(200, 50, '<h2 class="handle bar">Alert</h2>', '<div onClick=$(".alert").hide()><h1>Contents</h1><h3>click to hide alert</h3></div>');
}