$(document).ready(function() {
	$('body').append("<div class=\"not-loged-in-user\" style=\" text-align:center; position:fixed; top:0; min-width:500px;\"><a style=\"text-decoration:none;\"><p id=\"login_button\" class=\"butt\">Log In!</p></a><div class=\"log-in-buttons-space\" style=\"display:inline-block; \"> </div><a style=\"text-decoration:none;\"><p id=\"register_button\" class=\"butt\">Register!</p></a></div><br/>");

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
	
	$('#login_button').mouseup(function() {
		showForm($("#tabs-login"), "Login  form", 350, 205);

	});

	$("#register_button").mouseup(function() {
		showRegisterForm();
	});
});