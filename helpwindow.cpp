#include "helpwindow.h"
#include "ui_helpwindow.h"

helpWindow::helpWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::helpWindow)
{
    ui->setupUi(this);
    connect(closeButton,SIGNAL(clicked()),this,SLOT(hide()));
}

helpWindow::~helpWindow()
{
    delete ui;
    delete closeButton;
}
