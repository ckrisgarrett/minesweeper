#include "main_window.h"
#include "mine_widget.h"
#include "game_logic.h"
#include <QPushButton>
#include <QGridLayout>
#include <QLCDNumber>

static QLCDNumber *s_lcd_number;
static Mine_Widget *s_mine_widget;
static QPushButton *s_reset_button;
static Main_Window *s_main_window;

Main_Window::Main_Window()
{
   s_main_window = this;

   QVBoxLayout *main_layout = new QVBoxLayout();
   QWidget *central_widget = new QWidget();
   central_widget->setLayout(main_layout);
   setCentralWidget(central_widget);

   QWidget *top_widget = new QWidget();
   QHBoxLayout *top_layout = new QHBoxLayout();
   top_layout->addStretch();
   s_lcd_number = new QLCDNumber(2);
   s_lcd_number->setStyleSheet("color: red; background: black;");
   top_layout->addWidget(s_lcd_number);
   top_layout->addStretch();
   top_widget->setLayout(top_layout);
   main_layout->addWidget(top_widget);

   s_mine_widget = new Mine_Widget();
   main_layout->addWidget(s_mine_widget);

   QWidget *bottom_widget = new QWidget();
   QHBoxLayout *bottom_layout = new QHBoxLayout();
   bottom_layout->addStretch();
   s_reset_button = new QPushButton("Reset");
   bottom_layout->addWidget(s_reset_button);
   bottom_layout->addStretch();
   bottom_widget->setLayout(bottom_layout);
   main_layout->addWidget(bottom_widget);
   connect(
      s_reset_button, QPushButton::clicked, 
      this, Main_Window::reset_button_click);
}

Main_Window::~Main_Window()
{

}

void display_num_bombs(int num_bombs)
{
   s_lcd_number->display(num_bombs);
}

void Main_Window::reset_button_click()
{
   reset_game();
   this->setWindowTitle("Minesweeper");
   s_mine_widget->setDisabled(false);
   s_mine_widget->update();
}

void game_win()
{
   s_main_window->setWindowTitle("You Win");
   s_mine_widget->setDisabled(true);
}

void game_lose()
{
   s_main_window->setWindowTitle("You Lose");
   s_mine_widget->setDisabled(true);
}

