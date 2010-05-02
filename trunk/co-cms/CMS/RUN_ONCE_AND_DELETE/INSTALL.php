<?php  require_once( ".." . DIRECTORY_SEPARATOR . "includes" . DIRECTORY_SEPARATOR . "constants.php");?>

<?php // mysql oriented DB creation
$connection = mysql_connect(DB_SERVER,DB_USER,DB_PASS);
if (!$connection) {
	die("Database connection failed: " . mysql_error());
}

$query = "CREATE DATABASE  `" . DB_NAME ."` ;";
$subject_set = mysql_query($query, $connection);
// 
?>

<?php  require_once(".." . DIRECTORY_SEPARATOR . "includes" . DIRECTORY_SEPARATOR . "crystal" . DIRECTORY_SEPARATOR . "Crystal.php"); ?>

<?php


		$dn = DB_NAME;
		$manipulation = Crystal::manipulation();
		//$manipulation->create_database($dn)->execute();

//		
//$fields = array(
//				'id' => array('type' => 'int', 'auto_increment' => TRUE, 'unsigned' => TRUE, 'primary_key' => TRUE),
//                'username' => array('type' => 'varchar', 'constraint' => '128' , 'NOT NULL' => TRUE),
//                'hashed_password' => array('type' => 'varchar', 'constraint' => '128', 'NULL DEFAULT'=>'NULL' ),
//				'email' => array('type' => 'varchar', 'constraint' => '128', 'NULL DEFAULT'=>'NULL' ),
//				'CG' => array('type' => 'varchar', 'constraint' => '128' , 'NOT NULL DEFAULT' => TRUE ),
//				'TIMESTAMP' => array('type' => 'TIMESTAMP', 'NOT NULL DEFAULT' => TRUE, 'CURRENT_TIMESTAMP' => TRUE )
//                );
//$table_options = array('engine' => 'MYISAM', 'char_set' => 'utf8','collation' => 'utf8_general_ci');
//   
//$manipulation->create_table('test_table', $table_options)->with_fields($fields)->execute();
		
		
/////////////////	
//					$query = "CREATE TABLE `user` (
//		`id` INT( 11 ) NOT NULL AUTO_INCREMENT ,
//		`username` VARCHAR( 100 ) NOT NULL ,
//		`hashed_password` VARCHAR( 100 ) NULL DEFAULT NULL ,
//		`email` VARCHAR( 100 ) NULL DEFAULT NULL ,
//		`CG` VARCHAR( 100 ) NULL DEFAULT NULL ,
//		`TIMESTAMP` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ,
//		PRIMARY KEY (  `id` )
//		) ENGINE = MYISAM ; ";
//					$result_set = mysql_query($query);
//					confirm_query($result_set);			
//					$message = "The USER table was successfully created.";
//					
//								$query = "CREATE TABLE   `streams` (
//		`id` INT( 11 ) NOT NULL AUTO_INCREMENT ,
//		`userID` INT( 11 ) NOT NULL ,
//		`streamID` INT( 11 ) NOT NULL ,
//		`LastSeen` DATETIME NOT NULL ,
//		PRIMARY KEY (  `id` )
//		) ENGINE = MYISAM ; ";
//					$result_set = mysql_query($query);
//					confirm_query($result_set);			
//					$message = "The STREAMS table was successfully created.";

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
			<legend class="ui-widget-header ui-corner-all">message</legend>

			<?php if (!empty($message)) {echo " <p class=\"message\">" . $message . "</p>";} ?>
			<?php if (!empty($errors)) { display_errors($errors); } ?>
				</fieldset>	
	</form>

			<br/>
			
			<div>
			<div>
		</div><!-- / content -->		
	</div><!-- / container -->
	
</body>
