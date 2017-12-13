# Makefile for gtest examples

GOOGLE_TEST_LIB = gtest
GOOGLE_TEST_INCLUDE = /usr/include

G++ = g++
G++_FLAGS = -c -Wall -I $(GOOGLE_TEST_INCLUDE) -I ./ -I ../../src
LD_FLAGS = -L /usr/lib -l $(GOOGLE_TEST_LIB) -l pthread

OBJECTS = ../../src/Addition.o Addition_Test.o ../../src/Multiply.o Multiply_Test.o Main_TestAll.o
TARGET = testAll

all: $(TARGET)

$(TARGET): $(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS) $(LD_FLAGS)

%.o : %.cpp
	$(G++) $(G++_FLAGS) $<

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean
