<?php require_once("includes/session.php"); ?>
<?php require_once("includes/connection.php"); ?>
<?php require_once("includes/functions.php"); ?>
<?php
if (logged_in()) {
		redirect_to("Registred.php");
	}
		include_once("includes/form_functions.php");

	// START FORM PROCESSING
    if (isset($_POST['submitLogin'])) { // Form has been submitted.
		$errors = array();

		// perform validations on the form data
		$required_fields = array('email', 'password');
		$errors = array_merge($errors, check_required_fields($required_fields, $_POST));

		$fields_with_lengths = array('email' => 40, 'password' => 40);
		$errors = array_merge($errors, check_max_field_lengths($fields_with_lengths, $_POST));

		$email = trim(mysql_prep($_POST['email']));
		$password = trim(mysql_prep($_POST['password']));
		$hashed_password = sha1($password);
		
		if ( empty($errors) ) {
			// Check database to see if username and the hashed password exist there.
			$query = "SELECT id, username, email ";
			$query .= "FROM user ";
			$query .= "WHERE email = '{$email}' ";
			$query .= "AND hashed_password = '{$hashed_password}' ";
			$query .= "LIMIT 1";
			$result_set = mysql_query($query);
			confirm_query($result_set);
			if (mysql_num_rows($result_set) == 1) {
				// username/password authenticated
				// and only 1 match
				$found_user = mysql_fetch_array($result_set);
				$_SESSION['user_id'] = $found_user['id'];
				$_SESSION['username'] = $found_user['username'];
				$_SESSION['email'] = $found_user['email'];
				
					$message = "The user was successfully LogedIn.";
		redirect_to("Registred.php");
			} else {
				// username/password combo was not found in the database
				$message = "Username/password combination incorrect.<br />
					Please make sure your caps lock key is off and try again.";
			}
		} else {
			if (count($errors) == 1) {
				$message = "There was 1 error in the form.";
			} else {
				$message = "There were " . count($errors) . " errors in the form.";
			}
		}
		
	} else {
		
			if (isset($_POST['submitRegister'])) { // Form has been submitted.
		$errors = array();

		// perform validations on the form data
		$required_fields = array('username', 'password', 'email');
		$errors = array_merge($errors, check_required_fields($required_fields, $_POST));

		$fields_with_lengths = array( 'password' => 40, 'email' => 40 );
		$errors = array_merge($errors, check_max_field_lengths($fields_with_lengths, $_POST));
         	
		$username = trim(mysql_prep($_POST['username']));
		$password = trim(mysql_prep($_POST['password']));
		$email = trim(mysql_prep($_POST['email']));
		
			$query = "SELECT id, email ";
			$query .= "FROM user ";
			$query .= "WHERE email = '{$email}' ";
			$result_set = mysql_query($query);
			confirm_query($result_set);
			
		if (mysql_num_rows($result_set) == 0) {
		$rand_val = md5(uniqid() + mt_rand());
		$key = trim(mysql_prep($rand_val));
		$hashed_password = sha1($password);
        
		if ( empty($errors) ) {
			$query = "INSERT INTO user (
							username, hashed_password, email, CG
						) VALUES (
							'{$username}', '{$hashed_password}',  '{$email}',  '{$key}'
						)";
			$result = mysql_query($query, $connection);
			if ($result) {
				$_SESSION['user_id'] = $result['id'];
				$_SESSION['username'] = $username;
				$_SESSION['email'] = $email;
				$message = "The user was successfully created.";
			////////////
			
					$query = "SELECT id, username, email ";
			$query .= "FROM user ";
			$query .= "WHERE email = '{$email}' ";
			$query .= "AND hashed_password = '{$hashed_password}' ";
			$query .= "LIMIT 1";
			$result_set = mysql_query($query);
			confirm_query($result_set);
			if (mysql_num_rows($result_set) == 1) {
				// username/password authenticated
				// and only 1 match
				$found_user = mysql_fetch_array($result_set);
				$_SESSION['user_id'] = $found_user['id'];
				$_SESSION['username'] = $found_user['username'];
				$_SESSION['email'] = $found_user['email'];
				
					$message = "The user was successfully LogedIn.";
		redirect_to("Registred.php");
			}
				
			///////////	
			} else {
				$message = "The user could not be created.";
				$message .= "<br />" . mysql_error();
			}
		} else {
			if (count($errors) == 1) {
				$message = "There was 1 error in the form.";
			} else {
				$message = "There were " . count($errors) . " errors in the form.";
			}
		}} else {
				//   found in the database
				$message = " Email is already taken, combination incorrect.<br />
					Please make sure your caps lock key is off and try again.";
			}
	} else { 
		 if (isset($_POST['CreateStream'])) { // Form has been submitted.
				$errors = array();

		// perform validations on the form data
		$required_fields = array('uid', 'sid');
		$errors = array_merge($errors, check_required_fields($required_fields, $_POST));

		$fields_with_lengths = array('uid' => 11, 'sid' => 11);
		$errors = array_merge($errors, check_max_field_lengths($fields_with_lengths, $_POST));
      
		$uid = trim(mysql_prep($_POST['uid']));
			$query = "SELECT id, email ";
			$query .= "FROM user ";
			$query .= "WHERE id = '{$uid}' ";
			$result_set = mysql_query($query);
			confirm_query($result_set);	
		if (mysql_num_rows($result_set) == 1) {
	
		$sid = trim(mysql_prep($_POST['sid']));
		$LastSeen = trim(mysql_prep(strftime("%Y-%m-%d %H:%M:%S", time())));
        
		if ( empty($errors) ) {
			$query = "INSERT INTO streams (
							userID, streamID, LastSeen
						) VALUES (
							'{$uid}', '{$sid}',  '{$LastSeen}'
						)";
			$result = mysql_query($query, $connection);
			if ($result) {
				$message = "The Stream was successfully created.";
			} else {
				$message = "The Stream could not be created.";
				$message .= "<br />" . mysql_error();
			}
		} else {
			if (count($errors) == 1) {
				$message = "There was 1 error in the form.";
			} else {
				$message = "There were " . count($errors) . " errors in the form.";
			}
		} } else {
				//   found in the database
				$message = "No Such UserID detected! combination incorrect.<br />
					Please make sure your caps lock key is off and try again.";
			}
	}
		else { // Form has not been submitted.
		$username = "";
		$password = "";
		
	 }
	}	
		 // Form has not been submitted.
		if (isset($_GET['logout']) && $_GET['logout'] == 1) {
			$message = "You are now logged out.";
		} 
		$username = "";
		$password = "";
	}
?>
<?php include("includes/header.php"); ?>

<!-- Panel -->
<div id="toppanel" style="position:fixed">
	<div id="panel">
		<div class="content clearfix">
						<div class="left">
				<h1>Cloud Observer Welcomes you</h1>
				<h2>Open Conference Demo</h2>		
				<p class="grey">Now You can stream anything you want! Your track will be published right away! And Youll be able to share it with your friends! The only limit is your imagination!</p>
				<h2>You can start streaming now!</h2>
				<p class="grey"> For free! Your stream will be playable in Itunes, Flash, and lots of other players!</p>
			</div>
<div class="left">

	<form id="form1" action="index.php" method="post">
	<fieldset class="ui-widget-content ui-corner-all">
			<legend class="ui-widget-header ui-corner-all">A Member? Login!</legend>
				<label class="grey" for="email">Email (6-30):</label>
					<input class="text ui-widget-content ui-corner-all" type="text"  name="email" id="email1" value="<?php echo $_SESSION['email']; ?>" size="30"  />
					<label class="grey" for="password">Password (6-15):</label>
					<input class="text ui-widget-content ui-corner-all" type="password" name="password"  id="password1" size="30" value=""  />
					<br/>
			<input type="submit" name="submitLogin" id="submitLogin" value="Login" class="ui-state-default ui-corner-all" />
			<input type="reset" value="Reset" class="ui-state-default ui-corner-all" />
				</fieldset>	
	</form>
</div>

<div class="left right">				

					<form id="form2" action="index.php" method="post">
		<fieldset class="ui-widget-content ui-corner-all">
			<legend class="ui-widget-header ui-corner-all">Not a member yet? Sign Up!</legend>	
					<label class="grey" for="username">Username  (6-15):</label>
					<input class="text ui-widget-content ui-corner-all"  type="text" name="username" id="username"  size="30"  value="Example Name"/>
					<label class="grey" for="email">Email  (6-30):</label>
					<input class="text ui-widget-content ui-corner-all"  type="text" name="email" id="email" size="30"  value="Example@Example.com"  />
					<label class="grey" for="password" >Password  (6-15):</label>
					<input class="text ui-widget-content ui-corner-all"  type="password" name="password"  id="password" size="30"  value=""  />	
          <input type="submit" name="submitRegister" id="submitRegister" value="Register" class="ui-state-default ui-corner-all" />
			<input type="reset" value="Reset" class="ui-state-default ui-corner-all" />
				</fieldset>	
		
	</form>
</div>

		</div>
	</div> <!-- /login -->	

    <!-- The tab on top -->	
	<div class="tab">
		<ul class="login">
	    	<li class="left">&nbsp;</li>
	        <li>Hello Guest!</li>
		 	<li class="sep">|</li>
			<li id="toggle">
				<a id="open" class="open" href="#">Log In | Register</a>
				<a id="close" style="display: none;" class="close" href="#">Close Panel</a>			
			</li>
	    	<li class="right">&nbsp;</li>
		</ul> 

	</div> <!-- / top -->
	
</div> <!--panel -->

    <div id="container">
		<div id="content" style="padding-top:100px;">
			<?php if (!empty($message)) {echo "<h2>message</h2> <p class=\"message\">" . $message . "</p>";} ?>
			<?php if (!empty($errors)) { display_errors($errors); } ?>
			<div>
				
		<H1> USER STREAMS CAN BE LISTENED BY EVERY ONE!</H1>
  <form id="form4"  method="post">
	<fieldset class="ui-widget-content ui-corner-all">
			<legend class="ui-widget-header ui-corner-all">All user's streams!</legend>
  <iframe  src="Debug.php"   width="100%" height="240"  class="ui-widget-content ui-corner-all" align="center"
   align="right" SCROLLING="NO"></iframe>
   
				</fieldset>	
	</form>

<?php include("includes/DebugComponentAd.php"); ?>



			<div>
		</div><!-- / content -->		
	</div><!-- / container -->
	
	<script type="text/javascript" src="js/jquery-1.4.1.js"></script>
	<script type="text/javascript" src="js/jquery-ui-1.8rc1.custom.min.js"></script>
	<script type="text/javascript" src="js/ui.formValidator.js"></script>
	<script type="text/javascript">	
		$(function() {			
			var formular1 = $("#form1").formValidator({
				forms: {			
					email1: {
						rules: {
							lengthMin: 6,
							lengthMax: 30,
							regEx: "email",
							required: true
						},
						msg: {	
							regEx: "Please enter a valid email adress.",
							required: "Please enter your email adress."	
						}
					},
					password1: {
						rules: {
							lengthMin: 6,
							lengthMax: 15,
							required: true
						},
						msg: {
							required: "Please enter a password.",
							lengthMin: "Your Password must have between 6 and 15 chars.",
							lengthMax: "Your Password must have between 6 and 15 chars."
						}
					},

},
validateLive: true,
disabled: false,
submitHowTo: "post"		
			});		
					
			var formular2 = $("#form2").formValidator({
				forms: {
					username:{
						rules: {
							lengthMin: 6,
							lengthMax: 15,
							required: true
						},
						msg: {
							required: "Please enter a Name.",
							lengthMin: "Your Name must have between 6 and 15 chars.",
							lengthMax: "Your Name must have between 6 and 15 chars."
						}	
						
					},						
					email: {
						rules: {
							lengthMin: 6,
							lengthMax: 30,
							regEx: "email",
							required: true
						},
						msg: {	
							regEx: "Please enter a valid email adress.",
							required: "Please enter your email adress."	
						}
					},
					password: {
						rules: {
							lengthMin: 6,
							lengthMax: 15,
							required: true
						},
						msg: {
							required: "Please enter a password.",
							lengthMin: "Your Password must have between 6 and 15 chars.",
							lengthMax: "Your Password must have between 6 and 15 chars."
						}
					},

				},
validateLive: true,
disabled: false,
submitHowTo: "post"			
			});				
		});		
		
	</script>
</body>
</html>

