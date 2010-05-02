<?php  require_once( ".." . DIRECTORY_SEPARATOR . "includes" . DIRECTORY_SEPARATOR . "constants.php");?>
<?php
$dn  = DB_NAME;
// HERE WE CAN NOT USE CRYSTAL - this part is DB type dependent.
// mysql oriented DB creation
$connection = mysql_connect(DB_SERVER,DB_USER,DB_PASS);
if (!$connection) {
		$errors .= "Database connection failed: " . mysql_error();
}
$query = "CREATE DATABASE  `" . DB_NAME ."` ;";
$subject_set = mysql_query($query, $connection);
// $errors .= " <br/> " . mysql_error(); // some Debug info...
$message = "The " . $dn . " database was Created. ";
	
// Here we could use CRYSTAL but there is no actual need in it and I do not know how to say to create something with param "NULL DEFAULT NULL" in it with crystal
$db_select = mysql_select_db(DB_NAME,$connection);
if (!$db_select) {
 $errors .= " <br/> " . mysql_error(); // some Debug info...
}


					$query = "CREATE TABLE `user` (
		`id` INT( 11 ) NOT NULL AUTO_INCREMENT ,
		`username` VARCHAR( 100 ) NOT NULL ,
		`hashed_password` VARCHAR( 100 ) NULL DEFAULT NULL ,
		`email` VARCHAR( 100 ) NULL DEFAULT NULL ,
		`CG` VARCHAR( 100 ) NULL DEFAULT NULL ,
		`TIMESTAMP` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ,
		PRIMARY KEY (  `id` )
		) ENGINE = MYISAM ; ";
$subject_set = mysql_query($query, $connection);
 // $errors .= " <br/> " . mysql_error(); //some Debug info...	
					$message .= " <br/> The USER table was successfully created.";
					
		$query = "CREATE TABLE   `streams` (
		`id` INT( 11 ) NOT NULL AUTO_INCREMENT ,
		`userID` INT( 11 ) NOT NULL ,
		`streamID` INT( 11 ) NOT NULL ,
		`LastSeen` DATETIME NOT NULL ,
		PRIMARY KEY (  `id` )
		) ENGINE = MYISAM ; ";
$subject_set = mysql_query($query, $connection);
	// $errors .= " <br/> " . mysql_error(); //some Debug info...		
					$message .= " <br/> The STREAMS table was successfully created.";

		?>
<?php include("header.php"); ?>
		<div id="toppanel" style="position:fixed">
	<div id="panel">
		<div class="content clearfix">

		</div>
	</div> <!-- /login -->	

    <!-- The tab on top -->	
	<div class="tab">
		<ul class="login">
	    	<li class="left">&nbsp;</li>
	        <li>INSTALL DB Module</li>
			<li class="sep">|</li>
			<li id="toggle">
			<a  href="index.php">Go to Run Once And Delete Module Packet Index Page </a>
			</li> 
	    	<li class="right">&nbsp;</li>
		</ul> 

	</div> <!-- / top -->
	
</div> <!--panel -->

    <div id="container">
		<div id="content" style="padding-top:100px;">
			<form id="form1" action="index.php" method="post">
	<fieldset class="ui-widget-content ui-corner-all">
			<legend class="ui-widget-header ui-corner-all">MESSAGE</legend>

			<?php if (!empty($message)) {echo " <p class=\"message\">" . $message . "</p>";} ?>
<?php if (!empty($errors)) { echo " <p class=\"message\">" . $errors . "</p>";} ?>
				</fieldset>	
	</form>

			<br/>
			
			<div>
			<div>
		</div><!-- / content -->		
	</div><!-- / container -->
	
</body>
