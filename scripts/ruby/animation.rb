#!/usr/bin/env ruby

# Set the Content-Type header
puts "Content-Type: text/html\r\n"
puts "\r\n"

# Generate the HTML page with the animation
puts "<!DOCTYPE html><html><head><title>Shape Animation</title></head><body>"
puts "<h1>Shape Animation</h1>"
puts "<div id='container' style='position: relative; width: 400px; height: 200px; border: 1px solid #000;'>"

# Ruby CGI script for a simple shape animation
puts "<style>"
puts "  .shape { width: 50px; height: 50px; position: absolute; border-radius: 5px; animation: move 3s linear infinite; }"
puts "  .red { background-color: red; }"
puts "  .green { background-color: green; }"
puts "  .blue { background-color: blue; }"
puts "@keyframes move {"
puts "  0% { left: 0; top: 0; }"
puts "  25% { left: 100%; top: 0; }"
puts "  50% { left: 100%; top: 100%; }"
puts "  75% { left: 0; top: 100%; }"
puts "  100% { left: 0; top: 0; }"
puts "}"
puts "</style>"

colors = %w(red green blue)

# Generate and animate colored squares
10.times do
  color = colors.sample
  puts "<div class='shape #{color}'></div>"
end

puts "</div>"
puts "</body></html>"
