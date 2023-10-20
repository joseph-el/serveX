#!/usr/bin/php-cgi
<?php
// Set the Content-Type header
header("Content-Type: text/html\r\n");


// Parse the query string
parse_str($_SERVER['QUERY_STRING'], $queryParameters);

// Get query string parameters
$firstName = isset($queryParameters['first_name']) ? htmlspecialchars($queryParameters['first_name']) : "";
$lastName = isset($queryParameters['last_name']) ? htmlspecialchars($queryParameters['last_name']) : "";

// Generate the HTML page with CSS styling and animation
echo "<html><head><title>Animated CGI Page</title>";
echo "<style>";
echo "body { font-family: Arial, sans-serif; background-color: #f5f5f5; text-align: center; }";
echo "h1 { color: #333; }";
echo ".container { background-color: #fff; padding: 20px; border-radius: 5px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); display: inline-block; }";
echo "p { color: #007BFF; font-size: 20px; }";
echo "p.anim { animation: colorChange 2s infinite; }";
echo "@keyframes colorChange { 0% { color: #007BFF; } 50% { color: #FF5733; } 100% { color: #007BFF; } }";
echo "</style></head><body>";
echo "<div class='container'>";
echo "<h1>Information Received</h1>";
echo "<p class='anim'>First Name: $firstName</p>";
echo "<p class='anim'>Last Name: $lastName</p>";
echo "</div></body></html>";
?>
