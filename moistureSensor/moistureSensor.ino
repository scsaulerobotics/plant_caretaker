// 1. LIBRERÍAS
#include <Wire.h>              // Librería para comunicación I2C
#include <LiquidCrystal_I2C.h> // Librería para la pantalla LCD I2C

// 2. DEFINICIONES DE PINES Y PARÁMETROS

// Sensor de Suelo Capacitivo
#define SOIL_PIN A0   // Pin Analógico A0

// Parámetros de Calibración del Suelo (¡AJUSTA ESTOS VALORES!)
// Estos valores definen el rango de 0% (seco) a 100% (mojado) para tu sensor.
// DEBES calibrarlos para tu unidad específica.
const int AIR_VALUE = 548;   // Valor RAW de la lectura cuando el sensor está en el aire (SECO = 0%)
const int WATER_VALUE = 350; // Valor RAW de la lectura cuando el sensor está sumergido en agua (MOJADO = 100%)

// 3. INICIALIZACIÓN DE OBJETOS
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando Sensor de Humedad de Suelo...");
  
  // Inicia el bus I2C (usa pines A4 y A5 por defecto)
  Wire.begin(); 

  // Inicializa el LCD
  lcd.init();
  lcd.backlight(); 
  lcd.print("Humedad Suelo Init");
  
  delay(2000);
  lcd.clear();
}

void loop() {
  // Espera 1 segundo entre lecturas
  delay(1000);
  
  // Lectura analógica del pin A0 (0 a 1023)
  int soil_raw_value = analogRead(SOIL_PIN); 

  int soil_percent = map(soil_raw_value, AIR_VALUE, WATER_VALUE, 0, 100);

  // Asegurar que el valor esté entre 0 y 100
  if (soil_percent < 0) soil_percent = 0;
  if (soil_percent > 100) soil_percent = 100;
  
  lcd.setCursor(0, 0);
  lcd.print("Humedad del Suelo");

  lcd.setCursor(0, 1);
  lcd.print(soil_percent);
  lcd.print("% (RAW: ");
  lcd.print(soil_raw_value);
  lcd.print(")"); 
  
  // debug por terminal
  Serial.print("RAW: ");
  Serial.print(soil_raw_value);
  Serial.print(" | Humedad: ");
  Serial.print(soil_percent);
  Serial.println("%");
}
