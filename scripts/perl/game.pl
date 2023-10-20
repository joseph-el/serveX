#!/usr/bin/perl

use strict;
use warnings;

# Set the "Content-Type" header and end it with "\r\n"
print "Content-Type: text/html\r\n\r\n";

# The rest of the HTML content
print <<HTML;
<!DOCTYPE html>
<html>
<head>
    <title>Shapes Bouncing</title>
    <style>
        body {
            margin: 0;
            overflow: hidden;
            background-color: #1e2125;
        }
        canvas {
            display: block;
        }
    </style>
</head>
<body>
    <h1 style="color: white; text-align: center;">Shapes Bouncing</h1>
    <canvas id="myCanvas" style="border: 1px solid #000;"></canvas>
    <script>
        var canvas = document.getElementById("myCanvas");
        var context = canvas.getContext("2d");
        var shapes = [];

        function createShape(x, y, width, height, color) {
            return {
                x: x,
                y: y,
                width: width,
                height: height,
                color: color,
                dx: 2,
                dy: -2,
            };
        }

        // Create and initialize shapes
        shapes.push(createShape(canvas.width / 2, canvas.height - 30, 20, 20, "blue"));
        shapes.push(createShape(canvas.width / 3, canvas.height - 50, 30, 30, "red"));

        function drawShapes() {
            context.clearRect(0, 0, canvas.width, canvas.height);

            for (var i = 0; i < shapes.length; i++) {
                var shape = shapes[i];

                context.beginPath();
                context.rect(shape.x, shape.y, shape.width, shape.height);
                context.fillStyle = shape.color;
                context.fill();
                context.closePath();

                if (shape.x + shape.dx > canvas.width - shape.width || shape.x + shape.dx < 0) {
                    shape.dx = -shape.dx;
                }
                if (shape.y + shape.dy > canvas.height - shape.height || shape.y + shape.dy < 0) {
                    shape.dy = -shape.dy;
                }

                shape.x += shape.dx;
                shape.y += shape.dy;
            }
        }

        setInterval(drawShapes, 10);
    </script>
</body>
</html>
HTML
