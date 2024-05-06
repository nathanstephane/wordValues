PROG=wordVal
SRC_FILES = main.cpp \
			wordProcessor.cpp

CFLAGS = --std=c++17 -W -Wall -Werror -Wno-deprecated-declarations -Wno-unused-variable -Wno-unused-but-set-variable \
		-Wno-unused-parameter

OBJ = $(foreach file, $(SRC_FILES), $(file:.cpp=.o))

all: compile link

compile:
	g++  $(CFLAGS) -I./include/ -c src/*.cpp 

link:

	g++  $(OBJ)  -o bin/$(PROG) 

run:
	.\bin\$(PROG).exe

clean:

	rm $(OBJ)
	rm .\bin\$(PROG).exe
	
	