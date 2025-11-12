#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

const char *ssid = "realme 8";
const char *password = "amenisahmim";

//const char *ssid = "TOPNET_CE68";
//const char *password = "fb36b8i211";

#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 8883
#define AIO_USERNAME "chaimaghouili"
#define AIO_KEY ""

// Objets WiFi et MQTT
WiFiClientSecure client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish testFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/test");
Adafruit_MQTT_Publish temperatureFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish humidityFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");
Adafruit_MQTT_Publish solFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/sol_hymidity");
Adafruit_MQTT_Publish lumiereFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/lumiere");
Adafruit_MQTT_Publish errorFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/errors");
Adafruit_MQTT_Subscribe timeFeed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/time", MQTT_QOS_1);

unsigned long lastReconnectAttempt = 0;
const unsigned long RECONNECT_INTERVAL = 5000;

void timeCallback(char *data, uint16_t len) {
  Serial.print("[MQTT] Message reçuuuu: ");
  Serial.write(data, len);
  Serial.println();
  
  String message;
  for(uint16_t i=0; i<len; i++) {
    message += (char)data[i];
  }
  message.trim();
  
  if(validateDateFormat(message)) {
    Serial.println("Format d'heure valide");
    Serial2.println(data);
    if(!errorFeed.publish("validee")) {
      Serial.println("Erreur lors de la publication de confirmation");
    }
  } else {
    Serial.println("Format d'heure invalide");
    String errorMsg = "Erreur: format invalide (" + message + "), utilisez hh:mm";
    if(!errorFeed.publish(errorMsg.c_str())) {
      Serial.println("Erreur lors de la publication d'erreur");
    }
  }
}

bool validateDateFormat(String date) {
  if(date.length() != 5) return false;
  if(date[2] != ':' ) return false;
  
  for(uint8_t i=0; i<5; i++) {
    if(i == 2) continue;
    if(!isdigit(date[i])) return false;
  }
  String hourStr = date.substring(0, 2);
  String minStr = date.substring(3, 5);
  
  int hours = hourStr.toInt();
  int minutes = minStr.toInt();
  
  if(hours < 0 || hours > 23) return false;
  if(minutes < 0 || minutes > 59) return false;
  return true;
}

void connectToWiFi() {
  Serial.println();
  Serial.print("Connexion à ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connecté");
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());
}

void connectToMQTT() {
  Serial.println("Connexion à Adafruit IO...");
  
  int8_t ret;
  while((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Nouvelle tentative dans 5 secondes...");
    mqtt.disconnect();
    delay(5000);
  }
  
  Serial.println("Connecté à Adafruit IO!");
  
  timeFeed.setCallback(timeCallback);
  mqtt.subscribe(&timeFeed);
}

void processSensorData(String data) {
  Serial.println("Sensor data: " + data);

  if(!testFeed.publish(data.c_str())) {
    Serial.println("Failed to publish to test feed");
  }

  int index1 = data.indexOf(',');
  int index2 = data.indexOf(',', index1 + 1);
  int index3 = data.indexOf(',', index2 + 1);

  if(index1 == -1 || index2 == -1 || index3 == -1) {
    Serial.println("Invalid data format");
    return;
  }

  String tempStr = data.substring(0, index1);
  tempStr.trim();
  
  String humStr = data.substring(index1 + 1, index2);
  humStr.trim();
  
  String solStr = data.substring(index2 + 1, index3);
  solStr.trim();
  
  String lumiereStr = data.substring(index3 + 1);
  lumiereStr.trim();

  if (!temperatureFeed.publish(tempStr.c_str()))
    Serial.println("Temperature publish error!");
  else
    Serial.println("Temperature published!");

  if (!humidityFeed.publish(humStr.c_str()))
    Serial.println("Humidity publish error!");
  else
    Serial.println("Humidity published!");

  if (!solFeed.publish(solStr.c_str()))
    Serial.println("Soil moisture publish error!");
  else
    Serial.println("Soil moisture published!");
  String lightStatus = (lumiereStr == "1") ? "dark" : "light";

  if (!lumiereFeed.publish(lightStatus.c_str())) {
    Serial.println("Light status publish error!");
  } else {
    Serial.println("Light status published!");
  }
}


void checkConnections() {
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi déconnecté, reconnexion...");
    connectToWiFi();
  }

  if(!mqtt.connected()) {
    if(millis() - lastReconnectAttempt > RECONNECT_INTERVAL) {
      lastReconnectAttempt = millis();
      connectToMQTT();
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  connectToWiFi();
  client.setInsecure();
  connectToMQTT();
}

void loop() {
  checkConnections();
  mqtt.processPackets(10000);
  
  if(!mqtt.ping()) {
    mqtt.disconnect();
  }

  if(Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    data.trim();
    processSensorData(data);
  }

  delay(100);
}