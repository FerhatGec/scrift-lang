# MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
#

# For Castle
GCFLAGS=-std=c++11 -O2 -g -Wall $(shell pkg-config --cflags ncursesw)
GLDFLAGS=$(shell pkg-config --libs ncursesw)

# Apps
SRCAPPSDIREC = ./Apps/

# Libraries
SRCLIBDIREC = ./Library/

# Scrift's Syntax
SRCSYNTAXDIREC = ./src/Syntax/

# Fetcheya
SRCFETCHEYADIREC = ./src/Fetcheya/

# Edifor
SRCEDIFORDIREC = ./src/Edifor/

# Games
GAMESDIREC = ./Games/

# Source
SRCDIREC = ./src/

# Prefix
PREFIX = /bin/

INCLUDELIB = ./Library/
INCLUDEDIR = ./include/

# Include flags etc.
CFLAGS = -Wall -I$(INCLUDELIB) -I$(INCLUDEDIR)

GCC = cc
COMPILER = c++ -std=c++17
COMP = g++ -c

# Clean all
CLEANALL = scrift /Games/Castle/castle

# Clean object files
CLEAN = *.o

# Scrift's Syntax objects
HEADERFILE = CommandFunc.o GetNameFunction.o FileFunction.o RunFunction.o \
Log.o History.o Branch.o Template.o Settings.o HelpFunction.o ASCIIFunction.o \
Install.o Setup.o Tools.o

# Platform
ifeq ($(OS),Windows_NT)
	echo Windows_NT is not supported!
	#CLEAN := del $(CLEAN)
	#CLEANALL := del $(CLEANALL)
else
	CLEAN := rm -f $(CLEAN)
	CLEANALL := rm -f $(CLEANALL)
endif

# Build
all: conio headersfile edifor main datec clean

# Build & Install
install: headersfile mainc ediforc date clean

# Remove & Clean all
removeall: uninstall cleanall

# Build & Run
runall: all run

# For me & developers
gra: runall git

# Git
git:
	git add .
	git commit -a
	git push origin master

push:
	git push origin master

# Only clean all
nall: cleanall

# Scrift's Core.
headersfile: $(HEADERFILE)


conio: $(SRCLIBDIREC)FConio.c
	$(GCC) -c -Wno-unused-function -Wno-unused-value $(SRCLIBDIREC)FConio.c -o fconio.o

# Syntax
%.o: $(SRCSYNTAXDIREC)%.cpp
	$(COMPILER) -Wno-unused-function -Wno-unused-value $(CFLAGS) -c $< -o $@

# Main Build
main: $(SRCDIREC)Scrift.cpp
	$(COMPILER) $(CFLAGS) -Wno-unused-function -Wno-unused-value $< $(HEADERFILE) $(FETCHEYAFILE) -o scrift
	echo Scrift building successfully!

# Main Build & Install
mainc: $(SRCDIREC)Scrift.cpp
	$(COMPILER) $(CFLAGS) -Wno-unused-function -Wno-unused-value $< $(HEADERFILE) $(FETCHEYAFILE) -o /bin/scrift
	echo Scrift building successfully in Bin Directory!

# Edifor Build
edifor:
	$(GCC) $(CFLAGS) $(SRCEDIFORDIREC)Edifor.c -o edifor
	echo Edifor building successfully!

# Edifor Build & Install
ediforc:
	$(GCC) $(CFLAGS) $(SRCEDIFORDIREC)Edifor.c -o /bin/edifor
	echo Edifor building successfully in Bin Directory!

# Castle
castle: $(GAMESDIREC)/Castle/Castle.hpp
	$(COMPILER) $(GCFLAGS) $(GAMESDIREC)/Castle/Castle.cpp -o $(PREFIX)castle $(GLDFLAGS)
	echo Castle building successfully in Bin Directory

# TicTacToe
tictactoe: $(GAMESDIREC)/TicTacToe/TicTacToeMain.cpp
	$(COMPILER) -Wall $(GAMESDIREC)/TicTacToe/TicTacToeMain.cpp $(GAMESDIREC)/TicTacToe/tictactoe.cpp -o $(PREFIX)tictactoe
	echo TicTacToe building successfully in Bin Directory!

# Pong
pong: $(GAMESDIREC)/Pong/Pong.cpp
	$(COMPILER) -Wall $(GAMESDIREC)/Pong/Pong.cpp -o $(PREFIX)pong -lncurses
	echo Pong building successfully in Bin Directory!

# Calendar & Converter Build
# Calendar
datec: $(SRCAPPSDIREC)/FDate/FDate.cpp
	$(COMPILER)  $(SRCAPPSDIREC)/FDate/FDate.cpp -o fdate
	echo FDate building successfully!

# Calendar & Converter & Build & Install
date: $(SRCAPPSDIREC)/FDate/FDate.cpp
	$(COMPILER)  $(SRCAPPSDIREC)/FDate/FDate.cpp -o $(PREFIX)fdate
	echo FDate building successfully in Bin Directory!

# Integrated Scrift's core.
# Fetcheya Build
#fetcheya: $(SRCFETCHEYADIREC)Fetcheya.cpp
#	$(COMPILER) $(CFLAGS) $(SRCFETCHEYADIREC)Logos.cpp $(SRCFETCHEYADIREC)Fetcheya.cpp -o fetcheya
#	echo Fetcheya building successfully!

# Fetcheya Build & Install
#fetcheyac: $(SRCFETCHEYADIREC)Fetcheya.cpp
#	$(COMPILER) $(CFLAGS) $(SRCFETCHEYADIREC)Logos.cpp $(SRCFETCHEYADIREC)Fetcheya.cpp -o $(PREFIX)fetcheya
#	echo Fetcheya building successfully in Bin Directory!

# Remove Scrift.
uninstall:
	rm -f /bin/scrift
	rm -f /bin/edifor
	rm -f /bin/castle
	rm -f /src/Games/Castle/castle
	rm -f /bin/fdate
	rm -f /bin/pong
	rm -f /bin/tictactoe

# Run Scrift
run:
	./scrift

# Clean object files
clean:
		$(CLEAN)

# Clean object files and Scrift, Fetcheya.
cleanall:
		echo Cleaning build directory!
		$(CLEANALL)
