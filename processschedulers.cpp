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
    connect(SJHButton,SIGNAL(clicked()),this,SLOT(setTextSJF()));
    connect(FIFO_button,SIGNAL(clicked()),this,SLOT(setTextFIFO()));
    connect(STCF_button,SIGNAL(clicked()),this,SLOT(setTextSTCF()));
    connect(FPPS_button,SIGNAL(clicked()),this,SLOT(setTextFPPS()));
    connect(RR__button,SIGNAL(clicked()),this,SLOT(setTextRR()));
    connect(MLFQ_button,SIGNAL(clicked()),this,SLOT(setTextMLFQ()));
    connect(LS_button,SIGNAL(clicked()),this,SLOT(setTextLS()));
    connect(NONE_button,SIGNAL(clicked()),this,SLOT(setTextNOTSET()));
    qDebug()<<"end of processSchedulers constructor";
}

void processSchedulers::setTextSJF()
{
    CurScheduler_Label->setText("SJF");
}

void processSchedulers::setTextFIFO()
{
    CurScheduler_Label->setText("FIFO");
}

void processSchedulers::setTextSTCF()
{
    CurScheduler_Label->setText("STCF");
}

void processSchedulers::setTextFPPS()
{
    CurScheduler_Label->setText("FPPS");
}

void processSchedulers::setTextRR()
{
    CurScheduler_Label->setText("RR");
}

void processSchedulers::setTextMLFQ()
{
    CurScheduler_Label->setText("MLFQ");
}

void processSchedulers::setTextLS()
{
    CurScheduler_Label->setText("LS");
}

void processSchedulers::setTextNOTSET()
{
    CurScheduler_Label->setText("");
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
