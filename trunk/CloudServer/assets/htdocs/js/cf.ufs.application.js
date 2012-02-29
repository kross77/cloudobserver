var file_id;
var file_title;
$(document).ready(function() {
	user = readCookie('session-id');
	var files_menu = ui.menu()
	.add('Download item' , function(){ window.open('/'+file_id, '_blank'); })
	.add('Get link' , function(){ showAlert( 600, 100 , ('link to ' + file_title + ' file.') , '<input type="text" style="width:590px" class="text" value=\"' + location.host + ('/'+file_id ) + '\">'); });
	
	if (user != null) {	
			$('.loged-in-user').show();
			$('.not-loged-in-user').remove();
			   var fs = Tempo.prepare('marx-brothers');
				fs.starting();
	
		$.getJSON("ufs.json", function(data) {
		    fs.render(data);

			$('.butt2').mousedown(function() {
				$(this).addClass("hilight2");
			}).mouseup(function() {
				$(this).removeClass("hilight2");
			}).mouseover(function() {
				$(this).addClass("border2");
			}).mouseout(function() {
				$(this).removeClass("border2");
				$(this).removeClass("hilight2");
			});
		});
	}
	
	$('.lst .uf .butt2').live('click', function(e) {
		file_title = this.title;
		file_id = this.id;
		files_menu.moveTo(e.pageX, e.pageY).show();
	}).live('mousedown', function(e){
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