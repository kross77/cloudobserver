	function updateMenu(){
		$('.nav li').each( function(i, e) { $(e).css("opacity", 1);});
		var listWidth = 0;
		$('.nav li').each( function(i, e) { listWidth += $(e).width();});
		
		
		var lastItemIndex = Number.POSITIVE_INFINITY;
		var lastItemText = "";
		var maxWidth = 0;
		var overflowCount=0;
		var navHeight = $('#pser').height() ;
		$('.nav li').each(function(i,e){
		console.log( "$(e).position().top " +  $(e).position().top);
			if($(e).position().top>=navHeight){
				if(i<=lastItemIndex) lastItemIndex=i-1;
				if($(e).width()>maxWidth) maxWidth = $(e).width();
				overflowCount++;
			}
		});
		maxWidth = Math.max(maxWidth,$('.nav li:eq('+(lastItemIndex)+')').width());

				var moreHeight =  (overflowCount+2)*(navHeight);
		$('#moreMenu').remove();
		//if( ($('#pser').width() - listWidth) <=0 ){
		if(overflowCount>0){
			console.log( "overflowCount " +  overflowCount);
			$('.nav li:eq('+(lastItemIndex)+')').css("opacity", 0);
			$('.nav li:gt('+(lastItemIndex)+')').css("opacity", 0);
			//alert(overflowCount);
			$('<ul id="moreMenu"/>').appendTo('body').width(maxWidth+40).height(navHeight);
			$('#moreMenu').offset($('.nav li:eq('+(lastItemIndex)+')').offset());
			if( (lastItemIndex - 1) >= 0 ){
				$('#moreMenu').append('<li>More... <span class="profile-triangle">▾</span></li>');
		        $('.nav li:gt(' + (lastItemIndex - 1) + ')').each(function(i, e) {
		            $('#moreMenu').append('<li>' + $(e).html() + '</li>');
		        });
		    }else{	
		    	$('#moreMenu').append('<li>Services <span class="profile-triangle">▾</span></li>');
		        $('.nav li').each(function(i, e) {
		            $('#moreMenu').append('<li>' + $(e).html() + '</li>');
		        });
		    }
			moreHeight = 0;
			$('#moreMenu li').each(function(i, e) {
				moreHeight += $(e).innerHeight();
			});
			$('#moreMenu').hover(
				function(){$(this).height(moreHeight);},
				function(){$(this).height(40);});
		}	
	//	}
	}


function hidePopUbBubble(){
	$(".new").empty();
	$(".new").detach();
	$(".new").remove();
}

$(document).ready(function() {

	$('body').append("<div class=\"hidden-c\" style=\"display: none;\"><!-- --><div id=\"tabs-logout\" class=\"logout\"><fieldset><legend>Logout?</legend><form  action=\"./uac.service\"><input type=\"hidden\" name=\"redirect_to\" value=\""+location.href+"\"><input type=\"hidden\" name=\"user_control\" value=\"logout\"><input type=\"hidden\" name=\"logout\" value=\"true\"><input type=\"submit\" class=\"eButton\" value=\"OK\" /><input type=\"button\" class=\"eButton\" value=\"Cancel\" onClick=\'hideDialog($(\".alert\"));\' /></form></fieldset></div><!-- --></div>");

	$('body').prepend("<div class='header'><table style='color:white; padding:0px; margin: 0px 100px 0px 0px; width:100%' cellpadding='0' cellspacing='0'><tr><td id='plogo' style='width:50px; height:40px;'><div><a href='index.html'><p class='logo' style='background: url(/logo-small.png); width:50px; height:40px; background-repeat: no-repeat;	background-position: center center;'></p></a></div></td><td  id='pser' style='text-align: left;'><div id='marx-services-list'><ul class='nav'><div data-template><li><a href='{{url}}' style='width:100%; height:100%'><p style='min-width:100px;'>{{name}}</p></a></li></div></ul></div></td><td style='white-space:nowrap;text-align:right;'><div id='marx-user-name' ><div data-template><a><p class='header-item' id='user_name' class='hidden-c' style='min-width:100px; z-index=999;'>{{user_name}}</p></a></div></div></td></tr></table></div><script>$(document).ready(function() {page_update.run();});</script>");
	updateMenu();
	//$(window).resize(updateMenu);
	page_update.add(updateMenu);
   var servicesList = Tempo.prepare('marx-services-list').notify( function (event) {
	if ( event.type === TempoEvent.Types.RENDER_COMPLETE) { page_update.run(); updateMenu();}
	});
			servicesList.starting();
	
	getJSONFromServer("server.json", function(data){
		servicesList.render(data);
		 updateMenu();
		});
	
	//updateMenu();
	user = readCookie('session-id');
	if (user != null) {
		var user_name = Tempo.prepare('marx-user-name').notify( function (event) {
	if ( event.type === TempoEvent.Types.RENDER_COMPLETE) { page_update.run();}
	});
		user_name.starting();
		
		getJSONFromServer("ufs.service?user_name=true", function(data){
			user_name.render(data);
		});
		
		$("#marx-user-name").show();
		
		$("#user_name").live('mouseup', function(eventObj){
			th =  $(this);
			var elemZIndex = $(this).css('z-index', '100');
			var elemPos = $(this).offset();
	
			var ran_unrounded=Math.random()*50000;
		var ran_number = Math.floor(ran_unrounded);
		var newer = "newer" +  ran_number;
		var newer_id = "#" + newer;
		$(this).append('<div id=\"'+newer+'\" class="new" style="position:absolute; left:' +( eventObj.pageX) + 'px; top:' + 0 + 'px; z-index:' + (elemZIndex + 10) + '">&nbsp;</div>');
	//( elemPos.top  + (40%(eventObj.pageY))
			$(newer_id).grumble({
				text: "  <a href='#' class='logout-but'><h3>Log me out</h3></a> <br/> <a href='#' ><h3>Cancel</h3></a>    ",
				angle: (Math.random() * 30 + 190),
				distance: 3,
				showAfter: 15,
				hideAfter: false,
				//type : 'alt-',
				hasHideButton: false,
				hideOnClick : true,
				// just shows the button
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
					hidePopUbBubble();
					$(newer_id).grumble('hide');
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
	}else{
		$('#user_name').hide();
		}
	page_update.run();
});