#!/usr/bin/env ruby

# Set the Content-Type header
puts "Content-Type: text/html\r\n"
puts "\r\n"

# Generate the HTML page with the canvas animation
puts "<!DOCTYPE html><html><head><title>Canvas Animation</title></head><body>"
puts "<h1>Canvas Animation</h1>"
puts "<canvas id='myCanvas' width='400' height='200' style='border: 1px solid #000;'></canvas>"

# Ruby CGI script for a simple canvas animation
puts "<script>"
puts "const canvas = document.getElementById('myCanvas');"
puts "const ctx = canvas.getContext('2d');"
puts "let x = 0; // Initial x-coordinate for the ball"

puts "function drawBall() {"
puts "  ctx.clearRect(0, 0, canvas.width, canvas.height);"
puts "  ctx.beginPath();"
puts "  ctx.arc(x, 100, 20, 0, Math.PI * 2);"
puts "  ctx.fillStyle = 'blue';"
puts "  ctx.fill();"
puts "  x += 2; // Move the ball to the right"
puts "  if (x > canvas.width) { x = 0; } // Reset the position when it reaches the canvas width"
puts "}"

puts "setInterval(drawBall, 20); // Call drawBall every 20 milliseconds for animation"
puts "</script>"

puts "</body></html>"
