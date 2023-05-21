TARGET=extractor
LIBS=-lm
CC=gcc
CFLAGS=-g -Wall
OBJFILES = src/filesystem.o src/extractor.o

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -rf src/*.o $(TARGET).exe