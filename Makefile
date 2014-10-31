## *******************************************************************
##   (C) Copyright 2014 Leiden Institute of Advanced Computer Science
##   Universiteit Leiden
##   All Rights Reserved
## *******************************************************************
## Open Dag 21 maart 2014 --- King of the Jungle
## *******************************************************************
## FILE INFORMATION:
##   File:     Makefile
##   Author:   Jonathan K. Vis
##   Revision: 0.01a
##   Date:     2014/03/19
## *******************************************************************
## DESCRIPTION:
##   Gebruik het commando `make' om het project te compileren. Of
##   wanneer headers zijn aangepast bebruik dan `make rebuild'.
##   Pas de variabele `EXECUTABLE' aan. Ook kunnen de compileervlaggen
##   worden aangepast bijvoorbeeld aan het gebruik van een debugger of
##   het uitzetten van optimalisatie.
## *******************************************************************

CC=g++
CFLAGS=-c -Wall -Wextra -O3
LDFLAGS=-Wall -Wextra -O3
HEADERS=location.h \
        move.h \
        move_list.h \
        movement.h \
        pieces.h \
        position.h \
        search.h \
        terrain.h \
        types.h \
        zobrist.h \
        balanced.h \
        attacking.h \
        defending.h
SOURCES=location.cc \
        move.cc \
        move_list.cc \
        movement.cc \
        pieces.cc \
        position.cc \
        terrain.cc \
        evaluation.cc \
        main.cc \
        search.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=jungle
SCRIPTS=contest.sh

.PHONY: all clean rebuild tarball

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

rebuild: clean all

tarball:
	tar -cvzf jungle.tgz $(HEADERS) $(SOURCES) Makefile contest.sh

