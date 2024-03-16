#include "cursor.h"

Cursor::Cursor(unsigned int x, unsigned int y) : x{x}, y{y} {
}

void Cursor::up() {
    if (x == 0) {
        return;
    }

    --x;
}

void Cursor::right() {
    ++y;
}

void Cursor::down() {
    ++x;
}

void Cursor::left() {
    if (y == 0) {
        return;
    }

    --y;
}

unsigned int Cursor::get_x() {
    return x;
}

void Cursor::set_x(unsigned int x) {
    this->x = x;
}

unsigned int Cursor::get_y() {
    return y;
}

void Cursor::set_y(unsigned int y) {
    this->y = y;
}
