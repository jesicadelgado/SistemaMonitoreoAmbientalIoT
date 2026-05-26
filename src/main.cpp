
#include <WiFi.h>
#include "DHT.h"
#include "ThingSpeak.h"
#include "Config.h"
#include "MisClases.h"

SensorDHT dht(DHT_PIN, DHT_TYPE);
LDR ldr(LDR_PIN);
Led led(LED_PIN);
Boton botonReset(BUTTON_PIN);
WiFiClient client;

bool alertaActiva = false;
bool alertaSilenciada = false;
unsigned long ultimoEnvioThingSpeak = 0;

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println("[DEBUG] Serial iniciado a " + String(SERIAL_BAUDRATE));

  dht.begin();
  ldr.begin();
  led.begin();
  botonReset.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  unsigned long wifiStart = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - wifiStart) < WIFI_TIMEOUT) {
    delay(500);
    Serial.println("Wifi No conectado");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Wifi conectado!");
    Serial.println("Local IP: " + WiFi.localIP().toString());
    WiFi.mode(WIFI_MODE);
    ThingSpeak.begin(client);
  } else {
    Serial.println("Wifi sin conexion ");
  }
  
  Serial.println("\n========== SISTEMA INICIADO ==========");
  Serial.println("[SETUP] DHT22 en pin: " + String(DHT_PIN));
  Serial.println("[SETUP] Boton reset en pin: " + String(BUTTON_PIN));
  Serial.println("[SETUP] LED en pin: " + String(LED_PIN));
  Serial.println("[SETUP] LDR en pin: " + String(LDR_PIN));
  Serial.println("[SETUP] Canal ThingSpeak: " + String(THINGSPEAK_CHANNEL_ID));
  Serial.println("====================================\n");
}

void loop() {
  dht.leer();
  float temperatura = dht.temperatura();
  float humedad = dht.humedad();
  int valorLDR = ldr.leer();

  if (temperatura > TEMPERATURE_THRESHOLD) {
    if (!alertaSilenciada) {
      alertaActiva = true;
    }
  } else {
    alertaActiva = false;
    alertaSilenciada = false;
  }

  if (alertaActiva) {
    led.on();
  } else {
    led.off();
  }

  Serial.print("[SENSORES] Temp: " + String(temperatura, 2) + "°C");
  Serial.print(" | Humedad: " + String(humedad, 1) + "%");
  Serial.print(" | LDR: " + String(valorLDR));
  Serial.print(" | Alerta: " + String(alertaActiva ? "ACTIVA" : "OK"));
  Serial.println(" | Silenciada: " + String(alertaSilenciada ? "SI" : "NO"));


  if (botonReset.fuePresionado()) {
    Serial.println("[BOTON] Presionado");
    
    if (alertaActiva) {
      alertaActiva = false;
      alertaSilenciada = true;
      led.off();
      Serial.println("[BOTON] Alerta de temperatura silenciada.");
    } else {
      Serial.println("[BOTON] No hay alerta activa para silenciar.");
    }
  }

  if ((millis() - ultimoEnvioThingSpeak) >= THINGSPEAK_UPDATE_INTERVAL) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("[THINGSPEAK] Enviando datos...");
      
      ThingSpeak.setField(TS_FIELD_TEMPERATURE, temperatura);
      ThingSpeak.setField(TS_FIELD_HUMIDITY, humedad);
      ThingSpeak.setField(TS_FIELD_LDR, valorLDR);
      
      int responseCode = ThingSpeak.writeFields(THINGSPEAK_CHANNEL_ID, THINGSPEAK_API_KEY);
      ultimoEnvioThingSpeak = millis();
      
      if (responseCode == TS_SUCCESS) {
        Serial.println("[THINGSPEAK] Datos enviados correctamente");
      } else {
        Serial.println("[THINGSPEAK] Error: " + String(responseCode));
      }
    } else {
      Serial.println("[THINGSPEAK] Sin conexion WiFi");
      WiFi.reconnect();
    }
  }

  Serial.println("-------------------------------------------");
  delay(SERIAL_LOG_INTERVAL);
}