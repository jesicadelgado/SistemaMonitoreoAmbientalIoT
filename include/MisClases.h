
#ifndef MIS_CLASES_H
#define MIS_CLASES_H

#include <Arduino.h>

class Led {
  private:
    int pin;
  public:
    Led(int p) { pin = p; }
    void begin() { pinMode(pin, OUTPUT); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};

class Boton {
  private:
    int pin;
    bool estado;
  public:
    Boton(int p) { pin = p; estado = HIGH; }
    void begin() { pinMode(pin, INPUT_PULLUP); }
    bool fuePresionado() {
      bool ahora = digitalRead(pin);
      if (estado == HIGH && ahora == LOW) { estado = ahora; return true; }
      estado = ahora;
      return false;
    }
};

class Potenciometro {
  private:
    int pin;
  public:
    Potenciometro(int p) { pin = p; }
    void begin() { pinMode(pin, INPUT); }
    int leer()   { return analogRead(pin); }
};

class SensorDHT {
  private:
    DHT dht;
    float ultimaTemp;
    float ultimaHum;
  public:
    SensorDHT(int pin, int tipo = DHT22) : dht(pin, tipo) {
      ultimaTemp = -999;
      ultimaHum  = -999;
    }

    void begin() { dht.begin(); }

    bool leer() {
      float t = dht.readTemperature();
      float h = dht.readHumidity();
      if (isnan(t) || isnan(h)) return false;
      ultimaTemp = t;
      ultimaHum  = h;
      return true;
    }

    float temperatura() { return ultimaTemp; }
    float humedad()     { return ultimaHum;  }
    bool  valido()      { return ultimaTemp != -999; }
};

class LDR {
  private:
  int pin;
  public:
  LDR(int p) { pin = p; }
  void begin() { pinMode(pin, INPUT); }
  int leer() { return analogRead(pin); }
};


#endif