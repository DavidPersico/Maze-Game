#include <time.h>       /* time */
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include "Maze.h"
#include "Player.h"
#include <iostream>
#include <string>

#define WALL '='  /* thats the wall char*/

//constuctor
Board::Board(const int size, const int level, Player& p)
  {
  size_ = size; //dimesions
  level_ = level; //what level we are on
  points_ = MakePoints(size, level); //points are used to provide solvable maps
  arr_ = SetSquares(size, level, p); //arr is 1D vector of our gameboard
  }
  //Meth heads
  //GetMoves find what Moves are possible_moves

  std::vector<int> Board::MakePoints(int size, int level)
    {
    std::vector<int> point;
    point.push_back(0);
    for (int a=0; a<level*3-2; a++)
      {
      point.push_back(rand() % (size*size-2) + 2);
      }
    point.push_back(size*size - 1);//add exit
    point.push_back(size*size);// end of board vector
    return point;
    }
  //Finds which moves are possible, returning a vector of them
  std::vector<char> Board::GetMoves(Player& p)
    {
    std::vector<char> possible_moves;
    if (p.get_position()-size_ >= 0 && arr_[p.get_position() - size_] != WALL){possible_moves.push_back('w');}
    if (p.get_position() - 1 >= 0 && arr_[p.get_position() - 1] != WALL){possible_moves.push_back('a');}
    if (p.get_position()+size_ < size_*size_ && arr_[p.get_position() + size_] != WALL){possible_moves.push_back('s');}
    if (p.get_position() + 1 < size_*size_ && arr_[p.get_position() + 1] != WALL) {possible_moves.push_back('d');}
    return possible_moves;
    }
  //Preforms Player Move and Board rearrange
  bool Board::MovePlayer(Player& p, char m)
    {
      switch(m)
      {
        case 'w' : // move up
          {
          std::cout << m << std::endl;
          if (p.get_position()-size_ >= 0 && arr_[p.get_position()-size_] != WALL)
            {
            arr_[p.get_position()] = ' ';
            arr_[p.get_position() - size_] = '&';
            p.set_position(p.get_position() - size_);
            return true;
            }
          else return false;
          }
        case 's' : // move down
          {
          std::cout << m << std::endl;
          std::cout<<p.get_position();
          if (p.get_position()+size_ < size_*size_ && arr_[p.get_position()+size_] != WALL)
            {
            std::cout << m << std::endl;
            arr_[p.get_position()] = ' ';
            arr_[p.get_position() + size_] = '&';
            p.set_position(p.get_position() + size_);
            return true;
            }
          else return false;
          }
        case 'd' : // move right
          {
          if (p.get_position() + 1 < size_*size_ && arr_[p.get_position() + 1] != WALL)
            {
            arr_[p.get_position()] = ' ';
            arr_[p.get_position() + 1] = '&';
            p.set_position(p.get_position() + 1);
            return true;
            }
          else return false;
          }
        case 'a' :// move left
          {
          if (p.get_position() - 1 >= 0 && arr_[p.get_position() - 1] != WALL)
            {
            arr_[p.get_position()] = ' ';
            arr_[p.get_position() - 1] = '&';
            p.set_position(p.get_position() - 1);
            return true;
            }
          else return false;
          }
        default: return false;
      }
    return false;
    }
  //check if player beat a maze
  bool Board::GetExitOccupant(Player& p)
    {
    return (p.get_position() == (size_*size_-1));
    }
  //Display everything
  void Board::PrintBoard()
    {
    int new_line_count = 0;
    std::cout << std::string(size_+2, '~');
    std::cout<<"\n|";
    for (int a=0;a<size_*size_;a++)
      {
      if (a-new_line_count == size_)
        {
        std::cout<<"|\n|";
        new_line_count=new_line_count+size_;
        }
      std::cout<<arr_[a];
      }
    std::cout<<"| \n";
    std::cout << std::string(size_+2, '~');
    std::cout<<'\n';
    }
  std::vector<char> Board::SetSquares(int size, int level, Player& p)
    {
    p.set_position(0);
    srand (time(NULL));
    std::vector<char> board;
    board.push_back('&');
    board.push_back(' ');
    for (int a=2; a<size*size - 1; a++)// create the boar
      {
      if (rand() % 11 + 1 <= 2*level) // make walls based on difficulty
        {
        board.push_back(WALL);
        }
      else board.push_back(' ');
      }
    board.push_back('X'); // add exit
    //creating a cleared path
    //first we pick random points along the way, more points at a higher level

    //now we make sure spaces between points are empty
    for (int n = 1; n <= level*3; n++)
      {
      bool finished = false;
      while (!finished)
        {
        if (points_[n-1] == points_[n]) {finished = true;} //path is cleared
        if (points_[n]-points_[n-1] >= size) {points_[n-1] = points_[n-1]+size; board[points_[n-1]] = ' ';} //clear down
        if (points_[n-1]-points_[n] >= size) {points_[n-1] = points_[n-1]-size; board[points_[n-1]] = ' ';} //clear up
        if (points_[n] > points_[n-1]) {points_[n-1] = points_[n-1]+1; board[points_[n-1]] = ' ';} //clear forward
        else {points_[n-1] = points_[n-1]-1; board[points_[n-1]] = ' ';} //clear back
        }
      }
    for (int a=0; a<level*3-3; a++)
      {
      board[points_[a]]= '$';

      }
    board[size*size-1]='X';//just in case exit is erased
    return board;
    }
