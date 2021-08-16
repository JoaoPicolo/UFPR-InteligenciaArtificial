CC     = g++
CFLAGS = -Wall -O3
LFLAGS = 

PROG = main 
OBJS = board.o

.PHONY: limpa faxina clean purge all

all: main

%.o: %.cpp %.hpp
	$(CC) -c $(CFLAGS) $<

$(PROG) : % :  $(OBJS) %.o
	$(CC) -o $@ $^ $(LFLAGS)

faxina purge:
	@rm -f *~ *.bak

limpa clean:   faxina
	@rm -f *.o core a.out
	@rm -f $(PROG)
