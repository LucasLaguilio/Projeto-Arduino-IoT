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


//Codigo 2, em que o servidor roda no pc invés do esp32

#include <HTTPClient.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DistanceSensor.h>

// --- Configurações de Rede ---
const char* ssid = "aula_iot";
const char* password = "aula_iot";

const char* host = "192.168.0.102"; 
const int port = 3000;


long distanceCm = 0;
const int echoPin = 18;
const int trigPin = 19;
const int ledverde = 2;
const int ledvermelho = 4;


WebServer server(80);


DistanceSensor sensor(trigPin, echoPin);



void adicionarCors();
void handlesensor();
void handleGetDados();
void handleOptions();
void sendSensorData();



void adicionarCors() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
    server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
}

void handlesensor() {
    distanceCm = sensor.getCM();


    if (distanceCm < 50 && distanceCm >= 0) {
        digitalWrite(ledvermelho, HIGH);
        digitalWrite(ledverde, LOW);
    } else {
        digitalWrite(ledvermelho, LOW);
        digitalWrite(ledverde, HIGH);
    }

    Serial.print("Distancia: ");
    Serial.print(distanceCm);
    Serial.println(" cm");
}

void handleGetDados() {
    handlesensor(); 
    adicionarCors();
    String json = "{\"sensor\": \"distancia\", \"valor\": " + String(distanceCm) + ", \"unidade\": \"cm\"}";
    server.send(200, "application/json", json);
    Serial.println("Servidor: GET /dados recebido. Enviado: " + json);
}

void handleOptions() {
    adicionarCors();
    server.send(200);
}



void sendSensorData() {

    handlesensor(); 
    

    int sensorValue = distanceCm; 

    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

  
        String path = "/teste/" + String(sensorValue);
        String url = "http://" + String(host) + ":" + String(port) + path;
        Serial.println("Cliente: Tentando enviar dados para: " + url);
        

        http.begin(url);

        int httpCode = http.GET(); 
        if (httpCode > 0) {
            Serial.printf("Cliente: GET enviado. Codigo de Resposta: %d\n", httpCode);
            if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_CREATED) {
                String payload = http.getString();
                Serial.println("Cliente: Resposta do Servidor Externo: " + payload);
            }
        } else {
            Serial.printf("Cliente: Falha no GET. Erro: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end(); 
    }
}




void setup () {
    Serial.begin(230400);
    pinMode(ledverde, OUTPUT);
    pinMode(ledvermelho, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);


    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());


    server.on("/dados", HTTP_GET, handleGetDados);
    server.on("/dados", HTTP_OPTIONS, handleOptions);
    server.begin();
    Serial.println("Servidor HTTP local iniciado na porta 80");
}

void loop () {
    server.handleClient();
    sendSensorData();
    
}