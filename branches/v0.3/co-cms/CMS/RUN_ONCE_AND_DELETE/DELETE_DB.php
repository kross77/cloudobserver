<?php  require_once( ".." . DIRECTORY_SEPARATOR . "includes" . DIRECTORY_SEPARATOR . "constants.php"); ?>
<?php 
$dn  = DB_NAME;
// HERE WE CAN USE CRYSTAL - But it is not what we need because it dies with error if BD is already deleted.
// See crystal code 
// require_once(".." . DIRECTORY_SEPARATOR . "includes" . DIRECTORY_SEPARATOR . "crystal" . DIRECTORY_SEPARATOR . "Crystal.php");  
// $manipulation = Crystal::manipulation();
// $manipulation->drop_database($dn)->execute();
// So if you want - just uncomment=)

// mysql oriented DB delite
$connection = mysql_connect(DB_SERVER,DB_USER,DB_PASS);
if (!$connection) {
	$errors .= "Database connection failed: " . mysql_error();
}
$query = "DROP DATABASE  `" . DB_NAME ."` ;";
$subject_set = mysql_query($query, $connection);
// $errors .= " \n " . mysql_error(); some Debug info...
$message = "The " . $dn . " database was deleted.";
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
	<li>UNINSTALL DB Module</li>
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

<body></body>
</div>
</div>