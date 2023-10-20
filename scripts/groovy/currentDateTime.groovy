#!/usr/bin/env groovy

println "Content-Type: text/html\r\n"
println "\r\n"

println """
<!DOCTYPE html>
<html>
<head>
  <title>CGI Date and Time</title>
</head>
<body>
  <h1>Current Date and Time</h1>
  <p>${new Date()}</p>
</body>
</html>
"""
