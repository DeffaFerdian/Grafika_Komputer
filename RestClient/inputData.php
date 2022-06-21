<?php
	$url='http://localhost:8080/latRest2/webresources/testController/cekLogin';
	$ch=curl_init($url);
	$data=array(
		"nim" => "672018004",
		"nama" => "Alpha",
		"tagihan" => 7000
	);

	$dataencode=json_encode($data);
	curl_setopt($ch, CURLOPT_POST, 1);
	curl_setopt($ch, CURLOPT_POSTFIELDS, $dataencode);
	curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type:application/json'));
	$result=curl_exec($ch);
?>