<?php require_once("includes/session.php"); ?>
<?php require_once("includes/connection.php"); ?>
<?php require_once("includes/functions.php"); ?>
<?php confirm_logged_in(); ?>
<?php include("includes/header.php"); ?>
<?php 
include_once("includes/form_functions.php");
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


?>
<!-- Panel -->
<div id="toppanel">
	<div id="panel">
		<div class="content clearfix">

		</div>
	</div> <!-- /login -->	

    <!-- The tab on top -->	
	<div class="tab">
		<ul class="login">
	    	<li class="left">&nbsp;</li>
	        <li>Hello <?php echo $_SESSION['username'];  ?></li>
		 	<li class="sep">|</li>
			<li id="toggle">
				<a  href="logout.php">Log Out</a>
				
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
  <iframe  src="MSE.php"   width="100%" height="240"  class="ui-widget-content ui-corner-all" align="center"
   align="right" SCROLLING="NO"></iframe>
   
				</fieldset>	
	</form>
			<H1> TRANSFER INTO REGISTRED USERS!</H1>
		

	<form id="form3" action="Reg.php" method="post">
	<fieldset class="ui-widget-content ui-corner-all">
			<h1>Want to add stream? Add It!</h1>
		<legend class="ui-widget-header ui-corner-all">CMS supports multiple streams of same ID in one user</legend>
		<div class="ui-formular-error"></div> 
		<h1> Your ID is <?php echo $_SESSION['user_id'];?> <h1>
				<!--<label class="grey" for="uid"  >User ID (in real life CMS taken from session in API KEY) :</label> -->
					<input class="text ui-widget-content ui-corner-all" type="hidden"  name="uid" id="uid" value="<?php echo $_SESSION['user_id'];?>" size="30"  />
					<br/>
					<label class="grey" for="sid">Stream ID (Cloud Observer Core SID):</label>
					<input class="text ui-widget-content ui-corner-all" type="sid" name="sid"  id="sid" size="30" value=""  />
					<br/>
			<input type="submit" name="CreateStream" id="CreateStream" value="Add Stream" class="ui-state-default ui-corner-all" />
			<input type="reset" value="Reset" class="ui-state-default ui-corner-all" />
				</fieldset>	
	</form>



			<div>
		</div><!-- / content -->		
	</div><!-- / container -->
	
	<script type="text/javascript" src="js/jquery-1.4.1.js"></script>
	<script type="text/javascript" src="js/jquery-ui-1.8rc1.custom.min.js"></script>
	<script type="text/javascript" src="js/ui.formValidator.js"></script>
	<script type="text/javascript">	
		$(function() {				
						var formular1 = $("#form3").formValidator({
				forms: {			
					uid: {
						rules: {
							lengthMin: 1,
							lengthMax: 11,
							regEx: "number",
							required: true
						},
						msg: {	
							regEx: "Please enter a valid User ID adress.",
							required: "Please enter your User ID adress."	
						}
					},
					sid: {
						rules: {
							lengthMin: 1,
							lengthMax: 11,
							regEx: "number",
							required: true
						},
						msg: {	
							regEx: "Please enter a valid Stream ID adress.",
							required: "Please enter your Cloud Observer Stream ID adress."	
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

