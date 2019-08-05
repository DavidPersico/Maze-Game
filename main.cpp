/*
This is part of David Persico's Maze Game!
This file contains the actual execution of said game!
*/

#include <time.h>       /* time */
#include <vector>
#include "Maze.cpp"
#include "Player.cpp"
#include "Event.cpp"


int main( int argc, char **argv )
  {
  //GAME SETUP
  std::cout<<"Welcome to: Dave's Maze \nSelect your maze size by entering an integer between 10 and 120\nNote: Larger mazes are more fun/playable\n\n\n\n\n";
  bool invalid = true;
  int choice_size;
  std::cin >> choice_size;
  if(!std::cin || choice_size<=9 || choice_size>120) // 120 is abirtary, a 4k screen should handle at least 200
    {
    choice_size = 60; // No time for your error prone BS
    std::cout<<"Invalid Input: Maze set to size 60. \n";
    }
  std::cin.clear();
  int anything;//press any key to continue
  std::cout<<"Dave's Maze follows Dave's Rules.\nWASD movement controls:\nw=Up, a=Left, s=Down d=Right\n";
  std::cout<<"This is you '&' and you have three lives\nYou ('&') can move through '|' and '$' but not through '~' or '='\nPicking up '$' give you points.";
  std::cout<<"Watch out for these:'*'. They destroy everything in their path! Try moving up to escape the '*'.\n\nAfter reading enter anything to start!\n\n";
  std::cin >> anything;
  std::cin.clear();
  std::cin.clear();//This prevents infinite loops
  Player p('p',3,0,0);

  for (int l=1; l <= 12; l++)
    {
    bool level_over = false; //Level Not Over
    Board maze(choice_size,l,p); //Create GameBoard

    //Initialize coins and enemys
    std::vector<bool> event_bool;
    std::vector<int> event_pos; //C++ uses compile time for most stuff, so my monster can't be dynamically allocated
    event_pos= maze.GetPoints();
    for (int c = 0; c<event_pos.size(); c++){event_bool.push_back(false);}
    for (int x = 0; x<=6; x++)
      {
      event_bool.push_back(true);
      event_pos.push_back((choice_size*choice_size-5)-1-x*l);//space the enemys
      }
    Event events(event_bool,event_pos);

    //PLAY THE GAME
    while(!level_over)
      {
      //do coins/monster interaction
      events.DoEvent(p, maze);
      events.CheckEvent(p, maze);

      //check if looser
      if (p.get_lives()<=-1){std::cout<<"YOU LOSE! TRY AGAIN";return 0;}
      //Help people comfortably by telling them what to do
      std::cout<<"Adjust your terminal, this line should not be visible!\n";
      //show Possible moves
      std::vector<char> moves;
      moves = maze.GetMoves(p);
      std::cout<<"Possible moves:";
      for (int m = 0; m<=moves.size();m++){std::cout<<" "<<moves[m];}
      //show lives and Points
      std::cout<<" Lives:"<<p.get_lives()<<" Points:"<< p.get_points()<<"\n";
      //show updated board
      maze.PrintBoard();
      //take in player movement
      char move;
      std::cin.clear();
      std::cin >> move;
      maze.MovePlayer(p,move);
      //check if they beat this level
      level_over = maze.GetExitOccupant(p);

      }
    std::cout<<"You Passed Level "<<l<<". That's pretty neat!\n You are awesome!\n";
    }
    std::cout<<"You Win!!, I can't beleive it!";
  }
