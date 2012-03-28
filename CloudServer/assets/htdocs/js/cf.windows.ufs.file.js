$(document).ready(function() {
	var local_url =  location.href;
	$('body').append("<div class=\"hidden-c\" style=\"display: none;\"><!-- --><div id=\"tabs-ufs\" class=\"ufs\"><form method=\"POST\" id=\"ufs_form_upload\" enctype=\"multipart/form-data\" action=\"./ufs.service\"><input type=\"hidden\" name=\"redirect_location\" value=\""+local_url+"\"><input type=\"hidden\" class=\"f_type\" name=\"type\" value=\"none\"><fieldset><legend>Name:</legend><input type=\"text\" class=\"required\" name=\"file_name\" /></fieldset><fieldset><legend>Sharing settings:</legend><p><input type=\"radio\" name=\"is_public\" value=\"true\">Public</p><p><input type=\"radio\" name=\"is_public\" value=\"false\" checked>Private</p></fieldset><fieldset><legend>File:</legend><input type=\"file\" class=\"f_f\" name=\"datafile\"></fieldset><input type=\"submit\" class=\"eButton\" value=\"Upload\" /><input type=\"button\" class=\"eButton\" value=\"Cancel\" onClick=$(\".alert\").hide() /></form></div><!-- --></div>");
		
	$('.f_f').live('change', function(e){
		var file = $(this).val().toLowerCase();
		if(file.indexOf(".") != -1){
			var ext = file.split('.').pop();
			$('.f_type').val(ext);   
		}
	});
	
	$('#upload_button').mouseup(function() {
		showForm($("#tabs-ufs"), "Files upload form", 350, 295);
	});
});