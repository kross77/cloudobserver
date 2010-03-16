
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
