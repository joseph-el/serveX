#!/usr/bin/guile -s

(use-modules (web server))
(use-modules (ice-9 format))

(server-start
 (make-request-handler
  (lambda (request environment)
    (format #t "Content-Type: text/html~%~%")
    (format #t "<!DOCTYPE html><html><head><title>CGI Animation</title></head><body>~%")
    (format #t "<h1>Rotating Square</h1>~%")
    (format #t "<div id='animation' style='width: 200px; height: 200px; border: 1px solid #000;'>~%")
    (format #t "<style>~%")
    (format #t "@keyframes rotate {~%")
    (format #t "  from { transform: rotate(0deg); }~%")
    (format #t "  to { transform: rotate(360deg); }~%")
    (format #t "}~%")
    (format #t "#animation {~%")
    (format #t "  animation: rotate 5s linear infinite;~%")
    (format #t "}~%")
    (format #t "</style>~%")
    (format #t "</div>~%")
    (format #t "</body></html>~%"))))

(server-loop)
