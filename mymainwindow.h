#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QtWidgets>
#include <QtWebKitWidgets>
#include <progresslineedit.h>

class MyMainWindow : public QWidget {
    //!!!
    Q_OBJECT

public:
    MyMainWindow();

private slots:
    void backSlot();
    void forwardSlot();
    void reloadSlot();

    void returnPressedSlot();
    void linkClickedSlot(QUrl);

    void urlChangedSlot(QUrl);
    void titleChangedSlot(QString);

private:
    QPushButton *backButton;
    QPushButton *forwardButton;
    QPushButton *reloadButton;

    ProgressLineEdit *addressLineEdit;
    QWebView *webView;
};

#endif // WIDGET_H
