#ifndef MYBUTTON_H
#define MYBUTTON_H
#include <QPushButton>
#include <QUrl>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = 0);
    QUrl url;
public slots:
    void pushButtonSlot();
signals:
    void pushButtonSignal(QUrl);
};

#endif // MYBUTTON_H
