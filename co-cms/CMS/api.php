<?php
include_once("includes/form_functions.php");
require_once(  "includes" . DIRECTORY_SEPARATOR . "constants.php");
require_once(  "includes" . DIRECTORY_SEPARATOR . "crystal" . DIRECTORY_SEPARATOR . "Crystal.php");
// Errors Array

$error = "API USER YOU MADE AN ERROR! YOU MESSED WITH ME! AND NOW YOU'LL BE PUNISHED! I WILL COME AND KILL YOU! OH! Error Code 1000: Epic Fail - You called an API with wrong attributes - GO FUCK YOUR SELF, API USER!";

// API VARIABLES
// To create anothtr API (to be able to use API from 2 or more frameworks (eg Flash SL WPF etc use Another key one for each new Framework put it into db))
$db;
$key;
$userID;
$userName;
$userPass;
$userEmail;
$streamID;
$randomVal;
$connection;

// Special API Functions

function  resetCrystal()
{
	$db = Crystal::db();
}

function resetBacicConnection()
{
	$connection = mysql_connect(DB_SERVER,DB_USER,DB_PASS);
	if (!$connection) { die("Database connection failed: " . mysql_error()); }

	$db_select = mysql_select_db(DB_NAME,$connection);
	if (!$db_select) {die( "Database selection failed: " . mysql_error()); }
}

function mysql_prep( $value ) {
	$value = stripslashes( $value );
	$value = mysql_real_escape_string( $value );
	return $value;
}

function getKey($userID = 00) 
{
	$rand_val = $userID . md5(uniqid() + mt_rand());
	$rand_val = trim(mysql_prep($rand_val));
	return $rand_val;
}

function validName( $userName ) {
	$userName = trim(mysql_prep($userName));
	if ( strlen($userName) <= 40 && strlen($userName) >= 4)
		{return $userName; } else {	die( "Name langth is invalid "); }	// Name Langth
}

function validPass( $userPass ) {
	$userPass = trim(mysql_prep($userPass));
		if ( strlen($userPass) <= 40 && strlen($userPass) >= 4)
			{return $userPass;} else {	die( "Password langth is invalid "); }	// Pass langth
}


function validEmail( $userEmail ) {
	$db = Crystal::db();
	$data = array(
 			 		'userEmail' => $userEmail
	);
	$rules = array(
	 			'userEmail' => array('valid_email, message: Please provide valid email address | unique , table: user, field: email, message : This email is already taken')
	);
	$validation = Crystal::validation($rules, $data, $db);
		if($validation->passed == TRUE)
	{ return $userEmail; } else {	print_r($validation->errors); die( " Email is invalid " ); }// Not Valid Email
}

// API FUNCTIONS

function validStreamId( $streamID ) {
	$db = Crystal::db();
	$data = array(
			'streamId' => $streamID,
	);
	$rules = array(
	  'streamId' => array('numeric, message: Please supply a valid number | unique , table: streams, field: streamID, message : This streamID is already taken '),
	 	);
	$validation = Crystal::validation($rules, $data, $db);
		if($validation->passed == TRUE)
	{ return $streamID; } else {	print_r($validation->errors); die( " Stream ID is invalid " ); }// Not Valid Email
}

function createUnregedUser( $userName ) {
			
				$name = validName($userName);
				$key = getKey();
				$query = "INSERT INTO user (
							username, CG
						) VALUES (
							'{$name}', '{$key}'
						)";
				
	$connection = mysql_connect(DB_SERVER,DB_USER,DB_PASS);
	if (!$connection) { die("Database connection failed: " . mysql_error()); }

	$db_select = mysql_select_db(DB_NAME,$connection);
	if (!$db_select) {die( "Database selection failed: " . mysql_error()); }
				
				$result = mysql_query($query, $connection);
				$userID = mysql_insert_id();
				if ($result) {echo $key; return $userID; } else {	die( "Database INSERT failed: " . mysql_error()); }
	}  

function createUser($userEmail, $userName, $userPass) {
				$email = validEmail($userEmail);
				$name = validName($userName);
				$password = validPass($userPass);
				$key = getKey();
				$hashed_password = sha1($password);
				$query = "INSERT INTO user (
							username, hashed_password, email, CG
						) VALUES (
							'{$name}', '{$hashed_password}',  '{$email}',  '{$key}'
						)";
								
	$connection = mysql_connect(DB_SERVER,DB_USER,DB_PASS);
	if (!$connection) { die("Database connection failed: " . mysql_error()); }

	$db_select = mysql_select_db(DB_NAME,$connection);
	if (!$db_select) {die( "Database selection failed: " . mysql_error()); }
				
				$result = mysql_query($query, $connection);
				$userID = mysql_insert_id();
				if ($result) { echo $key; return $userID;  } else {	die( "Database INSERT failed: " . mysql_error()); }
	}  



function createStream($streamID, $userID) {
				$db = Crystal::db();
				$data = array('userID' => $userID, 'streamID' => $streamID );
				$db->insert('streams', $data)->execute();
}
function createPassword($key, $userEmail) {

}
function setPassword($key, $userEmail, $userPass) {

}

function getMyName($streamID, $userID) {

}
// API POST\GET Processor

switch($_GET["method"])
{

	// Create

	case "createUserWithStream":


		if((int)$_GET[streamId] != null && (string)$_GET[userName] != null && (string)$_GET[userEmail] != null && (string)$_GET[userPass] != null)
          {
         // create user with pass and email and with Stream! (Stream ID should be uniqe and beter be confermed somehow by kernel)
         // You can Call once something like http://localhost/cms/api.php?method=createUserWithStream&streamId=5&userName=Olgr2&userEmail=Email@emcorp.com&userPass=000000  and go to http://localhost/cms5/includes/crystal/Ctest.php to see what has happened	
        $streamID = validStreamId($_GET[streamId]);
		$userID =createUser($_GET[userEmail], $_GET[userName], $_GET[userPass]);
		createStream($streamID, $userID);
          }
		elseif((int)$_GET[streamId] != null && (string)$_GET[userName] != null )
		{
		 // create user with NO pass and NO email But with Stream! (Stream ID should be uniqe and beter be confermed somehow by kernel)
		// You can Call once something like http://localhost/cms/api.php?method=createUserWithStream&streamId=4&userName=Ol%D0%AFDgr and go to http://localhost/cms5/includes/crystal/Ctest.php to see what has happened	
		$streamID = validStreamId($_GET[streamId]);
		$userID  =	createUnregedUser($_GET[userName]);
		createStream($streamID, $userID);
		}
		else
		{
			echo $error;
		}

		break;

case "createUser":
	if((int)$_GET[streamId] != null && (string)$_GET[userName] != null && (string)$_GET[userEmail] != null && (string)$_GET[userPass] != null)
	{
			
	}
	else
	{
		echo $error;
	}
	break;

case "createPassword":
	if((int)$_GET[key] != null && (string)$_GET[userEmail] != null && (string)$_GET[newUserPass] != null)
	{
			
	}
	else
	{
		echo $error;
	}
	break;

	// Log

case "logIn":
	if((int)$_GET[userEmail] != null && (string)$_GET[userPass] != null)
	{
			
	}
	else
	{
		echo $error;
	}
	break;

case "logOut":
	if((int)$_GET[userEmail] != null && (string)$_GET[key] != null)
	{
			
	}
	else
	{
		echo $error;
	}
	break;

	// GET

case "getMyName":
	if((int)$_GET[streamId] != null && (string)$_GET[userName] != null && (string)$_GET[userEmail] != null && (string)$_GET[userPass] != null)
	{
			
	}
	else
	{
		echo $error;
	}
	break;

case "getGatewayAddress":
	if((int)$_GET[streamId] != null && (string)$_GET[userName] != null && (string)$_GET[userEmail] != null && (string)$_GET[userPass] != null)
	{
			
	}
	else
	{
		echo $error;
	}
	break;

case "getStreamsFromAll":
	if((int)$_GET[streamId] != null && (string)$_GET[userName] != null && (string)$_GET[userEmail] != null && (string)$_GET[userPass] != null)
	{
			
	}
	else
	{
		echo $error;
	}
	break;

case "getMyStreams":
	if((int)$_GET[streamId] != null && (string)$_GET[userName] != null && (string)$_GET[userEmail] != null && (string)$_GET[userPass] != null)
	{
			
	}
	else
	{
		echo $error;
	}
	break;

	// SET

case "setMyName":
	if((int)$_GET[streamId] != null && (string)$_GET[userName] != null && (string)$_GET[userEmail] != null && (string)$_GET[userPass] != null)
	{
			
	}
	else
	{
		echo $error;
	}
	break;

case "setMyNewPassword":
	if((int)$_GET[streamId] != null && (string)$_GET[userName] != null && (string)$_GET[userEmail] != null && (string)$_GET[userPass] != null)
	{
			
	}
	else
	{
		echo $error;
	}
	break;

case "setStream":
	if((int)$_GET[streamId] != null && (string)$_GET[userName] != null && (string)$_GET[userEmail] != null && (string)$_GET[userPass] != null)
	{
			
	}
	else
	{
		echo $error;
	}
	break;

	// Delete

case "deleteStream":
	if((int)$_GET[streamId] != null && (string)$_GET[userName] != null && (string)$_GET[userEmail] != null && (string)$_GET[userPass] != null)
	{
			
	}
	else
	{
		echo $error;
	}
	break;

case "deleteUser":
	if((int)$_GET[streamId] != null && (string)$_GET[userName] != null && (string)$_GET[userEmail] != null && (string)$_GET[userPass] != null)
	{
			
	}
	else
	{
		echo $error;
	}
	break;

	// Unregistred Mathod or No method

default:
	echo $error;

 }

 ?>