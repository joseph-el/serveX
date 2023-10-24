#!/usr/bin/python

import os

# Set the Content-Type header
print "Content-Type: text/html \r"
print "\r"


# Start the HTML page
print "<html><head><title>Environment Variables</title></head><body>"
print "<h1>Environment Variables</h1>"
print "<table>"
print "<tr><th>Variable</th><th>Value</th></tr>"

# Print environment variables
for key, value in os.environ.iteritems():
    print "<tr><td>%s</td><td>%s</td></tr>" % (key, value)

print "</table>"
print "</body></html>"
