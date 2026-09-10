CC = gcc
CFLAGS = -Wall -Wextra -O3
LDFLAGS = -lSDL2 -lSDL2_mixer -lm

SRC = infinite-3d-floor.c
TARGET = infinite-3d-floor

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)
	strip $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)