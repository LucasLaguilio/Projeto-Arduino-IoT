#include <WiFi.h>
#include <WebServer.h>

  const char* ssid = "LF2G";
  const char* password = "Laguilio052419";

WebServer server(80);

/
void adicionarCors() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
}


void handleGetDados() {
  adicionarCors(); 
  
  // Simula leitura de um sensor
  int sensorValue = random(0, 100); 
  
  // Cria um JSON simples manualmente
  String json = "{\"sensor\": \"temperatura\", \"valor\": " + String(sensorValue) + "}";
  
  server.send(200, "application/json", json);
  Serial.println("GET recebido. Enviado: " + json);
}

}

// 4. Rota OPTIONS: Necessária para o navegador "perguntar" se pode conectar (Preflight)
void handleOptions() {
  adicionarCors();
  server.send(200);
}

void setup() {
  Serial.begin(115200);


  WiFi.begin(ssid, password);
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Conectado! IP do ESP32: ");
  Serial.println(WiFi.localIP());


  server.on("/dados", HTTP_GET, handleGetDados);

  
  

  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  server.handleClient();
}



