# Reference: https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html

CC = g++
# CFLAGS  = -g -Wall -std=c++11
CFLAGS  = -g -Wall

all: product

# To create the executable file main we need the object files
# main.o:
#
product:  main.o
	$(CC) $(CFLAGS) -o product main.o

# To create the object file main.o, we need the source
# files main.cxx:
#
main.o:  main.cxx
	$(CC) $(CFLAGS) -c main.cxx

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) *.o *~