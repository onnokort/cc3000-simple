all: libcc3k.a

FLAGS=-Wall  -Wextra -Wimplicit-function-declaration -Wredundant-decls \
      -Wundef -Wshadow -I../include/cc3000/
#FLAGS+=-DCC3000_TINY_DRIVER

CFLAGS+=$(FLAGS)

OBJECTS=cc3000_common.o evnt_handler.o hardware.o hci.o \
	netapp.o nvmem.o security.o socket.o spi.o wlan.o

libcc3k.a: $(OBJECTS)
	ar rcs $@ $^

clean:
	rm -f libcc3k.a *.o *~
