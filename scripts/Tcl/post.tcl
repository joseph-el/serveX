#!/usr/bin/tclsh

# Set the Content-Type and other headers
puts "Content-Type: image/jpeg\r\n"
puts "Content-Length: [file size @stdin]\r\n"
puts "\r\n"

# Read image data from stdin and output it
puts [read [open @stdin rb]]
