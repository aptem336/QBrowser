#include "mymainwindow.h"
#include "mysettings.h"
#include <QWidget>
#include <QNetworkProxy>
#include <QWebHistory>
#include <QNetworkReply>
#include <shlobj.h>

const QString MyMainWindow::browserName = QString("QBrowser");

MyMainWindow::MyMainWindow(QWidget *parent) : QWidget(parent) {
    setMinimumWidth(900);
    setWindowIcon(QIcon(QStringLiteral(":web.png")));
    setWindowTitle(browserName);

    this->setStyleSheet("QPushButton::menu-indicator {"
            "image: url(myindicator.png);"
            "subcontrol-position: right center;"
            "subcontrol-origin: padding;"
            "left: -2px;"
            "}");

    backButton = new QPushButton();
    backButton->setIcon(QIcon(QStringLiteral(":back.png")));
    backButton->setStyleSheet("border: none; padding: 5px;");

    nextButton = new QPushButton();
    nextButton->setIcon(QIcon(QStringLiteral(":forward.png")));
    nextButton->setStyleSheet("border: none; padding: 5px;");

    reloadButton = new QPushButton();
    reloadButton->setIcon(QIcon(QStringLiteral(":reload.png")));
    reloadButton->setStyleSheet("border: none; padding: 5px;");

    stopButton = new QPushButton();
    stopButton->setIcon(QIcon(QStringLiteral(":stop.png")));
    stopButton->setStyleSheet("border: none; padding: 5px;");

    settingsButton = new QPushButton();
    settingsButton->setIcon(QIcon(QStringLiteral(":settings.png")));
    settingsButton->setStyleSheet("border: none; padding: 5px;");

    backButton->setEnabled(false);
    nextButton->setEnabled(false);
    reloadButton->setEnabled(false);
    stopButton->setEnabled(false);

    addressLineEdit = new QLineEdit();

    webView = new QWebView();
    readSettings();
    webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    webView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout *toolbarLayout = new QHBoxLayout();
    toolbarLayout->setContentsMargins(5, 5, 5, 5);

    QVBoxLayout *innerLayout = new QVBoxLayout();
    innerLayout->setContentsMargins(5, 0, 5, 5);

    innerLayout->addLayout(toolbarLayout);
    innerLayout->addWidget(webView);

    toolbarLayout->addWidget(backButton);
    toolbarLayout->addWidget(nextButton);
    toolbarLayout->addWidget(reloadButton);
    toolbarLayout->addWidget(stopButton);
    toolbarLayout->addWidget(addressLineEdit);
    toolbarLayout->addWidget(settingsButton);

    setLayout(innerLayout);

    connect(backButton, SIGNAL(clicked(bool)), this, SLOT(backSlot()));
    connect(nextButton, SIGNAL(clicked(bool)), this, SLOT(forwardSlot()));
    connect(reloadButton, SIGNAL(clicked(bool)), this, SLOT(reloadSlot()));
    connect(stopButton, SIGNAL(clicked(bool)), this, SLOT(stopSlot()));
    connect(settingsButton, SIGNAL(clicked(bool)), this, SLOT(settingsOpenSlot()));

    connect(addressLineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressedSlot()));

    connect(webView, SIGNAL(linkClicked(QUrl)), this, SLOT(loadSlot(QUrl)));


    connect(webView, SIGNAL(urlChanged(QUrl)), this, SLOT(urlChangedSlot(QUrl)));
    connect(webView, SIGNAL(titleChanged(QString)), this, SLOT(titleChangedSlot(QString)));
    connect(webView, SIGNAL(loadStarted()), this, SLOT(loadStartedSlot()));
    connect(webView, SIGNAL(loadFinished(bool)), this, SLOT(loadFinishedSlot()));

    webView->load(QUrl("http://google.com"));
}

void MyMainWindow::backSlot(){
    webView->back();
}

void MyMainWindow::forwardSlot(){
    webView->forward();
}

void MyMainWindow::reloadSlot(){
    webView->reload();
}

void MyMainWindow::stopSlot(){
    webView->stop();
}

void MyMainWindow::returnPressedSlot() {
    QString addr = addressLineEdit->text();
    QRegExp reg("(?:(?:https?|ftp|telnet)://(?:[a-z0-9_-]{1,32}(?::[a-z0-9_-]{1,32})?@)?)?(?:(?:[a-z0-9-]{1,128}.)+(?:ru|su|com|net|org|mil|edu|arpa|gov|biz|info|aero|inc|name|[a-z]{2})|(?!0)(?:(?!0[^.]|255)[0-9]{1,3}.){3}(?!0|255)[0-9]{1,3})(?:/[a-z0-9.,_@%&?+=~/-]*)?(?:#[^ '\"&]*)?");
    if (!reg.exactMatch(addr)) {
        addr = "https://www.google.ru/search?q=" + addr + "&oq=" + addr + "&ie=UTF-8";
    }
    if (!(addr.startsWith("http://") || addr.startsWith("https://"))) {
        addr = "http://" + addr;
    }
    webView->load(QUrl(addr));
}

void MyMainWindow::loadSlot(QUrl url){
    webView->load(url);
}

void MyMainWindow::urlChangedSlot(QUrl url) {
    addressLineEdit->setText(url.toString());
    backButton->setEnabled(webView->history()->canGoBack());
    nextButton->setEnabled(webView->history()->canGoForward());
}

void MyMainWindow::titleChangedSlot(QString title) {
    setWindowTitle(browserName + " :: " + title);
}

void MyMainWindow::loadStartedSlot() {
    reloadButton->setEnabled(true);
    stopButton->setEnabled(true);
}

void MyMainWindow::loadFinishedSlot() {
    stopButton->setEnabled(false);
}

void MyMainWindow::settingsOpenSlot() {
    MySettings *dialog = new MySettings(settings, this);
    dialog->show();
    connect(dialog, SIGNAL(settingsChanged()), this, SLOT(changeSettings()));
}

void MyMainWindow::readSettings() {
    QString settingsPath = "./";
    // В commonAppDataPath будет храниться путь к системной папке с данными программ ProgramData
    wchar_t commonAppDataPath[MAX_PATH];
    // SHGetSpecialFolderPath возвращает путь папки, определяемой ее CSIDL (лист постоянных специальных индентификаторов элемента)
    // Первый аргумент - зарезервирован
    // Второй аргумент - указатель на строку с нулевых завершением, которая получает диск и путь к указанной папке
    // (буфер должен содержать не менее MAX_PATH символов)
    // Третий аргумент - CSIDL, идентифицирующий интересующую папку
    // Четвёртый аргумент - указывает, должна ли создаваться папка, если она не существует
    if (SHGetSpecialFolderPath(0, commonAppDataPath, CSIDL_COMMON_APPDATA, FALSE)) {
        settingsPath = QString::fromWCharArray(commonAppDataPath) + QDir::separator() +
                "QBrowser" + QDir::separator();
        if (!QDir(settingsPath).exists()) {
            QDir(QString::fromWCharArray(commonAppDataPath)).mkpath(settingsPath);
        }
    }
    /* =======================
     * = Структура ini-файла =
     * =======================
     *   [proxy]
     *   useproxy=false
     *   host=172.27.100.5
     *   port=4444
     *   user=student.istu
     *   password=student
     */
    settings = new QSettings(settingsPath + "settings.ini", QSettings::IniFormat, this);
    changeSettings();
}

void MyMainWindow::changeSettings() {
    if (settings->value("proxy/useProxy").toBool()) {
        webView->page()->networkAccessManager()->setProxy(QNetworkProxy(QNetworkProxy::HttpProxy,
                settings->value("proxy/host").toString(),
                settings->value("proxy/port").toInt(),
                settings->value("proxy/user").toString(),
                settings->value("proxy/password").toString()));
    } else {
        webView->page()->networkAccessManager()->setProxy(QNetworkProxy(QNetworkProxy::NoProxy));
    }
}


