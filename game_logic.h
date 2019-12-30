#pragma once

int get_num_x();
int get_num_y();
void reset_game();
bool is_selected(int i, int j);
bool is_flagged(int i, int j);
bool is_bomb(int i, int j);
int num_adjacent(int i, int j);
void toggle_flagged(int i, int j);
void set_selected(int i, int j);
