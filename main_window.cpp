#include "main_window.h"
#include "mine_widget.h"
#include "game_logic.h"
#include <QPushButton>
#include <QGridLayout>
#include <QLCDNumber>
#include <QLabel>

static QLabel *s_bombs_label;
static Mine_Widget *s_mine_widget;
static QPushButton *s_reset_button;

Main_Window::Main_Window()
{
   QVBoxLayout *main_layout = new QVBoxLayout();
   QWidget *central_widget = new QWidget();
   central_widget->setLayout(main_layout);
   setCentralWidget(central_widget);

   s_bombs_label = new QLabel();
   QFont font;
   font.setPointSize(12);
   s_bombs_label->setFont(font);
   main_layout->addWidget(s_bombs_label);

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
   char text[100];
   sprintf(text, "Bombs not flagged: %d", num_bombs);
   s_bombs_label->setText(text);
}

void Main_Window::reset_button_click()
{
   reset_game();
   s_mine_widget->reset();
   this->setWindowTitle("Minesweeper");
   s_mine_widget->setDisabled(false);
   s_mine_widget->update();
}

void game_win()
{
   s_bombs_label->setText("You Win");
   s_mine_widget->setDisabled(true);
}

void game_lose()
{
   s_bombs_label->setText("You Lose");
   s_mine_widget->setDisabled(true);
}

