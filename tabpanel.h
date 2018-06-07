#ifndef TABPANEL_H
#define TABPANEL_H

#include <mybutton.h>
#include <QUrl>

class TabPanel : public QWidget
{
    Q_OBJECT
public:
    explicit TabPanel(QWidget *parent = nullptr);

public slots:
    void showSlot();
    void pushSlot(QUrl);
signals:
    void pushSignal(QUrl);
private:
    QList<MyButton *> *buttons_list;
};

#endif // TABPANEL_H
