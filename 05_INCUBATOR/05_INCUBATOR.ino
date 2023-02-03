#include "Adafruit_Si7021.h"
Adafruit_Si7021 sensor = Adafruit_Si7021();

//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

int relay_01 = 9;
int relay_02 = 8;

LiquidCrystal_I2C lcd(0x27,20,4);
void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  
  // wait for serial port to open
  while (!Serial) {
    delay(10);
  }

  Serial.println("Si7021 test!");
  
  if (!sensor.begin()) {
    Serial.println("Did not find Si7021 sensor!");
    while (true)
      ;
  }

  Serial.print("Found model ");
  switch(sensor.getModel()) {
    case SI_Engineering_Samples:
      Serial.print("SI engineering samples"); break;
    case SI_7013:
      Serial.print("Si7013"); break;
    case SI_7020:
      Serial.print("Si7020"); break;
    case SI_7021:
      Serial.print("Si7021"); break;
    case SI_UNKNOWN:
    default:
      Serial.print("Unknown");
  }
  Serial.print(" Rev(");
  Serial.print(sensor.getRevision());
  Serial.print(")");
  Serial.print(" Serial #"); Serial.print(sensor.sernum_a, HEX); Serial.println(sensor.sernum_b, HEX);

  pinMode(relay_01, OUTPUT);
  pinMode(relay_02, OUTPUT);
}

bool start {true};
void loop() 
{
  run_time();
  if(start == true)
  {
    Slow_start();
  }
  else
  {
    maintain_temp_within_range();
  }
  print_temp();
}

int seconds {0};

void run_time()
{
  seconds = millis()/1000;
  if(seconds%1 == 0)
  {
    lcd.setCursor(0,2);
    lcd.print(seconds);
  }
}

void tilt()
{
  if(seconds%18000 == 0)
  {
    //tilt
    digitalWrite(relay_02, LOW); // On
  }
}

void print_temp()
{
  if(seconds%1 == 0) // runs code every second
  {
    lcd.setCursor(0,0);
    lcd.print("Humidity:");
    lcd.setCursor(10,0);
    lcd.print(sensor.readHumidity());
    lcd.setCursor(0,1);
    lcd.print("Temperature:");
    lcd.setCursor(13,1);
    lcd.print(sensor.readTemperature(), 2);
    
  }
  
}

void maintain_temp_within_range() // average 1 min ON,and then OFF for average 5 minutes;
                                  // 200 watts heater ON for ave 5 hours a day. 300 pesos for 25 days of use
{

  if(sensor.readTemperature() > 37.5)// temp rise up to 38.12 ~ 38.21
  {
    digitalWrite(relay_01, HIGH); // Off
    lcd.setCursor(0,3);
    lcd.print("Relay OFF ");
  }

  if(sensor.readTemperature() < 37.2) // temp drops up to 37.06
  {
    digitalWrite(relay_01, LOW); // On
    lcd.setCursor(0,3);
    lcd.print("Relay on ");
  }
}

bool clear_once = true;
void Slow_start() // Swithces on relay for 10 seconds and off for 20 seconds
{
  if(seconds%10 == 0 && seconds%20 != 0 && seconds%30 != 0)
  {
    if(clear_once == true) // uses bool to clear lcd string once
    {
      lcd.clear();
      clear_once = false;
    }
     digitalWrite(relay_01, LOW);
     lcd.setCursor(0,3);
     lcd.print("relay on");
  }
  
  if(seconds%20 == 0 || seconds%30 == 0)
  {
    clear_once = true;
    digitalWrite(relay_01, HIGH);//relay off
    lcd.setCursor(0,3);
    lcd.print("relay off");
  }
  if(sensor.readTemperature() > 37) // will stop calling the function after reaching 37 degree Celcius
  {
    start = false;
  }
}
