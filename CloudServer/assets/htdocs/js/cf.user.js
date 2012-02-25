function loged_in_user_div_position_update(){
	$('.loged-in-user').css("margin-top", "" + ($('.header').height() + 3) + "px" );
	$('.loged-in-user').css("width", "" + ($('html').width() -1 ) + "px" );
}

$(document).ready(function() {
	$('body').append("<div class=\"not-loged-in-user\" style=\" text-align:center; position:fixed; top:0; min-width:500px;width:auto !important;width:500px;\"><a style=\"text-decoration:none;\"><p id=\"login_button\" class=\"butt\">Log In!</p></a><div class=\"log-in-buttons-space\" style=\"display:inline-block; \"> </div><a style=\"text-decoration:none;\"><p id=\"register_button\" class=\"butt\">Register!</p></a><br/><div class=\"not-loged-in-user-error\"></div></div><br/><div style=\" text-align:center; position:fixed; top:0; min-width:500px;width:auto !important;width:500px;\" class=\"loged-in-user loged-in-user-error\"></div>");

	user = readCookie('session-id');
	if (user != null) {
		
		$('.loged-in-user').show();
		$('.not-loged-in-user').remove();
		//$('.loged-in-user').center();
		//page_update.add($('.loged-in-user').center());	
		} else {
		$('.not-loged-in-user').removeClass("hidden-c");

		$('.loged-in-user').remove();
		$('.not-loged-in-user').show();
		$('.not-loged-in-user').center();
		$(window).bind('resize', function() {
			$('.not-loged-in-user').center();
		});		
	}
	
	$('#login_button').mouseup(function() {
		showLogInForm();
	});

	$("#register_button").mouseup(function() {
		showRegisterForm();
	});
	
	$('.pseudo-no-js-heaser').remove();
	page_update.add(loged_in_user_div_position_update);
	
	//if($(window).width <= 500)
});