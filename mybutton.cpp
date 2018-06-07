#include "mybutton.h"
#include <QPushButton>
#include <QUrl>

MyButton::MyButton(QWidget *parent):QPushButton(parent){}

void MyButton::pushButtonSlot(){
    emit pushButtonSignal(url);
}
