CC=gcc
CFLAGS=-I $(IDIR) -g -Wall

IDIR = include
ODIR = obj
SDIR = src

_DEPS = disassemble.h emulator.h utils.h instructions_arithmetic.h \
	instructions_branch.h instructions_logical.h instructions_data_transfer.h \
	instructions_stack_io_machine.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = disassemble.o emulator.o utils.o instructions_arithmetic.o \
	instructions_branch.o instructions_logical.o instructions_data_transfer.o \
	instructions_stack_io_machine.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o main $(SDIR)/main.c $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
