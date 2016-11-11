#include <SoftwareSerial.h>

const int LEDPINS = 3;

const int RED = 11;
const int GREEN = 10;
const int BLUE = 9;

// LED Pins representing the RED, GREEN, and BLUE pins of the LED.
// Some RGB LEDs are different, check your datasheet.
const int LEDPin [3] = {11, 9, 10};

int LEDValue [3] = {0, 0, 0};

SoftwareSerial BT (7, 6);  // Rx, Tx pins, from the Arduino perspective  (Tx, Rx on BT)

int byteCount = 0;
int LEDIndex = 0;

int index = 0;
char serialString[20];
//String serialString;

void setup ()
{
   for (int i = 0; i < LEDPINS; i++)
   {
      pinMode (LEDPin [i], OUTPUT);
   }

   BT.begin (9600);
   Serial.begin (9600);

   Serial.println ("BT Interface");
}

void loop ()
{
   byteCount = BT.available ();

   if (byteCount > 0)
   {
      LEDIndex = 0;
      while (BT.available () &&  LEDIndex < LEDPINS)
      {
         // Android doesn't support an unsigned byte conversion, so I'm sending
         // a string from Android to Arduino.  So use parseInt to read the values
         // in between commas.
         LEDValue [LEDIndex] = BT.parseInt();
         LEDIndex++;
      }
      
      // Send the various color values to the LED
      for (int i = 0; i < LEDPINS; i++)
      {
         analogWrite (LEDPin [i], LEDValue [i]);
      };

   }

   byteCount = Serial.available ();
   if (byteCount > 0)
   {
      // Send the received string over Bluetooth to the phone.
      index = 0;
      while (Serial.available ())
      {
         serialString [index] = Serial.read();
      }

      Serial.write (serialString);
      
      BT.write (serialString);
   }
}

