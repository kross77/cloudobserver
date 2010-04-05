
<?php require_once("includes/connection.php"); ?>
<?php require_once("includes/functions.php"); ?>
<?php
		include_once("includes/form_functions.php");
		$dn = DB_NAME;
			$query = "CREATE TABLE `user` (
`id` INT( 11 ) NOT NULL AUTO_INCREMENT ,
`username` VARCHAR( 100 ) NOT NULL ,
`hashed_password` VARCHAR( 100 ) NULL DEFAULT NULL ,
`email` VARCHAR( 100 ) NULL DEFAULT NULL ,
`CG` VARCHAR( 100 ) NULL DEFAULT NULL ,
`TIMESTAMP` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ,
PRIMARY KEY (  `id` )
) ENGINE = MYISAM ; ";
			$result_set = mysql_query($query);
			confirm_query($result_set);			
			$message = "The USER table was successfully created.";
			
						$query = "CREATE TABLE   `streams` (
`id` INT( 11 ) NOT NULL AUTO_INCREMENT ,
`userID` INT( 11 ) NOT NULL ,
`streamID` INT( 11 ) NOT NULL ,
`LastSeen` DATETIME NOT NULL ,
PRIMARY KEY (  `id` )
) ENGINE = MYISAM ; ";
			$result_set = mysql_query($query);
			confirm_query($result_set);			
			$message = "The STREAMS table was successfully created.";

		?>
		<?php include("includes/header.php"); ?>
		<div id="toppanel" style="position:fixed">
	<div id="panel">
		<div class="content clearfix">

		</div>
	</div> <!-- /login -->	

    <!-- The tab on top -->	
	<div class="tab">
		<ul class="login">
	    	<li class="left">&nbsp;</li>
	        <li>Set Up Tables Module</li>
		 	<li class="sep">|</li>
			<li id="toggle">
			<a  href="logout.php">		Go to Main Page </a>
			</li>
	    	<li class="right">&nbsp;</li>
		</ul> 

	</div> <!-- / top -->
	
</div> <!--panel -->

    <div id="container">
		<div id="content" style="padding-top:100px;">
			<?php if (!empty($message)) {echo "<h2>message</h2> <p class=\"message\">" . $message . "</p>";} ?>
			<?php if (!empty($errors)) { display_errors($errors); } ?>
			<br/>
			<h1> <a  href="logout.php">		Go to Main Page </a> <h1>
			<div>
			<div>
		</div><!-- / content -->		
	</div><!-- / container -->
	
</body>
