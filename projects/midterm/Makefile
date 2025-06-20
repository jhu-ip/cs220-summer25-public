# <your name> and <your JHED>
# __Add your name and JHED above__
# Midterm Project - Solution Makefile

CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra

## TODO: Write your own Makefile commands to link and compile your project as well as the cleanup


## Below are commands to link and compile the checkerboard program
# Links together files needed to create the checkerboard executable
checkerboard : checkerboard.o ppm_io.o
	$(CC) -o $@ checkerboard.o ppm_io.o

# Compile the ppm i/o source code
ppm_io.o: ppm_io.c ppm_io.h
	$(CC) $(CFLAGS) -c ppm_io.c

# Removes all object files and the executable named project, so we can start fresh
clean:
	rm -f *.o checkerboard
