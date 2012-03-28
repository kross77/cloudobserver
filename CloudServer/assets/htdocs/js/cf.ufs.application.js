var file_id;
var file_title;
var mfu_uploader_created = 0;
var mfu_html = "";
var fs;
function createUploaders(){
	prepareWindowWithStaticObject("mfu_tab", mfu_uploader_created, mfu_html, "Multiple Files upload form");
	var publicUploader = new qq.FileUploader({
			element: document.getElementById('fileUploader'),
			listElement: document.getElementById('separate-list'),
			action: './ufs.service',
			params: {
				action: 'upload'
		},
	onSubmit: function(id, fileName){
			this.params['is_public'] = $('#fuCheckbox').is(':checked');  
			if(fileName.indexOf(".") != -1){
				var uri = fileName.split('.');
				this.params['type'] = uri.pop().toLowerCase();  
				this.params['name'] = uri.pop();  
			}else{
				this.params['name'] = fileName;
			}
		},
	onComplete: function(id, fileName, responseJSON){
		ui.dialog("Uploaded "+ fileName +" !")
			.effect('slide')
			.show()
			.hide(1500);
		$.getJSON("ufs.json", function(data) {fs.render(data);});
	}
	});
}  

$(document).ready(function() {

	var files_menu = ui.menu()
	.add('Download item' , function(){ window.open(""+file_id, '_blank'); })
	.add('Get link' , function(){ showAlert( 600, 100 , ('link to ' + file_title + ' file.') , '<input type="text" style="width:590px" class="text" value=\"' + location.host + ('/'+file_id ) + '\">'); })
	.add('Delete item' , function(){ $.ajax({
		type: "GET",
		url:"ufs.service", 
		data: "action=delete&url="+file_id,
		success: function(data) {
			$.getJSON("ufs.json", function(data) {
				fs.render(data);
			});
		}
	});
});

	user = readCookie('session-id');
	if (user != null) {	
		$('.loged-in-user').show();
		$('.not-loged-in-user').remove();
		fs = Tempo.prepare('marx-brothers')
			.notify( function (event) {
				if (event.type === TempoEvent.Types.RENDER_COMPLETE) {
					$( "#marx-brothers" ).selectable({
						start: function(e, ui) { files_menu.hide(); },
						stop:  function(e, ui) {
							var selected_array = []
							$( "div.ui-selected > li > a > p", this ).each(function() {
							if (! $(this).parent('a').hasClass('ui-selected'))
							{
								$(this).parent('a').addClass('ui-selected');
							}
							
							var element = this; //$(this) .closest('a > p');
							selected_array = selected_array.concat( element );
			
							});
							if(selected_array.length == 1)
							{
								file_title = selected_array[0].title;
								file_id = selected_array[0].id;
								files_menu.moveTo(e.pageX, e.pageY).show();
							}
					}
				});
			}
		});
		
		$(document).click( function (){$(".ui-selected").removeClass("ui-selected");});
		
		fs.starting();
	
		$.getJSON("ufs.json", function(data) {
			fs.render(data);
		});
	}
	
	$('.butt2').live('click', function(e) {
		file_title = this.title;
		file_id = this.id;
		files_menu.moveTo(e.pageX, e.pageY).show();
	});
	
	mfu_html = "<div id=\"tabs-ufs-mfu\"><div id=\"fuForm\"><div id=\"fileUploader\"></div><form><input id=\"fuCheckbox\" type=\"checkbox\" name=\"mfucheckbox\" value=\"true\"/>Public<br /></form></div><ul id=\"separate-list\" ></ul><input type=\"button\" class=\"eButton\" value=\"Cancel\" onclick=\'hideDialog($(\".alertmfu_tab\"));$.getJSON(\"ufs.json\", function(data) {fs.render(data);});\'></div>";
	
	$('#upload_multiple_btton').mouseup(function() {
		if(mfu_uploader_created == 0){
			createUploaders();
		}
		showStaticForm("mfu_tab",200,150);
		center_by_width(".qq-upload-button", "#demo_boxmfu_tab"); 
	});
});