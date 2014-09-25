#include "processschedulers.h"
#include "ui_processschedulers.h"

processSchedulers::processSchedulers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::processSchedulers)
{
    ui->setupUi(this);
    quitButton = ui->quitButton;

    connect(quitButton,SIGNAL(clicked()),this,SLOT(hide()));
}

processSchedulers::~processSchedulers()
{
    delete ui;
}
