$(document).ready(function() {
	$('body').append("<div class='header'><div id='marx-user-name' ><div data-template><a><p class='header-item' id='user_name' class='hidden-c' >{{user_name}}</p></a></div></div><div id='marx-services-list'><div data-template><a href='{{url}}'><p class='header-item'>{{name}}</p></a></div></div></div>");
	
   var servicesList = Tempo.prepare('marx-services-list');
			servicesList.starting();

	$.get("server.json", function(json) {
			var data = $.parseJSON(json);
			servicesList.render(data);	
	});

	$('.header-item').live('mousedown', function(){
		$(this).addClass("hilight");
	}).live('mouseup', function(){
		$(this).removeClass("hilight");
	}).live('mouseover', function(){
		$(this).addClass("border");
	}).live('mouseout', function(){
		$(this).removeClass("border");
		$(this).removeClass("hilight");
	});
	
	user = readCookie('session-id');
	if (user != null) {
		var user_name = Tempo.prepare('marx-user-name');
		user_name.starting();
		$.get("ufs.service?user_name=true", function(json) {
			var data = $.parseJSON(json);
			user_name.render(data);
		});
		
		$("#marx-user-name").show();
		
		$("#user_name").live('mouseup', function(eventObj){
			th =  $(this);
			var elemZIndex = $(this).css('z-index', '100');
			var elemPos = $(this).offset();
	
			$(this).append('<div id="newer" class="new" style="position:absolute; left:' +( eventObj.pageX) + 'px; top:' + 0 + 'px; z-index:' + (elemZIndex + 10) + '">&nbsp;</div>');
	//( elemPos.top  + (40%(eventObj.pageY))
			$('#newer').grumble({
				text: "  <a href='#' class='logout-but'><h3>Log me out</h3></a> <br/> <a href='#' ><h3>Cancel</h3></a>    ",
				angle: (Math.random() * 50 + 130),
				distance: 3,
				showAfter: 15,
				hideAfter: false,
				//type : 'alt-',
				hasHideButton: true,
				// just shows the button
				buttonHideText: 'Pop!',
				onShow: function() {
					$('.logout-but').mouseup(function() {
						showForm($('#tabs-logout'), 'Logout form',350, 120);
					});
					th.addClass("border");
				},
				onBeginHide: function() {
					$('.border').removeClass("border");
				},
				onHide: function() {
					$("#newer").empty();
					$("#newer").detach();
					$("#newer").remove();
				}
			});
	
		}).live('mousedown', function(){
			$(this).addClass("hilight");
		}).live('mouseup', function(){
			$(this).removeClass("hilight");
		}).live('mouseover', function(){
			$(this).addClass("border");
		}).live('mouseout', function(eventObj){
			$(this).removeClass("border");
			$(this).removeClass("hilight");
		});					
	}else{$('#marx-user-name').hide();}
});