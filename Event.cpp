/*
This is part of David Persico's Maze Game!
This class handles in game events! Coin and Enemy
*/

#include "Event.h"
#include "Player.h"
#include "Maze.h"
#include <string>

Event::Event(std::vector<bool> is_enemy, std::vector<int> pos)
  {
  is_enemy_ = is_enemy;
  pos_    = pos;
  }

  std::vector<bool> Event::get_type() {return is_enemy_; } /* Inline member function */

  void Event::set_position( std::vector<int> new_pos )
    {
    pos_ = new_pos;
    }

  /* Makes sure events go as planned */
  void Event::CheckEvent(Player& p,Board& b)
    {
    std::vector<int> coins;
    coins = b.GetPoints();
    int level = b.get_level();
    for (int c = 0; c<pos_.size(); c++)
      {
      if (is_enemy_[c])
        b.SetSquare('*',pos_[c]);
      if (p.get_position() == pos_[c])
        {
        if(is_enemy_[c])
          {
          p.LoseLife();
          b.SetSquare('*',pos_[c]);
          }
        else
          p.ChangePoints(10, true);
        }
      }
    }

  /* Do the thing! THIS IS THE AI! Killin you before you win! */
  void Event::DoEvent(Player& p, Board& b)
    {
    int ppos = p.get_position();
    int size = b.get_size();
    for (int c = 0; c < pos_.size(); c++)
      {
      if (is_enemy_[c])
        {/* Move towards player as if board is simple 1d array :) */
        if (ppos-pos_[c] >= size)
          {
          b.SetSquare(' ',pos_[c]);
          pos_[c] = pos_[c]+size;
          } /*Down*/
        if (pos_[c]-ppos >= size)
          {
          b.SetSquare(' ',pos_[c]);
          pos_[c] = pos_[c]-size;
          } /*Up*/
        if (ppos > pos_[c])
          {
          b.SetSquare(' ',pos_[c]);pos_[c] = pos_[c]+1;
          } /*Right*/
        else
          {
          b.SetSquare(' ',pos_[c]);
          pos_[c] = pos_[c]-1;
          } /*Left*/
        }
      }
    }
