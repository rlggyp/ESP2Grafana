#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_SSID"; // Replace with your WiFi SSID
const char* password = "YOUR_PASSWORD"; // Replace with your WiFi password

// Static IP Configuration (Optional)
IPAddress local_ip(192, 168, 1, 12);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 224);

WebServer server(80); // Running web server on port 80

// Variables to store temperature and humidity data
float temperature = 25.3;
float humidity = 60.5;

// Function to handle incoming request with parameters
void HandleSet() {
  if (!server.hasArg("temperature") && !server.hasArg("humidity")) {
    server.send(400, "application/json", "{\"error\": \"Missing parameters\"}");
    return;
  }
  
  if (server.hasArg("temperature")) {
    temperature = server.arg("temperature").toFloat();
  }
  
  if (server.hasArg("humidity")) {
    humidity = server.arg("humidity").toFloat();
  } 
  
  String response = "{ \"status\": \"OK\", \"temperature\": " + String(temperature) + 
                    ", \"humidity\": " + String(humidity) + " }";

  server.send(200, "application/json", response);
}

// Function to handle Prometheus metrics endpoint
void HandleMetrics() {
  String response = 
    "# HELP temperature Temperature in Celsius\n"
    "# TYPE temperature gauge\n"
    "temperature " + String(temperature) + "\n\n"
    "# HELP humidity Humidity in percentage\n"
    "# TYPE humidity gauge\n"
    "humidity " + String(humidity) + "\n";

  server.send(200, "text/plain", response);
}

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi network
  WiFi.config(local_ip, gateway, subnet);
  WiFi.begin(ssid, password);
  
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected to WiFi!");
  Serial.print("Device IP Address: ");
  Serial.println(WiFi.localIP());
  
  // Register endpoint for Prometheus metrics
  server.on("/set", HTTP_GET, HandleSet);
  server.on("/metrics", HTTP_GET, HandleMetrics);
  
  // Start the web server
  server.begin();
}

void loop() {
  server.handleClient(); // Handle incoming client requests
}
