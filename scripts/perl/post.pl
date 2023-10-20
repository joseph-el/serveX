#!/usr/bin/perl

use strict;
use warnings;

use CGI;

# Create a new CGI object
my $cgi = CGI->new;

# Read image data from stdin
my $imageData;
while (<STDIN>) {
    $imageData .= $_;
}

# Set the "Content-Type" header for an image and the content length, ending with "\r\n"
print $cgi->header(-type => 'image/jpeg\r\n', -content_length => length($imageData)) . "\r\n\r\n";

# Output the image data
print $imageData;
