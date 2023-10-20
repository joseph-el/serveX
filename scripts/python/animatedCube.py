#!/usr/bin/env python3

# Set the content type to HTML

print("Content-Type: text/html\r\n")

# HTML code to create a canvas and animate a moving rectangle
print("""
<!DOCTYPE html>
<html>
<head>
    <title>CGI Animation</title>
</head>
<body>
    <h1>Python CGI Animation</h1>
    <canvas id="myCanvas" width="400" height="200" style="border:1px solid #000;"></canvas>
    <script>
        var canvas = document.getElementById("myCanvas");
        var context = canvas.getContext("2d");
        var x = 0; // Initial x-coordinate for the rectangle

        function drawRectangle() {
            context.clearRect(0, 0, canvas.width, canvas.height);
            context.fillStyle = "blue";
            context.fillRect(x, 50, 50, 50);
            x += 2; // Move the rectangle to the right
            if (x > canvas.width) {
                x = 0; // Reset the position when it reaches the canvas width
            }
        }

        setInterval(drawRectangle, 20); // Call drawRectangle every 20 milliseconds for animation
    </script>
</body>
</html>
""")