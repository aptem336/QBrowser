#include "mysettings.h"
#include "mymainwindow.h"

MySettings::MySettings(QSettings *mysettings, QWidget *parent = 0) : QDialog(parent) {
    settings = mysettings;
    setModal(true);
    setWindowTitle(tr("Browser settings"));
    setAttribute(Qt::WA_DeleteOnClose);

    hostnameEdit = new QLineEdit();
    portEdit = new QLineEdit();
    userNameEdit = new QLineEdit();
    passwordEdit = new QLineEdit();
    passwordEdit->setEchoMode(QLineEdit::Password);
    useProxy = new QCheckBox();

    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp ipRegex("^" + ipRange
            + "\\." + ipRange
            + "\\." + ipRange
            + "\\." + ipRange + "$");
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    hostnameEdit->setValidator(ipValidator);

    QPushButton *okButton = new QPushButton(tr("OK"));
    QPushButton *cancelButton = new QPushButton(tr("Cancel"));
    QPushButton *defaultButton = new QPushButton(tr("Default"));

    QGridLayout *mainLayout = new QGridLayout();

    mainLayout->addWidget(new QLabel(tr("Enable proxy")), 0, 0);
    mainLayout->addWidget(new QLabel(tr("Host")), 1, 0);
    mainLayout->addWidget(new QLabel(tr("Port")), 2, 0);
    mainLayout->addWidget(new QLabel(tr("Username")), 3, 0);
    mainLayout->addWidget(new QLabel(tr("Password")), 4, 0);

    mainLayout->addWidget(useProxy, 0, 1);
    mainLayout->addWidget(hostnameEdit, 1, 1);
    mainLayout->addWidget(portEdit, 2, 1);
    mainLayout->addWidget(userNameEdit, 3, 1);
    mainLayout->addWidget(passwordEdit, 4, 1);

    mainLayout->addWidget(okButton, 5, 0);
    mainLayout->addWidget(cancelButton, 6, 0);
    mainLayout->addWidget(defaultButton, 7, 0);

    setLayout(mainLayout);

    hostnameEdit->setEnabled(false);
    portEdit->setEnabled(false);
    userNameEdit->setEnabled(false);
    passwordEdit->setEnabled(false);

    connect(useProxy, SIGNAL(clicked(bool)), this, SLOT(enableChanged(bool)));
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(okClicked()));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(cancelClicked()));
    connect(defaultButton, SIGNAL(clicked(bool)), this, SLOT(defaultSettings()));

    hostnameEdit->setText(settings->value("proxy/host").toString());
    portEdit->setText(settings->value("proxy/port").toString());
    userNameEdit->setText(settings->value("proxy/user").toString());
    passwordEdit->setText(settings->value("proxy/password").toString());
}

void MySettings::enableChanged(bool flag){
    hostnameEdit->setEnabled(flag);
    portEdit->setEnabled(flag);
    userNameEdit->setEnabled(flag);
    passwordEdit->setEnabled(flag);
}

void MySettings::okClicked() {
    settings->setValue("proxy/useProxy", useProxy->isChecked());
    settings->setValue("proxy/host", hostnameEdit->text());
    settings->setValue("proxy/port", portEdit->text());
    settings->setValue("proxy/user", userNameEdit->text());
    settings->setValue("proxy/password", passwordEdit->text());
    settings->sync();
    emit settingsChanged();
    close();
}

void MySettings::cancelClicked() {
    close();
}

void MySettings::defaultSettings() {
    hostnameEdit->setText("172.27.100.5");
    portEdit->setText("4444");
    userNameEdit->setText("student.istu");
    passwordEdit->setText("student");
}
