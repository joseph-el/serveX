#!/usr/bin/lua

-- Set the Content-Type header
io.write("Content-Type: text/html\r\n\r\n")

-- Generate HTML
io.write("<!DOCTYPE html><html><head><title>Canvas Animation</title></head><body>")
io.write("<h1>Canvas Animation</h1>")
io.write("<canvas id='myCanvas' width='400' height='200' style='border: 1px solid #000;'></canvas>")

-- JavaScript animation
io.write("<script>")
io.write("var canvas = document.getElementById('myCanvas');")
io.write("var context = canvas.getContext('2d');")
io.write("var x = 0;  // Initial x-coordinate for the ball")
io.write("var direction = 1;  // 1 for right, -1 for left")

io.write("function drawBall() {")
io.write("  context.clearRect(0, 0, canvas.width, canvas.height);")
io.write("  context.beginPath();")
io.write("  context.arc(x, 100, 20, 0, Math.PI * 2);")
io.write("  context.fillStyle = 'blue';")
io.write("  context.fill();")
io.write("  context.closePath();")
io.write("  x += 2 * direction;")

io.write("  if (x > canvas.width || x < 0) {")
io.write("    direction *= -1;  // Change direction when ball hits the canvas edge")
io.write("  }")
io.write("  requestAnimationFrame(drawBall);")
io.write("}")

io.write("drawBall();")
io.write("</script>")

io.write("</body></html>")
