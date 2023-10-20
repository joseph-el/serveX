#!/usr/bin/php-cgi
<?php
// Set the Content-Type header and end it with "\r\n"
header("Content-Type: text/html\r\n");

?>

<!DOCTYPE html>
<html>
<head>
    <title>PHP Bouncing Ball</title>
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
    <h1 style="color: white; text-align: center;">PHP Bouncing Ball</h1>
    <canvas id="myCanvas" style="border: 1px solid #000;"></canvas>
    <script>
        var canvas = document.getElementById("myCanvas");
        var context = canvas.getContext("2d");
        var ballX = canvas.width / 2;
        var ballY = canvas.height - 30;
        var ballRadius = 20;
        var dx = 2;
        var dy = -2;

        function drawBall() {
            context.clearRect(0, 0, canvas.width, canvas.height);
            context.beginPath();
            context.arc(ballX, ballY, ballRadius, 0, Math.PI * 2);
            context.fillStyle = "blue";
            context.fill();
            context.closePath();

            if (ballX + dx > canvas.width - ballRadius || ballX + dx < ballRadius) {
                dx = -dx;
            }
            if (ballY + dy > canvas.height - ballRadius || ballY + dy < ballRadius) {
                dy = -dy;
            }

            ballX += dx;
            ballY += dy;
        }

        setInterval(drawBall, 10);
    </script>
</body>
</html>
