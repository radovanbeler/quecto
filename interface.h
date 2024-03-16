#ifndef INTERFACE_H
#define INTERFACE_H

#include <termios.h>

#include "key.h"

class Interface {
public:
    virtual void move_cursor(unsigned int x, unsigned int y) = 0;
    virtual void get_size(unsigned int &x, unsigned int &y) = 0;
};

class TerminalInterface : public Interface {
public:
    TerminalInterface();
    ~TerminalInterface();
    Key get_key();
    void clear_screen();
    void reset_cursor();
    void move_cursor(unsigned int x, unsigned int y) override;
    void get_size(unsigned int &x, unsigned int &y) override;

private:
    struct termios initial_state;
    void set_raw_mode();
    void restore_mode();
    KeyType key_type(int key);
    Key handle_escape_sequence();
};

#endif
