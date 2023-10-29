/*
 * library for solving problems with a maze according to
 * the rule of the left/right hand:
 * https://github.com/Ni3nayka/easy_arduino_navigator
 *
 * author: Egor Bakay <egor_bakay@inbox.ru>
 * write:  october 2022
 * modify: october 2022
 */

/* MANUAL:
 *
 * direction:
 *   1       N
 *   |       |
 * 2-0-4   W-0-E
 *   |       |
 *   3       S
 *
 * coordinate system:
 * ^ y
 * |
 * |
 * +-----> x
 */

#pragma once

#ifndef NAVIGATOR_QUANTITY_POINT 
#define NAVIGATOR_QUANTITY_POINT 0
#endif

#define NAVIGATOR_RIGHT_ARM_RULE 1
#define NAVIGATOR_LEFT_ARM_RULE  0

#define NAVIGATOR_END          0
#define NAVIGATOR_MOVE_FORWARD 1
#define NAVIGATOR_MOVE_LEFT    2
#define NAVIGATOR_MOVE_RIGHT   3
#define NAVIGATOR_MOVE_RIGHT_AND_FORWARD 31 // rirht, NEXT forward (after right)
#define NAVIGATOR_MOVE_LEFT_AND_FORWARD  21
#define NAVIGATOR_ERROR_LONG_ROUTE 100

#define NAVIGATOR_DIR_N 1
#define NAVIGATOR_DIR_W 2
#define NAVIGATOR_DIR_S 3
#define NAVIGATOR_DIR_E 4

class Navigator {
  public:
    Navigator(bool hand);
    void set_start(int X, int Y, int dir);
    void set_finish(int X, int Y, int dir);

    int get_x();
    int get_y();
    int get_dir();

    void turn_right();
    void turn_left();
    void run_forward(bool forward);

    bool this_is_finish();
    int next_move(bool forward_wall, bool side_wall);

    bool this_is_start();
    int next_move_backward();

  private:
    bool hand;
    int start_X, start_Y;
    int real_dir, end_dir;
    int real_X, real_Y;
    int end_X, end_Y;
    int road[NAVIGATOR_QUANTITY_POINT][2];
    int road_i;
    bool error_long_route;
};

Navigator::Navigator(bool hand) {
  Navigator::hand = hand;
  Navigator::error_long_route = false;
  Navigator::road_i = 0;
  Navigator::error_long_route = false;
//  for (int i = 0; i<NAVIGATOR_QUANTITY_POINT; i++) {
//    Navigator::road[i][0] = 0;
//    Navigator::road[i][1] = 0;
//  }
}

void Navigator::set_start(int X, int Y, int dir) {
  Navigator::real_X = X;
  Navigator::real_Y = Y;
  Navigator::start_X = X;
  Navigator::start_Y = Y;
  Navigator::real_dir = dir;
  if (NAVIGATOR_QUANTITY_POINT>0) {
    road[0][0] = X;
    road[0][1] = Y;
    Navigator::road_i = 1;
  }
}

void Navigator::set_finish(int X, int Y, int dir) {
  Navigator::end_X = X;
  Navigator::end_Y = Y;
  Navigator::end_dir = dir;
}

int Navigator::get_x() {
  return Navigator::real_X;
}
int Navigator::get_y() {
  return Navigator::real_Y;
}

int Navigator::get_dir() {
  return Navigator::real_dir;
}

void Navigator::turn_right() {
  Navigator::real_dir--;
  if (Navigator::real_dir < 1)
    Navigator::real_dir += 4;
}

void Navigator::turn_left() {
  Navigator::real_dir++;
  if (Navigator::real_dir > 4)
    Navigator::real_dir -= 4;
}

void Navigator::run_forward(bool forward=true) {
  // движение
  if      (Navigator::real_dir == 1) Navigator::real_Y++;
  else if (Navigator::real_dir == 2) Navigator::real_X--;
  else if (Navigator::real_dir == 3) Navigator::real_Y--;
  else if (Navigator::real_dir == 4) Navigator::real_X++;
  // запоминание кратчайшего пути назад
  if (NAVIGATOR_QUANTITY_POINT>0 && forward) { 
    if (NAVIGATOR_QUANTITY_POINT<=Navigator::road_i) {
      Navigator::error_long_route = true;
      return;
    }
    bool flag = true;
    for (int i = Navigator::road_i-1; i>=0; i--) {
      if (road[i][0]==real_X && road[i][1]==real_Y) {
        Navigator::road_i = i+1;
        flag = false;
        break;
      }
    }
    if (flag) {
      road[Navigator::road_i][0] = Navigator::real_X;
      road[Navigator::road_i][1] = Navigator::real_Y;
      Navigator::road_i++;
    }
  }
}

bool Navigator::this_is_finish() {
  return Navigator::real_dir == Navigator::end_dir && Navigator::real_X == Navigator::end_X && Navigator::real_Y == Navigator::end_Y;
}

bool Navigator::this_is_start() {
  return Navigator::real_X == Navigator::start_X && Navigator::real_Y == Navigator::start_Y;
}

int Navigator::next_move(bool forward_wall, bool side_wall) { // 1 - wall, 0 - empty
  if (Navigator::error_long_route) 
    return NAVIGATOR_ERROR_LONG_ROUTE;
  // finish
  if (Navigator::this_is_finish())
    return NAVIGATOR_END;
  //turn on finish
  if (Navigator::real_X == Navigator::end_X && Navigator::real_Y == Navigator::end_Y) {
    if (Navigator::real_dir - 1 == Navigator::end_dir || Navigator::real_dir == 1 && Navigator::end_dir == 4) {
      Navigator::turn_right();
      return NAVIGATOR_MOVE_RIGHT;
    }
    Navigator::turn_left();
    return NAVIGATOR_MOVE_LEFT;
  }
  // move in finish (the rule of the left/right hand)
  if (Navigator::hand == NAVIGATOR_RIGHT_ARM_RULE) {
    if (side_wall) {
      if (forward_wall) {
        Navigator::turn_left();
        return NAVIGATOR_MOVE_LEFT;
      }
      Navigator::run_forward();
      return NAVIGATOR_MOVE_FORWARD;
    }
    Navigator::turn_right();
    Navigator::run_forward();
    return NAVIGATOR_MOVE_RIGHT_AND_FORWARD;
  }
  else {
    if (side_wall) {
      if (forward_wall) {
        Navigator::turn_right();
        return NAVIGATOR_MOVE_RIGHT;
      }
      Navigator::run_forward();
      return NAVIGATOR_MOVE_FORWARD;
    }
    Navigator::turn_left();
    Navigator::run_forward();
    return NAVIGATOR_MOVE_LEFT_AND_FORWARD;
  }
}

int Navigator::next_move_backward() {
//  for (int i=0; i<NAVIGATOR_QUANTITY_POINT; i++) {
//    Serial.print(road[i][0]);
//    Serial.print("-");
//    Serial.print(road[i][1]);
//    Serial.print(" ");
//  }
//  Serial.println();
  if (NAVIGATOR_QUANTITY_POINT==0 or Navigator::error_long_route) 
    return NAVIGATOR_ERROR_LONG_ROUTE;
  if (Navigator::this_is_start()) 
    return NAVIGATOR_END;
  int x = Navigator::real_X;
  int y = Navigator::real_Y;
  int d = Navigator::real_dir;
  Navigator::run_forward(0);
  if (road[Navigator::road_i-2][0]==real_X && road[Navigator::road_i-2][1]==real_Y) {
    Navigator::road_i--;
    return NAVIGATOR_MOVE_FORWARD;
  }
  else {
    Navigator::real_X = x;
    Navigator::real_Y = y;
    Navigator::turn_right();
    Navigator::run_forward(0);
    if (road[Navigator::road_i-2][0]==real_X && road[Navigator::road_i-2][1]==real_Y) {
      Navigator::road_i--;
      return NAVIGATOR_MOVE_RIGHT_AND_FORWARD;
    }
    else {
      Navigator::real_X = x;
      Navigator::real_Y = y;
      Navigator::real_dir = d;
      Navigator::turn_left();
      return NAVIGATOR_MOVE_LEFT;
    }
  }
}
