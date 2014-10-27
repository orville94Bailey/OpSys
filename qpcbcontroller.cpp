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
    nodeToKill->nextPCB->prevPCB = nodeToKill->prevPCB;
    nodeToKill->prevPCB->nextPCB = nodeToKill->nextPCB;

    delete nodeToKill;
}

bool QPCBController::insertPCB(PCB *nodeToInsert)
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
        return false;
        break;
    }
}

void QPCBController::RemovePCB(PCB* nodeToRemove)
{
    if(readyList.findPCB(nodeToRemove->getName())!=NULL)
    {
        qDebug()<<"entered ready remove";
        readyList.removePCB(nodeToRemove);
        qDebug()<<"removed from ready list";
    }
    if(blockedList.findPCB(nodeToRemove->getName())!=NULL)
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

void QPCBController::shortestJobFirst()
{
    PCB* shortestJob;
    while(blockedList.firstNode != NULL)
    {
        qDebug()<<"before shortestToCompleteon";
        shortestJob = blockedList.shortestToCompletion();
        qDebug()<<"before remove PCB";
        qDebug()<<shortestJob;
        RemovePCB(shortestJob);
        if(shortestJob!=NULL)
        {
            shortestJob->setState(READY);
        }

        qDebug()<<shortestJob;
        qDebug()<<shortestJob->getState();
        insertPCB(shortestJob);
    }
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

void QPCBController::step(PCB* runningPCB)
{


    systemTime++;
    runningPCB->setTimeRemaining(runningPCB->getTimeRemaining()-1);
}
