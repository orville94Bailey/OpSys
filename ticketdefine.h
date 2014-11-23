#ifndef TICKETDEFINE_H
#define TICKETDEFINE_H

#include <QWidget>
#include <QPushButton>
#include <QSpinBox>

namespace Ui {
class ticketDefine;
}

class ticketDefine : public QWidget
{
    Q_OBJECT

public:
    explicit ticketDefine(QWidget *parent = 0);
    ~ticketDefine();
    QPushButton *Accept_button,
                *Cancel_button;
    QSpinBox    *Ticket_SpinBox;

private:
    Ui::ticketDefine *ui;
};

#endif // TICKETDEFINE_H
