#include "main_window.h"
#include <QPushButton>
#include <QGridLayout>
#include <QLCDNumber>
#include "mine_widget.h"

static QLCDNumber *s_lcd_number;
static QPushButton *s_reset_button;

Main_Window::Main_Window()
{
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

   Mine_Widget *m = new Mine_Widget();
   main_layout->addWidget(m);

   QWidget *bottom_widget = new QWidget();
   QHBoxLayout *bottom_layout = new QHBoxLayout();
   bottom_layout->addStretch();
   s_reset_button = new QPushButton("Reset");
   bottom_layout->addWidget(s_reset_button);
   bottom_layout->addStretch();
   bottom_widget->setLayout(bottom_layout);
   main_layout->addWidget(bottom_widget);
}

Main_Window::~Main_Window()
{

}

void display_num_bombs(int num_bombs)
{
   s_lcd_number->display(num_bombs);
}

void Main_Window::button_click()
{
   printf("Button click\n");
}

