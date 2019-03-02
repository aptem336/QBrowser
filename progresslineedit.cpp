#include "progresslineedit.h"

ProgressLineEdit::ProgressLineEdit() : QLineEdit(nullptr) {};

void ProgressLineEdit::updateProgressSlot(int progress) {
    double progress_ratio = progress % 100 / 100.0;
    QString style_string = "QLineEdit{background: qlineargradient(x1:0, x2:1, stop:0 #ABCD44, stop: %1 #ABCD44, stop: %2 #FFFFFF, stop:1 #FFFFFF); border: none;}";
    setStyleSheet(style_string.arg(progress_ratio).arg(progress_ratio+0.001));
}
