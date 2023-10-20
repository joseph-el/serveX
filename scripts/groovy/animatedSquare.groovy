#!/usr/bin/env groovy

// Set the Content-Type header
println "Content-Type: text/html\r\n"
println "\r\n"

// Generate the HTML page with the square animation
println """
<!DOCTYPE html>
<html>
<head>
  <title>CGI Square Animation</title>
  <style>
    .square {
      width: 50px;
      height: 50px;
      background-color: red;
      position: absolute;
    }
  </style>
</head>
<body>
  <h1>CGI Square Animation</h1>
  <div class="square" id="animatedSquare"></div>
  <script>
    const square = document.getElementById('animatedSquare');
    let leftPosition = 0;
    const animationSpeed = 2;

    function animateSquare() {
      leftPosition += animationSpeed;
      square.style.left = leftPosition + 'px';
      if (leftPosition >= window.innerWidth) {
        leftPosition = -50;
      }
      requestAnimationFrame(animateSquare);
    }

    animateSquare();
  </script>
</body>
</html>
"""
