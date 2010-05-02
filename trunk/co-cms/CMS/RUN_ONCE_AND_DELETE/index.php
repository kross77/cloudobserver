<?php require_once("../includes/crystal/Crystal.php"); ?>
<?php 
$dn = DB_NAME;
// $manipulation = Crystal::manipulation();
// $manipulation->drop_database($dn)->execute();
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
	        <li>Run Once And Delete Module Packet</li>
	    	<li class="right">&nbsp;</li>
		</ul> 

	</div> <!-- / top -->
	
</div> <!--panel -->

    <div id="container">
		<div id="content" style="padding-top:100px;">
			<form id="form1" action="index.php" method="post">
	<fieldset class="ui-widget-content ui-corner-all">
			<legend class="ui-widget-header ui-corner-all">LINKS</legend>
			<a  href="INSTALL.php"> INSTALL CMS Module </a> <BR/>
			<a  href="DELETE_DB.php"> Delete CURRENT CMS DB Module </a>
				
				</fieldset>	
	</form>

			<br/>
			
			<div>
			<div>
		</div><!-- / content -->		
	</div><!-- / container -->
	
</body>