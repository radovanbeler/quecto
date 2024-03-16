#include "cursor.h"
#include "interface.h"
#include "key.h"

#ifndef EDITOR_H
#define EDITOR_H

class Editor {
public:
    Editor(Interface &interface, Cursor &cursor);
    void send_key(Key key);
    void refresh();
    bool quit();

private:
    Interface &interface;
    bool quit_editor;
    Cursor &cursor;
};

#endif
