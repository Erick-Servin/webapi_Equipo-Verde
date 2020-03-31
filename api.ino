#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

const char* ssid = "IZZI5335";
const char* password = "60725335";

#define pos1 D4
#define pos2 D2

void setup(){
  Serial.begin(115200);
  
  pinMode(pos1, INPUT);
  pinMode(pos2, INPUT);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  
  Serial.println(""); 
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());
}

void loop(){
  inter_izq();
  inter_der();
}

int inter_izq(){
  
  int estado = 0;
  int salida = 0;
  int estado_ant = 0;
  String lado_izq = "IZQUIERDO";
  
  estado = digitalRead(pos1);

  if((estado == HIGH) && (estado_ant == LOW)){
    salida = 1 - salida;
  }

  estado_ant = estado;
  delay(1000);

    if(salida == 1){   
      Serial.println(lado_izq);

      postInterIzq(lado_izq);
    
      //return lado_izq;
    }
    else{
        Serial.print("\n . ");
      }
}

int inter_der(){
  
  int estado2 = 0;
  int salida2 = 0;
  int estado_ant2 = 0;
  String lado_der= "DERECHO";
  
  estado2 = digitalRead(pos2);

  if((estado2 == HIGH) && (estado_ant2 == LOW)){
    salida2 = 1 - salida2;
  }

  estado_ant2 = estado2;
  delay(1000);

    if(salida2 == 1){   
      Serial.println(lado_der);

      postInterDer(lado_der);
      
    }
    else{
        Serial.print("\n . ");
      }
}

void postInterIzq(String lado_izq){
  
  String server = "http://10.0.0.18:3000/webapi/interrupt";

  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& JSONencoder = jsonBuffer.createObject();
  JSONencoder["Lado"] = lado_izq;

  char JSONmessageBuffer[256];
  JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  
  HTTPClient http;
  http.begin(server);
  Serial.println("Insertando en -> " +server);
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.POST(JSONmessageBuffer);
  String payload = http.getString();

  http.end();
}

void postInterDer(String lado_der){
  
  String server = "http://10.0.0.18:3000/webapi/interrupt";

  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& JSONencoder = jsonBuffer.createObject();
  JSONencoder["Lado"] = lado_der;

  char JSONmessageBuffer[256];
  JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  
  HTTPClient http;
  http.begin(server);
  Serial.println("Insertando en -> " +server);
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.POST(JSONmessageBuffer);
  String payload = http.getString();
  
  http.end();
}
