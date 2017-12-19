# Makefile for gtest

GOOGLE_TEST_LIB = gtest
GOOGLE_TEST_INCLUDE = /usr/include

G++ = g++ -std=c++1y
G++_FLAGS = -c -Wall -I $(GOOGLE_TEST_INCLUDE) -I ./ -I ../../src
LD_FLAGS = -L /usr/lib -l $(GOOGLE_TEST_LIB) -l pthread

OBJECTS = lexer_test.o token_test.o parser_test.o evaluator_test.o all_tests.o
TARGET = test_all.out

all: $(TARGET)

$(TARGET): $(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS) $(LD_FLAGS)

%.o : %.cpp
	$(G++) $(G++_FLAGS) $<

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean
