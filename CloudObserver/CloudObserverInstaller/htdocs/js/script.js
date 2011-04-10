            var _gaq = _gaq || [];
            _gaq.push(['_setAccount', 'UA-21524436-1']);
            _gaq.push(['_setDomainName', 'none']);
            _gaq.push(['_setAllowLinker', true]);
            _gaq.push(['_trackPageview']);
        
            (function()
            {
                var ga = document.createElement('script');
                ga.type = 'text/javascript';
                ga.async = true;
                ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
                var s = document.getElementsByTagName('script')[0];
                s.parentNode.insertBefore(ga, s);
            })();
            _gaq.push(['_setCustomVar', 1, // This custom var is set to slot #1
            'URL', // The name acts as a kind of category for the user activity
            window.location.toString(), // This value of the custom variable
            1]);
            _gaq.push(['_trackEvent', 'Visit on page', // category of activity
            window.location.toString() // Action
            ]);
            
                   
            function resizedw()
            {
        
                if (html5support == 1) if (((document.body.clientWidth / document.body.clientHeight) < 6) && ((document.body.clientWidth / document.body.clientHeight) > (1 / 6)))
                {
                    if (document.body.clientWidth > $("#" + 'info').width)
                    {
                        $("#" + 'container').width = document.body.clientWidth;
                    }
                    else
                    {
                        $("#" + 'container').width = $("#" + 'info').width;
                    }
                    if (document.body.clientHeight > $("#" + 'info').height)
                    {
                        $("#" + 'container').height = document.body.clientHeight;
                    }
                    else
                    {
                        $("#" + 'container').height = $("#" + 'info').height;
                    }
                    dinit();
                    render();
                }
            }
        
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
                    var file = './' + name + '.flv?action=play';
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
                var xmlhttp;
                try
                {
                    xmlhttp = new XMLHttpRequest();
                }
                catch (e)
                {
                    var success = false;
                    var objects = ["MSXML2.XMLHTTP.5.0", "MSXML2.XMLHTTP.4.0", "MSXML2.XMLHTTP.3.0", "MSXML2.XMLHTTP", "Microsoft.XMLHTTP"];
                    for (var i = 0; i < objects.length && !success; i++)
                    {
                        try
                        {
                            xmlhttp = new ActiveXObject(objects[i]);
                            success = true;
                        }
                        catch (e)
                        {};
                    }
                    if (!success) throw new Error("AJAX is unavailabe");
                }
                xmlhttp.onreadystatechange = function()
                {
                    if (xmlhttp.readyState == 4)
                    {
                        if (document.getElementById('usersList').innerHTML != xmlhttp.responseText) document.getElementById('usersList').innerHTML = xmlhttp.responseText;
                    };
                }
                xmlhttp.open("get", "buttons.html", true);
                xmlhttp.send(null);
            }
			
			function stopHtml5()
			{
				$("body").removeClass("html5Supported");
				$("#container").remove();
				$("body").addClass("html5StupSupport");
		$(".html5StupSupport").append('<style type="text/css">  body { background-color: rgb(255,255,255); margin: 0px; overflow: hidden; font: 100.01% "Trebuchet MS",Verdana,Arial,sans-serif; }	div#nifty{background: #9BD1FA; -moz-border-radius:15px; border-radius: 15px;}</style>');
			}
			
			function startHtml5()
			{
			$("body").removeClass("html5StupSupport");
			$('#containerHolder').html('<div id="container" style="position:absolute"></div>');
			html5support = 1; //  document.write('<p>' + '3d three js, Html 5 Capable' + '</p>');
			$("body").addClass("html5Supported");
			$(".html5Supported").append('<style type="text/css">  body { background-color: rgb(200,200,200); margin: 0px; overflow: hidden; font: 100.01% "Trebuchet MS",Verdana,Arial,sans-serif; } #info { position: absolute; top: 0px; width: 100%; color: #ffffff;  font-family:Monospace;font-size:13px; font-weight: bold; 			position:absolute;		height:100%;	overflow:auto; } a { color: #ffffff;} h1,h2,p{margin: 0 10px} h1{font-size: 250%;color: #FFF; text-shadow:0px 1px 1px #000;} h2{font-size: 200%;color: #f0f0f0;padding-top: 0.3em}div#nifty{ margin: 0 10%;background: rgba(250, 250, 250, 0.1); -moz-border-radius:15px; border-radius: 15px;} b.rtop, b.rbottom{display:block;background:#FFF; } b.rtop b, b.rbottom b{display:block;height: 1px;overflow: hidden; background: #9BD1FA} b.r1{margin: 0 5px} b.r2{margin: 0 3px} b.r3{margin:0 2px} b.rtop b.r4, b.rbottom b.r4{margin: 0 1px;height: 2px} p, ul{color:#000;text-shadow: 0px 1px 1px rgba(255,255,255,0.6);padding-bottom:1em}input[type="button"], .eButton {width: 150px;padding: 5px 10px;word-wrap:break-word;height: auto;} b.rtop, b.rbottom{display:none;background: rgba(0,0,0,0)}html{ width:100%; height:100%; min-width:900; min-height:700;} body{ width:100%; height:100%; }  #container{ width:100%; height:100%;} </style>');
			dinit();
			render();
			$(window).resize(function()
			{
				resizedw();
			});
			}