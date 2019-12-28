#include "main_window.h"
#include "game_logic.h"
#include <QApplication>

int main(int argc, char **argv)
{
   QApplication app(argc, argv);
   Main_Window main_window;
   main_window.show();
   reset_game();
   return app.exec();
}
