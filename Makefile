#
# File:		Makefile
#
#
# Makefile for a sorting suite
#

#
# designed to compile code against a driver for unit testing
# OBJS are the core code to be tested, TEST_OBJS are the driver
#
OBJS =		bubblesort.o heapsort.o insertionsort.o mergesort.o quicksort.o
TEST_OBJS =	main.o

TARGET = test

CC =	gcc
#CC =	cc

CFLAGS =	-Ofast -Wall 
#CFLAGS =	-g -Wall -DDEBUG 

LDFLAGS =
LIBS =		-lm

# generic rules to make .c file
.c.o:
	$(CC) $(CFLAGS) -c $<

#
# targets:
#

all:	$(TARGET) 

$(TARGET):	$(TEST_OBJS) $(OBJS) 
	$(CC) $(TEST_OBJS) $(OBJS) $(LDFLAGS) $(LIBS) -o $@

clean:
	/bin/rm -f $(TARGET) $(OBJS) $(TEST_OBJS) 


