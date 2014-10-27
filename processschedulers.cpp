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

    connect(quitButton,SIGNAL(clicked()),this,SLOT(hide()));
    qDebug()<<"end of processSchedulers constructor";
}

processSchedulers::~processSchedulers()
{
    delete ui;
    delete quitButton;
    delete SJHButton;
}
