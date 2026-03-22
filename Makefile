CC = gcc
CFLAGS = -Wall
TARGET = duck
PREFIX = /usr

all: $(TARGET)

$(TARGET): duck.c
	$(CC) $(CFLAGS) duck.c -o $(TARGET)

install:
	install -Dm755 $(TARGET) $(DESTDIR)$(PREFIX)/bin/$(TARGET)
	install -Dm644 LICENSE $(DESTDIR)$(PREFIX)/share/licenses/$(TARGET)/LICENSE

clean:
	rm -f $(TARGET)
