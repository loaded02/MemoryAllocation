CC = g++
CFLAGS = -Wall
PROG = testAlloc

SRCS = main.cpp

LIBS = -pthread

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
