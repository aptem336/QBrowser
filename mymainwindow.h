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
    void backSlot();
    void forwardSlot();
    void reloadSlot();
    void stopSlot();
    void returnPressedSlot();
    void loadSlot(QUrl);
    void urlChangedSlot(QUrl);
    void titleChangedSlot(QString);
    void loadStartedSlot();
    void loadFinishedSlot();
    void settingsOpenSlot();
    void changeSettings();

private:
    QPushButton *backButton;
    QPushButton *nextButton;
    QPushButton *reloadButton;
    QPushButton *stopButton;
    QPushButton *settingsButton;

    QLineEdit *addressLineEdit;
    QWebView *webView;

    QSettings *settings;
    void readSettings();

    const static QString browserName;
};

#endif // WIDGET_H
