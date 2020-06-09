/* PROJETO JARDIM INTELIGENTE
 * Automacao da irrigacao e coleta de dados
 * 
 * @claudio monteiro
 * @douglas carvalho
 * 
 * https://github.com/adafruit/Adafruit_Sensor
 * https://github.com/sarful/DHT_monitoring_In_Blynk_app_Use_NodeMcu/blob/master/DHT%20Library.zip
 */
 
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include "DHT.h"
#define DHTTYPE DHT11

#define FIREBASE_HOST "projeto-jardim.firebaseio.com"                          // database URL 
#define FIREBASE_AUTH "C2tuKvBx1yJE2TzhKO6ymf2G3RKmIBQVqBMYMWjY"             // secret key

#define WIFI_SSID "KATIA MARIA"                                           
#define WIFI_PASSWORD "100200300"   
  
#define pin_relay1 4
#define pin_relay2 5
#define pin_dht D6 
#define pin_ldr A0

int valor_ldr;

DHT dht (pin_dht, DHTTYPE);

void setupPins(){
  pinMode(pin_relay1, OUTPUT);
  pinMode(pin_relay2, OUTPUT);
  dht.begin(); 
}

void setupWifi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("conectando");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("conectado: ");
  Serial.println(WiFi.localIP());
}

void setupFirebase(){
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  if (Firebase.failed())    {
    Serial.print("setting number failed:");
    Serial.println(Firebase.error());
    ESP.reset();
  }
}

void setup() {
  Serial.begin (115200);
  setupPins();
  setupWifi();    
  setupFirebase();
}

void loop() {

    // leitura dos sensores
    valor_ldr = analogRead(pin_ldr);
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    // enviar dados dos sensores
    Firebase.pushInt("temperature", t); 
    Firebase.pushFloat("humidity", h); 

    // puxar o valor da lampada no firebase 
    bool lampValue = Firebase.getBool("lamp");

    // controle do relay
    digitalWrite(pin_relay1, lampValue ? HIGH : LOW);   
    digitalWrite(pin_relay2, lampValue ? HIGH : LOW);  
    delay(10000);

    // visualizar informacoes na tela
      Serial.print("Lamp Firebase: ");Serial.println(Firebase.getBool("lamp"));
      Serial.print("Umidade do Ar: ");Serial.println(h);
      Serial.print("Temperatura: ");Serial.println(t);
      Serial.print("Luminosidade: ");Serial.println(valor_ldr);
      Serial.println("");

    
}
