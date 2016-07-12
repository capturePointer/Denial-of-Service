CC = gcc
CFLAGS = -g -Wall

SRCDIR = ./src/
BUILDDIR = ./build/

all: build_dir denial.bin tmpclean

denial.bin: helper.o main.o
	$(CC) $(CFLAGS) dos_helper.o main.o -o $(BUILDDIR)denial.bin

main.o: $(SRCDIR)main.c
	$(CC) $(CFLAGS) -c $(SRCDIR)main.c

helper.o: $(SRCDIR)dos_helper.c $(SRCDIR)dos_helper.h
	$(CC) $(CFLAGS) -c $(SRCDIR)dos_helper.c

build_dir:
	mkdir -p $(BUILDDIR)

tmpclean:
	rm *.o

clean:
	rm $(BUILDDIR)*.bin
