#ifndef CURSOR_H
#define CURSOR_H

class Cursor {
public:
    Cursor(unsigned int x = 0, unsigned int y = 0);
    void up();
    void right();
    void down();
    void left();
    unsigned int get_x();
    void set_x(unsigned int x);
    unsigned int get_y();
    void set_y(unsigned int y);

private:
    unsigned int x;
    unsigned int y;
};

#endif
