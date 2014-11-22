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
    case 0:
        if(runningPCB->getTimeRemaining()<=0 || runningPCB==NULL)
        {
            freePCB(runningPCB);
            setAsRunning(shortestJob());
        }
        break;
    case 1:
        if(runningPCB->getTimeRemaining()<=0 || runningPCB==NULL)
        {
            freePCB(runningPCB);
            setAsRunning(readyList.pop());
        }
        break;
    case 2:
        if(runningPCB->getTimeRemaining()<=0 || runningPCB==NULL)
        {
            freePCB(runningPCB);
            setAsRunning(shortestJob());
        }
        break;
    case 3:
        if(runningPCB->getTimeRemaining()<=0 || runningPCB==NULL)
        {
            freePCB(runningPCB);
            setAsRunning(highestPriority());
        }
        break;
    case 4:
        if(runningPCB->getTimeRemaining()<=0 ||
                runningPCB==NULL ||
                systemTime%quantum==0)
        {
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
        }
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
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
