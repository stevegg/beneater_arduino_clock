// Simple 2 mode clock circuit to replace Ben Eater's 555 timer
// version.

#define STEP_BUTTON 2
#define MODE_BUTTON 3
#define CLOCK 4


// Make sure that if a button is clicked less than the DEBOUNCE_INTERVAL_MS from 
// the last time it is ignored.
#define DEBOUNCE_INTERVAL_MS 35

boolean runMode = true;                 // When true we are in astable mode otherwise
                                        // in monostable mode.
unsigned int lastModeButtonClick = 0;   // Used to de-bounce the mode button
unsigned int lastStepButtonClick = 0;   // Used to de-bounce the step button

void setup() {
  // Setup the CLOCK pin as an output
  pinMode(CLOCK, OUTPUT);
  // Setup both the Step and mode buttons as input
  pinMode(STEP_BUTTON, INPUT);
  pinMode(MODE_BUTTON, INPUT);
  // Set the initial value of the clock pin to LOW
  digitalWrite(CLOCK, LOW);

  // Use an interrupt to handle the mode button.  Probably overkill
  attachInterrupt(digitalPinToInterrupt(MODE_BUTTON), modeButtonClick, RISING);
}

// Handle the mode button being clicked.
void modeButtonClick() {
  if ( (millis() - lastModeButtonClick) > DEBOUNCE_INTERVAL_MS) {
    runMode = !runMode;
  }
  // Save the last time it was pressed regardless of whether we were within
  // the DEBOUNCE_INTERVAL_MS time or not.
  lastModeButtonClick = millis();
}

// Send a clock pulse with an equal duty cycle of rate (in ms).
void sendClockPulse(int rate) {
    digitalWrite(CLOCK, HIGH);
    delay(rate);
    digitalWrite(CLOCK, LOW);
    delay(rate);
}

// Main Loop
void loop() {
  // Read the potentiometer settings.  We never want to be zero so will add a minimum
  // interval (10ms in this case).  I'm also inverting the value so that when the 
  // potentiometer is at its highest resistance we're pulsing at the fastest rate
  // just to make it more intuitive.
  int rate = 10 + (1023 - analogRead(A0));
  // Check state of the mode button.  If we are in astable mode then just pulse the clock
  if ( runMode ) {

    // Send a Clock pulse
    sendClockPulse(rate);

  } else {
    if ( digitalRead(STEP_BUTTON) ) {
      if ( (millis() - lastStepButtonClick) > DEBOUNCE_INTERVAL_MS) {
        // Send a Clock Pulse
        sendClockPulse(rate);
      }
      // Save the last time it was pressed regardless of whether we were within
      // the DEBOUNCE_INTERVAL_MS time or not.
      lastStepButtonClick = millis();
    }
  }
}
