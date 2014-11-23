#include "ticketdefine.h"
#include "ui_ticketdefine.h"

ticketDefine::ticketDefine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ticketDefine)
{
    ui->setupUi(this);
    Accept_button = ui->Accept_button;
    Cancel_button = ui->Cancel_button;
    Ticket_SpinBox = ui->spinBox;

    connect(Cancel_button,SIGNAL(clicked()),this,SLOT(close()));
}

ticketDefine::~ticketDefine()
{
    delete ui;
    delete Accept_button;
    delete Cancel_button;
    delete Ticket_SpinBox;
}
