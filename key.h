#ifndef KEY_H
#define KEY_H

enum class KeyType {
    NONE,
    ARROW_UP,
    ARROW_RIGHT,
    ARROW_DOWN,
    ARROW_LEFT,
    BACKSPACE,
    ESC,
    OTHER
};

class Key {
public:
    Key(KeyType type);
    Key(KeyType type, int key);
    bool is(KeyType type);
    bool is(int key);
    int get_key();
    KeyType get_type();

private:
    const KeyType type;
    const int key;
    KeyType to_key_type(int key);
};

#endif
