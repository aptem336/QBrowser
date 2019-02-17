#ifndef MYDIALOG_H
#define MYDIALOG_H
#include <QSettings>
#include <QtWidgets>

class MySettings : public QDialog {
    Q_OBJECT
public:
    MySettings(QSettings *settings, QWidget *parent);
private:
    QLineEdit *hostnameEdit;
    QLineEdit *portEdit;
    QLineEdit *userNameEdit;
    QLineEdit *passwordEdit;
    QCheckBox *useProxy;
    QSettings *settings;
private slots:
    void enableChanged(bool);
    void okClicked();
    void cancelClicked();
    void defaultSettings();
signals:
    void settingsChanged();
};

#endif // MYDIALOG_H
