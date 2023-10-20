#!/usr/bin/Rscript

# Set the Content-Type header
cat("Content-Type: text/html\r\n\r\n")

# Generate HTML
cat("<!DOCTYPE html><html><head><title>Animation</title></head><body>")
cat("<h1>Simple Animation</h1>")
cat("<div id='container' style='position: relative; width: 400px; height: 200px; border: 1px solid #000;'>")
cat("<div id='rectangle' style='position: absolute; width: 50px; height: 50px; background-color: blue;'></div>")
cat("</div>")

# JavaScript animation
cat("<script>")
cat("var container = document.getElementById('container');")
cat("var rectangle = document.getElementById('rectangle');")
cat("var x = 0; // Initial x-coordinate for the rectangle")

cat("function animateRectangle() {")
cat("  if (x >= (container.offsetWidth - rectangle.offsetWidth) || x <= 0) {")
cat("    x = 0; // Reset the position when it reaches the container's edge")
cat("  }")
cat("  x += 2; // Move the rectangle to the right")
cat("  rectangle.style.left = x + 'px';")
cat("  requestAnimationFrame(animateRectangle);")
cat("}")

cat("animateRectangle();")
cat("</script>")

cat("</body></html>")
