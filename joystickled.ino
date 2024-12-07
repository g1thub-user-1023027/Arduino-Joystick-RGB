// Pin assignments
const int redPin = 9;    // Red LED pin
const int greenPin = 10; // Green LED pin
const int bluePin = 11;  // Blue LED pin
const int buzzerPin = 3; // Buzzer pin
const int joyX = A0;     // Joystick X-axis pin
const int swPin = 2;     // Joystick button (SW pin)

// Variables
int currentColor = 0;    // 0: Red, 1: Green, 2: Blue
int brightness = 0;      // Current brightness (0-255)
bool buttonPressed = false; // Tracks button state

void setup() {
  // Set LED pins as outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Set buzzer pin as output
  pinMode(buzzerPin, OUTPUT);

  // Set joystick button pin as input with pull-up resistor
  pinMode(swPin, INPUT_PULLUP);

  // Initialize LEDs to off
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
}

void loop() {
  // Read joystick X-axis for brightness adjustment
  int xValue = analogRead(joyX);
  brightness = map(xValue, 0, 1023, 0, 255);

  // Adjust the current color's brightness
  updateLED();

  // Check for joystick button press
  if (digitalRead(swPin) == LOW && !buttonPressed) {
    currentColor = (currentColor + 1) % 3; // Cycle through colors (0, 1, 2)
    playBuzzer(); // Emit a short beep on button press
    buttonPressed = true; // Prevent multiple presses
    delay(200); // Debounce delay
  } else if (digitalRead(swPin) == HIGH) {
    buttonPressed = false; // Reset button state
  }

  delay(10); // Small delay for smooth operation
}

// Function to adjust LED brightness
void updateLED() {
  switch (currentColor) {
    case 0: // Red
      analogWrite(redPin, brightness);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      break;
    case 1: // Green
      analogWrite(redPin, 0);
      analogWrite(greenPin, brightness);
      analogWrite(bluePin, 0);
      break;
    case 2: // Blue
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, brightness);
      break;
  }
}

// Function to play buzzer sound
void playBuzzer() {
  tone(buzzerPin, 1000, 100); // Play a 1kHz tone for 100ms
}
