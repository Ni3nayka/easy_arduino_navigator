/*
 * Integration the Trackduino to Arduino IDE:
 * https://github.com/Ni3nayka/easy_arduino_navigator
 *
 * author: Egor Bakay <egor_bakay@inbox.ru>
 * write:  october 2022
 * modify: october 2022
 */

#include <easy_arduino_navigator.h>

Navigator navigator(RIGHT_ARM_RULE); // LEFT_ARM_RULE

/* MANUAL:
 *
 * direction:
 *   N
 *   |
 * W-0-E
 *   |
 *   S
 *  NAVIGATOR_DIR_N
 *  NAVIGATOR_DIR_W
 *  NAVIGATOR_DIR_S
 *  NAVIGATOR_DIR_E
 *
 * coordinate system:
 * ^ y
 * |
 * |
 * +-----> x
 */

void test() {
  Serial.print(navigator.get_x());
  Serial.print(" ");
  Serial.print(navigator.get_y());
  Serial.print(" ");
  Serial.println(navigator.get_dir());
}

void move(bool forward_wall, bool side_wall) {
  //Serial.println(navigator.next_move(forward_wall,side_wall));
  
  // real move
  if (navigator.this_is_finish()) {
    Serial.println("end");
    return;
  }
  int t = navigator.next_move(forward_wall,side_wall);
  if (t==NAVIGATOR_END) {
    Serial.println("end");
    return;
  }
  if (t==NAVIGATOR_MOVE_FORWARD) {
    Serial.println("move forvard");
  }
  if (t==NAVIGATOR_MOVE_LEFT) {
    Serial.println("turn left");
  }
  if (t==NAVIGATOR_MOVE_RIGHT) {
    Serial.println("move right");
  }
  if (t==NAVIGATOR_MOVE_RIGHT_AND_FORWARD) {
    Serial.println("turn right");
    Serial.println("move forward");
  }
  if (t==NAVIGATOR_MOVE_LEFT_AND_FORWARD) {
    Serial.println("turn left");
    Serial.println("move forward");
  }
}

void setup() {
  Serial.begin(9600);
  // (X_coordinate, Y_coordinate, direction)
  navigator.set_start(0,0,NAVIGATOR_DIR_E);
  navigator.set_finish(4,4,NAVIGATOR_DIR_S);
  test();
  move(0,1);
  move(0,1);
  move(0,1);
  move(1,1);
  move(1,1);
  move(0,1);
  move(0,0);
  move(0,1);

  move(0,0);
  move(1,1);
  move(1,1);
  move(0,1);
  move(0,0);
  move(0,1);
  move(1,0);
  move(0,1);

  move(1,1);
  move(1,1);
  move(1,1);
  move(1,1);
  move(1,1);

  test();

}

void loop() {
  
}
