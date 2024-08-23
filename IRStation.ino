//Transmitter program

#include <SPI.h>
#include "nRF24L01.h"


Nrf24l Mirf = Nrf24l(10, 9);
int ch1 = 2;
int ch2 = 3;
int ch3 = 4;
int ch4 = 5;
//int readIC[8] = {0, 0, 0, 0, 0, 0, 0, 0};
const int IRSensor1 = 6;
const int IRSensor2 = 7;
void setup()
{
  Serial.begin(9600);
  pinMode(IRSensor1, INPUT);
  pinMode(IRSensor2, INPUT);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setTADDR((byte *)"ABCDE"); // Set your own address (sender address) using 5 characters
  Mirf.payload = 32;
  Mirf.channel = 90; // Set the channel used
  Mirf.config();
  attachInterrupt(digitalPinToInterrupt(6), forward, FALLING);
  attachInterrupt(digitalPinToInterrupt(7), backward, FALLING);
}

void forward(){
  Mirf.send((byte*)"F");
  Serial.println("Signal sent: FORWARD");
}

void backward(){
    Mirf.send((byte*)"B");
    Serial.println("Signal sent: BACKWARD");
}

void loop()
{
  if(digitalRead(IRSensor1)==LOW){
  forward();
  }
  else if(digitalRead(IRSensor2)==LOW){
    backward();
  }
 // else if (digitalRead(IRSensor1)==LOW && digitalRead(IRSensor2)==LOW){
    //Mirf.send((byte*)"STOP");
    //Serial.println("Signal sent: STOP");
  //}
  delay(200);
}
