#include <time.h>
#include <vector>
#include <iostream>
#include <cstdlib>

#include "game.h"
#include "maze.h"
#include "player.h"
#include "event.h"

void play_game()
{
  /*** Game setup ***/
  std::cout<< "Welcome to Dave's Maze!\n"
              "Please enter your desired maze size. It must be between 10 and 120!\n"
              "You should know that larger mazes are more fun/playable but, may they might not fit your screen.\n\n";
  int choice_size;
  std::cin >> choice_size;
  if (!std::cin || choice_size <= 9 || choice_size > 120) // 120 is abirtary, a 4k screen should handle at least 200
  {
    choice_size = 60;
    std::cout<<"Invalid input...\n Maze set to size 60.\n\n";
  }
  else
    std::cout<<"Great. Let's get started!\n\n";
  std::cin.clear();

  std::cout<< "Controls:\n"
              "WASD movement controls:\nW = Up, A = Left, S = Down D = Right\n"
              "You can make multiple moves at once like this \"SSSD\".\n"
              "\n"
              "Rules:\n"
              "You look like this --> & <--\n"
              "You've 3 lives to finish 12 levels.\n"
              "As the '&' you can pass through'|' and '$' but not through '~' or '='.\n"
              "Moving through a '$' gives you more points.\n"
              "Watch out for these '*'. They destroy everything in their path!\n"
              "Hint: Try moving up to escape the '*'.\n"
              "\n"
              "After reading, enter anything to start!\n\n";
  std::cin.get(); /* Press any key to continue */
  std::cin.clear();

  /* Initialize player and level variables */
  Player p ('p',3,0,0);
  bool level_won; /* Level finished check */
  std::vector<bool> event_bool;
  std::vector<int> event_pos;
  std::vector<char> moves;
  char move;

  for (int level = 1; level <= 12; level++)
  {
    /* Initialize level with level dependent coins and enemys */
    Board maze(choice_size, level, p); /* Create board for level*/
    event_pos = maze.get_points();
    event_bool.clear();
    for (int c = 0; c < event_pos.size(); c++)
      event_bool.push_back(false);
    for (int x = 0; x <= level; x++)
    {
      event_bool.push_back(true);
      event_pos.push_back((choice_size*choice_size-5)-1-x*level);//space the enemys
    }
    Event events(event_bool,event_pos);

    /*** Play the game ***/
    level_won = false;
    while(!level_won)
    {
      /* Check on coins and move the monster. */
      events.CheckEvent(p, maze);
      events.DoEvent(p, maze);

      /* Check if the game is over. */
      if (p.get_lives()<=-1)
      {
        std::cout<<"Sorry, you lost...\nBetter luck next time!";
        exit(1);
      }

      /* Message for those with improper window size.  */
      std::cout<<"Adjust your terminal, this line should not be visible!\n";

      /* Show possible moves, lives and points. */
      moves = maze.get_moves(p);
      std::cout<<"Possible moves:";
      for (int m = 0; m <= moves.size(); m++)
        std::cout<<" "<<moves[m];
      std::cout<<" Lives:"<<p.get_lives()<<" Points:"<< p.get_points()<<"\n";

      /* Display the updated maze. */
      maze.print_board();

      /* Get player move and move player. */
      std::cin >> move;
      std::cin.clear();
      maze.move_player(p,move);

      /* Check if the exit was reached. */
      level_won = maze.check_exit(p);
    }
    std::cout<<"You Passed Level "<< level <<". That's pretty neat!\nYou're awesome!\n";
  }
  std::cout<<"You Win!!, I can't beleive it!";
}
