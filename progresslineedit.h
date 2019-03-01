#ifndef DOWNLOADPROGRESS_H
#define DOWNLOADPROGRESS_H

#include <QLineEdit>
#include <QWebView>

class ProgressLineEdit : public QLineEdit {
    Q_OBJECT

public:
    ProgressLineEdit();

public slots:
    void updateProgressSlot(int progress);

protected:
    virtual void paintEvent(QPaintEvent *e);

private:
    int progress = 0;
};

#endif // DOWNLOADPROGRESS_H
