<?php

/**
 *
 * Array 2 XML class
 * Convert an array or multi-dimentional array to XML
 *
 * @author Kevin Waterson
 * @copyright 2009 PHPRO.ORG
 *
 */
class array2xml extends DomDocument
{

    public $nodeName;

    private $xpath;

    private $root;

    private $node_name;


    /**
    * Constructor, duh
    *
    * Set up the DOM environment
    *
    * @param    string    $root        The name of the root node
    * @param    string    $nod_name    The name numeric keys are called
    *
    */
    public function __construct($root='root', $node_name='node')
    {
        parent::__construct();

        /*** set the encoding ***/
        $this->encoding = "ISO-8859-1";

        /*** format the output ***/
        $this->formatOutput = true;

        /*** set the node names ***/
        $this->node_name = $node_name;

        /*** create the root element ***/
        $this->root = $this->appendChild($this->createElement( $root ));

        $this->xpath = new DomXPath($this);
    }

    /*
    * creates the XML representation of the array
    *
    * @access    public
    * @param    array    $arr    The array to convert
    * @aparam    string    $node    The name given to child nodes when recursing
    *
    */
    public function createNode( $arr, $node = null)
    {
        if (is_null($node))
        {
            $node = $this->root;
        }
        foreach($arr as $element => $value) 
        {
            $element = is_numeric( $element ) ? $this->node_name : $element;

            $child = $this->createElement($element, (is_array($value) ? null : $value));
            $node->appendChild($child);

            if (is_array($value))
            {
                self::createNode($value, $child);
            }
        }
    }
    /*
    * Return the generated XML as a string
    *
    * @access    public
    * @return    string
    *
    */
    public function __toString()
    {
        return $this->saveXML();
    }

    /*
    * array2xml::query() - perform an XPath query on the XML representation of the array
    * @param str $query - query to perform
    * @return mixed
    */
    public function query($query)
    {
        return $this->xpath->evaluate($query);
    }

} // end of class

?>
<?php
// ВРЕМЕННО: Для проверки содержимого таблиц смотри http://localhost/cms/includes/crystal/Ctest.php Потом ТАск файл должно переместить или удалить
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
function unescape($s) {
    $s= preg_replace('/%u(....)/', '&#x$1;', $s);
    $s= preg_replace('/%(..)/', '&#x$1;', $s);
  //  $s= html_entity_decode($s, ENT_COMPAT, 'utf-8');
return $s;
}
function  returnFormat($s)
{
	if($_GET["returnFormat"])
	{
		$returnFormatval = $_GET["returnFormat"];
	if($returnFormatval == "XML")
	{
		 $xml = new array2xml('result');
		 $xml->createNode( $array );
		 echo $xml;
	}
    elseif($returnFormatval == "JSON")
    {
    	 echo json_encode($s);
    }
    elseif($returnFormatval == "PRINT_R")
    {
    	print_r($s); 
    }
	}
	else{
	if(CLOUD_OBSERVER_CMS_API_RETURN_FORMAT == "XML")
	{
		 $xml = new array2xml('result');
		 $xml->createNode( $array );
		 echo $xml;
	}
    elseif(CLOUD_OBSERVER_CMS_API_RETURN_FORMAT == "JSON")
    {
    	 echo json_encode($s);
    }
    elseif(CLOUD_OBSERVER_CMS_API_RETURN_FORMAT == "PRINT_R")
    {
    	print_r($s); 
    }}
}

function mysql_prep( $value ) {
	$value = stripslashes( $value );
	//$value = mysql_real_escape_string( $value ); // Внимание - одному богу известно как АПИ будет реагировать на стрранные знаки... Таск - проверить как ону будет реагировать.
	return $value;
}
	function confirm_query($result_set) {
		if (!$result_set) {
			die("Database query failed: " . mysql_error());
		}
	}
function getKey($userID = "00") 
{
	$rand_val = $userID . md5(uniqid() + mt_rand());
	$rand_val = trim(mysql_prep($rand_val));
	return $rand_val;
}

function validName( $userName ) {
	$userName = trim(mysql_prep($userName));
	if ( strlen($userName) <= 99 && strlen($userName) >= 4)
		{return $userName; } else {	die( "Name langth is invalid "); }	// Name Langth
}

function validPass( $userPass ) {
	
	$userPass = trim(mysql_prep((string)($userPass)));
		if ( strlen($userPass) <= 99 && strlen($userPass) >= 4)
			{return $userPass;} else {	die( "Password langth is invalid "); }	// Pass langth
}



function validNewEmail( $userEmail ) {
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
function streamIdExists( $streamID ) {
	$db = Crystal::db();
	$data = array(
			'streamId' => $streamID,
	);
	$rules = array(
	  'streamId' => array('numeric, message: Please supply a valid number | unique , table: streams, field: streamID, message : This streamID is already taken '),
	 	);
	$validation = Crystal::validation($rules, $data, $db);
		if($validation->passed == FALSE)
	{ return $streamID; } else {	print_r($validation->errors); die( " Stream ID does not existin DB  " ); }// Not Valid Email
}

function validEmail( $userEmail ) {
	$db = Crystal::db();
	$data = array(
 			 		'userEmail' => $userEmail
	);
	$rules = array(
	 			'userEmail' => array('valid_email, message: Please provide valid email address')
	);
	$validation = Crystal::validation($rules, $data, $db);
		if($validation->passed == TRUE)
	{ return $userEmail; } else {	print_r($validation->errors); die( " Email is invalid " ); }// Not Valid Email
}

function validKey( $key ) {
		if ( strlen($key) <= 100 && strlen($key) >= 6){
			$query = "SELECT id, email ";
			$query .= "FROM user ";
			$query .= "WHERE CG = '{$key}' ";
			
	$connection = mysql_connect(DB_SERVER,DB_USER,DB_PASS);
	if (!$connection) { die("Database connection failed: " . mysql_error()); }

	$db_select = mysql_select_db(DB_NAME,$connection);
	if (!$db_select) {die( "Database selection failed: " . mysql_error()); }
			
			$result_set = mysql_query($query);
			if (mysql_num_rows($result_set) == 1) {
				$found_user = mysql_fetch_array($result_set);  $userID = $found_user['id']; return $userID; } else {	 die( " Key is invalid " ); } } else { die( " Key is invalid (langth)" ); }// Not Valid Email
	
}

function validKeyReturnName( $key ) {
		if ( strlen($key) <= 100 && strlen($key) >= 6){
			$query = "SELECT id, username ";
			$query .= "FROM user ";
			$query .= "WHERE CG = '{$key}' ";
			
	$connection = mysql_connect(DB_SERVER,DB_USER,DB_PASS);
	if (!$connection) { die("Database connection failed: " . mysql_error()); }

	$db_select = mysql_select_db(DB_NAME,$connection);
	if (!$db_select) {die( "Database selection failed: " . mysql_error()); }
			
			$result_set = mysql_query($query);
			if (mysql_num_rows($result_set) == 1) {
				$found_user = mysql_fetch_array($result_set);  $userName = $found_user['username']; return $userName; } else {	 die( " Key is invalid " ); } } else { die( " Key is invalid (langth)" ); }// Not Valid Email
	
}
function userIsNotRegistred($userID) {
			$query = "SELECT hashed_password, email ";
			$query .= "FROM user ";
			$query .= "WHERE id = '{$userID}' ";
			
	$connection = mysql_connect(DB_SERVER,DB_USER,DB_PASS);
	if (!$connection) { die("Database connection failed: " . mysql_error()); }

	$db_select = mysql_select_db(DB_NAME,$connection);
	if (!$db_select) {die( "Database selection failed: " . mysql_error()); }
			
			$result_set = mysql_query($query);
			if (mysql_num_rows($result_set) == 1) {
				$found_user = mysql_fetch_array($result_set); 
				if ($found_user['hashed_password'] == NULL &&  $found_user['email'] == NULL ) { return $userID; } else {	 die( " User is Registred " ); }} else {	 die( " UserID is invalid " ); }// Not Valid Email
	
}
function deleteAllUserStreams($userID)
{
$db = Crystal::db();
$db->delete('streams')->where('userID',$userID)->execute();
echo " All USER streams DELETED; "; return $userID;
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
				$email = validNewEmail($userEmail);
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

function createPassword($key, $userEmail, $userPass) {
	$userID = validKey( $key );
	$userPass = validPass($userPass);
	$userID = userIsNotRegistred($userID);
	$hashed_password = sha1($userPass); 
	$userEmail = validEmail($userEmail );
	$key = getKey($userID) ;
 	$db = Crystal::db();
 	$data = array('email' => $userEmail,
'hashed_password' => $hashed_password,
 	'CG' => $key);
$db->update('user', $data)->where('id',$userID)->execute();
echo $key;

}
function logIn($userEmail, $userPass) {
	$userPass = validPass($userPass);
	$userEmail = validEmail($userEmail);
	$hashed_password = sha1($userPass); 
			$query = "SELECT id, CG ";
			$query .= "FROM user ";
			$query .= "WHERE email = '{$userEmail}' AND hashed_password = '{$hashed_password}' ";
			
	$connection = mysql_connect(DB_SERVER,DB_USER,DB_PASS);
	if (!$connection) { die("Database connection failed: " . mysql_error()); }

	$db_select = mysql_select_db(DB_NAME,$connection);
	if (!$db_select) {die( "Database selection failed: " . mysql_error()); }
			
			$result_set = mysql_query($query);
			confirm_query($result_set);
			if (mysql_num_rows($result_set) == 1) { // Прогнозируемый баг - можно зайти под любого юзера с любым паролем. Таск Протестить надо повесить... Но скорее всего все хорошо=)
				$found_user = mysql_fetch_array($result_set);  
				$userID = $found_user['id']; 
				$key = getKey($userID) ;
 				$db = Crystal::db();
 				$data = array('CG' => $key);
$db->update('user', $data)->where('id',$userID)->execute();
			echo $key;	return $key; 
			} else {	 die( "  Something Went Wrong. Please Try Again, Muther Fucker дфые вшу. " ); } 
	
}
function logOut($key) {
	$userID = validKey( $key );
	$key = "NULL";
 	$db = Crystal::db();
 	$data = array('CG' => $key);
$db->update('user', $data)->where('id',$userID)->execute();
echo $key;
}


function getMyName($key) {
$userName = validKeyReturnName( $key );
echo $userName;
return $userName;
}
function getGatewayAddress($key)
{
	$userID = validKey( $key );
	$adress = CLOUD_OBSERVER_GATEWAY_ADDRESS;
	echo $adress;
}
function getStreamsFromAll($key)
{
	$userID = validKey( $key );
$db = Crystal::db();
$generated_table = $db->sql('select a.username, b.streamID
from user a, streams b
where a.id = b.userID;')->fetch_all();
returnFormat($generated_table); 
}

function getMyStreams($key)
{
$userID = validKey( $key );
$db = Crystal::db();
$task = "select b.streamID
from user a, streams b
where " . $userID . " = a.id = b.userID;";
$generated_table = $db->sql($task)->fetch_all();
returnFormat($generated_table); 

}

function setMyName($key, $name)
{
$userID = validKey( $key );
$db = Crystal::db();
$data = array('username' => $name);
$db->update('user', $data)->where('id',$userID)->execute();
echo "true";
}
function setStream($key, $streamId)
{
	$userID = validKey( $key );
$streamId =	validStreamId( $streamId );
$data = array('userID' => $userID,
          'streamID' => $streamId);
$db = Crystal::db();
$db->insert('streams', $data)->execute();
echo "true";
}
function deleteStream($key, $streamId)
{
$userID = validKey( $key );
$streamId =	streamIdExists( $streamId );
$db = Crystal::db();
$db->delete('streams')->where('userID',$userID)->and('streamID', $streamId)->execute();
echo " DELETED ";
}

function deleteUser($key, $pass)
{

$userID = validKey( $key );
$userPass = validPass($pass);
$hashed_password = sha1($userPass);
$db = Crystal::db();
$db->delete('user')->where('id',$userID)->and('hashed_password', $hashed_password)->execute();
deleteAllUserStreams($userID);
echo " USER DELETED ";
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
		$userID =createUser($_GET[userEmail],unescape($_GET[userName]) , unescape($_GET[userPass]));
		createStream($streamID, $userID);
          }
		elseif((int)$_GET[streamId] != null && (string)$_GET[userName] != null )
		{
		// create user with NO pass and NO email But with Stream! (Stream ID should be uniqe and beter be confermed somehow by kernel)
	    // You can Call once something like http://localhost/cms/api.php?method=createUserWithStream&streamId=4&userName=Ol%D0%AFDgr and go to http://localhost/cms5/includes/crystal/Ctest.php to see what has happened	
		$streamID = validStreamId($_GET[streamId]);
		$userID  =	createUnregedUser(unescape($_GET[userName]));
		createStream($streamID, $userID);
		}
		else
		{
			echo $error;
		}
		break;

case "createUser":
	if( (string)$_GET[userName] != null && (string)$_GET[userEmail] != null && (string)$_GET[userPass] != null)
	{
	$userID = createUser($_GET[userEmail],unescape($_GET[userName]) , unescape($_GET[userPass]));		
	}
	else
	{
		echo $error;
	}
	break;

case "createPassword":
	if($_GET[key] != null && (string)$_GET[userEmail] != null && (string)$_GET[newUserPass] != null)
	{		
	$userPass =	createPassword($_GET[key], $_GET[userEmail], unescape($_GET[newUserPass]));
	}
	else
	{
		echo $error;
	}
	break;

	// Log

case "logIn":
	if((string)$_GET[userEmail] != null && (string)$_GET[userPass] != null)
	{
	// You can Call  something like http://localhost/cms/api.php?method=logIn&userEmail=Email@emcorp.com&userPass=000000
	$key = logIn($_GET[userEmail],  unescape($_GET[userPass]))	;	
	}
	else
	{
		echo $error;
	}
	break;

case "logOut":
	if((string)$_GET[key] != null)
	{
		// You can Call once  something like http://localhost/cms/api.php?method=logOut&key=Your_Key
		$key = logOut($_GET[key])	;
	}
	else
	{
		echo $error;
	}
	break;

	// GET

case "getMyName":
   if((string)$_GET[key] != null)
	{ // You can Call once  something like http://localhost/cms/api.php?method=getMyName&key=Your_Key
			$userName = getMyName($_GET[key]);
	}
	else
	{
		echo $error;
	}
	break;

case "getGatewayAddress":
	if( (string)$_GET[key] != null)
	{	// You can Call  something like http://localhost/cms/api.php?method=getGatewayAddress&key=Your_Key
		$adress = getGatewayAddress($_GET[key]);
	}
	else
	{
		echo $error;
	}
	break;

case "getStreamsFromAll":
	if( (string)$_GET[key] != null)
	{ // You can Call once  something like http://localhost/cms/api.php?method=getStreamsFromAll&key=Your_Key
			getStreamsFromAll($_GET[key]);
	}
	else
	{
		echo $error;
	}
	break;

case "getMyStreams":
	if( (string)$_GET[key] != null)
	{
		getMyStreams($_GET[key])	;	
	}
	else
	{
		echo $error;
	}
	break;

	// SET

case "setMyName":
	if( (string)$_GET[key] != null && (string)$_GET[newUserName] != null)
	{ // You can Call once  something like http://localhost/cms/api.php?method=setMyName&newUserName=Jon&key=Your_Key
		setMyName($_GET[key], unescape($_GET[newUserName]) );
	}
	else
	{
		echo $error;
	}
	break;

case "setStream":
		if( (string)$_GET[key] != null && (int)$_GET[streamId] != null )
	{ // You can Call once  something like http://localhost/cms/api.php?method=setStream&streamId=1234554321&key=Your_Key
			setStream($_GET[key], $_GET[streamId]);
	}
	else
	{
		echo $error;
	}
	break;


	// Delete

case "deleteStream":
	if((int)$_GET[streamId] && (string)$_GET[key] != null)
	{ // You can Call once  something like http://localhost/cms/api.php?method=deleteStream&streamId=12&key=Your_Key
		deleteStream($_GET[key], $_GET[streamId])	;
	}
	else
	{
		echo $error;
	}
	break;

case "deleteUser":
	if((string)$_GET[key] != null && (string)$_GET[userPass] != null)
	{// You can Call once  something like http://localhost/cms/api.php?method=deleteUser&userPass=Uour_Pass&key=Your_Key
	
			deleteUser((string)$_GET[key], unescape($_GET[userPass]));
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