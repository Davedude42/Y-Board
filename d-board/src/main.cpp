#include "accel_led.h"
#include "accelerometer.h"
#include "accelerometer.cpp"
#include "yboard.h"
#include <Arduino.h>


struct point2 {
  float x;
  float y;
};
struct wall {
  point2 start;
  point2 end;
};

/////////////////////////////////////////////////////////////////////////////////////

// Need to setup:
// 1. Serial Communication
// 2. Y-Board (includes accelerometer)
// 3. Off-Board OLED Display
// 4. 3D Axes (will be drawn on display)
void setup() {
  Serial.begin(115200); // Serial
  Serial.println("Starting up...");
  Yboard.setup();  // Y-Board
  setup_display(); // Display
  setup_axes();    // Axes
  Serial.println("All set, ready to go!");
}

float MAGIC_CONST_1 = 0.01;
float FOV = PI / 1.6;

point2 player = {.x = 0.0, .y = 0.0};
float playerFacing = 0;

wall walls[] = {
  {.start = {.x = -1.0, .y = 1.0}, .end = {.x = 1.0, .y = 1.0}}
};

float mag(point2 point) {
  return sqrt(point.x * point.x + point.y * point.y);
}

point2 add(point2 point_1, point2 point_2) {
  return {.x = point_1.x + point_2.x, .y = point_1.y + point_2.y};
}
point2 sub(point2 point_1, point2 point_2) {
  return {.x = point_1.x - point_2.x, .y = point_1.y - point_2.y};
}

point2 scale(point2 point, float s) {
  return {.x = point.x * s, .y = point.y * s};
}

point2 normalize(point2 point) {
  return scale(point, 1/mag(point));
}

float shootRay(point2 start, float angle) {
  point2 rayVector = {.x = cos(angle), .y = sin(angle)};

  for (int i = 0; i < sizeof(walls); i++) {
    float alphabeta = 1.0;
    point2 intersection = add(start, scale(rayVector, mag(sub()) * alphabeta))
  }
}

void drawWalls() {
  for (int sx = 0; sx < SCREEN_WIDTH; sx++) {
    float rayAngle = playerFacing + (sx - SCREEN_WIDTH/2)/SCREEN_WIDTH * FOV;
    int wallHeight = (int)(shootRay(player, rayAngle) * MAGIC_CONST_1 * SCREEN_HEIGHT);

    display.drawLine(sx, SCREEN_HEIGHT/2 - wallHeight/2, sx, SCREEN_HEIGHT/2 + wallHeight/2, ON);
  }
}

void loop() {
  display.clearDisplay();

  float knob = float(Yboard.get_knob() - 50) / 50;

  drawWalls();

  // This is another function I wrote to light up the board's LEDs
  // based on how the board is rotated in 3D space.
  // Uncomment this line to give it a try!
  //light_LEDs();

  /*********************************************************************/
  /************************* EXTRA TINKERING ***************************/
  /*********************************************************************/
  // Below are some functions for you to mess around with. Try changing the
  // numbers in each function call to change how each shape is drawn or what
  // letters are typed on the screen.

  // Draw a line
  // display.drawLine(2, 2, 37, 15, ON);

  // Draw some shapes
  // display.drawCircle(111, 52, 8, ON);
  // display.fillTriangle(96, 60, 89, 27, 73, 26, ON);
  // display.drawRect(104, 12, 16, 14, ON);
  // display.drawRoundRect(12, 34, 30, 17, 5, ON);

  // Write on the screen
  // display.setTextSize(3);
  // display.setCursor(0, 0);
  // display.print("Word");

  display.display();
}