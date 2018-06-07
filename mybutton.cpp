#include "mybutton.h"
#include <QPainter>
#include <QDebug>

MyButton::MyButton(QWidget *parent):QPushButton(parent){}

void MyButton::pushButtonSlot(){
    emit pushButtonSignal(url);
}
void MyButton::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QRect rect = this->rect();
    QLinearGradient gradient(0,rect.height(),rect.width(),0);
    gradient.setColorAt(0, QColor(0xdedede));
    gradient.setColorAt(1, QColor(0xfefefe));
    painter.setPen(Qt::transparent);
    painter.setBrush(gradient);
    painter.drawRoundedRect(rect, 10, 10);
    if (!name.isEmpty()){
        painter.drawPixmap(rect.x()+5, rect.y()+30, QPixmap::fromImage(image.scaledToWidth(rect.width()-10)));
        painter.setPen(QColor(0x2980b9));
        painter.setFont(QFont("Arial SansSerif", 14));
        painter.drawText(rect, Qt::AlignHCenter, name);
    }
}
