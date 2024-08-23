#include <SparkFun_TB6612.h>
#include <SPI.h>
#include "nRF24L01.h"

#define AIN1 2
#define AIN2 4
#define PWMA 6
#define STBY 8

Nrf24l Mirf = Nrf24l(10, 9);

const int offsetA = 1;
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
//Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
void setup()
{
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"ABCDE"); // Set your own address (receiver address) using 5 characters
  Mirf.payload = 32;
  Mirf.channel = 90; // Set the used channel
  Mirf.config();
  Serial.println("Listening..."); // Start listening to received data
  motor1.drive(150);
}
void processIncomingData() {
 if (Mirf.dataReady()) { // When the program is received, the received data is output from the serial port
    byte receivedData[32];
    Mirf.getData(receivedData);
    Serial.print("Got data: ");
    Serial.println((char*)receivedData);
    if (strcmp((char*)receivedData, "F") == 0){
    motor1.drive(150);
    Serial.print("Motor moving forward");
    //delay(500);
    }
    else if (strcmp((char*)receivedData, "B") == 0) {
      motor1.drive(-150);
      Serial.print("Motor moving backward");
      //delay(500);
    }
    //else if (strcmp((char*)receivedData, "STOP") == 0) {
      //motor1.drive(0);
      //delay(500);
    //}
   }
}


void loop()
{
  processIncomingData();
}