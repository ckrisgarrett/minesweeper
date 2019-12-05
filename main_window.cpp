#include "main_window.h"
#include <QPushButton>
#include <QGridLayout>

Main_Window::Main_Window()
{
   const int num_rows = 9;
   const int num_cols = 9;
   QPushButton *b = new QPushButton[num_rows * num_cols];
   QGridLayout *buttons_layout = new QGridLayout();
   buttons_layout->setSpacing(0);
   for (int i = 0; i < num_rows; i++)
   for (int j = 0; j < num_cols; j++)
   {
      buttons_layout->addWidget(&b[i * num_cols + j], i, j);
      b[i * num_cols + j].setText("123");
      b[i * num_cols + j].setSizePolicy(
         QSizePolicy::Expanding, QSizePolicy::Expanding);
      connect(&b[i * num_cols + j], &QPushButton::clicked, this, &Main_Window::button_click);
   }
   QWidget *buttons_widget = new QWidget();
   buttons_widget->setLayout(buttons_layout);
   setCentralWidget(buttons_widget);
}

Main_Window::~Main_Window()
{

}

void Main_Window::button_click()
{
   printf("Button click\n");
}

