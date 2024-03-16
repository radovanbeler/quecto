SRC = quecto.cpp interface.cpp key.cpp cursor.cpp editor.cpp
OBJ = $(SRC:.cpp=.o)
OUT = quecto
CC= g++
CFLAGS = -std=c++11 -ggdb -Wall -Wextra -Wpedantic

all: quecto

quecto: $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OUT) $(OBJ)

.PHONY: clean
