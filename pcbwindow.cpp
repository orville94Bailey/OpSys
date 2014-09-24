#include "pcbwindow.h"
#include "ui_pcbwindow.h"
#include <QtDebug>

pcbWindow::pcbWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pcbWindow)
{
    ui->setupUi(this);

    //button to pointer
    createButton = ui->createButton;
    deleteButton = ui->deleteButton;
    blockButton = ui->blockButton;
    unblockButton = ui->unblockButton;
    suspendButton = ui->suspendButton;
    resumeButton = ui->resumeButton;
    priorityButton = ui->priorityButton;
    pcbShowButton = ui->pcbShower;
    quitButton = ui->quitButton;
    showAllButton = ui->showAll;
    showBlockedButton = ui->showBlocked;
    showReadyButton = ui->showReady;

    //line edit to pointer
    nameLEdit = ui->nameLEdit;
    classLEdit = ui->classLEdit;
    prioritySBox = ui->prioritySBox;

    //connecting buttons to function calls
    connect(createButton, SIGNAL(clicked()),this,SLOT(createPCB()));
    connect(deleteButton, SIGNAL(clicked()),this,SLOT(deletePCB()));
    connect(blockButton, SIGNAL(clicked()),this,SLOT(block()));
    connect(unblockButton,SIGNAL(clicked()),this,SLOT(unblock()));
    connect(suspendButton,SIGNAL(clicked()),this,SLOT(suspend()));
    connect(resumeButton, SIGNAL(clicked()),this,SLOT(resume()));
    connect(priorityButton,SIGNAL(clicked()),this,SLOT(setPriority()));
    connect(pcbShowButton,SIGNAL(clicked()),this,SLOT(showPCBList()));
    connect(quitButton,SIGNAL(clicked()),this,SLOT(hide()));
    connect(priorityButton,SIGNAL(clicked()),this,SLOT(setPriority()));
    connect(showAllButton,SIGNAL(clicked()),this,SLOT(showAllPCB()));
}

pcbWindow::~pcbWindow()
{
    delete ui;
    delete createButton;
    delete deleteButton;
    delete blockButton;
    delete unblockButton;
    delete suspendButton;
    delete resumeButton;
    delete priorityButton;
    delete pcbShowButton;
    delete nameLEdit;
    delete classLEdit;
    delete prioritySBox;
    delete quitButton;

    delete showAllButton;
    delete showBlockedButton;
    delete showReadyButton;
}

void pcbWindow::showPCBList()
{
    showWindow.show();

      showWindow.updateDisplay(control.findPCB(nameLEdit->text().toStdString()));
      showWindow.show();
}

void pcbWindow::createPCB()
{
    //<<"createPCB started";
    if(control.findPCB(nameLEdit->text().toStdString())==NULL)
    {
        if(classLEdit->text().toStdString()=="APPLICATION" || classLEdit->text().toStdString()=="SYSTEM")
        {
            //<<"before insert";
            control.insertPCB(control.setupPCB(nameLEdit->text().toStdString(),prioritySBox->value(),READY));
            //qDebug()<<"after insert";
        }
    }
}

bool pcbWindow::deletePCB()
{
    PCB* toDelete;
    toDelete = control.findPCB(nameLEdit->text().toStdString());
    if(toDelete !=NULL)
    {
        control.RemovePCB(toDelete);
        control.freePCB(toDelete);
        return true;
    }
    return false;
}

bool pcbWindow::block()
{
    PCB* toBlock;
    toBlock = control.findPCB(nameLEdit->text().toStdString());

    if(toBlock!=NULL)
    {
        if(toBlock->getState()==READY || toBlock->getState()==SUSPENDEDREADY)
        {
            control.RemovePCB(toBlock);
            if(toBlock->getState()==READY)
            {
                toBlock->setState(BLOCKED);
            }
            if(toBlock->getState()==SUSPENDEDREADY)
            {
                toBlock->setState(SUSPENDEDBLOCKED);
            }

            control.insertPCB(toBlock);
            return true;
        }
        return false;
    }
    return false;
}

bool pcbWindow::unblock()
{
    PCB* toUnblock;
    toUnblock = control.findPCB(nameLEdit->text().toStdString());

    if(toUnblock != NULL)
    {
        if(toUnblock->getState()==BLOCKED || toUnblock->getState()==SUSPENDEDBLOCKED)
        {
            control.RemovePCB(toUnblock);
            if(toUnblock->getState()==BLOCKED)
            {
                toUnblock->setState(READY);
            }
            if(toUnblock->getState()==SUSPENDEDBLOCKED)
            {
                toUnblock->setState(SUSPENDEDREADY);
            }

            control.insertPCB(toUnblock);
            return true;
        }
        return false;
    }
    return false;
}

bool pcbWindow::suspend()
{
    PCB* toSuspend;
    toSuspend = control.findPCB(nameLEdit->text().toStdString());

    if(toSuspend!=NULL)
    {
        if(toSuspend->getState()==READY)
        {
            toSuspend->setState(SUSPENDEDREADY);
            return true;
        }
        if(toSuspend->getState()==BLOCKED)
        {
            toSuspend->setState(SUSPENDEDBLOCKED);
            return true;
        }
        return false;
    }
    return false;
}

bool pcbWindow::resume()
{
    PCB* toResume;
    toResume = control.findPCB(nameLEdit->text().toStdString());

    if(toResume!=NULL)
    {
        if(toResume->getState()==SUSPENDEDREADY)
        {
            toResume->setState(READY);
            return true;
        }
        if(toResume->getState()==SUSPENDEDBLOCKED)
        {
            toResume->setState(BLOCKED);
            return true;
        }
        return false;
    }
    return false;
}

bool pcbWindow::setPriority()
{
    PCB* toChange;
    toChange = control.findPCB(nameLEdit->text().toStdString());

    if(toChange!=NULL)
    {
        toChange->setPriority(prioritySBox->value());
        return true;
    }
    return false;
}

void pcbWindow::showAllPCB()
{

}

void pcbWindow::showBlockedPCB()
{

}

void pcbWindow::showReadyPCB()
{

}
