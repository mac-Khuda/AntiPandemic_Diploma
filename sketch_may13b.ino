  
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

//Датчик приближення
 int IRLED = 5;

//Ключ розмикання живлення датчика температури
 int key = 2;

//Значення датчика приближення
 int IRLEDval = 0;

//Зміна закінчування вимірювання
 bool isFinishedMeasuring = false;

//Піни LED-лампочки
 int red = 9;
 int blue = 10;
 int green = 11;

//Пін лазера
 int laser = 7;

//Пін реле на дозатор
 int rele = 3;

void setup() {  
  Serial.begin(9600);

  pinMode(IRLED, INPUT);
  pinMode(key, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(laser, OUTPUT);
  pinMode(rele, OUTPUT);

  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  digitalWrite(blue, HIGH);

  mlx.begin();

}

void loop() {
  digitalWrite(key, LOW);
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  digitalWrite(blue, LOW);
  digitalWrite(laser, HIGH);
  digitalWrite(rele, HIGH);
//  int test = digitalRead(5);
//  Serial.println(test);
  
  IRLEDval = digitalRead(IRLED);
  if (IRLEDval == LOW) {
    if (isFinishedMeasuring == false) {
      digitalWrite(key, HIGH);
      digitalWrite(blue, HIGH);

      digitalWrite(rele, LOW);
      delay(1000);
      
      Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
      Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
      float TEMP = mlx.readObjectTempC();
      Serial.print("*C\tObject = "); Serial.print(TEMP); Serial.println("*C");

      if (TEMP < 31.5) {
        digitalWrite(green, LOW);
        Serial.println("green");
        delay(2000);
      } else {
        digitalWrite(red, LOW);
        Serial.println("red");
        delay(2000);
      }
      isFinishedMeasuring = true;
    }
  } else {
      reuse();
  }

}

void reuse() {
  delay(2000);
  
  isFinishedMeasuring = false;
}
