#pragma once
#include <QWidget>

class Mine_Widget : public QWidget
{
   Q_OBJECT

public:
   Mine_Widget();

protected:
   void paintEvent(QPaintEvent *event) override;
   QSize sizeHint() const override;
   void mouseMoveEvent(QMouseEvent *event) override;
   void mousePressEvent(QMouseEvent *event) override;

private:
   get_bound_x(int index);
   get_bound_y(int index);
   int c_button_x, c_button_y;
};

