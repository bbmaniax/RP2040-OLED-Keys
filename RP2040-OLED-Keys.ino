/*
  OLED Keys

  A simple OLED display demo with button navigation
  showing multiple display patterns on SSD1306.
*/

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SSD1306_128X64
// #define SSD1306_128X32

#define BUTTON1_PIN 15
#define BUTTON2_PIN 29

#if defined(SSD1306_128X64)
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_I2C_ADDRESS 0x3C
#define DISPLAY_COLOR_WHITE SSD1306_WHITE
#elif defined(SSD1306_128X32)
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 32
#define DISPLAY_I2C_ADDRESS 0x3C
#define DISPLAY_COLOR_WHITE SSD1306_WHITE
#else
#error "No display size defined"
#endif

#define PATTERN_COUNT 4

Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT);

int patternIndex = 0;

void setup() {
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
}

void loop() {
  switch (patternIndex) {
    case 0: displayLogo(); break;
    case 1: displayHello(); break;
    case 2: displayGraphics(); break;
  }

  while (digitalRead(BUTTON1_PIN) == LOW || digitalRead(BUTTON2_PIN) == LOW) { delay(10); }

  while (true) {
    if (digitalRead(BUTTON1_PIN) == LOW) {
      delay(50);
      if (digitalRead(BUTTON1_PIN) == LOW) {
        patternIndex = (patternIndex - 1 + PATTERN_COUNT) % PATTERN_COUNT;
        break;
      }
    }
    if (digitalRead(BUTTON2_PIN) == LOW) {
      delay(50);
      if (digitalRead(BUTTON2_PIN) == LOW) {
        patternIndex = (patternIndex + 1) % PATTERN_COUNT;
        break;
      }
    }
    delay(10);
  }
}

void displayLogo() {
  display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_I2C_ADDRESS);
  display.display();
}

void displayHello() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(DISPLAY_COLOR_WHITE);
#if defined(SSD1306_128X64)
  display.setTextSize(2);
  display.setTextColor(DISPLAY_COLOR_WHITE);
  printCenter(4, "HELLO");
  printCenter(24, "OLED");
  printCenter(44, "SSD1306");
#elif defined(SSD1306_128X32)
  display.setTextSize(1);
  display.setTextColor(DISPLAY_COLOR_WHITE);
  printCenter(4, "HELLO");
  printCenter(12, "OLED");
  printCenter(20, "SSD1306");
#endif
  display.display();
}

void displayGraphics() {
  display.clearDisplay();
  for (int x = 0; x < DISPLAY_WIDTH; x += 8) {
    display.drawLine(x, 0, DISPLAY_WIDTH - 1 - x, DISPLAY_HEIGHT - 1, DISPLAY_COLOR_WHITE);
    display.display();
  }
  for (int y = 0; y < DISPLAY_HEIGHT; y += 8) {
    display.drawLine(DISPLAY_WIDTH - 1, y, 0, DISPLAY_HEIGHT - 1 - y, DISPLAY_COLOR_WHITE);
    display.display();
  }
}

void printCenter(int y, const String& text) {
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  display.setCursor((DISPLAY_WIDTH - w) / 2, y);
  display.print(text);
}
