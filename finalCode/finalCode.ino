#include <Wire.h>              // Librería para comunicación I2C
#include <LiquidCrystal_I2C.h> // Librería para la pantalla LCD I2C
#include <Servo.h>


//Sensor de Suelo Capacitivo -------------------------------------------------
#define SOIL_PIN A3

//Parámetros de Calibración del Suelo
const int AIR_VALUE = 548;   // Valor RAW de la lectura cuando el sensor está en el aire (SECO = 0%)
const int WATER_VALUE = 336; // Valor RAW de la lectura cuando el sensor está sumergido en agua (MOJADO = 100%)

const int HUMEDAD_MINIMA = 40;  //40% minimo de humedad para encender la bomba

//Pantalla LCD ---------------------------------------------------------------
LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 es la dirección I2C común (puede ser 0x3F)


//LDRs -----------------------------------------------------------------------
//1 3
// 2
const int pinLDR1 = A0; //arriba izquierda
const int pinLDR2 = A1; //abajo
const int pinLDR3 = A2; //arriba derecha

int valorLDR1 = 0;
int valorLDR2 = 0;
int valorLDR3 = 0;

//SERVOS ---------------------------------------------------------------------
const int pinServoX = 9;  //base - horizontal
const int pinServoY = 10;  //vertical

Servo servoX;
Servo servoY;

//parámetros de control
const int margen = 15;  //dif < 15 no se mueve

int posX = 90;  //posicion inicial servos
int posY = 90;


//H-Bridge -------------------------------------------------------------------
const int B1A = 4;
const int B1B = 5;

bool bombaEncender = false;






void setup() {
  Serial.begin(9600);  //open serial port, set the baud rate to 9600 bps
  Serial.println("Iniciando Sensor de Humedad de Suelo...");

  // Inicia el bus I2C (usa pines A4 y A5 por defecto)
  Wire.begin(); 

  // Inicializa el LCD
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Humedad Suelo");
  lcd.setCursor(0, 1);
  lcd.print("Inicializado");
  
  delay(2000);
  lcd.clear();


  // servos
  servoX.attach(pinServoX);  //attach servo on pin 9
  servoY.attach(pinServoY);

  // h-bridge
  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);

  digitalWrite(B1A, LOW);
  digitalWrite(B1B, LOW);
}


void loop() {
  //Servos empiezan en 90 grados
  servoX.write(posX);
  servoY.write(posY);


  //LECTURA DEL SENSOR DE SUELO CAPACITIVO
  int soil_raw_value = analogRead(SOIL_PIN); 

  // Mapear el valor RAW a un porcentaje de humedad (0% = Seco, 100% = Mojado)
  // map(valor, de_min, de_max, a_min, a_max)
  int soil_percent = map(soil_raw_value, AIR_VALUE, WATER_VALUE, 0, 100);

  // Asegurar que el valor esté entre 0 y 100
  if (soil_percent < 0) soil_percent = 0;
  if (soil_percent > 100) soil_percent = 100;
  

  //Control motor bomba de agua
  if (soil_percent < HUMEDAD_MINIMA) {  //menos del 40%
    digitalWrite(B1A, HIGH);
    digitalWrite(B1B, LOW);
    bombaEncender = true;

  } else {
    digitalWrite(B1A, LOW);
    digitalWrite(B1B, LOW);
  }

  //MOSTRAR DATOS EN EL LCD
  lcd.setCursor(0, 0);
  lcd.print("Humedad:");
  lcd.print(soil_percent);
  lcd.print("% (RAW: ");
  lcd.print(soil_raw_value);
  lcd.print(")"); 

  lcd.setCursor(0,1);
  if (bombaEncender) {
    lcd.print("Bomba: ON  ");
  } else {
    lcd.print("Bomba: OFF ");
  }


  //LDRs ---------------------------------------------------------------
  //Leemos el valor analógico (de 0 (oscuro) a 1023(luz))
  valorLDR1 = analogRead(pinLDR1);
  valorLDR2 = analogRead(pinLDR2);
  valorLDR3 = analogRead(pinLDR3);

  //imprime valor LDRs
  Serial.print("\nLDRs ->");
  Serial.print(" 1: ");
  Serial.print(valorLDR1);
  Serial.print(" | 2: ");
  Serial.print(valorLDR2);
  Serial.print(" | 3: ");
  Serial.print(valorLDR3);
  delay(50);

  
  int difX = (valorLDR1 - valorLDR3);  //base; izquierda - derecha
  int difY = ((valorLDR1 + valorLDR3)/2) - (valorLDR2);  //arriba - abajo


  if (abs(difX) > margen) {  //base
    if (difX < 0) {
      posX++;  //hay más luz a la izq
    }
    else {
      posX--;  //hay más luz a la dcha
    }
  }
  
  if (abs(difY) > margen) {
    if (difY < 0) {
      posY++;  //hay más luz arriba
    }
    else {
      posY--;  //hay más luz abajo
    }
  }

  //revisar ángulos de los servos
  if (posX > 180) posX = 180;
  if (posX < 0) posX = 0;

  if (posY > 160) posY = 160;
  if (posY < 0) posY = 0;

  //mover servos
  servoX.write(posX);
  servoY.write(posY);


  //imprime nuevos valores de los servos
  Serial.print(" || Motores Ángulos ->");
  Serial.print(" Motor base: ");
  Serial.print(posX);
  Serial.print(" | Motor arriba: ");
  Serial.print(posY);
}

