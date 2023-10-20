#!/usr/bin/env node

// Set the Content-Type header
console.log("Content-Type: text/html\r\n");
console.log("status: 500\r\n");
console.log("\r\n");

// Generate the HTML page with the animation
console.log('<!DOCTYPE html><html><head><title>Snowfall Animation</title></head><body>');
console.log('<h1>Snowfall CGI Animation</h1>');
console.log('<canvas id="snowCanvas" style="position: absolute; top: 0; left: 0;"></canvas>');
console.log('<script>');
console.log('const canvas = document.getElementById("snowCanvas");');
console.log('const ctx = canvas.getContext("2d");');
console.log('const flakes = [];');
console.log('const maxFlakes = 50;');
console.log('for (let i = 0; i < maxFlakes; i++) {');
console.log('  flakes.push({');
console.log('    x: Math.random() * canvas.width,');
console.log('    y: Math.random() * canvas.height,');
console.log('    size: Math.random() * 3 + 2,');
console.log('    speed: Math.random() * 3 + 1,');
console.log('  });');
console.log('}');
console.log('function drawSnowflake(flake) {');
console.log('  ctx.beginPath();');
console.log('  ctx.arc(flake.x, flake.y, flake.size, 0, Math.PI * 2);');
console.log('  ctx.fillStyle = "#fff";');
console.log('  ctx.fill();');
console.log('}');
console.log('function moveSnowflake(flake) {');
console.log('  flake.y += flake.speed;');
console.log('  if (flake.y > canvas.height) {');
console.log('    flake.y = 0;');
console.log('  }');
console.log('}');
console.log('function animateSnowfall() {');
console.log('  ctx.clearRect(0, 0, canvas.width, canvas.height);');
console.log('  flakes.forEach((flake) => {');
console.log('    drawSnowflake(flake);');
console.log('    moveSnowflake(flake);');
console.log('  });');
console.log('  requestAnimationFrame(animateSnowfall);');
console.log('}');
console.log('animateSnowfall();');
console.log('</script></body></html>');
