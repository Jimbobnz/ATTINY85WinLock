/*
  FADING A LED WITH SINE WAVE
  Andrea Toscano 2016
*/


#include "DigiKeyboard.h"

// Arduino LED PIN
#define LED_PIN 1
#define buttonPin 0
// Baudrate for Serial Communication
#define SERIAL_BAUD 115200

// Time period of fading in millisecs
#define PERIOD 2000
// Angular Frequency by definition
#define OMEGA 2*PI/PERIOD
// No Phase
#define PHASE 0
// Offset of the sine wave
#define OFFSET 128
// Amplitude of the sine wave
#define AMPLITUDE 127


// Used to generate time for the cos wave
unsigned long timer = 0;
int buttonState;


boolean OutputState = false;        //sets output to off
boolean lastButtonState = LOW;    // note the last button read to ensure it is released.

void setup() {
  // Uncomment for serial monitor
  //Serial.begin(SERIAL_BAUD);
  pinMode (buttonPin, INPUT_PULLUP);
}

void loop() {
  timer = millis(); // updating time
  int ledValue = ledValue = OFFSET + AMPLITUDE * (cos(OMEGA * timer) + PHASE);

  DigiKeyboard.update();

  //read the button pin and if HIGH AND doesn't equal last time then next line
  if (digitalRead(buttonPin) == LOW && digitalRead(buttonPin) != lastButtonState)
  {
    delay(50);                             // Wait 50mS for debounce and then check again
    if (digitalRead(buttonPin) == LOW)    // If it's still HIGH then change the outlet state
    {
      digitalWrite(LED_PIN, HIGH);
      DigiKeyboard.sendKeyStroke(KEY_L, MOD_GUI_LEFT);

      DigiKeyboard.sendKeyStroke(0, 0); // releasing keyboard.
      
      lastButtonState = LOW;
      delay(3000);
      analogWrite(LED_PIN, checkValue(ledValue));
    }
  } else {
    analogWrite(LED_PIN, checkValue(ledValue));
    lastButtonState = HIGH;
  }
  // ** this needs the button to restore before checking again **


}


// Useful to avoid LED values outside the bounds [0;255]
int checkValue(int val) {
  if (val > 255)
    val = 255;
  else if (val < 0)
    val = 0;
  return val;
}
