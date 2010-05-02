<?php

// Errors Array

$error = "API USER YOU MADE AN ERROR! YOU MESSED WITH ME! AND NOW YOU'LL BE PUNISHED! I WILL COME AND KILL YOU! OH! Error Code 1000: Epic Fail - You called an API with wrong attributes - GO FUCK YOUR SELF, API USER!";

// API Processor

switch($_GET["method"])
 {

 		// Create
 	
 		case "createUserWithStream":
 			if((int)$_GET[streamId] != null && (string)$_GET[userName] != null && (string)$_GET[userEmail] != null && (string)$_GET[userPass] != null)
 			{
 				
 			}
 			elseif((int)$_GET[streamId] != null && (string)$_GET[userName] != null )
 			{
 				
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