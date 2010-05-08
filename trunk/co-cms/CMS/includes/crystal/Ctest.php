<?php
// File for testing Crystal and SQL. Can go public into Admin aerea or should be deleted in future 
// BTW Crystall does not support rUssiaN it seems to me...
require_once(".." . DIRECTORY_SEPARATOR . "constants.php"); 
require_once('Crystal.php');
$db = Crystal::db();
?>
<br/>
<h1>User-Streams Mix - Generated Table</h1>
<br/>
<?php 
$db->sql('select a.username, b.streamID
from user a, streams b
where a.id = b.userID;')->print_as_table();
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
<br/>
<h1>User-Streams Mix - Generated Table. Specialy for user ¹1</h1>
<br/>
<?php 
$db->sql('select a.username, b.streamID
from user a, streams b
where 1 = a.id = b.userID;')->print_as_table();
?>
