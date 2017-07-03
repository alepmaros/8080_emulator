CC=gcc
CFLAGS=-I $(IDIR) -g -Wall

IDIR = include
ODIR = obj
SDIR = src

_DEPS = disassemble.h emulator.h utils.h instructions_arithmetic.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = disassemble.o emulator.o utils.o instructions_arithmetic.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o main $(SDIR)/main.c $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
