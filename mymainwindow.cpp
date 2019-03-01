#include "mymainwindow.h"
#include <QWidget>
#include <QNetworkProxy>
#include <QWebHistory>
#include <QNetworkReply>

MyMainWindow::MyMainWindow() : QWidget(nullptr) {
    setMinimumWidth(900);
    setWindowIcon(QIcon(QStringLiteral(":web.png")));
    setWindowTitle("QBrowser");

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

    addressLineEdit = new ProgressLineEdit();

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
    connect(webView, SIGNAL(loadProgress(int)), addressLineEdit, SLOT(updateProgressSlot(int)));
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
    QRegExp reg("_^(?:(?:https?|ftp)://)(?:\\S+(?::\\S*)?@)?(?:(?!10(?:\\.\\d{1,3}){3})(?!127(?:\\.\\d{1,3}){3})(?!169\\.254(?:\\.\\d{1,3}){2})(?!192\\.168(?:\\.\\d{1,3}){2})(?!172\\.(?:1[6-9]|2\\d|3[0-1])(?:\\.\\d{1,3}){2})(?:[1-9]\\d?|1\\d\\d|2[01]\\d|22[0-3])(?:\\.(?:1?\\d{1,2}|2[0-4]\\d|25[0-5])){2}(?:\\.(?:[1-9]\\d?|1\\d\\d|2[0-4]\\d|25[0-4]))|(?:(?:[a-z\\x{00a1}-\\x{ffff}0-9]+-?)*[a-z\\x{00a1}-\\x{ffff}0-9]+)(?:\\.(?:[a-z\\x{00a1}-\\x{ffff}0-9]+-?)*[a-z\\x{00a1}-\\x{ffff}0-9]+)*(?:\\.(?:[a-z\\x{00a1}-\\x{ffff}]{2,})))(?::\\d{2,5})?(?:/[^\\s]*)?$_iuS");
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
    setWindowTitle("QBrowser :: " + title);
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


