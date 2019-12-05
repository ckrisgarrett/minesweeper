#pragma once
#include <QMainWindow>

class Main_Window : public QMainWindow
{
   Q_OBJECT

public:
   Main_Window();
   ~Main_Window();

public slots:
   void button_click();
};

