var page_url = unescape(location.href.folderOf());

function showBox(images, ind) {
    $.fancybox(images, {
        'index': ind,
        'cyclic': 'true',
        'transitionIn': 'fade',
        'transitionOut': 'fade',
        'titlePosition': 'over',
        'type': 'image',
        'titleFormat': function (title, currentArray, currentIndex, currentOpts) {

            return '<span id="fancybox-title-over">Image ' + (currentIndex + 1) + ' / ' + currentArray.length + (title.length ? ' &nbsp; ' + title : '') + '</span>';
        },
        'onComplete': function () {
            document.title = "" + this.title + " proudly Brought To You By CF Images Rendering Service";
            window.location.hash = this.extra_href;
            $("#fancybox-wrap").hover(function () {
                $("#fancybox-title").show();
            }, function () {
                $("#fancybox-title").hide();
            });
        },
        'onClosed': function () {
            document.title = "Cloud Server Developers Image Service Page";
            window.location.hash = "";

        }


    });
}

function parseArrayForBox(JSON, images) {
    $.each(JSON, function (index, value) {

        if (value.is_public == 1) {
            //value.href = ;
            value.real_href = "./image_renderer.service?action=resize&from_format=" + value.type + "&from_url=" + page_url + value.href + "&to_format=jpg&w=" + $('html').width() + "&h=" + $('html').height();
        } else {
            value.real_href = value.href;
        }
        images.push({
            'href': value.real_href,
            'title': value.title,
            extra_href: value.href
        });
    });
}

shuffle = function (o) { //v1.0
    for (var j, x, i = o.length; i; j = parseInt(Math.random() * i), x = o[--i], o[i] = o[j], o[j] = x);
    return o;
};

if (location.hash.toString()) {
    var file_url = location.hash.substring(1);
    if (file_url) {
        $.getJSON("./ufs.json?action=file_info&url=" + file_url, function (images) {
            if (!(images.error)) {
                var JSON = [];
                JSON = JSON.concat(images);
                var user_image = [];
                parseArrayForBox(JSON, user_image);
                jQuery(document).ready(function () {
                    showBox(user_image, 0);
                });
            } else {
                user = readCookie('session-id');
                if (user != null) {
                    $(document).ready(function () {
                        $(".loged-in-user-error").html('<div><p>You don\'t permission to view this image</p></div>');
                        $(".loged-in-user-error").center();
                    });
                } else {
                    $(document).ready(function () {
                        $(".not-loged-in-user-error").html('<div><p>Currently you have not enough permissions to view this image. Please log in.</p></div>');
                    });
                }
            }
        });
    }
}

$(document).ready(function () {

    user = readCookie('session-id');
    if (user != null) {

        var is = Tempo.prepare('marx-images');
        is.starting();
        var joinedJSON = [];
        var user_images = [];
        $.getJSON("./ufs.json?action=type&type=mask", function (json_mask) {
            joinedJSON = joinedJSON.concat(json_mask);
            $.getJSON("./ufs.json?action=type&type=image", function (json_image) {
                joinedJSON = joinedJSON.concat(json_image);
                $.getJSON("./ufs.json?action=type&type=png", function (json_png) {
                    joinedJSON = joinedJSON.concat(json_png);
                    $.getJSON("./ufs.json?action=type&type=jpg", function (json_jpg) {
                        joinedJSON = joinedJSON.concat(json_jpg);
                        $.getJSON("./ufs.json?action=type&type=jpeg", function (json_jpeg) {
                            joinedJSON = joinedJSON.concat(json_jpeg);
                            $.getJSON("./ufs.json?action=type&type=svg", function (json_svg) {
                                joinedJSON = joinedJSON.concat(json_svg);
                                joinedJSON = shuffle(joinedJSON);
                                parseArrayForBox(joinedJSON, user_images);
                                is.render(joinedJSON);

                            }); // SVG	
                        }); // jpeg
                    }); // jpg
                }); // png
            }); // image
        }); //mask
        $('.image_service_url').live('click', function (e) {
            var temp_h = $(e.target).closest("a").attr('real_href');
            var ind = 0;
            $.each(user_images, function (index, value) {
                if (value.href === temp_h) {
                    ind = index;
                    return false;
                }
            });
            showBox(user_images, ind);
        });
    }
});