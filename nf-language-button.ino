/*
 nf-language-button

 See README.md in the git repo for details.
*/

// Remove comment to enable debug output to Serial Monitorlpp
//#define DEBUG

const String VERSION = "0.0.3";
 
// Pins used
const int BUTTON_PIN = 2;
const int LED_PIN = 13;

// How many milliseconds is considered a long press
const int LONG_PRESS_DURATION = 3000;

// Ingore button state changes for some ms to avoid false positives
const int DEBOUNCE_TIME = 10;

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
int previousButtonState = HIGH;
int buttonState;

void setup() {  
  #ifdef DEBUG
    // Start serial connection
    Serial.begin(9600);
    // Leondardo needs to wait for serial to be ready
    while (!Serial); 
    debug("\nnf-language-button version " + VERSION + " is ready!");
  #endif
  
  // Initialise control over the keyboard
  Keyboard.begin();
  
  // Enable the internal pull-up resistor for the button pin
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // How long have the board been running
  elapsedTime = millis();
  
  // Handle the language button 
  buttonState = digitalRead(BUTTON_PIN);
  
  if ((buttonState != previousButtonState) && buttonState == LOW) {
    // Button is pressed - change language
    debug("Toggle language");
    Keyboard.write(LANGUAGE_CHAR);
    delay(DEBOUNCE_TIME);
    lastPressTime = elapsedTime;
  }

  previousButtonState = buttonState; 

  // Check for long press
  if (buttonState == LOW && (elapsedTime - lastPressTime > LONG_PRESS_DURATION)) {
    // Send engagement gesture and cancel autoEngagement on long press
    debug("Long press! Engagement gesture");
    Keyboard.write(ENGAGEMENT_CHAR);
    autoEngagementEnabled = false;
    lastPressTime = elapsedTime;
  }

  // Automatic engagement gesture on bootup logic
  if (elapsedTime > ENGAGEMENT_DURATION) {
    autoEngagementEnabled = false;
  }
  
  if (autoEngagementEnabled) {
    if ((elapsedTime - lastEngagementTime) > ENGAGEMENT_INTERVAL) {
      debug("Engagement gesture");
      Keyboard.write(ENGAGEMENT_CHAR);
      lastEngagementTime = elapsedTime;
    } 
  }

  // Engagement gesture on languagelong press
  elapsedTime = millis();
}

void debug(String str) {
  #ifdef DEBUG
    Serial.println(str);
  #endif
}



