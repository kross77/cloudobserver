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
	        <li class="sep">|</li>
			<li id="toggle">
			<a  href="../index.php">Go to CloudObserverCMS Main Page </a>
			</li> 
	    	<li class="right">&nbsp;</li>
		</ul> 

	</div> <!-- / top -->
	
</div> <!--panel -->

    <div id="container">
		<div id="content" style="padding-top:100px;">
			<form>
	<fieldset class="ui-widget-content ui-corner-all">
			<legend class="ui-widget-header ui-corner-all">CONFIG MODULES</legend>
				<a  href="CONFIG.php"> CONFIG CMS PARAMETERS </a>		
				</fieldset>	
	</form>
			<br/>
						<form >
	<fieldset class="ui-widget-content ui-corner-all">
			<legend class="ui-widget-header ui-corner-all">DB MODULES</legend>
						<a  href="INSTALL.php"> INSTALL CMS DB </a> <BR/>
						<a  href="DELETE_DB.php"> DELETE CURRENT CMS DB</a>	
				</fieldset>	
	</form>
			<br/>
									<form >
	<fieldset class="ui-widget-content ui-corner-all">
			<legend class="ui-widget-header ui-corner-all">UNINSTALL MODULES</legend>
	<a  href="DELETE_ALL_CMS.php?MODULE=FILES"> DELETE ALL CMS FILES </a> <BR/>
	<a  href="DELETE_ALL_CMS.php?MODULE=ALL"> DELETE ALL CMS FILES AND DATABASE RECORDS </a>
				</fieldset>	
	</form>
			<br/>
				
			
				
			<div>
			<div>
		</div><!-- / content -->		
	</div><!-- / container -->
	
</body>