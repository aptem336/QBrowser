#include "tabpanel.h"
#include <mymainwindow.h>
#include <mybutton.h>

TabPanel::TabPanel(QWidget *parent) : QWidget(parent){
    QVBoxLayout *all = new QVBoxLayout();
    all->setMargin(10);
    QGridLayout *buttons_layout = new QGridLayout();
    buttons_layout->setMargin(10);
    buttons_list = new QList<MyButton *>();
    for (int i=0; i<6; i++){
        MyButton *button = new MyButton();
        connect(button, SIGNAL(clicked(bool)), button, SLOT(pushButtonSlot()));
        connect(button, SIGNAL(pushButtonSignal(QUrl)), this, SLOT(pushSlot(QUrl)));
        buttons_list->append(button);
        buttons_layout->addWidget(button, i/3+1, i%3);
    }
    all->addLayout(buttons_layout);
    setLayout(all);
}
void TabPanel::showSlot(){
    QFile *hfile = new QFile("history");
    QStringList names;
    QStringList urls;
    QList<int> counts;
    if (hfile->open(QIODevice::ReadOnly)) {
        QDataStream read(hfile);
        read>>names;
        read>>urls;
        read>>counts;
    }
//    qDebug()<<names;
//    qDebug()<<urls;
//    qDebug()<<counts;
    QString temp_name;
    QString temp_url;
    double temp_count;
    for (int i=0; i<counts.length(); i++){
        for (int j=0; j<counts.length()-i-1; j++){
            if (counts[j]<counts[j+1]){
                //синхронно переставляем соответствующие элементы всех массивов
                temp_name = names[j];
                names[j]=names[j+1];
                names[j+1]=temp_name;

                temp_url = urls[j];
                urls[j]=urls[j+1];
                urls[j+1]=temp_url;

                temp_count = counts[j];
                counts[j]=counts[j+1];
                counts[j+1]=temp_count;
            }
        }
    }
//    qDebug()<<names;
//    qDebug()<<urls;
//    qDebug()<<counts;
    for (int i=0; i<6; i++) {
        MyButton *button = buttons_list->value(i);
        button->setText("");
        button->setStyleSheet("background:white;width:100%;height:200%;font-size:24pt;font-weight:bold;color:gray;border:1px solid gray;border-radius:10px;");
    }
    for (int i=0; i<names.length(); i++){
        MyButton *button = buttons_list->value(i);
        QString name = names[i];
        //TODO:сделать что-то более приличное?
        if (name.length()>10){
            name = name.left(10);
            name+="...";
        }
        button->setText(name);
        button->url=QUrl(urls[i]);
    }
}

void TabPanel::pushSlot(QUrl url){
    if (!url.isEmpty()){
        emit pushSignal(url);
    }
}
