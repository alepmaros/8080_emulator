CC=gcc
CFLAGS=-I $(IDIR) -g -Wall

IDIR = include
ODIR = obj
SDIR = src

_DEPS =
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ =
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o main $(SDIR)/main.c $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
