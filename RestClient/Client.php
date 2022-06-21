<?php
	$url='http://localhost:8080/latRest2/webresources/testController/getData';
		$konten=file_get_contents($url);
		$data=json_decode($konten,true);
		
		for($a=0;$a<count($data);$a++){
			echo ($a+1).". ".$data[$a]['nim']." - ";
			echo $data[$a]['nama']." - ".$data[$a]['tagihan']."<br>";
		}
?>