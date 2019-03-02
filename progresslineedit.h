#ifndef DOWNLOADPROGRESS_H
#define DOWNLOADPROGRESS_H

#include <QLineEdit>

class ProgressLineEdit : public QLineEdit {
    //!!!
    Q_OBJECT

public:
    ProgressLineEdit();

public slots:
    void updateProgressSlot(int progress_ratio);
};

#endif // DOWNLOADPROGRESS_H
