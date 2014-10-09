#include "pcbcontroller.h"
#include <QtDebug>

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
        if(pcbClass == 'A')
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
        holder->setState(state);
    }
    //qDebug()<<"setupPCB returned successfully";
    return holder;
}

PCB* PCBController::findPCB(std::string name)
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
    //qDebug()<<"before the switch";
    switch(nodeToInsert->getState())
    {
    case READY:

    case SUSPENDEDREADY:
        //qDebug()<<"before pushing";
        readyList.push(nodeToInsert);
        //qDebug()<<"after pushing";
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
    //qDebug()<<"after the switch";
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
    QFile toOpen("fileName");
    if(!toOpen.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream toRead(&toOpen);

    toRead>>processName;
    toRead>>pcbClass;
    toRead>>priority;
    toRead>>memory;
    toRead>>timeRemaining;
    toRead>>timeOfArrival;
    toRead>>cpuPercent;
    pcbCreate
}
