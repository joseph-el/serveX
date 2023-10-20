#!/usr/bin/lua

-- Set the Content-Type header
io.write("Content-Type: text/html\r\n\r\n")

-- Generate HTML
io.write("<!DOCTYPE html><html><head><title>Animation</title></head><body>")
io.write("<h1>Simple Animation</h1>")
io.write("<div id='container' style='position: relative; width: 400px; height: 200px; border: 1px solid #000;'>")
io.write("<div id='circle' style='position: absolute; width: 50px; height: 50px; background-color: blue; border-radius: 50%;'></div>")
io.write("</div>")

-- JavaScript animation
io.write("<script>")
io.write("var container = document.getElementById('container');")
io.write("var circle = document.getElementById('circle');")
io.write("var x = 0;")  -- Initial x-coordinate for the circle

io.write("function animateCircle() {")
io.write("  if (x >= (container.offsetWidth - circle.offsetWidth) || x <= 0) {")
io.write("    x = 0;  // Reset the position when it reaches the container's edge")
io.write("  }")
io.write("  x += 2;  // Move the circle to the right")
io.write("  circle.style.left = x + 'px';")
io.write("  requestAnimationFrame(animateCircle);")
io.write("}")

io.write("animateCircle();")
io.write("</script>")

io.write("</body></html>")
