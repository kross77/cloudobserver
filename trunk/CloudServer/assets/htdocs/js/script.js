var openWindowDelayedPool = openWindowDelayedPool || {};

openWindowDelayedPool.functions = [];
openWindowDelayedPool.isRunning = false;
openWindowDelayedPool.sleepTime = 150;

openWindowDelayedPool.add = function(fn) {
    openWindowDelayedPool.functions.push(fn);
    openWindowDelayedPool.run();  
};

openWindowDelayedPool.remove = function(fn) {
    openWindowDelayedPool.functions.splice(openWindowDelayedPool.functions.indexOf(fn), 1);
};

openWindowDelayedPool.run = function() {
    if (!openWindowDelayedPool.isRunning) {
        openWindowDelayedPool.isRunning = true;
        $.each(openWindowDelayedPool.functions, function(index, val) {
            if (typeof val == "function") {
                setTimeout(function() {
                    val.call();
                    openWindowDelayedPool.remove(val);
                }, index * openWindowDelayedPool.sleepTime);
            }
        });
        setTimeout(function() {
            openWindowDelayedPool.isRunning = false;
            openWindowDelayedPool.run();  
        }, (openWindowDelayedPool.functions.length + 1) * openWindowDelayedPool.sleepTime)
    }
};


function getOffset(el)
{
	var _x = 0;
	var _y = 0;
	while (el && !isNaN(el.offsetLeft) && !isNaN(el.offsetTop))
	{
		_x += el.offsetLeft - el.scrollLeft;
		_y += el.offsetTop - el.scrollTop;
		el = el.parentNode;
	}
	return {
		top: _y,
		left: _x
	};
}

var exNames = [];
var wins = [];
var w = 0;
var h = 0;
var maxHeight = 0;
var firstRun = 0;

openInnerWin = function(name, width, height)
{

	
	var closedWins = [];
	for (var i = 0; i < wins.length; ++i)
	{
		if (wins[i].closed)
		{
			closedWins.push(exNames[i]);
			wins.splice (i, 1);
			exNames.splice(i, 1);
		}
		
	}
	var winsJoin = "|" + exNames.join("|") + "|";
	//alert(wins);
	var closedJoin = "|" + closedWins.join("|") + "|";
	
	if ( (winsJoin.indexOf('|' + name + '|') == -1 ) ||  ( closedJoin.indexOf('|' + name + '|') != -1 ) )
	{
		if (height > maxHeight)
		{
			maxHeight = height + 55;
		}
		if (window.screenX + getOffset(document.getElementById('usersList')).left >= screen.width / 2)
		{
			if (window.screenX + 102 - w - width < 0)
			{
				w = 0;
				h = h + maxHeight;
				top = h + 1;
				maxHeight = 0;
				if (screen.height - h - height + getOffset(document.getElementById('usersList')).left - 155 < 0)
				{
					h = 0;
				}
			}
		}
		if (window.screenX + getOffset(document.getElementById('usersList')).left < screen.width / 2)
		{
			if (firstRun == 0)
			{
				w = window.screenX + getOffset(document.getElementById('usersList')).left + 150;
				firstRun = 1;
			}
			if (screen.width - w - width < 0)
			{
				w = window.screenX + +getOffset(document.getElementById('usersList')).left + 150;
				h = h + maxHeight;
				top = h + 1;
				maxHeight = 0;
				if (screen.height - h - height < 0)
				{
					h = 0;
				}
			}
		}
		left = w + 1;
		tops = h + 1;
		w = w + width + 7;
		var file = "./player.html?" + Math.floor(Math.random()*10000+1) +"#" + name;
		var settings = 'width=' + width + ', height=' + height + ', left=' + left + ', top=' + tops + ', screenX=' + left + ', screenY=' + tops;
		var windo = window.open(file, name, settings);
		//windo.focus();
		wins.push(windo);
		exNames.push(name);
	}
	
	for (var i = 0; i < wins.length; i++)
	{
			wins[i].focus();
	}
	
	for (var i = 0; i < wins.length; i++)
	{
		var local_name = wins[i].name;
		if(local_name == name)
			wins[i].focus();
	}
}

openWin= function(name, width, height)
{
	openInnerWin(name, width, height);
	$('.eButton').attr("disabled", true);
	openWindowDelayedPool.add(function(){$('.eButton').attr("disabled", false);});
	//openWindowDelayedPool.add(function(){openInnerWin(name, width, height);});
}

function update()
{
	$.getJSON("users.json", function(obj) {
		var user_list_html = "";
		for (var i = 0, len = obj.length; i < len; i++ )
		{
				user_list_html += "<li><FORM><INPUT class='eButton' type='button' value='"+ obj[i].nickname +"' onClick=\"openWin('" + obj[i].nickname +"'," + obj[i].width + ',' +  obj[i].height +");\"'></FORM></li>" ;
		}
		$('.usersList').html(user_list_html);
	});
}

$(document).ready(function() {
	update();
	setInterval(update, 3000);
});
