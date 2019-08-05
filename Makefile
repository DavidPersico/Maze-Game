CXX = g++

all: maze

clean:
	rm Player.o Maze.o Event.o maze

maze: Player.o Maze.o Event.o
	$(CXX) main.cpp -o maze

Player.o: Player.cpp
	$(CXX) -c Player.cpp

Maze.o: Maze.cpp
	$(CXX) -c Maze.cpp

Event.o: Event.cpp
	$(CXX) -c Event.cpp
