/***************************************************************************
 *   Example for two SoftwareWire - BME280 connected on two different I2C 
 *   Tested on ATMEGA32U4 (https://www.dfrobot.com/product-1075.html)
 *   
 * - SoftwareWire sw(10, 11);  SDA=D10, SCL=D11
 * - SoftwareWire sw2(A0,9);   SDA=A0,  SCL=D9
 * 
 
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution

 ***************************************************************************/
#include <Wire.h>

#include <SoftwareWire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

//SoftWire sw(SDA, SCL);
SoftwareWire sw(10, 11);
SoftwareWire sw2(A0,9);

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
Adafruit_BME280 bme2; // I2C


unsigned long delayTime;

void setup() {
    Serial.begin(9600); while (!Serial);    
    Serial.println(F("BME280 test"));

    bool status;
    
    // default settings
    // (you can also pass in a Wire library object like &Wire2)
  //    status = bme.begin(0x76,&Wire);  
    status = bme.begin(0x76,&sw);  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        
        while (1);
    }

//  status = bme2.begin(0x76,&Wire);  
        status = bme2.begin(0x76,&sw2);  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
    
    Serial.println("-- Default Test --");
    delayTime = 1000;

    Serial.println();
}


void loop() { 
  Serial.println("1");
    printBme(bme);
    delay(delayTime);
    Serial.println("2");
    printBme(bme2);
    delay(delayTime);

}

void printBme(Adafruit_BME280& bme) {
      Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
}


