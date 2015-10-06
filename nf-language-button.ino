/*
 Input Pullup Serial

 This example demonstrates the use of pinMode(INPUT_PULLUP). It reads a
 digital input on pin 2 and prints the results to the serial monitor.

 The circuit:
 * Momentary switch attached from pin 2 to ground
 * Built-in LED on pin 13

 Unlike pinMode(INPUT), there is no pull-down resistor necessary. An internal
 20K-ohm resistor is pulled to 5V. This configuration causes the input to
 read HIGH when the switch is open, and LOW when it is closed.

 */

//#include "Keyboard.h"

int buttonPin = 2;
int previousButtonState = LOW;

void setup() {
  
  // Start serial connection
  Serial.begin(9600);

  // Initialize control over the keyboard
  Keyboard.begin();
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.println("\n\nReady!");
  Serial.print("Initial previousButtonState: ");
  Serial.print(previousButtonState);
  
  //configure pin2 as an input and enable the internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(13, OUTPUT);

  // initialize control over the keyboard:
  //Keyboard.begin();
}

void loop() {
  //read the pushbutton value into a variable
  int buttonState = digitalRead(buttonPin);
  //Serial.println(buttonState);

  if (buttonState != previousButtonState) {
    //Serial.println("\nButton state changed");
    //Serial.println(buttonState);

    if (buttonState == HIGH) {
      Serial.println("Send key!");
      Keyboard.print("All meeting!");
    } else {
      // HACK: Our buttons send one or more HIGHs on release. Ignore those!
      delay(50);
    }
  }
  

/*
  if ((buttonState == HIGH) && (buttonState != previousButtonState)) {
    // Button depressed
    digitalWrite(13, HIGH);
    Serial.println("\n\n --> Loop start: Send key!");
    Serial.print("buttonState: ");
    Serial.print(buttonState);
    Serial.print("\nprevioiusButtonState: ");
    Serial.print(previousButtonState);
  } else {    
    // Button open
    digitalWrite(13, LOW);
  }
*/

  previousButtonState = buttonState; 
}



