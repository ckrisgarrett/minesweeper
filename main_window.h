#pragma once
#include <QMainWindow>

class Main_Window : public QMainWindow
{
   Q_OBJECT

public:
   Main_Window();
   ~Main_Window();

public slots:
   void reset_button_click();
};

void display_num_bombs(int num_bombs);
void game_win();
void game_lose();
