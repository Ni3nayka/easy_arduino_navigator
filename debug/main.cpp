/*
 * Integration the Trackduino to Arduino IDE:
 * https://github.com/Ni3nayka/easy_arduino_navigator
 *
 * author: Egor Bakay <egor_bakay@inbox.ru>
 * write:  october 2022
 * modify: october 2022
 */

#include <iostream>
using namespace std;

#include "easy_arduino_navigator.h"

Navigator navigator(RIGHT_ARM_RULE);

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

void test() {
    cout << navigator.get_x() << " " << navigator.get_y() << " " << navigator.get_dir() << "\n";
}

void move(bool a, bool b) {
    cout << navigator.next_move(a,b) << "\n";
}

int main() {
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
