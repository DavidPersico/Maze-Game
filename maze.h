/*
This is part of David Persico's Maze Game!
Here we have a class for THE MAZE!
*/
#ifndef _MAZE_H_
#define _MAZE_H_

#include <time.h>       /* time */
#include <vector>
#include <string>
#include "player.h"


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


	int get_size() const {return size_; }
  int get_level() const {return level_;}
	std::vector<char> get_board(){return arr_;}
	void set_square(char c, int new_pos){arr_[new_pos] = c;}
	std::vector<int> get_points(){return points_;}


	std::vector<int> make_path(int size, int level);
	std::vector<char> get_moves( Player& p );
	bool move_player( Player& p, char m );
	bool check_exit( Player& p );
	void print_board();
	std::vector<char> set_squares(const int size, const int level, Player& p);
};

 #endif  // _MAZE_H_
