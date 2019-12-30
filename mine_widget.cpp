#include "mine_widget.h"
#include "game_logic.h"
#include <QPainter>
#include <QMouseEvent>
#include <QTextStream>

static const int s_widget_buffer = 10;
static const int s_button_side = 40;


Mine_Widget::Mine_Widget()
{
   this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
   this->setMouseTracking(true);
   c_button_x = -1;
   c_button_y = -1;
}

void Mine_Widget::paintEvent(QPaintEvent *event)
{
   Q_UNUSED(event);

   QPainter painter(this);
   QFont font;
   font.setPointSize(12);
   painter.setFont(font);
   painter.setPen(QColor(0,0,0));

   for (int i = 0; i < get_num_x(); i++)
   for (int j = 0; j < get_num_y(); j++)
   {
      if (is_selected(i, j))
      {
         painter.fillRect(
            get_line_bound(i), get_line_bound(j), 
            s_button_side, s_button_side, 
            QColor(200, 200, 200));

         if (is_bomb(i, j))
         {
            painter.fillRect(
               get_line_bound(i), get_line_bound(j), 
               s_button_side, s_button_side, 
               QColor(255, 0, 0));
            painter.drawText(
               get_line_bound(i), get_line_bound(j), 
               s_button_side, s_button_side, 
               Qt::AlignCenter, "B");

            QBrush brush = painter.brush();
            painter.setBrush(QColor(0,0,0));
            painter.drawEllipse(
               get_line_bound(i), get_line_bound(j), 
               s_button_side, s_button_side);
            painter.setBrush(brush);
               
         }
         else if (num_adjacent(i, j) > 0)
         {
            char text[4];
            sprintf(text, "%d", num_adjacent(i, j));
            painter.drawText(
               get_line_bound(i), get_line_bound(j), 
               s_button_side, s_button_side, 
               Qt::AlignCenter, text);
         }
      }
      else
      {
         if (c_button_x == i && c_button_y == j)
         {
            painter.fillRect(
               get_line_bound(i), get_line_bound(j), 
               s_button_side, s_button_side, 
               QColor(200, 200, 255));
         }
         else
         {
            painter.fillRect(
               get_line_bound(i), get_line_bound(j), 
               s_button_side, s_button_side, 
               QColor(150, 150, 150));
         }

         if (is_flagged(i, j))
         {
            painter.drawText(
               get_line_bound(i), get_line_bound(j), 
               s_button_side, s_button_side, 
               Qt::AlignCenter, "F");
         }
      }

      painter.drawRect(
         get_line_bound(i), get_line_bound(j), 
         s_button_side, s_button_side);
   }
}

QSize Mine_Widget::sizeHint() const
{
   int width = 2 * s_widget_buffer + get_num_x() * s_button_side;
   int height = 2 * s_widget_buffer + get_num_y() * s_button_side;
   return QSize(width, height);
}

void Mine_Widget::reset()
{
   c_button_x = -1;
   c_button_y = -1;
}

void Mine_Widget::mouseMoveEvent(QMouseEvent *event)
{
   int x = event->x();
   int y = event->y();

   x = x - s_widget_buffer;
   y = y - s_widget_buffer;
   int button_x = x / s_button_side;
   int button_y = y / s_button_side;
   if (x < 0)
      button_x = -1;
   if (y < 0)
      button_y = -1;

   if (button_x != c_button_x || button_y != c_button_y)
   {
      c_button_x = button_x;
      c_button_y = button_y;
      update();
   }
}

void Mine_Widget::mousePressEvent(QMouseEvent *event)
{
   int x = event->x();
   int y = event->y();

   x = x - s_widget_buffer;
   y = y - s_widget_buffer;
   int button_x = x / s_button_side;
   int button_y = y / s_button_side;
   if (x < 0)
      button_x = -1;
   if (y < 0)
      button_y = -1;

   if (button_x < 0 || button_x >= get_num_x() || 
       button_y < 0 || button_y >= get_num_y())
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

int Mine_Widget::get_line_bound(int index)
{
   return s_button_side * index + s_widget_buffer;
}

