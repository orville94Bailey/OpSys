#include "qpcbcontroller.h"
#include "ui_qpcbcontroller.h"
#include <qfile.h>
#include <qdebug.h>
#include <qglobal.h>
#include <QTime>

QPCBController::QPCBController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QPCBController)
{
    ui->setupUi(this);
    systemTime=0;
    runningPCB=NULL;
    totalTurnaround = 0;
    numOfPCB = 0;

    time = QTime::currentTime();
    qsrand((uint)time.msec());
}

int QPCBController::generateNumber(int low, int high)
{
    return qrand() % ((high+1)-low)+low;
}

void QPCBController::setSchedulerSFJ()
{
    qDebug()<<"butt nuts";
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
    qDebug()<<QCoreApplication::applicationDirPath()+"/"+fileName;
    if(toOpen.exists())
    {
        qDebug()<<"after toOpen.exists()";
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
            if(insertPCB(setupPCB(processName,pcbClass,priority,memory,timeRemaining,timeOfArrival,cpuPercent)))
            {
                qDebug()<<"insertion successful";
            }
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

void QPCBController::step()
{
    PCB* holder;
    switch(currentScheduler)
    {
    case SJF:
        if(runningPCB->getTimeRemaining()<=0 || runningPCB==NULL)
        {
            if(runningPCB!=NULL)
            {
                logProcessFinished(runningPCB->getName());
            }
            freePCB(runningPCB);
            setAsRunning(shortestJob());
        }
        break;
    case FIFO:
        if(runningPCB->getTimeRemaining()<=0 || runningPCB==NULL)
        {
            if(runningPCB!=NULL)
            {
                logProcessFinished(runningPCB->getName());
            }
            freePCB(runningPCB);
            setAsRunning(readyList.pop());
        }
        break;
    case STCF:
        if(runningPCB->getTimeRemaining()<=0 || runningPCB==NULL)
        {
            if(runningPCB!=NULL)
            {
                logProcessFinished(runningPCB->getName());
            }
            freePCB(runningPCB);
            setAsRunning(shortestJob());
        }
        break;
    case FPPS:
        if(runningPCB->getTimeRemaining()<=0 || runningPCB==NULL)
        {
            if(runningPCB!=NULL)
            {
                logProcessFinished(runningPCB->getName());
            }
            freePCB(runningPCB);
            setAsRunning(highestPriority());
        }
        break;
    case RR:

        if(runningPCB->getTimeRemaining()==0)
        {
            logProcessFinished(runningPCB->getName());
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
            logStateChange(runningPCB->getName(),runningPCB->getState());
            insertPCB(runningPCB);
            setAsRunning(readyList.pop());
        }
        break;
    case MLFQ:
        if(runningPCB->getTimeRemaining()==0)
        {
            logProcessFinished(runningPCB->getName());
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
            logStateChange(runningPCB->getName(),runningPCB->getState());
            insertPCB(runningPCB);
            if(runningPCB->getPriority()>-127)
            {
                runningPCB->setPriority(runningPCB->getPriority()-1);
            }
            setAsRunning(readyList.pop());
        }
        break;
    case LS://this finds number of tickets, then selects a process with a random number
            //we use the random number to find the process with the correct ticket number
            //if priority is negative this makes it positive
        holder = readyList.firstNode;
        tickets = 0;
        int ticketNum;
        if(runningPCB->getTimeRemaining()<=0 || runningPCB==NULL)
        {
            if(runningPCB!=NULL)
            {
                logProcessFinished(runningPCB->getName());
            }
            while(holder!=NULL)
            {
                if(holder->getPriority()<1)
                {
                    holder->setPriority(holder->getPriority()+128);
                }
                holder = holder->nextPCB;
            }
            holder = readyList.firstNode;
            while(holder!=NULL)
            {
                tickets+=holder->getPriority();
                holder = holder->nextPCB;
            }
            freePCB(runningPCB);
            ticketNum = generateNumber(0,tickets);
            holder = readyList.firstNode;
            while(tickets>0&&holder!=NULL)
            {
                ticketNum -=holder->getPriority();
                holder = holder->nextPCB;
            }
            setAsRunning(holder);
        }
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
            logStateChange(holder->getName(),holder->getState());
            holder->setState(READY);
        }
        if(holder->getState() == SUSPENDEDBLOCKED)
        {
            logStateChange(holder->getName(),holder->getState());
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
        logStateChange(holder->getName(),holder->getState());
    }
}

void QPCBController::setCurrentScheduler(SchedulerType scheduler)
{
    currentScheduler = scheduler;
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

void QPCBController::logProcessEnter(QString processName)
{
    QFile logFile(time.toString());
    logFile.open(QIODevice::Append | QIODevice::WriteOnly);
    QTextStream toWrite(&logFile);
    toWrite<<processName<<" entered the blocked queue";
    logFile.close();
}

void QPCBController::logProcessFinished(QString processName)
{
    QFile logFile(time.toString());
    logFile.open(QIODevice::Append | QIODevice::WriteOnly);
    QTextStream toWrite(&logFile);
    toWrite<<processName<<" finished and terminated";
    logFile.close();
}

void QPCBController::logStateChange(QString processName,PCBState state )
{
    QFile logFile(time.toString());
    logFile.open(QIODevice::Append | QIODevice::WriteOnly);
    QTextStream toWrite(&logFile);
    toWrite<<processName<<" now has the "<<stateToString(state)<<" state";
    logFile.close();
}

QString QPCBController::stateToString(PCBState state)
{
    switch(state)
    {
    case READY:
        return "READY";
        break;
    case BLOCKED:
        return "BLOCKED";
        break;
    case SUSPENDEDBLOCKED:
        return "SUSPENDEDBLOCKED";
        break;
    case SUSPENDEDREADY:
        return "SUSPENDEDREADY";
        break;
    case RUNNING:
        return "RUNNING";
        break;
    }
}
