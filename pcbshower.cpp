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

    connect(quitButton,SIGNAL(clicked()),this,SLOT(doThingsOnHide()));
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

void pcbShower::doThingsOnHide()
{
    currentNode = NULL;
    hide();
}

void pcbShower::updateDisplay(PCB* toShow)
{
    QString priorityString;

    if(toShow!=NULL)
    {
        priorityString = QString::number(toShow->getPriority());

        priorityText->setText(priorityString);
        nameText->setText(toShow->getName());

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
    if( currentNode->nextPCB!=NULL)
    {
        updateDisplay(currentNode->nextPCB);
    }
}

void pcbShower::showPrev()
{   if( currentNode->prevPCB!=NULL)
    {
        updateDisplay(currentNode->prevPCB);
    }
}
