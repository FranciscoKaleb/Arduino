#include "Arduino.h"
#include <SPI.h>
#include <RF24.h>

RF24 radio(7, 8);

byte addresses[][6] = {"1Node", "2Node"};

// -----------------------------------------------------------------------------
// SETUP   SETUP   SETUP   SETUP   SETUP   SETUP   SETUP   SETUP   SETUP
// -----------------------------------------------------------------------------
void setup() 
{
  Serial.begin(9600);
  Serial.println("TRANSMITTER");
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_2MBPS);
  radio.setChannel(124);
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);

}
int data = 12;
void loop() 
{
  radio.write(&data, sizeof(int));
  Serial.print("Sent: ");
  Serial.println(data);
  delay(1000);
  data = data + 1;
}
