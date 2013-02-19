CXXFLAGS = -Wall -g -include stdafx.h -Winvalid-pch -O2 -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio
OBJECTS =   $(patsubst %.cpp,%.o,$(wildcard *.cpp))
TARGET = my_program
CC = g++


$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(CXXFLAGS)

clean:
	del *.o