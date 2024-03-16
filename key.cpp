#include "key.h"

Key::Key(KeyType type) : type{type}, key{0} {
}

Key::Key(KeyType type, int key) : type{type}, key{key} {
}

bool Key::is(KeyType type) {
    return this->type == type;
}

bool Key::is(int key) {
    return this->key == key;
}

int Key::get_key() {
    return this->key;
}

KeyType Key::get_type() {
    return type;
}
