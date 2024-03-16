#include "editor.h"

Editor::Editor(Interface &interface, Cursor &cursor)
    : interface{interface}, quit_editor{false}, cursor{cursor} {
}

void Editor::send_key(Key key) {
    if (key.is(KeyType::ESC)) {
        this->quit_editor = true;
    }

    switch (key.get_type()) {
    case KeyType::ARROW_UP:
        cursor.up();
        break;
    case KeyType::ARROW_RIGHT:
        cursor.right();
        break;
    case KeyType::ARROW_DOWN:
        cursor.down();
        break;
    case KeyType::ARROW_LEFT:
        cursor.left();
        break;
    default:
        break;
    };

    interface.move_cursor(cursor.get_x(), cursor.get_y());
}

void Editor::refresh() {
    interface.clear_screen();

    unsigned int x, y;
    interface.get_size(x, y);

    for (unsigned int i = 0; i < y; ++i) {
        interface.print(i, 0, '~');
    }

    interface.move_cursor(cursor.get_x(), cursor.get_y());
}

bool Editor::quit() {
    return this->quit_editor;
}
