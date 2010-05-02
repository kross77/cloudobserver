<?php  require_once( ".." . DIRECTORY_SEPARATOR . "includes" . DIRECTORY_SEPARATOR . "constants.php"); ?>
<?php 
require_once(".." . DIRECTORY_SEPARATOR . "includes" . DIRECTORY_SEPARATOR . "crystal" . DIRECTORY_SEPARATOR . "Crystal.php");
 
 $dn  = DB_NAME;
 $manipulation = Crystal::manipulation();
 $manipulation->drop_database($dn)->execute();
 $message = "The " . $dn . " database was deleted.";
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
	        <li>UNINSTALL DB Module</li>
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