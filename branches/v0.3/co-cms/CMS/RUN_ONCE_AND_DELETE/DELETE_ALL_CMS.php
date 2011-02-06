<?php 
///////////////////////////////////////////
// TO DO
// ADD A BUTTON AND A WORNING.
// ADD DB CLEANING CALL FIRST
// THAN
//USE THIS CODE TO PERFORM DELETE PROCESS
//    function rmdir_r ( $dir, $DeleteMe = TRUE )
//    {
//        if ( ! $dh = @opendir ( $dir ) ) return;
//        while ( false !== ( $obj = readdir ( $dh ) ) )
//    {
//    if ( $obj == '.' || $obj == '..') continue;
//    if ( ! @unlink ( $dir . '/' . $obj ) ) rmdir_r ( $dir . '/' . $obj, true );
//        }
//
//    closedir ( $dh );
//    if ( $DeleteMe )
//        {
//            @rmdir ( $dir );
//        }
//    }
////use like this:
//
//rmdir_r( 'abc' );
// ADD DB CLEANING CALL FIRST
////////////////////////////////////////////


$message = "NOT IMPLEMENTED YET USE HANDS, BEACH!";
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
	<li>DELETE ALL CMS AND ITS CONTENTS Module</li>
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