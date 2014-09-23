#include "pcbcontroller.h"
#include <QtDebug>

PCBController::PCBController()
{
}

PCB* PCBController::allocatePCB()
{
    PCB* holder;
    holder=new PCB;
    qDebug()<<"allocatePCB running";
    return holder;
}

PCB* PCBController::setupPCB(std::string name, int priority, PCBState state)
{
    PCB* holder;
    if(findPCB(name)==NULL)
    {
        holder = allocatePCB();
        //qDebug()<<"allocatePCB returned succesfully";
        holder->setName(name);
        holder->setPriority(priority);
        holder->setState(state);
    }
    qDebug()<<"setupPCB returned successfully";
    return holder;
}

PCB* PCBController::findPCB(std::string name)
{
    qDebug()<<"findPCB running to find ";
    PCB* holder;
    holder = readyList.firstNode;

    if(holder == NULL)
    {
        holder = blockedList.firstNode;
        if(holder == NULL)
        {
            return NULL;
        }

        while(holder->nextPCB!=NULL)
        {
            if(holder->getName()!=name)
            {
                holder = holder->nextPCB;
            }
            else
                return holder;
        }
        return NULL;

    }
    while(holder->nextPCB!=NULL)
    {
        if(holder->getName()!=name)
        {
            holder = holder->nextPCB;
        }
        else
            return holder;
    }

    holder = blockedList.firstNode;
    if(holder == NULL)
    {
        return NULL;
    }
    while(holder->nextPCB!=NULL)
    {
        if(holder->getName()!=name)
        {
            holder = holder->nextPCB;
        }
        else
            return holder;
    }

    return NULL;
}

void PCBController::freePCB(PCB* nodeToKill)
{
    nodeToKill->nextPCB->prevPCB = nodeToKill->prevPCB;
    nodeToKill->prevPCB->nextPCB = nodeToKill->nextPCB;

    delete nodeToKill;
}

bool PCBController::insertPCB(PCB *nodeToInsert)
{
    qDebug()<<"before the switch";
    switch(nodeToInsert->getState())
    {
    case READY:

    case SUSPENDEDREADY:
        qDebug()<<"before pushing";
        readyList.push(nodeToInsert);
        qDebug()<<"after pushing";
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
    qDebug()<<"after the switch";
}

PCB* PCBController::RemovePCB(PCB* nodeToRemove)
{
    nodeToRemove->nextPCB->prevPCB=nodeToRemove->prevPCB;
    nodeToRemove->prevPCB->nextPCB=nodeToRemove->nextPCB;
    return nodeToRemove;
}
