SDIR = src
IDIR = src
ODIR = obj
BDIR = bin

CC = gcc
CFLAGS = -Wextra -Wall

LIBS = 

_DEPS = argparser.h help.h globals.h dynamiclist.h fileparser.h lines.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o argparser.o help.o dynamiclist.o fileparser.o lines.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BDIR)/vdf: $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	rm -rf $(BDIR)/vdf
	rm -rf $(ODIR)/*
