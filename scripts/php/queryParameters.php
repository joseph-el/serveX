#!/usr/bin/php-cgi
<?php

// Get the query string from the environment variable
$queryString = getenv("QUERY_STRING");

header("Content-Type: text/html\r\n");


// Parse the query string into an associative array
parse_str($queryString, $queryData);

// Output the parsed data
echo "<html>";
echo "<head><title>Query String Data</title></head>";
echo "<body>";
echo "<h1>Query String Data</h1>";
echo "<ul>";
foreach ($queryData as $key => $value) {
    echo "<li><strong>{$key}:</strong> {$value}</li>";
}
echo "</ul>";
echo "</body>";
echo "</html>";
