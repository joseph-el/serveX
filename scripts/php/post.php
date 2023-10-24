<?php


$imageData = file_get_contents('php://stdin');


header("Content-Type: image/jpg\r\n");
header("Content-Length: " . strlen($imageData));


echo $imageData;
