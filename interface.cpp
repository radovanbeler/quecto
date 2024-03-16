#include <string>
#include <termios.h>
#include <unistd.h>

#include "interface.h"
#include "key.h"

TerminalInterface::TerminalInterface() {
    this->set_raw_mode();
    this->clear_screen();
    this->reset_cursor();
}

TerminalInterface::~TerminalInterface() {
    this->restore_mode();
    this->reset_cursor();
}

void TerminalInterface::set_raw_mode() {
    struct termios current_state;

    tcgetattr(STDIN_FILENO, &current_state);
    this->initial_state = current_state;

    current_state.c_iflag &=
        ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    current_state.c_oflag &= ~OPOST;
    current_state.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    current_state.c_cflag &= ~(CSIZE | PARENB);
    current_state.c_cflag |= CS8;
    current_state.c_cc[VMIN] = 0;
    current_state.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &current_state);
}

void TerminalInterface::restore_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &this->initial_state);
}

Key TerminalInterface::get_key() {
    char key;
    read(STDIN_FILENO, &key, 1);

    KeyType type = key_type(key);

    switch (type) {
    case KeyType::NONE:
        return Key(KeyType::NONE);
        break;
    case KeyType::ESC:
        return handle_escape_sequence();
        break;
    }

    return Key(KeyType::OTHER, key);
}

Key TerminalInterface::handle_escape_sequence() {
    char sequence[3];

    for (int i = 0; i < 2; ++i) {
        if (read(STDIN_FILENO, &sequence[i], 1) != 1) {
            return Key(KeyType::ESC);
        }
    }

    if (sequence[0] == '[') {
        switch (sequence[1]) {
        case 'A':
            return Key(KeyType::ARROW_UP);
            break;
        case 'C':
            return Key(KeyType::ARROW_RIGHT);
            break;
        case 'B':
            return Key(KeyType::ARROW_DOWN);
            break;
        case 'D':
            return Key(KeyType::ARROW_LEFT);
            break;
        }
    }

    return Key(KeyType::ESC);
}

KeyType TerminalInterface::key_type(int key) {
    switch (key) {
    case 0x0:
        return KeyType::NONE;
        break;
    case 0x1b:
        return KeyType::ESC;
        break;
    }

    return KeyType::OTHER;
}

void TerminalInterface::clear_screen() {
    const std::string sequence = "\x1b[2J";

    write(STDOUT_FILENO, sequence.c_str(), sequence.size());
}

void TerminalInterface::reset_cursor() {
    const std::string sequence = "\x1b[H";

    write(STDOUT_FILENO, sequence.c_str(), sequence.size());
}

void TerminalInterface::move_cursor(unsigned int x, unsigned int y) {
    std::string sequence =
        "\x1b[" + std::to_string(x + 1) + ";" + std::to_string(y + 1) + "H";

    write(STDOUT_FILENO, sequence.c_str(), sequence.size());
}

void TerminalInterface::get_size(unsigned int &x, unsigned int &y) {
    x = 80;
    y = 25;
}
