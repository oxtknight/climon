CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = source.code/main.c
TARGET = climon
all:
    $(CC) $(CFLAGS) $(SRC) -lm -o $(TARGET)
install:
    $(CC) $(CFLAGS) $(SRC) -lm -o $(TARGET)
    sudo mv $(TARGET) /usr/local/bin/
    echo "Climon installed to Linux bin"
clean:
	rm -f $(TARGET)
