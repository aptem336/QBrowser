#include "mymainwindow.h"
#include <QWidget>
#include <QNetworkProxy>
#include <QWebHistory>
#include <QNetworkReply>

const QString MyMainWindow::browserName = QString("QBrowser");

MyMainWindow::MyMainWindow(QWidget *parent) : QWidget(parent) {
    setMinimumWidth(900);
    setWindowIcon(QIcon(QStringLiteral(":web.png")));
    setWindowTitle(browserName);

    backButton = new QPushButton();
    backButton->setIcon(QIcon(QStringLiteral(":back.png")));
    backButton->setStyleSheet("border: none; padding: 5px;");

    forwardButton = new QPushButton();
    forwardButton->setIcon(QIcon(QStringLiteral(":forward.png")));
    forwardButton->setStyleSheet("border: none; padding: 5px;");

    reloadButton = new QPushButton();
    reloadButton->setIcon(QIcon(QStringLiteral(":reload.png")));
    reloadButton->setStyleSheet("border: none; padding: 5px;");

    backButton->setEnabled(false);
    forwardButton->setEnabled(false);
    reloadButton->setEnabled(false);

    addressLineEdit = new QLineEdit();

    webView = new QWebView();
    webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    webView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout *toolbarLayout = new QHBoxLayout();
    toolbarLayout->setContentsMargins(5, 5, 5, 5);

    QVBoxLayout *innerLayout = new QVBoxLayout();
    innerLayout->setContentsMargins(5, 0, 5, 5);

    innerLayout->addLayout(toolbarLayout);
    innerLayout->addWidget(webView);

    toolbarLayout->addWidget(backButton);
    toolbarLayout->addWidget(forwardButton);
    toolbarLayout->addWidget(reloadButton);
    toolbarLayout->addWidget(addressLineEdit);

    setLayout(innerLayout);

    connect(addressLineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressedSlot()));
    connect(webView, SIGNAL(linkClicked(QUrl)), this, SLOT(linkClickedSlot(QUrl)));

    connect(webView, SIGNAL(urlChanged(QUrl)), this, SLOT(urlChangedSlot(QUrl)));
    connect(webView, SIGNAL(titleChanged(QString)), this, SLOT(titleChangedSlot(QString)));

    connect(backButton, SIGNAL(clicked(bool)), this, SLOT(backSlot()));
    connect(forwardButton, SIGNAL(clicked(bool)), this, SLOT(forwardSlot()));
    connect(reloadButton, SIGNAL(clicked(bool)), this, SLOT(reloadSlot()));

    webView->load(QUrl("https://google.com"));
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

void MyMainWindow::linkClickedSlot(QUrl url){
    webView->load(url);
}

void MyMainWindow::urlChangedSlot(QUrl url) {
    reloadButton->setEnabled(true);
    addressLineEdit->setText(url.toString());
    backButton->setEnabled(webView->history()->canGoBack());
    forwardButton->setEnabled(webView->history()->canGoForward());
}

void MyMainWindow::titleChangedSlot(QString title) {
    setWindowTitle(browserName + " :: " + title);
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


