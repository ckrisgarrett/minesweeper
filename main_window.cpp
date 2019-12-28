#include "main_window.h"
#include <QPushButton>
#include <QGridLayout>
#include "mine_widget.h"

Main_Window::Main_Window()
{
   Mine_Widget *m = new Mine_Widget;
   QVBoxLayout *main_layout = new QVBoxLayout;
   main_layout->addWidget(m);
   QWidget *central_widget = new QWidget();
   central_widget->setLayout(main_layout);
   setCentralWidget(central_widget);
}

Main_Window::~Main_Window()
{

}

void Main_Window::button_click()
{
   printf("Button click\n");
}

