var register_Window_Created = 0;
var register_Window_ID = 0;
var register_html = "";
var recapcha_public_key = "";

var login_Window_Created = 0;
var login_Window_ID = 0;
var login_html = "";

function prepareLogInAndRegisterWindows()
{

	$('#recaptcha_widget').hide();
	prepareWindowWithStaticObject(register_Window_ID, register_Window_Created, register_html, "Register  form");
	prepareWindowWithStaticObject(login_Window_ID, login_Window_Created, login_html, "Login  form");
	
	Recaptcha.create(recapcha_public_key,"recaptcha_widget", {
			        theme: 'custom', 
			         custom_theme_widget: 'recaptcha_widget'
	});
	Recaptcha.get_challenge();
	
	
	$('.recap_get_audio').mouseup(function() {
		Recaptcha.switch_type('audio');
		//$.wait( function(){showRegisterForm(); }, 1);
	});
	$('.recaptcha_audio_cant_hear_link').mouseup(function() {
		Recaptcha.playAgain();
		//$.wait( function(){showRegisterForm(); }, 1);
	});
	$('.recap_get_image').mouseup(function() {
		Recaptcha.switch_type('image');
		//$.wait( function(){showRegisterForm(); }, 1);
	});
	$('.recap_get_help').mouseup(function() {
		Recaptcha.showhelp();
	});
	$('.recap_get_another_image').mouseup(function() {
		Recaptcha.reload();
		//$.wait( function(){showRegisterForm(); }, 1);
	});
	
	$("#register").validate();
	$("#login").validate();

	$('.pass_value').live('blur',function() {
	$('.hidden_pass_value').val($.sha256($(this).val()));
	}).live('keyup', function () {
		var value = $(this).val();
		$('.hidden_pass_value').val($.sha256(value));
	});
	
	register_Window_Created = 1;
	login_Window_Created = 1;
	
	$('#recaptcha_widget').show();

}

function showRegisterForm()
{
	if(register_Window_Created == 0)
	{
		prepareLogInAndRegisterWindows();
	}
	
	showStaticForm(register_Window_ID,430, 390);
}

function showLogInForm()
{
	if(login_Window_Created == 0)
	{
		prepareLogInAndRegisterWindows();
	}
	
	showStaticForm(login_Window_ID,440,205);
}

$(document).ready(function() {
	
	var ran_unrounded_login_alert=Math.random()*50000;
	var ran_number_login_alert=Math.floor(ran_unrounded_login_alert);
	
	login_Window_ID = ran_number_login_alert;
	
	var login_alert = "alert" + ran_number_login_alert;
	var class_login_alert = '.' + login_alert;
	
	login_html = "<div id=\"tabs-login\" class=\"login\"><form id=\"login\"  action=\"./ufs.service\" ><input type=\"hidden\" name=\"redirect_to\" value=\""+location.href+"\"><input type=\"hidden\" name=\"user_control\" value=\"login\"><fieldset><legend>Email:</legend><input type=\"text\" class=\"required email\" name=\"login\" /></fieldset><fieldset><legend>Password:</legend><input type=\"hidden\" name=\"pass\" class=\"hidden_pass_value\" value=\"\"/><input type=\"password\" class=\"required pass_value\" /></fieldset><input type=\"submit\" class=\"eButton\" value=\"Submit\" /><input type=\"button\" class=\"eButton\" value=\"Cancel\" onClick=\'$(\""+ class_login_alert + "\").hide();\' /></form></div><!-- -->";
	
	var ran_unrounded_register_alert=Math.random()*50000;
	var ran_number_register_alert=Math.floor(ran_unrounded_register_alert);
	
	register_Window_ID = ran_number_register_alert;
	
	var register_alert = "alert" + ran_number_register_alert;
	var class_register_alert = '.' + register_alert;
	
	recapcha_public_key = "6LdRhsYSAAAAAAOG1BVM0qPtVtACn4IgU1DeQcJX";
	
	register_html = "<div id=\"tabs-register\" class=\"register\"><form id=\"register\" action=\"./ufs.service\"><input type=\"hidden\" name=\"redirect_to\" value=\""+location.href+"\"><input type=\"hidden\" name=\"user_control\" value=\"register\"><fieldset><legend>Email:</legend><input type=\"text\" class=\"required email\" name=\"register\" /></fieldset><fieldset><legend>Password:</legend><input type=\"hidden\" name=\"pass\" class=\"hidden_pass_value\" value=\"\"/><input type=\"password\" class=\"required pass_value\" /></fieldset><fieldset><legend>Captcha</legend><div id=\"content\" style=\"font-size: 10pt; \"><div id=\"recaptcha_widget\" style=\"\"><div style=\" width:300px; x:0px; y:0px;\"><div id=\"recaptcha_image\"></div><span class=\"recaptcha_only_if_image\">Enter the words above:<br/></span><span class=\"recaptcha_only_if_audio\">Type what you hear:<br/></span></div><div style=\" width:320px; font-size: 8pt; display:inline-block; y:100%; x:0px; \"><input name=\"recaptcha_response_field\" style=\"width:100%;\" id=\"recaptcha_response_field\" type=\"text\" autocorrect=\"off\" autocapitalize=\"off\" autocomplete=\"off\"><br/><a style=\"text-decoration:none;\"><p class=\" recaptcha_only_if_image butt recap_get_another_image\">Get another image</p></a><a style=\"text-decoration:none;\"><p class=\" recaptcha_only_if_image butt recap_get_audio\">Get an audio.</p></a><a style=\"text-decoration:none;\"><p class=\" recaptcha_only_if_audio butt recap_get_image\">Get an image</p></a><a style=\"text-decoration:none;\"><p class=\"butt recap_get_help\">CAPTCHA Help</p></a></div></div></div></fieldset><input type=\"submit\" class=\"eButton\" value=\"Submit\" /><input type=\"button\" class=\"eButton\" value=\"Cancel\" onClick=\'{Recaptcha.reload();$(\"" + class_register_alert + "\").hide();}\' /></form></div><div id=\"recap\"></div><div id=\"recap2\"></div><script></script><!-- -->";
	
});