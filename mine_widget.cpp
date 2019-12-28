#include "mine_widget.h"
#include "game_logic.h"
#include <QPainter>
#include <QMouseEvent>
#include <QTextStream>

Mine_Widget::Mine_Widget()
{
   this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
   this->setMouseTracking(true);
   c_button_x = -1;
   c_button_y = -1;
   reset_game();
}

void Mine_Widget::paintEvent(QPaintEvent *event)
{
   Q_UNUSED(event);

   QPainter painter(this);

   int button_width = get_bound_x(1) - get_bound_x(0);
   int button_height = get_bound_y(1) - get_bound_y(0);

   for (int i = 0; i < 9; i++)
   for (int j = 0; j < 9; j++)
   {
      if (is_selected(i, j))
      {
         painter.fillRect(
            get_bound_x(i), get_bound_y(j), 
            button_width, button_height, 
            QColor(200, 200, 200));

         if (is_bomb(i, j))
         {
            painter.drawText(
               get_bound_x(i), get_bound_y(j), 
               button_width, button_height, 
               Qt::AlignCenter, "B");
         }
         else if (num_adjacent(i, j) > 0)
         {
            char text[4];
            sprintf(text, "%d", num_adjacent(i, j));
            painter.drawText(
               get_bound_x(i), get_bound_y(j), 
               button_width, button_height, 
               Qt::AlignCenter, text);
         }
      }
      else
      {
         painter.fillRect(
            get_bound_x(i), get_bound_y(j), 
            button_width, button_height, 
            QColor(150, 150, 150));

         if (is_flagged(i, j))
         {
            painter.drawText(
               get_bound_x(i), get_bound_y(j), 
               button_width, button_height, 
               Qt::AlignCenter, "F");
         }

         if (c_button_x == i && c_button_y == j)
         {
            painter.fillRect(
               get_bound_x(i), get_bound_y(j), 
               button_width, button_height, 
               QColor(0, 0, 0, 50));
         }
      }

      painter.drawRect(
         get_bound_x(i), get_bound_y(j), 
         button_width, button_height);
   }
}

QSize Mine_Widget::sizeHint() const
{
   return QSize(400, 400);
}

void Mine_Widget::mouseMoveEvent(QMouseEvent *event)
{
   int x = event->x();
   int y = event->y();

   int button_width = get_bound_x(1) - get_bound_x(0);
   int button_height = get_bound_y(1) - get_bound_y(0);

   x = x - get_bound_x(0);
   y = y - get_bound_y(0);
   int button_x = x / button_width;
   int button_y = y / button_height;
   if (x < 0)
      button_x = -1;
   if (y < 0)
      button_y = -1;

   if (button_x != c_button_x || button_y != c_button_y)
   {
      c_button_x = button_x;
      c_button_y = button_y;
      //QTextStream out(stdout);
      //out << "Button move: " << c_button_x << " " << c_button_y << endl;
      update();
   }
}

void Mine_Widget::mousePressEvent(QMouseEvent *event)
{
   int x = event->x();
   int y = event->y();

   int button_width = get_bound_x(1) - get_bound_x(0);
   int button_height = get_bound_y(1) - get_bound_y(0);

   x = x - get_bound_x(0);
   y = y - get_bound_y(0);
   int button_x = x / button_width;
   int button_y = y / button_height;
   if (x < 0)
      button_x = -1;
   if (y < 0)
      button_y = -1;

   if (button_x < 0 || button_x > 8 || button_y < 0 || button_y > 8)
      return;

   if (event->button() == Qt::RightButton)
   {
      toggle_flagged(button_x, button_y);
      update();
   }
   if (event->button() == Qt::LeftButton)
   {
      if (!is_flagged(button_x, button_y))
      {
         set_selected(button_x, button_y);
         update();
      }
   }
}

int Mine_Widget::get_bound_x(int index)
{
   int width = (this->width() - 20) / 9;
   return width * index + 10;
}

int Mine_Widget::get_bound_y(int index)
{
   int height = (this->height() - 20) / 9;
   return height * index + 10;
}

