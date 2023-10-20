#!/usr/bin/env ruby

# Read image data from stdin
image_data = $stdin.read

# Set the Content-Type and Content-Length headers
puts "Content-Type: image/jpeg\r\n"
puts "Content-Length: #{image_data.length}\r\n"
puts "\r\n" # End the headers with a blank line

# Output the image data to stdout
print image_data
