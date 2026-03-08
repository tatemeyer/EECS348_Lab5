CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = matrix
SRC = Matrix.C

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) a.exe $(TARGET).exe
