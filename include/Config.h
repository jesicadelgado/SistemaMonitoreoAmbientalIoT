#ifndef CONFIG_H
#define CONFIG_H

// ============================================================
// Config.h
// Archivo de configuración central del proyecto.
// Aquí se definen credenciales, servidor, pines y parámetros
// generales para facilitar mantenimiento y reutilización.
// ============================================================

// ------------------------------------------------------------
// Configuración de red WiFi
// ------------------------------------------------------------

// Nombre de la red WiFi (SSID)
const char* WIFI_SSID = "Wokwi-GUEST";

// Contraseña de la red WiFi
const char* WIFI_PASSWORD = "";

// Modo de operación WiFi
#define WIFI_MODE WIFI_STA

// Tiempo de espera para conexión WiFi (ms)
#define WIFI_TIMEOUT 5000

// Tiempo para reconectar WiFi (ms)
#define WIFI_RECONNECT_DELAY 2000

// ------------------------------------------------------------
// Configuración de ThingSpeak
// ------------------------------------------------------------

// Servidor ThingSpeak
const char* THINGSPEAK_SERVER = "api.thingspeak.com";

// Clave de escritura (Write API Key) del canal de ThingSpeak
const char* THINGSPEAK_API_KEY = "JNKWVWHWB6F3OKH4";

// ID del canal ThingSpeak
const int THINGSPEAK_CHANNEL_ID = 3392724;

// Tiempo entre envíos a ThingSpeak (ms)
#define THINGSPEAK_UPDATE_INTERVAL 10000

// Códigos de respuesta ThingSpeak
#define TS_SUCCESS 200

// Mapeo de campos ThingSpeak
#define TS_FIELD_TEMPERATURE 1
#define TS_FIELD_HUMIDITY 2
#define TS_FIELD_LDR 3
#define TS_FIELD_RESET_FLAG 4

// Umbral de temperatura para LED (°C)
#define TEMPERATURE_THRESHOLD 30

// Valor para campo reset cuando está activo
#define RESET_FLAG_ACTIVE 1
#define RESET_FLAG_INACTIVE 0

// ------------------------------------------------------------
// Configuración de hardware - Pines
// ------------------------------------------------------------

// Pin donde está conectado el sensor DHT22
#define DHT_PIN 15

// Tipo de sensor DHT (DHT11, DHT21, DHT22)
#define DHT_TYPE DHT22

// Pin donde está conectado el sensor LDR (fotorresistencia)
#define LDR_PIN 32

// Pin donde está conectado el botón de reset
#define BUTTON_PIN 14

// Pin donde está conectado el LED indicador
#define LED_PIN 13

// Modo de entrada del botón (INPUT_PULLUP activa pull-up interno)
#define BUTTON_MODE INPUT_PULLUP

// Lógica del botón: LOW = presionado, HIGH = liberado
#define BUTTON_PRESSED LOW
#define BUTTON_RELEASED HIGH

// ------------------------------------------------------------
// Configuración de debounce del botón
// ------------------------------------------------------------

// Tiempo de debounce para evitar rebotes (ms)
#define BUTTON_DEBOUNCE_DELAY 50

// Tiempo mínimo que debe mantenerse presionado para activar reset (ms)
#define BUTTON_PRESS_DURATION 500

// Tiempo de espera después de enviar reset a ThingSpeak (ms)
#define RESET_THINGSPEAK_DELAY 2000

// Tiempo de espera antes de reiniciar ESP32 (ms)
#define RESET_ESP32_DELAY 3000

// ------------------------------------------------------------
// Configuración de comunicación serial
// ------------------------------------------------------------

// Velocidad del monitor serial (baudrate)
#define SERIAL_BAUDRATE 115200

// Intervalo de envío de logs a serial (ms)
#define SERIAL_LOG_INTERVAL 100

// Habilitar depuración detallada
#define DEBUG_MODE 1

#endif