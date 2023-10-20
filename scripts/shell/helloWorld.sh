#!/bin/bash

# Set the Content-Type header
echo "Content-Type: text/html\r\n"
echo "\r\n"

# Generate the HTML page with the "Hello, World!" message
echo "<!DOCTYPE html><html><head><title>Hello, World!</title></head><body>"
echo "<h1>Hello, World!</h1>"
echo "</body></html>"
