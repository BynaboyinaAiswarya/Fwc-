#include <WiFi.h>
#include <WebServer.h>

// Replace these with your network credentials
const char* ssid = "vivo";
const char* password = "123456ashu";

// Define the GPIO pins for the LEDs
#define X_LED_PIN 2   // Pin for LED representing X
#define Y_LED_PIN 4   // Pin for LED representing Y

// Create a web server object on port 80
WebServer server(80);

// Variables to hold the current state of X and Y
int X = 1;  // Default logic value for X (1)
int Y = 0;  // Default logic value for Y (0)

// Function declarations
void handleRoot();    // Function to handle root URL
void toggleX();       // Function to toggle X LED
void toggleY();       // Function to toggle Y LED

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Initialize the LEDs as outputs
  pinMode(X_LED_PIN, OUTPUT);
  pinMode(Y_LED_PIN, OUTPUT);

  // Set default states for the LEDs
  digitalWrite(X_LED_PIN, X);
  digitalWrite(Y_LED_PIN, Y);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Define the server routes
  server.on("/", handleRoot);    // Handle root URL
  server.on("/toggleX", toggleX); // Handle toggle for X LED
  server.on("/toggleY", toggleY); // Handle toggle for Y LED

  // Start the web server
  server.begin();
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
}

// Function to handle root URL
void handleRoot() {
  server.send(200, "text/plain", "Send /toggleX or /toggleY to control LEDs.");
}

// Function to toggle X LED
void toggleX() {
  X = !X; // Toggle the X state
  digitalWrite(X_LED_PIN, X);
  String message = "X LED is now " + String((X == 1) ? "ON" : "OFF");
  server.send(200, "text/plain", message); // Send the status as plain text
}

// Function to toggle Y LED
void toggleY() {
  Y = !Y; // Toggle the Y state
  digitalWrite(Y_LED_PIN, Y);
  String message = "Y LED is now " + String((Y == 1) ? "ON" : "OFF");
  server.send(200, "text/plain", message); // Send the status as plain text
}

