#include <WiFi.h>
#include <WebServer.h>
#include <DistanceSensor.h>

const char* ssid = "Fialho";
const char* password = "123456789";


const int echoPin = 18; 
const int trigPin = 19; 
const int ledverde = 2; 
const int ledvermelho = 4; 


// --- HTTP Server Setup ---
WebServer server(80);
DistanceSensor sensor(trigPin, echoPin);
long distanceCm = sensor.getCM();

// --- Function Prototypes ---
void adicionarCors();
void handleGetDados();
void handleOptions();


void adicionarCors() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
}

void handlesensor() {
  
  if (distanceCm < 50) { 
    digitalWrite(ledvermelho, HIGH);
    digitalWrite(ledverde, LOW);
  } else {
    digitalWrite(ledvermelho, LOW);
    digitalWrite(ledverde, HIGH);
  }
  Serial.println(distanceCm);
  
}




void handleGetDados() {
  adicionarCors();
  handlesensor();


  // Create JSON response
  String json = "{\"sensor\": \"distancia\", \"valor\": " + String(distanceCm) + ", \"unidade\": \"cm\"}";

  server.send(200, "application/json", json);
  Serial.println("GET recebido. Enviado: " + json);
}


void handleOptions() {
  adicionarCors();
  server.send(200); 
}

void setup () {
  Serial.begin(230400); 
  pinMode(ledverde, OUTPUT);
  pinMode(ledvermelho, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  server.on("/dados", HTTP_GET, handleGetDados);
  server.on("/dados", HTTP_OPTIONS, handleOptions); 

  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop () {
  server.handleClient();
}
