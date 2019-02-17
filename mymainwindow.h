#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QSettings>
#include <QtWidgets>
#include <QtWebKitWidgets>

class MyMainWindow : public QWidget {
    Q_OBJECT

public:
    MyMainWindow(QWidget *parent = 0);
private slots:
    void returnPressedSlot();
    void linkClickedSlot(QUrl);

    void urlChangedSlot(QUrl);
    void titleChangedSlot(QString);

    void backSlot();
    void forwardSlot();
    void reloadSlot();

private:
    QPushButton *backButton;
    QPushButton *forwardButton;
    QPushButton *reloadButton;

    QLineEdit *addressLineEdit;
    QWebView *webView;

    const static QString browserName;
};

#endif // WIDGET_H
