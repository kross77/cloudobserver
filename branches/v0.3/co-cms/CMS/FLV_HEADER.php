<?php
	if(isset($_GET[FILE]))
	{
		$fileName = $_GET[FILE];
		$file =  $fileName;

		if (!file_exists($file))
		{
			print('<b>ERROR:</b> php could not find (' . $fileName . ') please check your settings.'); 
			exit();
		}
		if(file_exists($file))
		{
			# stay clean
			@ob_end_clean();
			@set_time_limit(0);
			
			# keep binary data safe
			set_magic_quotes_runtime(0);
		
			$fh = fopen($file, 'rb') or die ('<b>ERROR:</b> php could not open (' . $fileName . ')');
			# content headers
			header("Content-Type: video/x-flv");
		
			# FLV file format header
                print('FLV');
                print(pack('C', 1));
                print(pack('C', 1));
                print(pack('N', 9));
                print(pack('N', 9));		
			# output file
			while(!feof($fh)) 
			{
					# output file without bandwidth limiting
					print(fread($fh, filesize($file))); 
			}	
		}	
	}
?>