#!/usr/bin/env python

# Set the content type to HTML
print("Content-Type: text/html\r\n")
print("\r\n")

# HTML code to create a visually appealing and interactive animation
print("""
<!DOCTYPE html>
<html>
<head>
    <title>Beautiful CGI Animation</title>
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
    <h1 style="color: white; text-align: center;">Beautiful CGI Animation</h1>
    <canvas id="myCanvas" style="border:1px solid #000;"></canvas>
    <select id="selectColor" style="margin: 20px; padding: 10px;">
        <option value="red">Red</option>
        <option value="green">Green</option>
        <option value="blue">Blue</option>
    </select>
    <script>
        var canvas = document.getElementById("myCanvas");
        var context = canvas.getContext("2d");
        var balls = [];

        // Ball class
        class Ball {
            constructor(x, y, radius, dx, dy, color) {
                this.x = x;
                this.y = y;
                this.radius = radius;
                this.dx = dx;
                this.dy = dy;
                this.color = color;
            }

            draw() {
                context.beginPath();
                context.arc(this.x, this.y, this.radius, 0, Math.PI * 2);
                context.fillStyle = this.color;
                context.fill();
                context.closePath();
            }

            update() {
                this.draw();

                if (this.x + this.dx > canvas.width - this.radius || this.x + this.dx < this.radius) {
                    this.dx = -this.dx;
                }
                if (this.y + this.dy > canvas.height - this.radius || this.y + this.dy < this.radius) {
                    this.dy = -this.dy;
                }

                this.x += this.dx;
                this.y += this.dy;
            }
        }

        // Create and initialize multiple balls
        for (let i = 0; i < 10; i++) {
            let x = Math.random() * (canvas.width - 2 * 20) + 20;
            let y = Math.random() * (canvas.height - 2 * 20) + 20;
            let radius = 20;
            let dx = (Math.random() - 0.5) * 4;
            let dy = (Math.random() - 0.5) * 4;
            let color = `rgb(${Math.floor(Math.random() * 256)}, ${Math.floor(Math.random() * 256)}, ${Math.floor(Math.random() * 256)})`;
            balls.push(new Ball(x, y, radius, dx, dy, color));
        }

        // Handle color selection
        var selectColor = document.getElementById("selectColor");
        selectColor.addEventListener("change", function() {
            var selectedColor = selectColor.value;
            balls.forEach(ball => {
                ball.color = selectedColor;
            });
        });

        function animate() {
            requestAnimationFrame(animate);
            context.clearRect(0, 0, canvas.width, canvas.height);

            for (let i = 0; i < balls.length; i++) {
                balls[i].update();
            }
        }

        animate();
    </script>
</body>
</html>
""")
