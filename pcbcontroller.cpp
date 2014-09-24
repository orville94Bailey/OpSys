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
    //qDebug()<<"setupPCB returned successfully";
    return holder;
}

PCB* PCBController::findPCB(std::string name)
{
    //qDebug()<<"findPCB running to find ";
    PCB* holder;
    holder = readyList.firstNode;

    //qDebug()<<holder;

    if(holder == NULL)
    {
        //qDebug()<<"ready list is empty";
        holder = blockedList.firstNode;
        if(holder == NULL)
        {
            //qDebug()<<"blocked list is empty";
            //qDebug()<<"NULL";
            return NULL;
        }

        while(holder->nextPCB!=NULL)
        {
            if(holder->getName()!=name)
            {
                holder = holder->nextPCB;
            }
            else
            {
                //qDebug()<<holder;
                return holder;
            }
        }
        //qDebug()<<"NULL";
        return NULL;

    }

    do
    {
        //qDebug()<<"ready list is not empty";
        if(holder->getName()!=name)
        {
            holder = holder->nextPCB;
        }
        else
        {
            //qDebug()<<holder;
            return holder;
        }
    }while(holder->nextPCB!=NULL);

    holder = blockedList.firstNode;
    if(holder == NULL)
    {
        //qDebug()<<"blocked list is empty";
        //qDebug()<<"NULL";
        return NULL;
    }
    do
    {
        if(holder->getName()!=name)
        {
            holder = holder->nextPCB;
        }
        else
        {
            //qDebug()<<holder;
            return holder;
        }
    }while(holder->nextPCB!=NULL);
    //qDebug()<<"NULL";
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

PCB* PCBController::RemovePCB(PCB* nodeToRemove)
{
    nodeToRemove->nextPCB->prevPCB=nodeToRemove->prevPCB;
    nodeToRemove->prevPCB->nextPCB=nodeToRemove->nextPCB;
    return nodeToRemove;
}
