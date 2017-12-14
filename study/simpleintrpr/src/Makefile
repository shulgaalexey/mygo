# Makefile for intrprtr examples

#COMMON_LIB = gtest
COMMON_INCLUDE = /usr/include

G++ = g++ -std=c++1y
G++_FLAGS = -c -Wall -I $(COMMON_INCLUDE) -I ./
#LD_FLAGS = -L /usr/lib -l $(COMMON_LIB) -l pthread
LD_FLAGS = -L /usr/lib -l pthread

OBJECTS = lexer.o main.o
TARGET = main.app

all: $(TARGET)

$(TARGET): $(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS) $(LD_FLAGS)

%.o : %.cpp
	$(G++) $(G++_FLAGS) $<

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean
