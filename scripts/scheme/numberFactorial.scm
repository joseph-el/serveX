#!/usr/bin/guile -s

(use-modules (web server))
(use-modules (ice-9 format))
(use-modules (srfi srfi-1))

(server-start
 (make-request-handler
  (lambda (request environment)
    (let* ((query-string (request-uri request))
           (params (string->alists query-string))
           (number (cdr (assoc "number" params))))
      (format #t "Content-Type: text/html~%~%")
      (format #t "<!DOCTYPE html><html><head><title>Factorial Calculator</title></head><body>~%")
      (format #t "<h1>Factorial Calculator</h1>~%")
      (if (and number (string-integer? number))
          (begin
            (let* ((num (string->integer number))
                   (factorial (apply * (iota num 1))))
              (format #t "<p>Factorial of ~a is ~a</p>~%" num factorial)))
          (format #t "<p>Invalid input</p>~%"))
      (format #t "</body></html>~%")))))

(server-loop)
