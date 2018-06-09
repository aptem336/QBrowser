#ifndef MYBUTTON_H
#define MYBUTTON_H
#include <QPushButton>
#include <QUrl>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget* parent = 0);
    virtual void paintEvent(QPaintEvent*);
    QString name;
    QUrl url;
    QImage image;
protected:

public slots:
    void pushButtonSlot();
signals:
    void pushButtonSignal(QUrl);
};

#endif // MYBUTTON_H
