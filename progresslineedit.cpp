#include "progresslineedit.h"
#include <QUrl>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionFrame>

ProgressLineEdit::ProgressLineEdit() : QLineEdit(nullptr) {};

void ProgressLineEdit::updateProgressSlot(int progress) {
    this->progress=progress % 100;
    update();
}

void ProgressLineEdit::paintEvent(QPaintEvent *e) {
    //??? TO-DO:почистить
    QLineEdit::paintEvent(e);
    QPainter painter(this);
    QStyleOptionFrame panel;
    initStyleOption(&panel);
    QRect backgroundRect = style()->subElementRect(QStyle::SE_LineEditContents, &panel, this);
    QColor loadingColor = QColor(65, 205, 82, 122);
    painter.setBrush(loadingColor);
    painter.setPen(Qt::transparent);
    int width = ((backgroundRect.width() + 50) * progress / 100);
    QRect progressRect(backgroundRect.x() - 25, backgroundRect.y() - 5, width, backgroundRect.height() + 10);
    painter.drawRect(progressRect);
}
