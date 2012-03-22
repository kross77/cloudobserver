function showUpdate(fileEU, name) {
	$("#tabs-ufs-update-file_eu").html(fileEU);
	$("#tabs-ufs-update-file_name").html(name);
	showForm($("#tabs-ufs-update"), "Files update form", 350, 295);
}

function showEdit(ue, name) {
	showUpdate("eu", "name");
}

$(document).ready(function() {

	var local_url =  location.href;
	$('body').append("<div class=\"hidden-c\" style=\"display: none;\"><!-- --><div id=\"tabs-ufs\" class=\"ufs\"><form method=\"POST\" id=\"ufs_form_upload\" enctype=\"multipart/form-data\" action=\"./ufs.service\"><input type=\"hidden\" name=\"redirect_location\" value=\""+local_url+"\"><input type=\"hidden\" class=\"f_type\" name=\"type\" value=\"none\"><fieldset><legend>Name:</legend><input type=\"text\" class=\"required\" name=\"file_name\" /></fieldset><fieldset><legend>Sharing settings:</legend><p><input type=\"radio\" name=\"is_public\" value=\"true\">Public</p><p><input type=\"radio\" name=\"is_public\" value=\"false\" checked>Private</p></fieldset><fieldset><legend>File:</legend><input type=\"file\" class=\"f_f\" name=\"datafile\"></fieldset><input type=\"submit\" class=\"eButton\" value=\"Upload\" /><input type=\"button\" class=\"eButton\" value=\"Cancel\" onClick=$(\".alert\").hide() /></form></div><!-- --><div id=\"tabs-ufs-update\" class=\"ufs\"><form method=\"POST\" id=\"ufs_form_upload\" enctype=\"multipart/form-data\" action=\"./ufs.service\"><input type=\"hidden\" name=\"redirect_location\" value=\""+local_url+"\"><input type=\"hidden\" class=\"f_type\" name=\"type\" value=\"none\"><input type=\"hidden\" id=\"tabs-ufs-update-file_eu\" name=\"tabs-ufs-update-file_eu\" value=\"sha256.user.file\"><fieldset><legend>Name:</legend><input type=\"text\" class=\"required\" id=\"tabs-ufs-update-file_name\" name=\"file_name\"/></fieldset><fieldset><legend>Sharing settings:</legend><p><input type=\"radio\" name=\"is_public\" value=\"true\">Public</p><p><input type=\"radio\" name=\"is_public\" value=\"false\" checked>Private</p></fieldset><fieldset><legend>New File:</legend><input type=\"file\" class=\"f_f\" name=\"datafile\"></fieldset><input type=\"submit\" class=\"eButton\" value=\"Upload\" /><input type=\"button\" class=\"eButton\" value=\"Cancel\" onClick=$(\".alert\").hide() /></form></div><!-- --></div>");
	
	$('.f_f').live('change', function(e){
		  var file = $(this).val();
		  var ext = file.split('.').pop().toLowerCase();
		$('.f_type').val(ext);   
	});
	
	$('#alert_button').mouseup(function() {
		showUpdate("eu", "name");
	});
	
	$('#upload_button').mouseup(function() {
		showForm($("#tabs-ufs"), "Files upload form", 350, 295);
	});
});