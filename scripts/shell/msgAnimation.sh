#!/bin/bash

# Set the Content-Type header
echo "Content-Type: text/html\r\n"
echo "\r\n"

# HTML page with the animation
echo "<!DOCTYPE html><html><head><title>Text Animation</title></head><body>"
echo "<h1>Text Animation</h1>"
echo "<div id='text' style='position: relative; font-size: 24px; white-space: nowrap; overflow: hidden; border: 1px solid #000; width: 400px; height: 50px;'></div>"

# JavaScript animation
echo "<script>"
echo "const textElement = document.getElementById('text');"
echo "const message = 'This is a text animation';"
echo "let charIndex = 0;"

echo "function animateText() {"
echo "  if (charIndex < message.length) {"
echo "    textElement.textContent += message.charAt(charIndex);"
echo "    charIndex++;"
echo "    setTimeout(animateText, 100);"
echo "  }"
echo "}"

echo "animateText();"
echo "</script>"

echo "</body></html>"
