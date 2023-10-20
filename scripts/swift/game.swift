#!/usr/bin/env swift

print("Content-type: text/html\r\n")
print("\r\n")

print("<html>")
print("<head><title>Swift CGI Animation</title></head>")
print("<body>")

print("<h1>Swift CGI Animation</h1>")
print("<div style=\"position: relative; width: 400px; height: 400px; border: 1px solid #000;\">")

// Animation code
print("<div id=\"animatedObject\" style=\"position: absolute; width: 50px; height: 50px; background-color: #3498db;\"></div>")

print("<script>")
print("var animatedObject = document.getElementById('animatedObject');")
print("var position = 0;")
print("setInterval(function() {")
print("  position += 5;")
print("  animatedObject.style.left = position + 'px';")
print("}, 100);")
print("</script>")

print("</div>")
print("</body>")
print("</html>")
