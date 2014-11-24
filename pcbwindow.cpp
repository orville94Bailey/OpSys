#include "pcbwindow.h"
#include "ui_pcbwindow.h"
#include <QtDebug>

pcbWindow::pcbWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pcbWindow)
{
    qDebug()<<"begining of pcbWindow constructor";
    ui->setupUi(this);

    control = new QPCBController();
    scheduler = new processSchedulers;
    ticketWindow = new ticketDefine;
    quantumWindow = new QuantumDefineWindow;

    //button to pointer
    //createButton = ui->createButton;
    //deleteButton = ui->deleteButton;
    //blockButton = ui->blockButton;
    //unblockButton = ui->unblockButton;
    suspendButton = ui->suspendButton;
    resumeButton = ui->resumeButton;
    priorityButton = ui->priorityButton;
    pcbShowButton = ui->pcbShower;
    quitButton = ui->quitButton;
    showBlockedButton = ui->showBlocked;
    showReadyButton = ui->showReady;
    timeRemainingSBox = ui->timeRemainingSBox;
    schedulerButton = ui->schedulerButton;

    //line edit to pointer
    nameLEdit = ui->nameLEdit;
    classLEdit = ui->classLEdit;
    prioritySBox = ui->prioritySBox;
    fileNameLEdit = ui->fileNameLEdit;
    readFileButton = ui->readFileButton;
    reqMemSBox = ui->reqMemSBox;

    //connecting buttons to function calls
    //connect(createButton, SIGNAL(clicked()),this,SLOT(createPCB()));
    //connect(deleteButton, SIGNAL(clicked()),this,SLOT(deletePCB()));
    //connect(blockButton, SIGNAL(clicked()),this,SLOT(block()));
    //connect(unblockButton,SIGNAL(clicked()),this,SLOT(unblock()));
    connect(suspendButton,SIGNAL(clicked()),this,SLOT(suspend()));
    connect(resumeButton, SIGNAL(clicked()),this,SLOT(resume()));
    connect(priorityButton,SIGNAL(clicked()),this,SLOT(setPriority()));
    connect(pcbShowButton,SIGNAL(clicked()),this,SLOT(showPCBList()));
    connect(quitButton,SIGNAL(clicked()),this,SLOT(hide()));
    connect(priorityButton,SIGNAL(clicked()),this,SLOT(setPriority()));
    connect(showBlockedButton,SIGNAL(clicked()),this,SLOT(showBlockedPCB()));
    connect(showReadyButton,SIGNAL(clicked()),this,SLOT(showReadyPCB()));
    connect(readFileButton,SIGNAL(clicked()),this,SLOT(readFile()));
    connect(schedulerButton,SIGNAL(clicked()),this,SLOT(showSchedulers()));
    qDebug()<<"before fuckup?";

    connect(scheduler->SJHButton,SIGNAL(clicked()),control,SLOT(setSchedulerSFJ()));
    connect(scheduler->FIFO_button,SIGNAL(clicked()),control,SLOT(setSchedulerFIFO()));
    connect(scheduler->STCF_button,SIGNAL(clicked()),control,SLOT(setSchedulerSTCF()));
    connect(scheduler->FPPS_button,SIGNAL(clicked()),control,SLOT(setSchedulerFPPS()));
    connect(scheduler->RR__button,SIGNAL(clicked()),control,SLOT(setSchedulerRR()));
    connect(scheduler->MLFQ_button,SIGNAL(clicked()),control,SLOT(setSchedulerMLFQ()));
    connect(scheduler->LS_button,SIGNAL(clicked()),control,SLOT(setSchedulerLS()));
    connect(scheduler->NONE_button,SIGNAL(clicked()),control,SLOT(setSchedulerNOTSET()));
    connect(quantumWindow->Accept_button, SIGNAL(clicked()),this,SLOT(setQuantum()));
    connect(ticketWindow->Accept_button, SIGNAL(clicked()),this,SLOT(setTickets()));
    connect(scheduler->RR__button,SIGNAL(clicked()),quantumWindow,SLOT(show()));
    connect(scheduler->MLFQ_button,SIGNAL(clicked()),quantumWindow,SLOT(show()));
    connect(scheduler->LS_button,SIGNAL(clicked()),ticketWindow,SLOT(show()));
    connect(quantumWindow->Accept_button, SIGNAL(clicked()),quantumWindow,SLOT(hide()));
    connect(ticketWindow->Accept_button, SIGNAL(clicked()),ticketWindow,SLOT(hide()));
    connect(ui->Run_button,SIGNAL(clicked()),this,SLOT(run()));
    qDebug()<<"end of pcbWindow constructor";
}

pcbWindow::~pcbWindow()
{
    delete ui;
    //delete createButton;
    //delete deleteButton;
    //delete blockButton;
    //delete unblockButton;
    delete suspendButton;
    delete resumeButton;
    delete priorityButton;
    delete pcbShowButton;
    delete nameLEdit;
    delete classLEdit;
    delete prioritySBox;
    delete quitButton;
    delete timeRemainingSBox;
    delete readFileButton;

    delete showBlockedButton;
    delete showReadyButton;
    delete fileNameLEdit;
    delete reqMemSBox;
}

void pcbWindow::run()
{
    if((control->quantum > 0 && control->currentScheduler==RR || control->currentScheduler==MLFQ) ||
            (control->currentScheduler!=MLFQ && control->currentScheduler!=RR))
    {
        while(control->readyList.listLength()>0 &&
              control->blockedList.listLength()>0)
        {
            control->step();
        }
    }
}

void pcbWindow::setQuantum()
{
    control->quantum = quantumWindow->Quantum_SpinBox->value();
    qDebug()<<control->quantum;
}

void pcbWindow::setTickets()
{
    control->tickets = ticketWindow->Ticket_SpinBox->value();
    qDebug()<<control->tickets;
}

void pcbWindow::showPCBList()
{
      showWindow.updateDisplay(control->findPCB(nameLEdit->text()));
      showWindow.show();
}

void pcbWindow::createPCB()
{
    if(control->findPCB(nameLEdit->text())==NULL)
    {
        if(classLEdit->text().toStdString()=="APPLICATION" || classLEdit->text().toStdString()=="SYSTEM")
        {
            control->insertPCB(control->setupPCB(nameLEdit->text(),classLEdit->text(),prioritySBox->value(), reqMemLEdit->text().toInt(),timeRemainingSBox->value(),0,1));
        }
    }
}

bool pcbWindow::deletePCB()
{
    PCB* toDelete;
    toDelete = control->findPCB(nameLEdit->text());
    if(toDelete !=NULL)
    {
        control->removePCB(toDelete);
        control->freePCB(toDelete);
        return true;
    }
    return false;
}

bool pcbWindow::block()
{
    PCB* toBlock;
    toBlock = control->findPCB(nameLEdit->text());

    if(toBlock!=NULL)
    {
        if(toBlock->getState()==READY || toBlock->getState()==SUSPENDEDREADY)
        {
            qDebug()<<toBlock->getState();
            control->removePCB(toBlock);
            if(toBlock->getState()==READY)
            {
                qDebug()<<"attempting block";
                toBlock->setState(BLOCKED);
                qDebug()<<"now blocked";
            }
            if(toBlock->getState()==SUSPENDEDREADY)
            {
                toBlock->setState(SUSPENDEDBLOCKED);
            }

            control->insertPCB(toBlock);
            return true;
        }
        return false;
    }
    return false;
}

bool pcbWindow::unblock()
{
    PCB* toUnblock;
    toUnblock = control->findPCB(nameLEdit->text());

    if(toUnblock != NULL)
    {
        if(toUnblock->getState()==BLOCKED || toUnblock->getState()==SUSPENDEDBLOCKED)
        {
            control->removePCB(toUnblock);
            if(toUnblock->getState()==BLOCKED)
            {
                toUnblock->setState(READY);
            }
            if(toUnblock->getState()==SUSPENDEDBLOCKED)
            {
                toUnblock->setState(SUSPENDEDREADY);
            }

            control->insertPCB(toUnblock);
            return true;
        }
        return false;
    }
    return false;
}

bool pcbWindow::suspend()
{
    PCB* toSuspend;
    toSuspend = control->findPCB(nameLEdit->text());

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
    toResume = control->findPCB(nameLEdit->text());

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
    toChange = control->findPCB(nameLEdit->text());

    if(toChange!=NULL)
    {
        toChange->setPriority(prioritySBox->value());
        return true;
    }
    return false;
}

void pcbWindow::showBlockedPCB()
{
    showWindow.updateDisplay(control->blockedList.firstNode);
    showWindow.show();
}

void pcbWindow::showReadyPCB()
{
    showWindow.updateDisplay(control->readyList.firstNode);
    showWindow.show();
}

void pcbWindow::readFile()
{
    if (fileNameLEdit->text()!="")
    {
        control->readFile(fileNameLEdit->text());
    }
}

void pcbWindow::showSchedulers()
{
    scheduler->show();
}
