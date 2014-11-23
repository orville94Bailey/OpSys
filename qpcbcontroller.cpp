#include "qpcbcontroller.h"
#include "ui_qpcbcontroller.h"
#include <qfile.h>
#include <qdebug.h>

QPCBController::QPCBController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QPCBController)
{
    ui->setupUi(this);
    systemTime=0;
    runningPCB=NULL;
    totalTurnaround = 0;
    numOfPCB = 0;


    connect(schedulerWindow.SJHButton,SIGNAL(clicked()),this,SLOT(setSchedulerSFJ()));
    connect(schedulerWindow.FIFO_button,SIGNAL(clicked()),this,SLOT(setSchedulerFIFO()));
    connect(schedulerWindow.STCF_button,SIGNAL(clicked()),this,SLOT(setSchedulerSTCF()));
    connect(schedulerWindow.FPPS_button,SIGNAL(clicked()),this,SLOT(setSchedulerFPPS()));
    connect(schedulerWindow.RR__button,SIGNAL(clicked()),this,SLOT(setSchedulerRR()));
    connect(schedulerWindow.MLFQ_button,SIGNAL(clicked()),this,SLOT(setSchedulerMLFQ()));
    connect(schedulerWindow.LS_button,SIGNAL(clicked()),this,SLOT(setSchedulerLS()));
    connect(schedulerWindow.NONE_button,SIGNAL(clicked()),this,SLOT(setSchedulerNOTSET()));
    connect(quantumWindow.Accept_button, SIGNAL(clicked()),this,SLOT(defineQuantum()));
    connect(ticketWindow.Accept_button, SIGNAL(clicked()),this,SLOT(defineTickets()));
}

void QPCBController::setSchedulerSFJ()
{
    setCurrentScheduler(SJF);
}

void QPCBController::setSchedulerFIFO()
{
    setCurrentScheduler(FIFO);
}

void QPCBController::setSchedulerSTCF()
{
    setCurrentScheduler(STCF);
}

void QPCBController::setSchedulerFPPS()
{
    setCurrentScheduler(FPPS);
}

void QPCBController::setSchedulerRR()
{
    setCurrentScheduler(RR);
}

void QPCBController::setSchedulerMLFQ()
{
    setCurrentScheduler(MLFQ);
}

void QPCBController::setSchedulerLS()
{
    setCurrentScheduler(LS);
}

void QPCBController::setSchedulerNOTSET()
{
    setCurrentScheduler(NOTSET);
}

QPCBController::~QPCBController()
{
    delete ui;
}

PCB* QPCBController::allocatePCB()
{
    PCB* holder;
    holder=new PCB;
    //qDebug()<<"allocatePCB running";
    return holder;
}

PCB* QPCBController::setupPCB(QString processName,QString pcbClass, int priority,int memory,int timeRemaining,int timeOfArrival,int cpuPercent)
{
    PCB* holder;
    if(findPCB(processName)==NULL)
    {
        holder = allocatePCB();

        holder->setName(processName);
        if(pcbClass[0] == 'A')
        {
            holder->setClass(APPLICATION);
        }
        else
        {
            holder->setClass(SYSTEM);
        }
        holder->setPriority(priority);
        holder->setMem(memory);
        holder->setTimeRemaining(timeRemaining);
        holder->setTimeOfArrival(timeOfArrival);
        holder->setPercentCPU(cpuPercent);
        holder->setState(BLOCKED);
    }
    //qDebug()<<"setupPCB returned successfully";
    return holder;
}

PCB* QPCBController::findPCB(QString name)
{
    PCB* holder=NULL;
    holder = readyList.findPCB(name);
    //qDebug()<<holder;
    if(holder == NULL)
    {
        //qDebug()<<"holder == NULL";
        holder = blockedList.findPCB(name);
    }
    return holder;
}

void QPCBController::freePCB(PCB* nodeToKill)
{
    if(nodeToKill!=NULL)
    {
        nodeToKill->nextPCB->prevPCB = nodeToKill->prevPCB;
        nodeToKill->prevPCB->nextPCB = nodeToKill->nextPCB;

        delete nodeToKill;
        nodeToKill = NULL;
    }

}

bool QPCBController::insertPCB(PCB *nodeToInsert)
{
    if(nodeToInsert!=NULL)
    {
        switch(nodeToInsert->getState())
        {
        case READY:

        case SUSPENDEDREADY:
            readyList.push(nodeToInsert);
            return true;
            break;

        case BLOCKED:

        case SUSPENDEDBLOCKED:
            blockedList.push(nodeToInsert);
            return true;
            break;

        default:
            break;
        }
    }
    return false;
}

void QPCBController::removePCB(PCB* nodeToRemove)
{
    if(readyList.findPCB(nodeToRemove->getName())!=NULL)
    {
        qDebug()<<"entered ready remove";
        readyList.removePCB(nodeToRemove);
        qDebug()<<"removed from ready list";
    }
    else if(blockedList.findPCB(nodeToRemove->getName())!=NULL)
    {
        qDebug()<<"entered blocked remove";
        blockedList.removePCB(nodeToRemove);
        qDebug()<<"removed from blocked list";
    }
}

void QPCBController::readFile(QString fileName)
{
    QString processName,
            pcbClass;

    int priority,
        memory,
        timeRemaining,
        timeOfArrival,
        cpuPercent;

    QFile toOpen(QCoreApplication::applicationDirPath()+"/"+fileName);
    if(toOpen.exists())
    {
        if(!toOpen.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return;
        }
        QTextStream toRead(&toOpen);
        while (!toRead.atEnd())
        {
            toRead>>processName;
            toRead>>pcbClass;
            toRead>>priority;
            toRead>>memory;
            toRead>>timeRemaining;
            toRead>>timeOfArrival;
            toRead>>cpuPercent;
            insertPCB(setupPCB(processName,pcbClass,priority,memory,timeRemaining,timeOfArrival,cpuPercent));
            processName = "";
        }
        toOpen.close();
    }
    else
    {
        return;
    }
}

PCB* QPCBController::shortestJob()
{
    int iterations = readyList.listLength();
    PCB* shortestJob;
    int shortestJobTime;
    PCB* holder = NULL;

    shortestJob = NULL;
    if(iterations>0)
    {
        shortestJob = readyList.firstNode;
        shortestJobTime = shortestJob->getTimeRemaining();
        holder = shortestJob;
    }
    for(int l=0; l<iterations;l++)
    {
        if(shortestJobTime>holder->getTimeRemaining())
        {
            shortestJob = holder;
            shortestJobTime = shortestJob->getTimeRemaining();
        }
        if(holder->nextPCB!=NULL)
        {
            holder = holder->nextPCB;
        }
    }
    removePCB(shortestJob);
    return shortestJob;
}

PCB* QPCBController::highestPriority()
{
    int iterations = readyList.listLength();
    PCB* highestPriority;
    int highestPriorityInt;
    PCB* holder = NULL;

    highestPriority = NULL;
    if(iterations>0)
    {
        highestPriority = readyList.firstNode;
        highestPriorityInt = highestPriority->getPriority();
        holder = highestPriority;
    }
    for(int l=0; l<iterations;l++)
    {
        if(highestPriorityInt>holder->getPriority())
        {
            highestPriority = holder;
            highestPriorityInt = highestPriority->getPriority();
        }
        if(holder->nextPCB!=NULL)
        {
            holder = holder->nextPCB;
        }
    }
    removePCB(highestPriority);
    return highestPriority;
}

PCB* QPCBController::checkForArrivals()
{
    PCB* holder;
    holder = NULL;
    if(blockedList.firstNode!=NULL)
    {
        holder = blockedList.firstNode;
        while (holder!=NULL)
        {
            if(holder->getTimeOfArrival()==systemTime)
                return holder;
            holder = holder->nextPCB;
        }
    }
    return NULL;
}

void QPCBController::step(SchedulerType SType)
{
    switch(SType)
    {
    case SJF:
        if(runningPCB->getTimeRemaining()<=0 || runningPCB==NULL)
        {
            freePCB(runningPCB);
            setAsRunning(shortestJob());
        }
        break;
    case FIFO:
        if(runningPCB->getTimeRemaining()<=0 || runningPCB==NULL)
        {
            freePCB(runningPCB);
            setAsRunning(readyList.pop());
        }
        break;
    case STCF:
        if(runningPCB->getTimeRemaining()<=0 || runningPCB==NULL)
        {
            freePCB(runningPCB);
            setAsRunning(shortestJob());
        }
        break;
    case FPPS:
        if(runningPCB->getTimeRemaining()<=0 || runningPCB==NULL)
        {
            freePCB(runningPCB);
            setAsRunning(highestPriority());
        }
        break;
    case RR:

        if(runningPCB->getTimeRemaining()==0)
        {
            freePCB(runningPCB);
            setAsRunning(readyList.pop());
        }
        else if(runningPCB==NULL)
        {
            setAsRunning(readyList.pop());
        }
        else//quantum has run out
        {
            runningPCB->setState(READY);
            insertPCB(runningPCB);
            setAsRunning(readyList.pop());
        }
        break;
    case MLFQ:
        if(runningPCB->getTimeRemaining()==0)
        {
            freePCB(runningPCB);
            setAsRunning(highestPriority());
        }
        else if(runningPCB==NULL)
        {
            setAsRunning(highestPriority());
        }
        else//quantum has run out
        {
            runningPCB->setState(READY);
            insertPCB(runningPCB);
            if(runningPCB->getPriority()>-127)
            {
                runningPCB->setPriority(runningPCB->getPriority()-1);
            }
            setAsRunning(readyList.pop());
        }
        break;
    case LS:
        break;
    case NOTSET:
        qDebug()<<"this isn't supposed to happen, like ever";
        break;
    }

    insertNewArrivals();

    if(runningPCB!=NULL)
    {
        runningPCB->setTimeRemaining(runningPCB->getTimeRemaining()-1);
    }

    systemTime++;
}

void QPCBController::insertNewArrivals()
{
    PCB* holder;
    holder = NULL;

    while(checkForArrivals()!=NULL)
    {
        holder = checkForArrivals();
        removePCB(holder);

        if(holder->getState() == BLOCKED)
        {
            holder->setState(READY);
        }
        if(holder->getState() == SUSPENDEDBLOCKED)
        {
            holder->setState(SUSPENDEDREADY);
        }

        insertPCB(holder);
    }
}

void QPCBController::setAsRunning(PCB* holder)
{
    if(runningPCB==NULL)
    {
        holder->setState(RUNNING);
        runningPCB = holder;
    }
}

void QPCBController::setCurrentScheduler(SchedulerType scheduler)
{
    currentScheduler = scheduler;
    switch(scheduler)
    {
    case SJF:
        qDebug()<<"SJF";
        schedulerWindow.CurScheduler_Label->setText("SJF");
        break;
    case FIFO:
        schedulerWindow.CurScheduler_Label->setText("FIFO");
        break;
    case STCF:
        schedulerWindow.CurScheduler_Label->setText("STCF");
        break;
    case FPPS:
        schedulerWindow.CurScheduler_Label->setText("FPPS");
        break;
    case RR:
        schedulerWindow.CurScheduler_Label->setText("RR");
        do
        {
            setCurrentQuantum();
        }while(quantum<1);
        break;
    case MLFQ:
        schedulerWindow.CurScheduler_Label->setText("MLFQ");
        do
        {
            setCurrentQuantum();
        }while(quantum<1);
        break;
    case LS:
        schedulerWindow.CurScheduler_Label->setText("LS");
        do
        {
            setCurrentTickets();
        }while(tickets<1);
        break;
    case NOTSET:
        schedulerWindow.CurScheduler_Label->setText("");
        break;
    }
    schedulerWindow.update();
}

void QPCBController::setCurrentQuantum()
{
    quantumWindow.show();
}

void QPCBController::defineQuantum()
{
    quantum = quantumWindow.Quantum_SpinBox->value();
}

void QPCBController::setCurrentTickets()
{
    ticketWindow.show();
}

void QPCBController::defineTickets()
{
    tickets = ticketWindow.Ticket_SpinBox->value();
}

void QPCBController::changePriorities()
{
    int readyLength,
        blockedLength;

    readyLength = readyList.listLength();
    blockedLength = blockedList.listLength();
    PCB* holder;

    holder = readyList.firstNode;
    for(int x = 0;x<readyLength;x++)
    {
        if(holder->getPriority()<=0)
        {
            holder->setPriority(holder->getPriority()+128);
        }
        if(holder->nextPCB!=NULL)
        {
            holder = holder->nextPCB;
        }
    }

    holder = blockedList.firstNode;
    for(int x=0;x<blockedLength;x++)
    {
        if(holder->getPriority()<=0)
        {
            holder->setPriority(holder->getPriority()+128);
        }
        if(holder->nextPCB!=NULL)
        {
            holder = holder->nextPCB;
        }
    }
}
