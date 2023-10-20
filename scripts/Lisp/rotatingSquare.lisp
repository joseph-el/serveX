#!/usr/bin/sbcl --script

(write-line "Content-Type: text/html\r\n")
(write-line "\r\n")

(write-line "<!DOCTYPE html><html><head><title>CGI Animation</title></head><body>")
(write-line "<h1>Rotating Square</h1>")
(write-line "<div id='animation' style='width: 200px; height: 200px; border: 1px solid #000;'>")
(write-line "<style>")
(write-line "@keyframes rotate {")
(write-line "  from { transform: rotate(0deg); }")
(write-line "  to { transform: rotate(360deg); }")
(write-line "}")
(write-line "#animation {")
(write-line "  animation: rotate 5s linear infinite;")
(write-line "}")
(write-line "</style>")
(write-line "</div>")
(write-line "</body></html>")
