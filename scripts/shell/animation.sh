#!/bin/bash

# Set the Content-Type header
echo "Content-Type: text/html\r\n"
echo "\r\n"

# HTML page with the animation
echo "<!DOCTYPE html><html><head><title>Bouncing Ball</title></head><body>"
echo "<h1>Bouncing Ball Animation</h1>"
echo "<div id='container' style='position: relative; width: 400px; height: 200px; border: 1px solid #000;'>"
echo "<div id='ball' style='position: absolute; width: 50px; height: 50px; background-color: blue; border-radius: 50%;'></div>"
echo "</div>"

# JavaScript animation
echo "<script>"
echo "const container = document.getElementById('container');"
echo "const ball = document.getElementById('ball');"
echo "let x = 0; // Initial x-coordinate for the ball"
echo "let direction = 1; // 1 for right, -1 for left"

echo "function animateBall() {"
echo "  if (x >= (container.offsetWidth - ball.offsetWidth) || x <= 0) {"
echo "    direction *= -1; // Change direction when ball hits the container's edge"
echo "  }"
echo "  x += 2 * direction; // Move the ball"
echo "  ball.style.left = x + 'px';"
echo "  requestAnimationFrame(animateBall);"
echo "}"

echo "animateBall();"
echo "</script>"

echo "</body></html>"
