#!/usr/bin/env groovy

// Read name from the query string
def query = System.getenv('QUERY_STRING')
def name = (query =~ /name=([^&]+)/).find() { it }
name = name ? name[1] : "Guest"

// Set the Content-Type header
println "Content-Type: text/html\r\n"
println "\r\n"

// Generate the HTML page with the greeting message
println """
<!DOCTYPE html>
<html>
<head>
  <title>Groovy CGI Greeting</title>
</head>
<body>
  <h1>Groovy CGI Greeting</h1>
  <p>Greeting for ${name}: Hello, $name!</p>
</body>
</html>
"""
