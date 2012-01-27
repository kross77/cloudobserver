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


run = function(name, width, height)
{

	var winsJoin = "|" + exNames.join("|") + "|";
	var closedWins = [];
	for (var i = 0; i < wins.length; ++i)
	{
		if (wins[i].closed)
		{
			closedWins.push(exNames[i]);
		}
	}
	var closedJoin = "|" + closedWins.join("|") + "|";
	if (winsJoin.indexOf('|' + name + '|') == -1 || closedJoin.indexOf('|' + name + '|') != -1)
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
		var file = './' + name;
		var settings = 'width=' + width + ', height=' + height + ', left=' + left + ', top=' + tops + ', screenX=' + left + ', screenY=' + tops;
		wins.push(window.open(file, name, settings));
		exNames.push(name);
	}
	for (var i = 0; i < wins.length; ++i)
	{
		wins[i].focus();
	}
}



openWin = function(name, width, height)
{

	var winsJoin = "|" + exNames.join("|") + "|";
	var closedWins = [];
	for (var i = 0; i < wins.length; ++i)
	{
		if (wins[i].closed)
		{
			closedWins.push(exNames[i]);
		}
	}
	var closedJoin = "|" + closedWins.join("|") + "|";
	if (winsJoin.indexOf('|' + name + '|') == -1 || closedJoin.indexOf('|' + name + '|') != -1)
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
		var file = "./player.html#" + name;
		var settings = 'width=' + width + ', height=' + height + ', left=' + left + ', top=' + tops + ', screenX=' + left + ', screenY=' + tops;
		wins.push(window.open(file, name, settings));
		exNames.push(name);
	}
	for (var i = 0; i < wins.length; ++i)
	{
		wins[i].focus();
	}
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
