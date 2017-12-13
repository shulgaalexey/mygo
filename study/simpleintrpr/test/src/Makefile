# Makefile for gtest 

GOOGLE_TEST_LIB = gtest
GOOGLE_TEST_INCLUDE = /usr/include

G++ = g++
G++_FLAGS = -c -Wall -I $(GOOGLE_TEST_INCLUDE) -I ./ -I ../../src
LD_FLAGS = -L /usr/lib -l $(GOOGLE_TEST_LIB) -l pthread

#OBJECTS = ../../src/lexer.o lexer_test.o all_tests.o
OBJECTS = ../../src/lexer.o lexer_test.o all_tests.o
TARGET = test_all

all: $(TARGET)

$(TARGET): $(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS) $(LD_FLAGS)

%.o : %.cpp
	$(G++) $(G++_FLAGS) $<

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean
