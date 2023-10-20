#!/usr/bin/tclsh

# Set the Content-Type header
puts "Content-Type: text/html\r\n"
puts "\r\n"

puts "<!DOCTYPE html><html><head><title>CGI Animation</title></head><body>"
puts "<h1>Rotating Square</h1>"
puts "<div id='animation' style='width: 200px; height: 200px; border: 1px solid #000;'>"
puts "<style>"
puts "@keyframes rotate {"
puts "  from { transform: rotate(0deg); }"
puts "  to { transform: rotate(360deg); }"
puts "}"
puts "#animation {"
puts "  animation: rotate 5s linear infinite;"
puts "}"
puts "</style>"
puts "</div>"

puts "</body></html>"
