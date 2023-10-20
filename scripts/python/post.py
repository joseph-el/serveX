#!/usr/bin/python

import sys
import os
import cgi

# Read image data from stdin
image_data = sys.stdin.read()

# Set the "Content-Type" header for an image and the content length, ending with "\r\n"
print("Content-Type: image/jpeg\r\n")
print("Content-Length: {}\r\n".format(len(image_data)))
print("\r\n")

# Output the image data
sys.stdout.write(image_data)
