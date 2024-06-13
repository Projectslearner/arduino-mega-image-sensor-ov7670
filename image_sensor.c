/*
    Project name : Image Sensor OV7670
    Modified Date: 13-06-2024
    Code by : Projectslearner
    Website : https://projectslearner.com/learn/arduino-mega-image-sensor-ov7670
*/

// Pin definitions
const int resetPin = 22;          // Reset pin of OV7670
const int vsyncPin = 2;           // VSYNC pin of OV7670
const int hrefPin = 3;            // HREF pin of OV7670
const int pixelClockPin = 4;      // Pixel Clock pin of OV7670
const int dataPins[] = {5, 6, 7, 8, 9, 10, 11, 12};  // Parallel data pins D0-D7

void setup() {
  // Initialize pins
  pinMode(resetPin, OUTPUT);
  pinMode(vsyncPin, INPUT);
  pinMode(hrefPin, INPUT);
  pinMode(pixelClockPin, INPUT);
  
  // Initialize data pins
  for (int i = 0; i < 8; i++) {
    pinMode(dataPins[i], INPUT);
  }

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Reset OV7670 (sequence may vary based on datasheet)
  digitalWrite(resetPin, HIGH);
  delay(100);
  digitalWrite(resetPin, LOW);
  delay(100);

  // Wait for VSYNC signal to start reading image data
  while (digitalRead(vsyncPin) == LOW);

  // Read image data from OV7670
  for (int row = 0; row < 480; row++) {
    for (int col = 0; col < 640; col++) {
      // Wait for HREF signal
      while (digitalRead(hrefPin) == LOW);
      
      // Read pixel data
      uint16_t pixelData = 0;
      for (int i = 0; i < 2; i++) {
        pixelData |= digitalRead(dataPins[i]) << i;
      }
      
      // Print pixel data to Serial Monitor for debugging
      Serial.println(pixelData);
      
      // Wait for next pixel clock cycle
      while (digitalRead(pixelClockPin) == LOW);
      while (digitalRead(pixelClockPin) == HIGH);
    }
  }
}
