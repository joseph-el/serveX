#!/usr/bin/node

// Import required modules
const http = require('http');

// Get environment variables
const environmentVariables = process.env;

// Create an HTTP server
const server = http.createServer((req, res) => {
  // Set the Content-Type header
  res.setHeader('Content-Type', 'text/html\r\n');
  res.write('\r\n');

  // Generate the HTML page with CSS styling
  res.write('<html><head><title>Environment Variables</title>');
  res.write('<style>');
  res.write('body { font-family: Arial, sans-serif; background-color: #f5f5f5; text-align: center; }');
  res.write('h1 { color: #333; }');
  res.write('.container { background-color: #fff; padding: 20px; border-radius: 5px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); display: inline-block; }');
  res.write('table { width: 100%; border-collapse: collapse; margin-top: 20px; }');
  res.write('th, td { border: 1px solid #ccc; padding: 10px; text-align: left; }');
  res.write('th { background-color: #333; color: #fff; }');
  res.write('</style></head><body>');
  res.write('<div class="container">');
  res.write('<h1>Environment Variables</h1>');
  res.write('<table>');
  res.write('<tr><th>Variable</th><th>Value</th></tr>');

  // Iterate through environment variables and display them
  for (const key in environmentVariables) {
    res.write(`<tr><td>${key}</td><td>${environmentVariables[key]}</td></tr>`);
  }
  res.write('</table>');
  res.write('</div></body></html>');
  res.end();
});

// Set the port to listen on
const port = 8000;

// Start the server
server.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});
