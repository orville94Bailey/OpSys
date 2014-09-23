#include "quitwindow.h"
#include "ui_quitwindow.h"
#include <QDialog>

quitWindow::quitWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::quitWindow)
{
    ui->setupUi(this);
    exampleDialog = new QDialog;

    closeButton = ui->closeButton;
    cancelButton = ui->pushButton_2;

    connect(closeButton, SIGNAL(clicked()), this, SLOT(quitButtonClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(hide()));
}

quitWindow::~quitWindow()
{
    delete ui;
    delete closeButton;
    delete cancelButton;
    delete exampleDialog;
}

void quitWindow::quitButtonClicked()
{
    QApplication::quit();
}
