<?php require_once("includes/session.php"); ?>
<?php require_once("includes/connection.php"); ?>
<?php require_once("includes/functions.php"); ?>
<?php $adress = CLOUD_OBSERVER_GATEWAY_ADDRESS; ?>

<head> 
    <link rel="stylesheet" href="css/common.css" type="text/css" />
	<link type="text/css" href="css/ui.multiselect.css" rel="stylesheet" />

		
			<link type="text/css" href="css/style.css" rel="stylesheet" />
  	<link rel="stylesheet" href="css/slide.css" type="text/css" media="screen" />
		<link type="text/css" href="css/ui-darkness/jquery-ui.css" rel="stylesheet" />	
		<script type="text/javascript" src="js/jquery-1.4.1.js"></script>
	<script type="text/javascript" src="js/jquery-ui-1.7.1.custom.min.js"></script>
	<script type="text/javascript" src="js/plugins/localisation/jquery.localisation-min.js"></script>   
	<script type="text/javascript" src="js/plugins/scrollTo/jquery.scrollTo-min.js"></script>
		<script type="text/javascript" src="js/ui.multiselect.js"></script>
	<script type="text/javascript">
		$(function(){
			$.localise('ui-multiselect', {/*language: 'en',*/ path: 'js/locale/'});
			$(".multiselect").multiselect();
			$('#switcher').themeswitcher();
		});
	</script>
		<script type="text/javascript" src="js/ui.formValidator.js"></script>
		<script src="media/AC_OETags.js" language="javascript"></script>
		<link rel="stylesheet" type="text/css" href="history/history.css" />
		<script src="media/history/history.js" language="javascript"></script>
		<script language="JavaScript" type="text/javascript">

// -----------------------------------------------------------------------------
// Globals
// Major version of Flash required
var requiredMajorVersion = 10;
// Minor version of Flash required
var requiredMinorVersion = 0;
// Minor version of Flash required
var requiredRevision = 0;
// -----------------------------------------------------------------------------

</script>
</head>
<body>

 	<div class="ui-widget-content ui-corner-all" style="width: 459px; margin: 0 auto;">
    <form action="Debug.php" method="post">
    		<fieldset class="ui-widget-content ui-corner-all">
  <select id="Streams" class="multiselect ui-widget-content ui-corner-all" multiple="multiple" name="Streams[]">
     <?php      
     $query = "
SELECT s.streamId, s.userId, u.username
FROM streams AS s
JOIN user AS u ON s.userId = u.id
LIMIT 0 , 30
  ";
$streams_set = mysql_query($query, $connection);
    confirm_query($streams_set);    
    $streams_count = mysql_num_rows($streams_set);

while ($row = mysql_fetch_array($streams_set)){
 echo '<option value="' . $row['streamId'] . '"' . (in_array($row['streamId'], $_POST['Streams']) ? ' selected' : ''). '>  ' . $row['username'] . ' (' . $row['streamId'] .')' .'</option> ';
} ?>
      </select>
      <br/>
      <input type="submit"  name="submitForm" id="submitForm"  value="Play selected streams!"/>    
     <input type="submit" class="ui-state-default ui-corner-all" name="submitForm" id="submitForm"  value="Save selected streams!"/>    
  </fieldset>
</form>
</div>
<div>
<script language="JavaScript" type="text/javascript">

// Version check for the Flash Player that has the ability to start Player Product Install (6.0r65)
var hasProductInstall = DetectFlashVer(6, 0, 65);

// Version check based upon the values defined in globals
var hasRequestedVersion = DetectFlashVer(requiredMajorVersion, requiredMinorVersion, requiredRevision);

if ( hasProductInstall && !hasRequestedVersion ) {
	// DO NOT MODIFY THE FOLLOWING FOUR LINES
	// Location visited after installation is complete if installation is required
	var MMPlayerType = (isIE == true) ? "ActiveX" : "PlugIn";
	var MMredirectURL = window.location;
    document.title = document.title.slice(0, 47) + " - Flash Player Installation";
    var MMdoctitle = document.title;

	AC_FL_RunContent(
		"src", "media/playerProductInstall",
		"FlashVars", "MMredirectURL="+MMredirectURL+'&MMplayerType='+MMPlayerType+'&MMdoctitle='+MMdoctitle+"",
		"width", "100%",
		"height", "100%",
		"align", "middle",
		"id", "CloudObserverCMSFP",
		"quality", "high",
		"bgcolor", "#ffffff",
		"name", "CloudObserverCMSFP",
		"allowScriptAccess","sameDomain",
		"type", "application/x-shockwave-flash",
		"pluginspage", "http://www.adobe.com/go/getflashplayer"
	);
} else if (hasRequestedVersion) {
	// if we've detected an acceptable version
	// embed the Flash Content SWF when all tests are passed
	AC_FL_RunContent(
			"src", "media/CloudObserverCMSFP",
			   "flashVars", "<?php
			 

  if (isset($_POST['submitForm'])){
	  	echo "&url=" , $adress;
	  $array =	$_POST[Streams];
$count = count($array);
echo "&sid=" ;
for ($i = 0; $i < $count; $i++) {
 echo $array[$i];
 if($i <= $count - 2){echo ",";} else{}

}}?>",
			"width", "100%",
			"height", "100%",
			"align", "middle",
			"id", "CloudObserverCMSFP",
			"quality", "high",
			"bgcolor", "#ffffff",
			"name", "CloudObserverCMSFP",
			"allowScriptAccess","sameDomain",
			"type", "application/x-shockwave-flash",
			"pluginspage", "http://www.adobe.com/go/getflashplayer"
	);
  } else {  // flash is too old or we can't detect the plugin
    var alternateContent = 'Alternate HTML content should be placed here. '
  	+ 'This content requires the Adobe Flash Player. '
   	+ '<a href=http://www.adobe.com/go/getflash/>Get Flash</a>';
    document.write(alternateContent);  // insert non-flash content
  }

</script>
<noscript>
  	<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000"
			id="CloudObserverCMSFP" width="100%" height="100%"
			codebase="http://fpdownload.macromedia.com/get/flashplayer/current/swflash.cab">
			<param name="movie" value="media/CloudObserverCMSFP.swf" />
			<param name="quality" value="high" />
			<param name="bgcolor" value="#ffffff" />
			<param name="allowScriptAccess" value="sameDomain" />
			 <param name='flashVars' value='<?php
			 

  if (isset($_POST['submitForm'])){
	  	echo ",url=" , $adress;
	  $array =	$_POST[Streams];
$count = count($array);
echo ",sid=" ;
for ($i = 0; $i < $count; $i++) {
 echo $array[$i];
if($i <= $count - 2){echo ",";} else{}

}}?>'/>
			<embed src="media/CloudObserverCMSFP.swf" quality="high" bgcolor="#ffffff"
				width="100%" height="100%" name="CloudObserverCMSFP" align="middle"
				play="true"
				loop="false"
				quality="high"
				allowScriptAccess="sameDomain"
				type="application/x-shockwave-flash"
				pluginspage="http://www.adobe.com/go/getflashplayer">
			</embed>
	</object>
</noscript>
</div>
</body> 
</html>