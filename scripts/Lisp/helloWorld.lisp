#!/usr/bin/sbcl --script

(write-line "Content-Type: text/html\r\n")
(write-line "\r\n")

(format t "Content-type: text/html~%")
(format t "Hello, World!~%")
