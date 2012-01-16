$(document).ready(function() {
	user = readCookie('session-id');
	if (user != null) {
		
		$('.loged-in-user').show();
		$('.not-loged-in-user').remove();
		} else {
		$('.not-loged-in-user').removeClass("hidden-c");

		$('.loged-in-user').remove();
		$('.not-loged-in-user').show();
		$('.not-loged-in-user').center();
		$(window).bind('resize', function() {
			$('.not-loged-in-user').center();
		});		
	}
	
	$('.f_f').live('change', function(e){
		  var file = $(this).val();
		  var ext = file.split('.').pop().toLowerCase();
		//  alert(ext);
		 // if((ext == 'png')||(ext == 'jpg')||(ext == 'jpeg'))
		//  {
		//	$('.f_type').val("image");
		//  }
	//	else
		//	{
				$('.f_type').val(ext);
		//	}  
		  
	});

	$('#demo4_box').bind('dragstart', function(event) {
		return $(event.target).is('.handle');
	}).bind('drag', function(event) {
		$(this).css({
			top: event.offsetY,
			left: event.offsetX
		});
	});

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


	$('#login_button').mouseup(function() {
		showForm($("#tabs-login"), "Login  form", 350, 205);

	});

	$("#register_button").mouseup(function() {
		
		showForm($("#tabs-register"), "Register  form",430, 380);

	});
	
	$('#alert_button').mouseup(function() {
		showUpdate("eu", "name");
	});

	$('#upload_button').mouseup(function() {
		showForm($("#tabs-ufs"), "Files upload form", 350, 295);
	});
	
	$("#register").validate();
	$("#login").validate();
	
	$('.pass_value').live('blur',function() {
		$('.hidden_pass_value').val($.sha256($(this).val()));
	}).live('keyup', function () {
	  var value = $(this).val();
	 $('.hidden_pass_value').val($.sha256(value));
	});
	
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
	
});