var file_id;
var file_title;
$(document).ready(function() {
	user = readCookie('session-id');
	var files_menu = ui.menu()
	.add('Download item' , function(){ window.open(""+file_id, '_blank'); })
	.add('Get link' , function(){ showAlert( 600, 100 , ('link to ' + file_title + ' file.') , '<input type="text" style="width:590px" class="text" value=\"' + location.host + ('/'+file_id ) + '\">'); });
	
	if (user != null) {	
			$('.loged-in-user').show();
			$('.not-loged-in-user').remove();
			   var fs = Tempo.prepare('marx-brothers')
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
		
});