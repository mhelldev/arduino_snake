#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4 // not used / nicht genutzt bei diesem Display
Adafruit_SSD1306 display(OLED_RESET);

const int buttonPin = 2; 
int buttonState = 0; 
int currentPositionX = 0;
int currentPositionY = 0;
int currentDirection = 0;

void setup()   {        
          
  Serial.begin(9600);  
  // initialize with the I2C addr 0x3C / mit I2C-Adresse 0x3c initialisieren
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  // random start seed / zufälligen Startwert für Random-Funtionen initialisieren
  randomSeed(analogRead(0));

  //drawIntro();
  currentPositionX = random(64);
  currentPositionY = random(32);
  currentDirection = random(0,3);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

#define DRAW_DELAY 118
#define D_NUM 47

void loop() {
  refreshPosition();
}

void refreshPosition() {

  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  
  display.clearDisplay();
  switch(currentDirection) {
    case 0:
      currentPositionY--;
      break;
    case 1:
      currentPositionX++;
      break;
    case 2:
      currentPositionY++;
      break;
    case 3:
      currentPositionX--;
      break;
  }
  if (currentPositionY < 0) {
    currentPositionY = 32;
  }
  if (currentPositionY > 32) {
    currentPositionY = 0;
  }
  if (currentPositionX < 0) {
    currentPositionX = 64;
  }
  if (currentPositionX > 64) {
    currentPositionX = 0;
  }
  display.drawPixel(currentPositionX,currentPositionY, WHITE);
  display.display();
  delay(100);
}

void drawIntro() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(36,6);
  display.println("SNAKE");
  display.setTextSize(1);
  display.setCursor(41,22);
  display.println("The Game");
  display.display();
  delay(2000);
  display.clearDisplay();
  display.invertDisplay(true);
  delay(2000); 
  display.invertDisplay(false);
  delay(1000); 
}


