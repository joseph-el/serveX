#!/usr/bin/php-cgi
<?php
// Set the Content-Type header
header("Content-Type: text/html\r\n");


// Get the environment variables
$environmentVariables = $_SERVER;

// Generate the HTML page with CSS styling
echo "<html><head><title>Environment Variables</title>";
echo "<style>";
echo "body { font-family: Arial, sans-serif; background-color: #f5f5f5; text-align: center; }";
echo "h1 { color: #333; }";
echo ".container { background-color: #fff; padding: 20px; border-radius: 5px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); display: inline-block; }";
echo "table { width: 100%; border-collapse: collapse; margin-top: 20px; }";
echo "th, td { border: 1px solid #ccc; padding: 10px; text-align: left; }";
echo "th { background-color: #333; color: #fff; }";
echo "</style></head><body>";
echo "<div class='container'>";
echo "<h1>Environment Variables</h1>";
echo "<table>";
echo "<tr><th>Variable</th><th>Value</th></tr>";
foreach ($environmentVariables as $key => $value) {
    echo "<tr><td>$key</td><td>$value</td></tr>";
}
echo "</table>";
echo "</div></body></html>";
?>
