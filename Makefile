CXX = g++
OBJ = player.o maze.o event.o game.o

all: maze clean

maze: $(OBJ) main.cpp
				$(CXX) -o $@ $^

%.o: %.cpp %.h
				$(CXX) -c $<

clean:
				rm $(OBJ)
