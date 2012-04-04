var file_id;
var file_title;
var mfu_uploader_created = 0;
var mfu_html = "";
var fs;
var files_menu;
var selected_array = [];

function updateFilesList() {
			$.getJSON("./ufs.json", function(data) {
				fs.render(data);
			});
		}

function deleteMultipleFiles(){ 
	var local_selected_array = selected_array.slice(0);
	$('body').append($('<div class=\"overlay\"></div>'))
	ui.confirm('are you sure you want to remove ' + local_selected_array.length +' files?')
	.closable()
	.show(function(ok){
		$('.overlay').remove();
		if (ok) $.ajax({
			type: "POST",
			url: "ufs.service?action=delete", 
			data: local_selected_array.join(", "),
			success: updateFilesList
		});
	});
}
	
function deleteFile(){ 
	$('body').append($('<div class=\"overlay\"></div>'))
	ui.confirm('are you sure you want to remove ' + file_title +' file?')
	.closable()
	.show(function(ok){
		$('.overlay').remove();
		if (ok) $.ajax({
			type: "GET",
			url:"ufs.service?action=delete&url="+file_id,
			success: updateFilesList
		});
	});
}

function renameFile(){ 
	showAlertWithCallback( 600, 100 , ('New name for to ' + file_title + ' file.') , '<input type=\"text\" id=\"rename_text\" style=\"width:590px\" class=\"text\" value=\"' + file_title + '\">', function(){
		$.ajax({
			type: "GET",
			url:"ufs.service?action=rename&url="+file_id + "&name=" + $("#rename_text").attr("value") ,
			success: updateFilesList
		});
	});
}


function showFileUrlAlert(){
	showAlert( 600, 100 , ('link to ' + file_title + ' file.') , '<input type="text" style="width:590px" class="text" value=\"' + location.host + ('/'+file_id ) + '\">');
 }
 
 function downloadAFile(){
	 window.open(""+file_id, '_blank'); 
 }

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

	files_menu = ui.menu();
	//.add('Download item' , downloadAFile)
	//.add('Get link' , showFileUrlAlert)
	//.add('Delete item' , deleteFile)
	//.add('Delete items' , deleteMultipleFiles);
	//.add('Rename item' , renameFile);

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
							selected_array = [];
							var titles_array = [];
							$( "div.ui-selected > li > a > p", this ).each(function() {
							if (! $(this).parent('a').hasClass('ui-selected'))
							{
								$(this).parent('a').addClass('ui-selected');
							}

							var element = $(this);// .closest('a > p');
							selected_array = selected_array.concat( element.attr("id") );
							titles_array =  titles_array.concat( element.attr("title") );
							});
							if(selected_array.length == 1)
							{
								file_title = titles_array[0];
								file_id = selected_array[0];
								
								if(files_menu.items['Delete items'] != null)
									files_menu.remove('Delete items');
								
								if(files_menu.items['Delete item'] == null)
									files_menu.add('Delete item' , deleteFile);
									
								if(files_menu.items['Get link'] == null)
									files_menu.add('Get link' , showFileUrlAlert);
									
								if(files_menu.items['Download item'] == null)
									files_menu.add('Download item' , downloadAFile);
									
								if(files_menu.items['Rename item'] == null)
									files_menu.add('Rename item' , renameFile);
									

							}else{
								if(files_menu.items['Delete items'] == null)
									files_menu.add('Delete items' , deleteMultipleFiles);
								
								if(files_menu.items['Delete item'] != null)
									files_menu.remove('Delete item');
									
								if(files_menu.items['Get link'] != null)
									files_menu.remove('Get link');
									
								if(files_menu.items['Download item'] != null)
									files_menu.remove('Download item');
									
								if(files_menu.items['Rename item'] != null)
									files_menu.remove('Rename item');

							}
							
							files_menu.moveTo(e.pageX, e.pageY).show();
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