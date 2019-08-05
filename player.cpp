/*
This is part of David Persico's Maze Game!
Here we have a class for players!
*/

#include "player.h"
#include <string>
Player::Player(char name, int lives, int points, int pos)
{
  name_   = name;
  lives_  = lives;
  points_ = points;
  pos_    = pos;
}

  /* Inline member functions*/
  char Player::get_name(){return name_;}
  int Player::get_lives(){return lives_;}
  int Player::get_points(){return points_;}
  int Player::get_position(){return pos_;}
  void Player::set_position( int new_pos ){pos_ = new_pos;}

  /* Method for when player dies */
  bool Player::die()
  {
    pos_=0;
    lives_ = lives_ - 1;
    if (lives_ == -1) {return true;}
    else {return false;}
  }

  /* Method to add or subtract player points. */
  void Player::ChangePoints(const int x, bool add)
  {
    if (add) {points_ = points_ + x;}
    else {points_ = points_ - x;}
  }
