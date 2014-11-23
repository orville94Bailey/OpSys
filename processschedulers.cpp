#include "processschedulers.h"
#include "ui_processschedulers.h"
#include <qdebug.h>


processSchedulers::processSchedulers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::processSchedulers)
{
    qDebug()<<"begining of processSchedulers constructor";
    ui->setupUi(this);
    quitButton = ui->quitButton;
    SJHButton = ui->pushButton;
    FIFO_button = ui->FIFO_button;
    STCF_button = ui->STCF_button;
    FPPS_button = ui->FPPS_button;
    RR__button = ui->RR_button;
    MLFQ_button = ui->MLFQ_button;
    LS_button = ui->LS_button;
    NONE_button = ui->NONE_button;
    CurScheduler_Label = ui->CurSchedule_label;


    connect(quitButton, SIGNAL(clicked()),this,SLOT(hide()));

    qDebug()<<"end of processSchedulers constructor";
}

processSchedulers::~processSchedulers()
{
    delete ui;
    delete quitButton;
    delete SJHButton;
    delete FIFO_button;
    delete STCF_button;
    delete FPPS_button;
    delete RR__button;
    delete MLFQ_button;
    delete LS_button;
    delete NONE_button;
    delete CurScheduler_Label;
}
