#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "quitwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dateDisplayButton = ui ->dateDisplayButton;
    directoryDisplayButton = ui->directoryDisplayButton;
    helpButton = ui->helpButton;
    helpLineEdit = ui->lineEdit;
    quitButton = ui->quitButton;
    pcbToolButton = ui->pcbToolButton;

    connect(quitButton, SIGNAL(clicked()), this, SLOT(quitClicked()));
    connect(dateDisplayButton, SIGNAL(clicked()), this, SLOT(dateClicked()));
    connect(helpButton, SIGNAL(clicked()), this, SLOT(helpClicked()));
    connect(directoryDisplayButton, SIGNAL(clicked()), this, SLOT(directoryClicked()));
    connect(pcbToolButton,SIGNAL(clicked()),this,SLOT(pcbToolsClicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete dateDisplayButton;
    delete directoryDisplayButton;
    delete helpButton;
    delete helpLineEdit;
    delete quitButton;

}

void MainWindow::quitClicked()
{
    exitWindow.show();
}

void MainWindow::dateClicked()
{
    dateShower.show();
}

void MainWindow::directoryClicked()
{
    directoryShower.show();
}

void MainWindow::helpClicked()
{
    //helpShower.show();
}

void MainWindow::pcbToolsClicked()
{
    pcbTools.show();
}
