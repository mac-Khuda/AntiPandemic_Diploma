/*************************************************** 
  This is a library example for the MLX90614 Temp Sensor

  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1747 3V version
  ----> https://www.adafruit.com/products/1748 5V version

  These sensors use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

  int measure = 5;
 
  int lazerPin = 3;
  int val = 0;
  int relePin = 2;
  bool isFinishedMeasuring = false;

void setup() {
  Serial.begin(9600);
  pinMode(measure, INPUT);
  pinMode(lazerPin, OUTPUT);
  pinMode(relePin, OUTPUT);
  
  Serial.println("Adafruit MLX90614 test");  

  mlx.begin();  

  
}

void loop() {
  digitalWrite(relePin, LOW);
  digitalWrite(lazerPin,HIGH);
  val = digitalRead(measure);
  if (val == LOW) {
    if (isFinishedMeasuring == false) {
      digitalWrite(relePin, HIGH);
      delay(1000);
      Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
      Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
      float TEMP = mlx.readObjectTempC();
      Serial.print("*C\tObject = "); Serial.print(TEMP); Serial.println("*C");
      //Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
      //Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
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
