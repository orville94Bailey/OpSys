#include "pcbcontroller.h"
#include <QtDebug>
#include <QFile>
#include <QCoreApplication>

PCBController::PCBController()
{
}

PCB* PCBController::allocatePCB()
{
    PCB* holder;
    holder=new PCB;
    //qDebug()<<"allocatePCB running";
    return holder;
}

PCB* PCBController::setupPCB(QString processName,QString pcbClass, int priority,int memory,int timeRemaining,int timeOfArrival,int cpuPercent)
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

PCB* PCBController::findPCB(QString name)
{
    PCB* holder=NULL;
    holder = readyList.findPCB(name);
    //qDebug()<<holder;
    if(holder == NULL)
    {
        //qDebug()<<"holder == NULL";
        holder = blockedList.findPCB(name);
    }
    qDebug()<<"pointer from findPCB:";
    qDebug()<<holder;
    return holder;
}

void PCBController::freePCB(PCB* nodeToKill)
{
    nodeToKill->nextPCB->prevPCB = nodeToKill->prevPCB;
    nodeToKill->prevPCB->nextPCB = nodeToKill->nextPCB;

    delete nodeToKill;
}

bool PCBController::insertPCB(PCB *nodeToInsert)
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

void PCBController::RemovePCB(PCB* nodeToRemove)
{
    readyList.removePCB(nodeToRemove);
    blockedList.removePCB(nodeToRemove);
}

void PCBController::readFile(QString fileName)
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
            qDebug()<<toOpen.error();
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
        qDebug()<<"File DNE";
        qDebug()<<QCoreApplication::applicationDirPath();
        return;
    }
}

void PCBController::shortestJobFirst()
{
    PCB* shortestJob;
    while(blockedList.firstNode != NULL)
    {
        shortestJob = blockedList.shortestToCompletion();
        RemovePCB(shortestJob);
        shortestJob->setState(READY);
        insertPCB(shortestJob);
    }
}
