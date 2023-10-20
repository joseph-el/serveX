<?php


$imageData = file_get_contents('php://stdin');


header('Content-Type: image/jpeg\r\n');
header('Content-Length: ' . strlen($imageData) . "\r\n");


echo $imageData;
