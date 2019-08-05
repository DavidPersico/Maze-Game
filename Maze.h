/*
This is part of David Persico's Maze Game!
Here we have a class for THE MAZE!
*/
#ifndef _MAZE_H_
#define _MAZE_H_

#include <time.h>       /* time */
#include <vector>
#include <string>
#include "Player.h"


class Board
{
//MEMBERS DESCRIBED IN  Maze.cpp
private:
	int size_;
	int level_;
	std::vector<int> points_;
	std::vector<char> arr_;
//DESCRIBED
public:
	Board(const int size, const int level, Player& p); // constuctor
	//Note for Munzy
	//I see we are given inconsistent names. why?
	//prefer GetCapitalAsFirstLetter, but I used your provided convention
	int get_size() const {return size_; }
  int get_level() const {return level_;}
	std::vector<char> GetBoard(){return arr_;}
	void SetSquare(char c, int new_pos){arr_[new_pos] = c;}
	std::vector<int> GetPoints(){return points_;}


	//MUST meth heads
	std::vector<int> MakePoints(int size, int level);
	std::vector<char> GetMoves( Player& p );
	bool MovePlayer( Player& p, char m );
	bool GetExitOccupant( Player& p );
	void PrintBoard();
	std::vector<char> SetSquares(const int size, const int level, Player& p);
};

 #endif  // _MAZE_H_
