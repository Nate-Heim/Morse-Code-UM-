#include <Wire.h>

#define SDA_PIN 0 // GPIO 0 as SDA
#define SCL_PIN 1 // GPIO 1 as SCL

const int redLED = 15;   // GPIO pin for Red LED
const int greenLED = 14; // GPIO pin for Green LED
const int blueLED = 13;  // GPIO pin for Blue LED

void setup() {
  // Initialize LED pins as output
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  Wire.setSDA(SDA_PIN);
  Wire.setSCL(SCL_PIN);

  // Start I2C as a slave on address 0x11
  Wire.begin(0x11);
  Wire.onReceive(receiveEvent);  // Set the function to call when data is received
}

void loop() {  
}

// Function to blink the red LED for a dash
void blinkRed() {
  digitalWrite(redLED, HIGH);
  delay(2000);  // Dash: on for 2000ms
  digitalWrite(redLED, LOW);
  delay(500);   // Off for 500ms
}

// Function to blink the green LED for a dot
void blinkGreen() {
  digitalWrite(greenLED, HIGH);
  delay(1000);  // Dot: on for 1000ms
  digitalWrite(greenLED, LOW);
  delay(500);   // Off for 500ms
}

// Function to blink the blue LED between characters
void blinkBlue() {
  digitalWrite(blueLED, HIGH);
  delay(400);  // Blue LED: on for 400ms
  digitalWrite(blueLED, LOW);
  delay(400);  // Off for 400ms
}

// This function is called whenever data is received via I2C
void receiveEvent(int numBytes) {
  while (Wire.available()) {
    char symbol = Wire.read();  // Read the symbol sent from the Raspberry Pi Zero

    if (symbol == '_') {        // Dash
      blinkRed();
    } else if (symbol == '.') { // Dot
      blinkGreen();
    } else if (symbol == ' ') { // Character break (space)
      blinkBlue();
    }
  }
}