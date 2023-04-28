#include"sMQTTBroker.h"

sMQTTBroker broker;

IPAddress local_ip(10,109,49,85);
IPAddress gateway(10,109,49,1);
IPAddress subnet(255,255,255,0);

const char* ssid = "Automacao";        
const char* password = "9xg14230pD";

void setup(){
    Serial.begin(115200);
    if(!WiFi.config(local_ip, gateway, subnet)) Serial.println("Falha ao configurar IP local."); 
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED){ 
        Serial.print(".");
        delay(500);
    }
    Serial.println("Conectado!");  
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    
    const unsigned short mqttPort = 1883;
    broker.init(mqttPort);
}
void loop(){
    broker.update();
}
