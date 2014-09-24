#include "pcbshower.h"
#include "ui_pcbshower.h"
#include <QDebug>

pcbShower::pcbShower(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pcbShower)
{
    ui->setupUi(this);
    quitButton = ui->quitButton;
    nextPCB = ui->nextButton;
    prevPCB = ui->prevButton;
    nameText = ui->nameText;
    classText = ui->classText;
    stateText = ui->stateText;
    priorityText = ui->priorityText;
    currentNode = NULL;

    connect(quitButton,SIGNAL(clicked()),this,SLOT(hide()));
    connect(nextPCB,SIGNAL(clicked()),this,SLOT(showNext()));
    connect(prevPCB,SIGNAL(clicked()),this,SLOT(showPrev()));
}

pcbShower::~pcbShower()
{
    delete ui;
    delete quitButton;
    delete nextPCB;
    delete prevPCB;
    delete nameText;
    delete classText;
    delete stateText;
    delete priorityText;
}

void pcbShower::updateDisplay(PCB* toShow)
{
    QString nameString,
            classString,
            priorityString;


    qDebug()<<toShow;
    if(toShow!=NULL)
    {
        nameString = QString::fromStdString(toShow->getName());
        priorityString = QString::number(toShow->getPriority());
        priorityText->setText(priorityString);

        nameText->setText(nameString);
        switch(toShow->getPCBClass())
        {
        case APPLICATION:
            classText->setText("Application");
            break;
        case SYSTEM:
            classText->setText("System");
            break;
        }

        switch(toShow->getState())
        {
        case READY:
            stateText->setText("Ready");
            break;
        case RUNNING:
            stateText->setText("Running");
            break;
        case BLOCKED:
            stateText->setText("Blocked");
            break;
        case SUSPENDEDBLOCKED:
            stateText->setText("Suspended Blocked");
            break;
        case SUSPENDEDREADY:
            stateText->setText("Suspended Ready");
        default:
            stateText->setText("Problem Occured Setting Text");

        }
        currentNode = toShow;

    }
}

void pcbShower::showNext()
{
    updateDisplay(currentNode->nextPCB);
}

void pcbShower::showPrev()
{
    updateDisplay(currentNode->prevPCB);
}
