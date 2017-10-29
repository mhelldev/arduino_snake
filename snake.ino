                                                                 #include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4 // not used / nicht genutzt bei diesem Display
#define DRAW_DELAY 118
#define D_NUM 47
Adafruit_SSD1306 display(OLED_RESET);

const int MONITOR_WIDTH = 128;
const int MONITOR_HEIGHT = 32;
const int buttonPin = 2; 
int lastButtonState = 0; 
int currentPositionX = 0;
int currentPositionY = 0;
int currentDirection = 0;
short snakeX[200];
short snakeY[200];
int currentSnakeLength = 1;
int counter = 0;

int currentAppleX = 0;
int currentAppleY = 0;

void setup()   {        
  Serial.begin(9600);  
  // initialize with the I2C addr 0x3C / mit I2C-Adresse 0x3c initialisieren
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // random start seed / zufälligen Startwert für Random-Funtionen initialisieren
  randomSeed(analogRead(0));

  //drawIntro();
  currentPositionX = random(MONITOR_WIDTH);
  currentPositionY = random(MONITOR_HEIGHT);
  currentDirection = random(0,3);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  display.clearDisplay();

  generateApple();
}

void loop() {
  display.clearDisplay();
  counter++;
  if (counter > 100) {
    refreshDirection();
    refreshPosition();
    checkAppleCollision();
    counter = 0;
  }
}


void generateApple() {
  currentAppleX = random(MONITOR_WIDTH-10);
  currentAppleY = random(MONITOR_HEIGHT-5);
}

void drawApple() {
  display.fillCircle(currentAppleX, currentAppleY, 1, WHITE);
  display.display();
}

void checkAppleCollision() {
  if (currentPositionX > currentAppleX -2 &&
      currentPositionX < currentAppleX +2 &&
      currentPositionY > currentAppleY -2 &&
      currentPositionY < currentAppleY + 2) {
        currentSnakeLength++;
        snakeX[currentSnakeLength-1] = currentPositionX;
        snakeY[currentSnakeLength-1] = currentPositionY;
        generateApple();
      }
}

void refreshPosition() {
  
 drawApple();
  switch(currentDirection) {
    case 0:
      currentPositionY--;
      break;
    case 1:
      currentPositionX+=2;
      break;
    case 2:
      currentPositionY++;
      break;
    case 3:
      currentPositionX-=2;
      break;
  }
  if (currentPositionY < 0) {
    currentPositionY = MONITOR_HEIGHT;
  }
  if (currentPositionY > MONITOR_HEIGHT) {
    currentPositionY = 0;
  }
  if (currentPositionX < 0) {
    currentPositionX = MONITOR_WIDTH;
  }
  if (currentPositionX > MONITOR_WIDTH) {
    currentPositionX = 0;
  }

  for (int i=0; i < currentSnakeLength-1; i++) {
      snakeX[i] = snakeX[i+1];
      snakeY[i] = snakeY[i+1];
  }

  snakeX[currentSnakeLength-1] = currentPositionX;
  snakeY[currentSnakeLength-1] = currentPositionY;
  
  for (int i=0; i < currentSnakeLength; i++) {
    display.drawPixel(snakeX[i],snakeY[i], WHITE);
  }
  display.display();
  //delay(100);
  
}

void refreshDirection() {
  int buttonState = digitalRead(buttonPin);
  if (buttonState == 1 && lastButtonState==0) {
      currentDirection++;
      if (currentDirection > 3) {
        currentDirection = 0;
      }
  }
  lastButtonState = buttonState;
  
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


