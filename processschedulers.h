#ifndef PROCESSSCHEDULERS_H
#define PROCESSSCHEDULERS_H

#include <QWidget>
#include <QPushButton>

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

private:
    Ui::processSchedulers *ui;
    QPushButton *quitButton,
                *SJHButton;
};

#endif // PROCESSSCHEDULERS_H
