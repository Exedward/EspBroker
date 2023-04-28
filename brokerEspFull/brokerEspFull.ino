#include<sMQTTBroker.h>

class MyBroker:public sMQTTBroker{
public:
    bool onConnect(sMQTTClient *client, const std::string &username, const std::string &password)
    {
        // check username and password, if ok return true
        return true;
    };
	void onRemove(sMQTTClient*)
    {
    };
    void onPublish(sMQTTClient *client,const std::string &topic, const std::string &payload)
    {
        // client publish a message to the topic
        // you can parse the message, save it to a database, or whatever, based on your goals
    }
    bool onEvent(sMQTTEvent *event)
    {
        switch(event->Type())
        {
        case NewClient_sMQTTEventType:
            {
                sMQTTNewClientEvent *e=(sMQTTNewClientEvent*)event;
                e->Login();
                e->Password();
            }
            break;
        case LostConnect_sMQTTEventType:
            WiFi.reconnect();
            break;
        }
        return true;
    }
};

MyBroker broker;

unsigned long Time;
unsigned long freeRam;

const char* ssid = "Automacao";         
const char* password = "9xg14230pD"; 

void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println("Conectado!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
  
  const unsigned short mqttPort=1883;
  broker.init(mqttPort);
  
  Time=millis();
  freeRam=ESP.getFreeHeap();
}
void loop(){
  broker.update();
  if(millis()-Time>1000){
    Time=millis();
    if(ESP.getFreeHeap()!=freeRam){
      freeRam=ESP.getFreeHeap();
      Serial.print("RAM:");
      Serial.println(freeRam);
    }
  }
}
