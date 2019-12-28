#include "game_logic.h"
#include "main_window.h"
#include <cstddef>
#include <ctime>
#include <cstdlib>
#include <vector>

static const int s_num_x = 9;
static const int s_num_y = 9;
static const int s_num_xy = 81;
static const int s_num_bombs = 10;

static std::vector<bool> s_bombs;
static std::vector<bool> s_flagged;
static std::vector<bool> s_selected;

static 
int i2d(int i, int j)
{
   return i + s_num_x * j;
}

void reset_game()
{
   srand(time(NULL));
   
   s_bombs.resize(s_num_xy);
   s_flagged.resize(s_num_xy);
   s_selected.resize(s_num_xy);
   for (int i = 0; i < s_num_xy; i++)
   {
      s_bombs[i] = false;
      s_flagged[i] = false;
      s_selected[i] = false;
   }

   for (int i = 0; i < s_num_bombs; i++)
   {
      int index = rand() % s_num_xy;
      if (s_bombs[index])
         i--;
      else
         s_bombs[index] = true;
   }

   display_num_bombs(s_num_bombs);
}

bool is_selected(int i, int j)
{
   if (i < 0 || j < 0 || i >= s_num_x || j >= s_num_y)
      return false;

   return s_selected[i2d(i,j)];
}

bool is_flagged(int i, int j)
{
   if (i < 0 || j < 0 || i >= s_num_x || j >= s_num_y)
      return false;

   return s_flagged[i2d(i,j)];
}

bool is_bomb(int i, int j)
{
   if (i < 0 || j < 0 || i >= s_num_x || j >= s_num_y)
      return false;

   return s_bombs[i2d(i,j)];
}

int num_adjacent(int i, int j)
{
   if (is_bomb(i, j))
      return -1;
   
   int adj = 0;
   if (is_bomb(i-1, j-1)) adj++;
   if (is_bomb(i-1, j+0)) adj++;
   if (is_bomb(i-1, j+1)) adj++;
   if (is_bomb(i+0, j-1)) adj++;
   if (is_bomb(i+0, j+1)) adj++;
   if (is_bomb(i+1, j-1)) adj++;
   if (is_bomb(i+1, j+0)) adj++;
   if (is_bomb(i+1, j+1)) adj++;

   return adj;
}

void set_selected(int i, int j)
{
   if (i < 0 || j < 0 || i >= s_num_x || j >= s_num_y)
      return;

   if (s_selected[i2d(i,j)])
      return;

   s_selected[i2d(i,j)] = true;

   if (num_adjacent(i, j) == 0)
   {
      set_selected(i-1, j-1);
      set_selected(i-1, j+0);
      set_selected(i-1, j+1);
      set_selected(i+0, j-1);
      set_selected(i+0, j+1);
      set_selected(i+1, j-1);
      set_selected(i+1, j+0);
      set_selected(i+1, j+1);
   }
}

void toggle_flagged(int i, int j)
{
   s_flagged[i2d(i,j)] = !s_flagged[i2d(i,j)];

   int num_bombs_left = 0;
   for (int i = 0; i < s_num_xy; i++)
   {
      if (s_bombs[i])
         num_bombs_left++;
      if (s_flagged[i])
         num_bombs_left--;
   }

   display_num_bombs(num_bombs_left);
}

