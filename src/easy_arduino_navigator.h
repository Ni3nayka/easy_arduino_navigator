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
 *   1
 *   |
 * 2-0-4
 *   |
 *   3
 *
 * coordinate system:
 * ^ y
 * |
 * |
 * +-----> x
 */

#pragma once

#define RIGHT_ARM_RULE 1
#define LEFT_ARM_RULE 0

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
        void run_forward();

        bool this_is_finish();

    private:
        bool _hand;
        int _real_dir, _end_dir;
        int _real_X, _real_Y;
        int _end_X, _end_Y;
};

Navigator::Navigator(bool hand) {
    _hand = hand;
}

void Navigator::set_start(int X, int Y, int dir) {
    _real_X = X;
    _real_Y = Y;
    _real_dir = dir;
}

void Navigator::set_finish(int X, int Y, int dir) {
    _end_X = X;
    _end_Y = Y;
    _end_dir = dir;
}

int Navigator::get_x() {
    return _real_X;
}
int Navigator::get_y(){
    return _real_Y;
}

int Navigator::get_dir(){
    return _real_dir;
}

void Navigator::turn_right() {
    _real_dir--;
    if (_real_dir<1)
        _real_dir += 4;
}

void Navigator::turn_left() {
    _real_dir++;
    if (_real_dir>4)
        _real_dir -= 4;
}

void Navigator::run_forward() {
    if      (_real_dir==1) _real_Y++;
    else if (_real_dir==2) _real_X--;
    else if (_real_dir==3) _real_Y--;
    else if (_real_dir==4) _real_X++;
}

bool Navigator::this_is_finish() {
    return _real_dir==_end_dir && _real_X==_end_X && _real_Y && _end_Y;
}
