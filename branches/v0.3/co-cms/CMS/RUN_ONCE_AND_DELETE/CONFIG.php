<?php 
///////////////////////////////////////////
// TO DO
// ADD A FORM AND PRESENT AN OPTION TO CALL NEW DB CREATION IMMIDIATLY.
// THAN
//USE THIS CODE TO PERFORM DELETE PROCESS
//		FILE_TO_REPLACE_IN.php:
//		
//		<?php
//		define("DB_SERVER", "{DB_SERVER}");
//		define("DB_USER", "{DB_USER}");
//		define("DB_PASS", "{DB_PASS}");
//		define("DB_NAME", "{DB_NAME}");
//		SCRIPT_TO_CHANGE_WITH.php:
//		
//		<?php
//		
//		$searchF  = array('{DB_SERVER}','{DB_USER}','{DB_PASS}','{DB_NAME}');
//		$replaceW = array('localhost',  'user',     'pass',     'db');
//		
//		$fh = fopen("FILE_TO_REPLACE_IN.php", 'w');
//		$file = file_get_contents($fh);
//		$file = str_replace($searchF, $replaceW, $file);
//		fwrite($fh, $file);
////////////////////////////////////////////


$message = "NOT IMPLEMENTED YET USE HANDS, You, Fucking Moron!";
?>
<?php include("header.php"); ?>
<div id="toppanel" style="position: fixed">
<div id="panel">
<div class="content clearfix"></div>
</div>
<!-- /login --> <!-- The tab on top -->
<div class="tab">
<ul class="login">
	<li class="left">&nbsp;</li>
	<li>CHANGE CONFIG OPTIONS Module</li>
	<li class="sep">|</li>
	<li id="toggle"><a href="index.php">Go to Run Once And Delete
	Module Packet Index Page </a></li>
	<li class="right">&nbsp;</li>
</ul>

</div>
<!-- / top --></div>
<!--panel -->

<div id="container">
<div id="content" style="padding-top: 100px;">
<form id="form1" action="index.php" method="post">
<fieldset class="ui-widget-content ui-corner-all"><legend
	class="ui-widget-header ui-corner-all">MESSAGE</legend> <?php if (!empty($message)) {echo " <p class=\"message\">" . $message . "</p>";} ?>
<?php if (!empty($errors)) { echo " <p class=\"message\">" . $errors . "</p>";} ?>
</fieldset>
</form>

<br />

<div>
<div></div>
<!-- / content --></div>
<!-- / container -->

</body>
</div>
</div>