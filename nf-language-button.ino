/*
 nf-language-button

 See README.md in the git repo for details.
*/

const String VERSION = "0.0.1";
 
// Pins used
const int BUTTON_PIN = 2;
const int LED_PIN = 13;

// How many milliseconds is considered a long press
const int LONG_PRESS_DURATION = 3000;

// This character is sent on button press
const char LANGUAGE_CHAR = 'l';

// This character is sent as an engagement gesture after bootup
const char ENGAGEMENT_CHAR = 'p';

// Keep sending 'p' for 10 minutes after bootup (1000 * 60 * 10)
const long ENGAGEMENT_DURATION = 600000; 

// Send 'p' after bootup every 10 seconds (1000 * 10)
const long ENGAGEMENT_INTERVAL =  10000; 

// Variables
boolean autoEngagementEnabled = true;
boolean longPressEngagementEnabled = true;
unsigned long elapsedTime = 0;
unsigned long lastEngagementTime = 0;
unsigned long lastPressTime = 0;
int previousButtonState = LOW;
int buttonState;

void setup() {  
  // Start serial connection
  Serial.begin(9600);

  // Initialise control over the keyboard
  Keyboard.begin();

  // Leondardo needs to wait for serial to be ready
  while (!Serial); 
  Serial.println("\nnf-language-button version " + VERSION + " is ready!");
  
  // Enable the internal pull-up resistor for the button pin
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // How long have the board been running
  elapsedTime = millis();
  
  // Handle the language button 
  buttonState = digitalRead(BUTTON_PIN);
  
  if (buttonState != previousButtonState) {
    if (buttonState == HIGH) {
      // Button is pressed - change language
      doLanguageToggle();
      lastPressTime = elapsedTime;
    } else {
      // HACK: Our buttons send one or more HIGHs on release; ignore those!
      delay(50);
    }
  }

  // Check for long press
  if (buttonState == HIGH && (elapsedTime - lastPressTime > LONG_PRESS_DURATION)) {
    Serial.println("Long press!");
    // Send engagement gesture and cancel autoEngagement on long press
    doEngagementGesture();
    autoEngagementEnabled = false;
    lastPressTime = elapsedTime;
  }

  previousButtonState = buttonState; 

  // Automatic engagement gesture on bootyp logic
  if (elapsedTime > ENGAGEMENT_DURATION) {
    autoEngagementEnabled = false;
  }
  
  if (autoEngagementEnabled) {
    if ((elapsedTime - lastEngagementTime) > ENGAGEMENT_INTERVAL) {
      doEngagementGesture();
      lastEngagementTime = elapsedTime;
    } 
  }

  // Engagement gesture on languagelong press
  elapsedTime = millis();
}

void doLanguageToggle() {
  Serial.println("Toggle language");
  Keyboard.write(LANGUAGE_CHAR);
}

void doEngagementGesture() {
  Serial.println("Engagement gesture");
  Keyboard.write(ENGAGEMENT_CHAR);
}




