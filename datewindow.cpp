#include "datewindow.h"
#include "ui_datewindow.h"
#include <iostream>

dateWindow::dateWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dateWindow)
{
    ui->setupUi(this);
    doneButton = ui->pushButton;

    connect(doneButton, SIGNAL(clicked()), this, SLOT(hide()));
}

dateWindow::~dateWindow()
{
    delete ui;
    delete doneButton;
}
