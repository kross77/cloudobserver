/*
 * jQuery UI FormValidator (07.03.10)
 * http://github.com/fnagel/jQuery-Accessible-RIA
 *
 * Copyright (c) 2009 Felix Nagel for Namics (Deustchland) GmbH
 * Licensed under the MIT license: http://www.opensource.org/licenses/mit-license.php
 *
 * Depends: ui.core.js
 */
(function(a){a.widget("ui.formValidator",{options:{validateLive:true,validateLiveMsg:true,validateTimeout:500,validateTimeoutCaptcha:3,validateOff:"Please click here to deactivate live validating of this form.",validateOn:"Please clkick here to activate live form validating.",errorSummery:true,errorsTitle:"Please check the following errors:",submitHowTo:"ajax",submitUrl:"",submitError:"Something wen't wrong while sending your data. Please retry.",submitSuccess:"Your data was succefully submitted, thank you!",originalUrl:"",selectDefault:"default"},_init:function(){var d=this.options,c=this;c._updateVirtualBuffer();var b=c.element.attr("id");if(b!=""){d.uid=b;}else{d.uid=new Date().getTime();}if(d.submitUrl==""){d.submitUrl=c.element.attr("action");}c.element.submit(function(e){if(!d.disabled){c.formSubmitted();}return d.disabled;});if(d.validateLive&&!d.disabled&&d.validateLiveMsg){c.element.find(".ui-formular-info").append('\t<p><a class="ui-formular-live" href="#nogo">'+d.validateOff+"</a></p>\n\t\t");c._updateVirtualBuffer();c.element.find(".ui-formular-live").toggle(function(){d.validateLive=false;a(this).attr("aria-live","polite").attr("aria-relevant","text").html(d.validateOn);c._updateVirtualBuffer();},function(){d.validateLive=true;a(this).attr("aria-live","polite").attr("aria-relevant","text").html(d.validateOff);c._updateVirtualBuffer();});}c._makeHover(c.element.find("input:submit, input:reset"));a.each(d.forms,function(g){d.forms[g]["errors"]=[];var e=c.element.find("#"+g);if(!e.length){e=c.element.find("input."+g);if(!e.length){alert("Error: Configuration corrupted!\n\nCan't find element with id or class = "+g);}else{value="group";c._makeHover(e.next());e.bind("mouseenter",function(){a(this).next().addClass("ui-state-hover");}).bind("mouseleave",function(){a(this).next().removeClass("ui-state-hover");}).bind("focus",function(){a(this).next().addClass("ui-state-focus");}).bind("blur",function(){a(this).next().removeClass("ui-state-focus");});}}else{c._makeHover(e);if(d.forms[g].rules.required){e.attr("aria-required",true);}if(e[0].nodeName.toLowerCase()=="select"){value="select";}else{value="single";}}d.forms[g].element=e;d.forms[g].type=value;if(d.validateLive){var f="blur ";if(d.validateTimeout!="blur"){if(d.forms[g].type!="group"){f+=(d.forms[g].type=="select")?"click change keyup":"keyup";}else{f+="click";}}d.forms[g].element.bind(f,function(i){if(d.validateTimeout=="blur"||i.type=="blur"){c._validator(g);c._setErrors(false);}else{if(d.validateLive&&!d.disabled&&i.keyCode!=a.ui.keyCode.TAB){if(d.forms[g].timeout){window.clearTimeout(d.forms[g].timeout);}var h=(d.forms[g].rules["regEx"]=="captcha")?d.validateTimeout*d.validateTimeoutCaptcha:d.validateTimeout;d.forms[g].timeout=window.setTimeout(function(){c._validator(g);c._setErrors(false);},h);}}});}});c._trigger("onInit",0);},_validator:function(f){var c=this.options,b=this;var e=c.forms[f].errors;var d=b._getValue(f);a.each(c.forms[f].rules,function(g,h){if(d==""){if(g!="required"){e[g]=b._whichError(true,e[g]);}if(g=="required"&&h){e[g]=b._whichError(false,e[g]);}}else{if(g=="required"&&h){e[g]=b._whichError(true,e[g]);}switch(g){case"regEx":switch(h){case"number":e[g]=b._whichError(b._number(d),e[g]);break;case"numberDE":e[g]=b._whichError(b._numberDE(d),e[g]);break;case"numberISO":e[g]=b._whichError(b._numberISO(d),e[g]);break;case"email":e[g]=b._whichError(b._email(d),e[g]);break;case"url":e[g]=b._whichError(b._url(d),e[g]);break;case"plz":e[g]=b._whichError(b._plz(d),e[g]);break;case"dateDE":e[g]=b._whichError(b._dateDE(d),e[g]);break;case"dateISO":e[g]=b._whichError(b._dateISO(d),e[g]);break;case"captcha":e[g]=b._whichError(b._captcha(d),e[g]);break;default:e[g]=b._whichError(b._regEx(d,h),e[g]);break;}break;case"lengthMin":e[g]=b._whichError(b._lengthMin(d,h),e[g]);break;case"lengthMax":e[g]=b._whichError(b._lengthMax(d,h),e[g]);break;case"equalTo":e[g]=b._whichError(b._equalTo(d,h),e[g]);break;case"custom":e[g]=b._whichError(h(d),e[g]);break;}}});c.forms[f]["id"]=f;b._trigger("customError",0,c.forms[f]);c.forms[f].errors=e;},formSubmitted:function(){var c=this.options,b=this;b._trigger("onformSubmitted",0);b.element.find(".ui-formular-success").remove();a.each(c.forms,function(e){var d=false;if(c.forms[e].type=="single"){b._validator(e);}else{if(!d){d=true;b._validator(e);}}});b._setErrors(true);},validate:function(d){var c=this.options,b=this;b._validator(d);b._setErrors(false);},_setErrors:function(j){var l=this.options,k=this;var g,m,e=false;var i="",d="";for(var b in l.forms){var c=false;for(var h in l.forms[b]["errors"]){if(l.forms[b]["errors"][h]=="corrected"){var f=l.forms[b].element;f.attr("aria-invalid",false);if(l.forms[b].type=="group"){f=f.next();}f.removeClass("ui-state-error");e=true;k._trigger("onValid",null,b);}if(l.forms[b]["errors"][h]=="new"||l.forms[b]["errors"][h]=="old"){if(l.errorSummery){i+='					<li><a href="#'+b+'">'+l.forms[b].msg[h]+"</a></li>\n";}g=c=true;k._trigger("onError",null,b);}if(l.forms[b]["errors"][h]=="new"){m=true;}}if(c){var f=l.forms[b].element;f.attr("aria-invalid",true);if(l.forms[b].type=="group"){f=f.next();}f.addClass("ui-state-error");}}if(l.errorSummery===true||(l.errorSummery=="onSubmit"&&j)){k._showErrors({submitted:j,isError:g,addError:m,removeError:e,msgs:i});}if(g){k._trigger("onErrors",0);}else{if(j){k._sendForm();}}k._updateVirtualBuffer();},_showErrors:function(f){var d=this.options,b=this;var c=' aria-live="assertive"';if(f["addError"]||f["removeError"]){c+=' aria-relevant="text';}if(f["addError"]){c+=" additions";}if(f["removeError"]){c+=" removals";}if(f["addError"]||f["removeError"]){c+='"';}var e="\n";if(f["isError"]){e+="			<div"+c+' class="info ui-state-highlight ui-state ui-corner-all">'+"\n";e+='				<p id="ui-error-title-'+d.uid+'">'+"\n";e+='					<span class="ui-icon ui-icon-alert" style="float: left; margin-right: 0.3em;"></span>'+"\n";e+="					"+d.errorsTitle+"\n";e+="				</p>"+"\n";e+='				<ul aria-labelledby="ui-error-title-'+d.uid+'">'+"\n";e+=f["msgs"];e+="				</ul>"+"\n";e+="			</div>"+"\n\t\t";}errorElement=b.element.find(".ui-formular-error");errorElement.html(e);if(f["isError"]){errorElement.find("a").click(function(g){g.preventDefault();var i=a(this).attr("href").split("#");i=i[1];var h=(d.forms[i].type=="single")?d.forms[i].element:d.forms[i].element[0];h.focus();});if(f["submitted"]){errorElement.attr("tabindex",-1).focus();}b._trigger("onErrors",0);}b._trigger("onShowErrors",0);},_sendForm:function(){var d=this.options,c=this;switch(d.submitHowTo){case"post":d.disabled=true;c.element.submit();break;case"ajax":a.ajax({data:c.element.serialize(),type:"post",url:d.submitUrl,error:function(f){c._showSuccess(f);},success:function(f){c._showSuccess(f);}});break;case"iframe":d.originalUrl=c.element.attr("action");c.element.attr("action",d.submitUrl);var b=("upload"+(new Date()).getTime());var e=a('<iframe name="'+b+'"></iframe>');e.css("display","none");e.load(function(f){c._showSuccess(a(this).contents().find("body").html());d.timeout=window.setTimeout(function(){e.remove();},200);});a("body").append(e);c.element.attr("target",b);d.disabled=true;c.element.submit();break;}},_showSuccess:function(f){var c=this.options,b=this;var g="",e="";c.disabled=false;if(jQuery.browser.safari){b.element.find(".ui-formular-success").remove();}switch(f){case"true":case"1":g=c.submitSuccess;e="check";break;default:if(f==""){g=c.submitError;}else{g=f;}e="alert";break;}var d="\n";d+='		<div class="ui-formular-success">'+"\n";d+='			<div aria-live="assertive" class="info ui-state-highlight ui-state ui-corner-all">'+"\n";d+="				<p>"+"\n";d+='					<span class="ui-icon ui-icon-'+e+'" style="float: left; margin-right: 0.3em;"></span>'+"\n";d+="					"+g+"\n";d+="				</p>"+"\n";d+="			</div>"+"\n\t\t";d+="		</div>"+"\n\t\t";b.element.prepend(d);b.element.find(".ui-formular-success").attr("tabindex",-1).focus();b._updateVirtualBuffer();b._trigger("onShowSuccess",null,f);},_whichError:function(b,d){var c="";if(!b){c=(d=="new"||d=="old")?"old":"new";}else{if(d=="new"||d=="old"){c="corrected";}}return c;},_getValue:function(f){var c=this.options;var d=c.forms[f].type;var e="";switch(d){case"single":e=c.forms[f].element.val();break;case"group":var b=c.forms[f].element.filter(":checked");if(b.length){e=b;}break;case"select":var b=c.forms[f].element.find("option").filter(":selected");if(b.length){e=(b.val()==c.selectDefault)?0:b;}break;}return e;},_makeHover:function(b){b.bind("mouseenter",function(){a(this).addClass("ui-state-hover");}).bind("mouseleave",function(){a(this).removeClass("ui-state-hover");}).bind("focus",function(){a(this).addClass("ui-state-focus");}).bind("blur",function(){a(this).removeClass("ui-state-focus");});},_regEx:function(c,b){b=new RegExp(b);return b.test(c);},_number:function(b){return/^\d+$/.test(b);},_numberDE:function(b){return/^[-+]?([0-9]*\,)?[0-9]+$/.test(b);},_numberISO:function(b){return/^[-+]?([0-9]*\.)?[0-9]+$/.test(b);},_email:function(b){return/^[A-Za-z0-9](([_\.\-]?[a-zA-Z0-9]+)*)@([A-Za-z0-9]+)(([\.\-]?[a-zA-Z0-9]+)*)\.([A-Za-z]{2,})$/.test(b);},_url:function(b){return/^(https?|ftp):\/\/(((([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(%[\da-f]{2})|[!\$&'\(\)\*\+,;=]|:)*@)?(((\d|[1-9]\d|1\d\d|2[0-4]\d|25[0-5])\.(\d|[1-9]\d|1\d\d|2[0-4]\d|25[0-5])\.(\d|[1-9]\d|1\d\d|2[0-4]\d|25[0-5])\.(\d|[1-9]\d|1\d\d|2[0-4]\d|25[0-5]))|((([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])*([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])))\.)+(([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])*([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])))\.?)(:\d*)?)(\/((([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(%[\da-f]{2})|[!\$&'\(\)\*\+,;=]|:|@)+(\/(([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(%[\da-f]{2})|[!\$&'\(\)\*\+,;=]|:|@)*)*)?)?(\?((([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(%[\da-f]{2})|[!\$&'\(\)\*\+,;=]|:|@)|[\uE000-\uF8FF]|\/|\?)*)?(\#((([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(%[\da-f]{2})|[!\$&'\(\)\*\+,;=]|:|@)|\/|\?)*)?$/i.test(b);},_plz:function(b){return/^\b((?:0[1-46-9]\d{3})|(?:[1-357-9]\d{4})|(?:[4][0-24-9]\d{3})|(?:[6][013-9]\d{3}))\b$/.test(b);},_dateDE:function(b){return/^\d\d?\.\d\d?\.\d\d\d?\d?$/.test(b);},_dateISO:function(b){return/^\d{4}[\/-]\d{1,2}[\/-]\d{1,2}$/.test(b);},_lengthMin:function(b,c){return(b.length>=c)?true:false;},_lengthMax:function(b,c){return(b.length<=c)?true:false;},_equalTo:function(b,c){return(b==a("#"+c).val())?true:false;},_captcha:function(b,c){return this._trigger("checkCaptcha",null,b);},destroy:function(){var b=this.options;a.each(b.forms,function(c){b.forms[c].element.removeClass("ui-state-error").removeClass("ui-state-hover").removeAttr("aria-invalid").removeAttr("aria-required").unbind();if(b.forms[c].type=="group"){b.forms[c].element.next().removeClass("ui-state-error").removeClass("ui-state-hover").removeAttr("aria-invalid").removeAttr("aria-required").unbind();}});this.element.unbind(".formValidator").unbind("submit").removeData("formValidator");if(b.originalUrl!=""){this.element.attr("action",b.originalUrl);}this.element.find(".ui-formular-live, .ui-formular-error, .ui-formular-success").remove();a("#virtualBufferForm").parent().remove();},_updateVirtualBuffer:function(){var c=a("#virtualBufferForm");if(c.length){(c.val()=="1")?c.val("0"):c.val("1");}else{var b='<form><input id="virtualBufferForm" type="hidden" value="1" /></form>';a("body").append(b);}}});a.extend(a.ui.formValidator,{defaults:{validateLive:true,validateLiveMsg:true,validateTimeout:500,validateTimeoutCaptcha:3,validateOff:"Please click here to deactivate live validating of this form.",validateOn:"Please clkick here to activate live form validating.",errorSummery:true,errorsTitle:"Please check the following errors:",submitHowTo:"ajax",submitUrl:"",submitError:"Something wen't wrong while sending your data. Please retry.",submitSuccess:"Your data was succefully submitted, thank you!",originalUrl:"",selectDefault:"default"}});})(jQuery);