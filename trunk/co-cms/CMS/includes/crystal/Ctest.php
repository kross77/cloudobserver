<?php require_once(".." . DIRECTORY_SEPARATOR . "constants.php"); ?>
<?php
require_once('Crystal.php');
$db = Crystal::db();
?>
<br/>
<h1>Users Table</h1>
<br/>
<?php 
$db->get('user')->print_as_table();
?>
<br/>
<h1>Streams Table</h1>
<br/>
<?php 
$db->get('streams')->print_as_table();
?>