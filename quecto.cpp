#include <iostream>

#include "editor.h"
#include "interface.h"
#include "key.h"

int main() {
    TerminalInterface interface;
    Cursor cursor;
    Editor editor(interface, cursor);

    while (true) {
        Key key = interface.get_key();
        if (!key.is(KeyType::NONE)) {
            editor.send_key(key);
        }

        if (editor.quit()) {
            break;
        }
    }

    return 0;
}
