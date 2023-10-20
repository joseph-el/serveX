#!/usr/bin/lua

-- Set the Content-Type header
io.write("Content-Type: text/html\r\n\r\n")

-- Generate HTML
io.write("<!DOCTYPE html><html><head><title>Canvas Animation</title></head><body>")
io.write("<h1>Canvas Animation</h1>")
io.write("<canvas id='myCanvas' width='400' height='400' style='border: 1px solid #000;'></canvas>")

-- JavaScript animation
io.write("<script>")
io.write("var canvas = document.getElementById('myCanvas');")
io.write("var context = canvas.getContext('2d');")
io.write("var squares = [];")

io.write("function createSquare(x, y, size, angle) {")
io.write("  squares.push({ x: x, y: y, size: size, angle: angle });")
io.write("}")

io.write("function clearCanvas() {")
io.write("  context.clearRect(0, 0, canvas.width, canvas.height);")
io.write("}")

io.write("function drawSquare(square) {")
io.write("  context.save();")
io.write("  context.translate(square.x, square.y);")
io.write("  context.rotate(square.angle);")
io.write("  context.fillStyle = 'blue';")
io.write("  context.fillRect(-square.size / 2, -square.size / 2, square.size, square.size);")
io.write("  context.restore();")
io.write("}")

io.write("function animateSquares() {")
io.write("  clearCanvas();")
io.write("  for (var i = 0; i < squares.length; i++) {")
io.write("    squares[i].angle += 0.02;")
io.write("    drawSquare(squares[i]);")
io.write("  }")
io.write("  requestAnimationFrame(animateSquares);")
io.write("}")

io.write("createSquare(200, 200, 50, 0);")
io.write("createSquare(100, 100, 30, 0.3);")
io.write("createSquare(300, 300, 70, 0.7);")
io.write("animateSquares();")
io.write("</script>")

io.write("</body></html>")
