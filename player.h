/*
This is part of David Persico's Maze Game!
Here we have a class for players!
*/

#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <string>


class Player
{
private: //members
	char name_;
	int lives_;
	int points_;
	int pos_;

public:
 //METH HEADS
	Player(char name, int lives, int points, int pos); // declare point memebers for constructor

	char get_name();// const {return name_; } // inline member function
	int get_lives();//{return lives_; } // inline member function
	int get_points();//{return points_; }  // inline member function
	int get_position();//{return pos_; } // inline member function

	void set_position(int new_pos);
	bool die();
	void ChangePoints(const int x, bool add);  // regular member functions

}; // class Player

#endif  // _PLAYER_H_
