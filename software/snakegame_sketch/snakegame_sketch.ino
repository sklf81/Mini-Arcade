#include <LedControl.h>
#include "SnakeGame.h"
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"

#define RST_PIN -1
#define I2C_ADDRESS 0x3C

SSD1306AsciiAvrI2c oled;

#define REFRESH_DELAY 200

#define XIN_PORT A1 //Orientation changed; originally (in schematics) A0
#define YIN_PORT A0 //Orientation changed; originally (in schematics) A1
#define JOYSTICK_SW 5

#define LEFT_THRESHOLD (1024/4)
#define RIGHT_THRESHOLD 3*(1024/4)
#define DOWN_THRESHOLD 3*(1024/4)
#define UP_THRESHOLD (1024/4)

#define DIN_PORT 11
#define CS_PORT 12
#define CLK_PORT 13
#define MAXMATRIX_USED 1

LedControl maxMatrix = LedControl(DIN_PORT, CLK_PORT, CS_PORT, MAXMATRIX_USED);

SnakeGame snakeg;
unsigned int score = 0;
byte lives = 3;
Vector2D movingDirection;

unsigned long int lastRefresh = millis();

void printStats(byte lives, unsigned int score){
  //OLED - Statistics
  oled.clear();
  oled.set2X();
  oled.println("Snake!");
  oled.set1X();
  oled.print("length :");
  oled.print(snakeg.snake.tail.length);
  oled.print(" score :");
  oled.println(score);
  oled.print("lives  :  ");
  for(byte i = 0; i < lives; i++){
    oled.print("%");
  }
}

void printGameOver(unsigned int score){
  oled.clear();
  oled.set2X();
  oled.println("GAME OVER!");
  oled.print("SCORE: ");
  oled.println(score);
}

void spawnFood(){
  //This will be implemented here because of an error with the random-generator
  
  Vector2D pos(random(0, 7), random(0, 7));

	for (byte i = 0; i < snakeg.snake.tail.length; i++)
	{
		if (pos.equals(snakeg.snake.tail.partsPosition[i])) {
			pos.set(random(0, 7), random(0, 7));
			i = 0;
		}
	}
  snakeg.foodposition.set(pos);
}

void resetSnakeGame(){
  //Externally re-implemented because of the extra "spawnFoodFunction"
  snakeg.snake.reset();
  spawnFood();
  snakeg.setObjectPositions();
}

void reset(){
  resetSnakeGame();
  movingDirection.set(0,0);

  maxMatrix.shutdown(0, false);
  maxMatrix.setIntensity(0, 8);
  maxMatrix.clearDisplay(0);

  lives = 3;
  score = 0;
  lastRefresh = millis();
}

void setup() {
  
  DDRD = B11111111;
  DDRB |= B00000111;
  DDRC |= B00000001;
  pinMode(XIN_PORT, INPUT);
  pinMode(YIN_PORT, INPUT);
  pinMode(JOYSTICK_SW, INPUT);
  Serial.begin(9600);

  #if RST_PIN >= 0
  oled.begin(&Adafruit128x32, I2C_ADDRESS, RST_PIN);
  #else // RST_PIN >= 0
  oled.begin(&Adafruit128x32, I2C_ADDRESS);
  #endif // RST_PIN >= 0
  // Call oled.setI2cClock(frequency) to change from the default frequency.
  
  oled.setFont(HeartlySystem5x7);
  reset();
  delay(1000);
  playIntroOnMatrix(maxMatrix);
  printStats(lives, score);
}
bool state = 0;

void loop() {
  getMovingDirection(&movingDirection);
  
  if(lives <= 0){
    printGameOver(score);

    
    while(digitalRead(JOYSTICK_SW)){
      state = !state;
      playDeadScreenOnMatrix(maxMatrix, state);
    }
    
    movingDirection.x = 0;
    movingDirection.y = 0;
    lives = 3;
    score = 0;
    printStats(lives, score);
  }
  if(millis() - lastRefresh >= REFRESH_DELAY){
    maxMatrix.clearDisplay(0);
    lastRefresh = millis();
    if (snakeg.snake.eatsFood()) {
      score += 1;
      snakeg.snake.tail.addPart();
      spawnFood();
      printStats(lives, score);
    }
    if (snakeg.snake.hitsBorder() || snakeg.snake.hitsItself()) {
      resetSnakeGame();
      lives--;
      movingDirection.x = 0;
      movingDirection.y = 0;
      printStats(lives, score);
    }
    
    snakeg.setObjectPositions();
    snakeg.snake.move(movingDirection.x, movingDirection.y);
    displayPointsOnMatrix(maxMatrix, snakeg.objectPositions);
    if(movingDirection.equals(Vector2D(0,0))){
      maxMatrix.setLed(0, snakeg.snake.headPosition->x, snakeg.snake.headPosition->y, state);
      state = !state;
    }
  }
  
  
}

void getMovingDirection(Vector2D* mov){
  unsigned short x_value = analogRead(XIN_PORT);
  unsigned short y_value = analogRead(YIN_PORT);
  Serial.print("x:");
  Serial.println(x_value);
  Serial.print("y:");
  Serial.println(y_value);
  
  if(x_value <= LEFT_THRESHOLD){
    /*
     * Orientation changed...
     * originally:
     * mov->x = -1;
     * mov->y = 0;
     */
    mov->x = -1;
    mov->y = 0;
  }
  else if(x_value >= RIGHT_THRESHOLD){
    /*
     * Orientation changed...
     * originally:
     * mov->x = 1;
     * mov->y = 0;
     */
    mov->x = 1;
    mov->y = 0;
  }
    
  if(y_value >= DOWN_THRESHOLD){
    /*
     * Orientation changed...
     * originally:
     * mov->y = -1;
     * mov->x = 0;
     */
    mov->y = 1;
    mov->x = 0;
  }
  else if(y_value <= UP_THRESHOLD){
    /*
     * Orientation changed...
     * originally:
     * mov->y = 1;
     * mov->x = 0;
     */
    mov->y = -1;
    mov->x = 0;
  }
}

void displayPointsOnMatrix(LedControl displayMatrix, Vector2D points[]){
  for(byte i = 0; !points[i].equals(Vector2D('N','D')); i++){
    displayMatrix.setLed(0, points[i].x, points[i].y, 1);
  }
}

void playIntroOnMatrix(LedControl displayMatrix){
  for(byte k = 1; k <= 2; k++){
    for(byte i = 0; i < 8; i++){
      for(byte j = 0; j < 8; j++){
          displayMatrix.setLed(0, i, j, k % 2);
          delay(12);
      }
    }
  }
}

void playDeadScreenOnMatrix(LedControl displayMatrix, bool state){
    for(byte i = 0; i < 8; i++){
      for(byte j = 0; j < 8; j++){
          displayMatrix.setLed(0, i, j, state);
      }
      //displayMatrix.setLed(0, i, i, !state);
      //displayMatrix.setLed(0, 7-i, 7-i, !state);
      delay(100);
    }
}
