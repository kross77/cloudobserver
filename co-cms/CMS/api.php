<?php require_once("includes/connection.php"); ?>
<?php require_once("includes/functions.php"); ?>
<?php
include_once("includes/form_functions.php");
require_once(  "includes" . DIRECTORY_SEPARATOR . "constants.php");
require_once(  "includes" . DIRECTORY_SEPARATOR . "crystal" . DIRECTORY_SEPARATOR . "Crystal.php");  
// Errors Array

$error = "API USER YOU MADE AN ERROR! YOU MESSED WITH ME! AND NOW YOU'LL BE PUNISHED! I WILL COME AND KILL YOU! OH! Error Code 1000: Epic Fail - You called an API with wrong attributes - GO FUCK YOUR SELF, API USER!";

// SPECIAL FUNCTIONS



// API POST\GET Processor

switch($_GET["method"])
 {

 		// Create
 	
 		case "createUserWithStream":
 			if((int)$_GET[streamId] != null && (string)$_GET[userName] != null && (string)$_GET[userEmail] != null && (string)$_GET[userPass] != null)
 			{

 			}
 			elseif((int)$_GET[streamId] != null && (string)$_GET[userName] != null )
 			{
			// Crapy Crystal way
 			///////////////////////////////////////////////////////////////////////////////////
			//			 			$data = array(
			//								'streamId' => $_GET[streamId],
			//								'userName' => $_GET[userName]
			//						);
			//			 			$rules = array(
			//			 				//'userName' => array('regexp: (/^[\p{L}_-]{5,20}+$/u), message : This email is already taken'), 
			//			 			    'streamId' => array('numeric, message: Please supply a valid number | required ')
			//			 			);
			//			 			$validation = Crystal::validation($rules, $data);
			//						if($validation->passed == TRUE)
			//							{
			//				//	echo "No errors"; // Debug Info
			//					$db = Crystal::db();
			//					$rand_val = md5(uniqid() + mt_rand());
			//					$key = trim(mysql_prep($rand_val));
			//				//	$hashed_password = sha1($password); // NOTE SHA1! 	
			//					$data = array('username' =>  $_GET[userName], 'CG' => $key );
			//					$db->insert('user', $data)->execute();
			//					$last_insert_user_id = $db->last_insert_id();
			//				//	echo " Last inserted user id " . $last_insert_user_id . "."; // Debug Info
			//				//  UserGenerated
			//				//////////
			//					$data = array('userID' => $last_insert_user_id, 'streamID' =>  $_GET[streamId] );
			//					$db->insert('streams', $data)->execute();
			//					$last_insert_stream_id = $db->last_insert_id();
			//				//	echo " Last inserted stream id " . $last_insert_stream_id . "."; // Debug Info
			//				//  StreamGenerated
			//				//	echo " Key: " . $key . "."; // Debug Info
			///////////////////////////////////////////////////////////////////////////////////////////////////////
			

 		$data = array(
						'streamId' => $_GET[streamId],
				);
	 			$rules = array(
	 			    'streamId' => array('numeric, message: Please supply a valid number | required ')
	 			);
	 			$validation = Crystal::validation($rules, $data);
				if($validation->passed == TRUE)
					{
		if ( strlen(trim(mysql_prep($_GET[userName]))) <= 40 && strlen(trim(mysql_prep($_GET[userName]))) >= 4)
		{    	
		$username = trim(mysql_prep($_GET[userName]));
		$rand_val = md5(uniqid() + mt_rand());
		$key = trim(mysql_prep($rand_val));
		$query = "INSERT INTO user (
				username, CG
						) VALUES (
							'{$username}', '{$key}'
						)";
			$result = mysql_query($query, $connection);
			if ($result) {
			$last_insert_user_id = mysql_insert_id(); 
			} 
				else {	echo "DB server error"; }
			}
			$db = Crystal::db();
			echo " Last inserted user id " . $last_insert_user_id . "."; // Debug Info
		//  UserGenerated
		//////////
			$data = array('userID' => $last_insert_user_id, 'streamID' =>  $_GET[streamId] );
			$db->insert('streams', $data)->execute();
			$last_insert_stream_id = $db->last_insert_id();
			echo " Last inserted stream id " . $last_insert_stream_id . "."; // Debug Info
		//  StreamGenerated
			echo " Key: " . $key . "."; // Debug Info
 				
			}else{	echo "DB server error"; }	
			}else
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