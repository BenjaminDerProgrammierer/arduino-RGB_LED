/*
 * B. Hartmann - DTN05 - 1AHITM - 2024/25
 * This Code controls a RGB LED with PWM
 * Level 1: Constant color
 * Level 2: Serial input for color
 * 
 * Serial input format: "R,G,B\n"
 * Example: "255,0,0\n" -> Red
 * Important! The input must end with '\n', so set your "Line ending" in the Serial Monitor to "LF"
*/

#include <Arduino.h>

// Temporary string to store input
String inputString = "";

#define RED_PIN 2 // PWM
#define GREEN_PIN 3 // PWM
#define BLUE_PIN 4 // PWM

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n') {
      // remove '\n' from string
      inputString = inputString.substring(0, inputString.length() - 1);
      inputString.trim();

      // split for ',' and convert to int
      int colors[3];
      char *token = strtok(&inputString[0], ",");
      for(int i = 0; i < 3 && token != NULL; i++) {
        colors[i] = atoi(token);
        token = strtok(NULL, ",");
      }

      // print received colors
      Serial.print("Received colors: ");
      for(int i = 0; i < 3; i++) {
        Serial.print(colors[i]);
        if (i < 2) Serial.print(", ");
      }
      Serial.println();

      // set colors
      analogWrite(RED_PIN, colors[0]);
      analogWrite(GREEN_PIN, colors[1]);
      analogWrite(BLUE_PIN, colors[2]);

      inputString = "";
    } else {
      inputString += c;
    }
  }
}
