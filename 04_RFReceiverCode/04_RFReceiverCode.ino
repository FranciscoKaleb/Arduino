#include "Arduino.h"
#include <SPI.h>
#include <RF24.h>
int LED = 2;
RF24 radio(7, 8);

byte addresses[][6] = {"1Node","2Node"};

void setup() 
{
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("RECEIVER");
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_2MBPS);
  radio.setChannel(124);
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  radio.startListening();
}

void loop() 
{
  int data;
  if ( radio.available()) 
  {
    while (radio.available()) 
    {
      radio.read( &data, sizeof(int));
    }
    //radio.stopListening();
    //data = data + 2;
    //radio.write( &data, sizeof(int) );
    //radio.startListening();
    Serial.print("received: ");
    Serial.println(data);
  }
  if(data%5 == 0)
  {
    digitalWrite(LED,HIGH);
  }
  else
  {
    digitalWrite(LED,LOW);
  }
}
