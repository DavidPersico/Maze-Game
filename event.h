/*
This is part of David Persico's Maze Game!
*/
#include <string>

#include "player.h"
#include "maze.h"
#ifndef _EVENT_H_
#define _EVENT_H_



class Event
{
private://members
	std::vector<bool> is_enemy_;
	std::vector<int> pos_;

public:
	Event(std::vector<bool> is_enemy, std::vector<int> pos); // declare point memebers for constructor

  std::vector<bool> get_type(); // inline member function
  //declare
  void set_position(std::vector<int> new_pos);
  void CheckEvent(Player& p, Board& b);
  void DoEvent(Player& p, Board& b);

}; // class Event

#endif  // _EVENT_H_
