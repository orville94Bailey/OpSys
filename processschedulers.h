#ifndef PROCESSSCHEDULERS_H
#define PROCESSSCHEDULERS_H

#include <QWidget>
#include <QPushButton>
#include "qpcbcontroller.h"

namespace Ui {
class processSchedulers;
}

class processSchedulers : public QWidget
{
    Q_OBJECT

private slots:

public:
    explicit processSchedulers(QWidget *parent = 0);
    ~processSchedulers();
    QPushButton *quitButton,
    *SJHButton;

private:
    Ui::processSchedulers *ui;

    QPCBController *controlPointer;
};

#endif // PROCESSSCHEDULERS_H
