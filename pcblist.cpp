#include "pcblist.h"
#include <QDebug>
PCBList::PCBList()
{
    firstNode = NULL;
    lastNode = NULL;
}

int PCBList::listLength()
{
    PCB* holder;
    holder = firstNode;

    int count=0;
    if(holder == NULL)
    {
        return count;
    }
    while(holder->nextPCB!=NULL)
    {
        count++;
    }
    return count;
}

void PCBList::push(PCB* nodeToAdd)
{
    qDebug()<<"push begin";
    if(lastNode!=NULL)
    {
        lastNode->nextPCB = nodeToAdd;
        nodeToAdd->prevPCB = lastNode;
        lastNode = nodeToAdd;
    }
    else
    {
        firstNode = nodeToAdd;
        lastNode = nodeToAdd;
    }
    qDebug()<<"end push";
}

PCB* PCBList::pop()
{
    PCB* holder;
    holder = firstNode;

    firstNode=firstNode->nextPCB;
    firstNode->prevPCB=NULL;

    return holder;
}

PCB* PCBList::findPCB(QString nameSearch)
{
    PCB* holder;
    holder = firstNode;
    if(nameSearch!=NULL)
    {
        while(holder!=NULL)
        {
            //qDebug()<<"inside while";
            if(holder->getName()==nameSearch)
            {
                //qDebug()<<"inside if";
                //qDebug()<<holder;
                return holder;
            }
            holder = holder->nextPCB;
        }
        //qDebug()<<holder;
    }
    return NULL;
}

void PCBList::removePCB(PCB* nodeToRemove)
{
    qDebug()<<"begin removePCB";
    if(nodeToRemove != NULL)
    {
        qDebug()<<"node != NULL";
        if(nodeToRemove->nextPCB!=NULL && nodeToRemove->prevPCB!=NULL)//NODE BEFORE AND AFTER
        {
            qDebug()<<"first case";
            nodeToRemove->nextPCB->prevPCB=nodeToRemove->prevPCB;
            nodeToRemove->prevPCB->nextPCB=nodeToRemove->nextPCB;
            nodeToRemove->nextPCB=NULL;
            nodeToRemove->prevPCB=NULL;
        }
        else if(nodeToRemove->nextPCB==NULL && nodeToRemove->prevPCB!=NULL)//NODE BEFORE NOT AFTER
        {
            qDebug()<<"second case";
            nodeToRemove->prevPCB->nextPCB=NULL;
            nodeToRemove->nextPCB=NULL;
            nodeToRemove->prevPCB=NULL;
        }
        else if(nodeToRemove->nextPCB!=NULL && nodeToRemove->prevPCB==NULL)//NODE AFTER NOT BEFORE
        {
            qDebug()<<"third case";
            firstNode = nodeToRemove->nextPCB;
            nodeToRemove->nextPCB=NULL;
            nodeToRemove->prevPCB=NULL;
            firstNode->prevPCB = NULL;
        }
        else if(nodeToRemove->nextPCB==NULL && nodeToRemove->prevPCB==NULL)//NO NODE BEFORE or AFTER
        {
            qDebug()<<"fourth case";
            nodeToRemove->nextPCB=NULL;
            nodeToRemove->prevPCB=NULL;
            firstNode = NULL;
        }
    }
}

PCB* PCBList::shortestToCompletion()
{
    PCB* holder = firstNode;
    PCB* shortestHolder = NULL;
    int shortestValue;
    if(firstNode!=NULL)
    {
        shortestValue = holder->getTimeRemaining();
        shortestHolder = holder;
        qDebug()<<holder;
        qDebug()<<shortestValue;
        while(holder!=NULL)
        {
            qDebug()<<holder;
            qDebug()<<holder->getTimeRemaining();
            if(holder->getTimeRemaining()<shortestValue)
            {
                shortestValue = holder->getTimeRemaining();
                shortestHolder = holder;
            }
            holder = holder->nextPCB;
        }
    }
    qDebug()<<shortestValue;
    qDebug()<<shortestHolder;
    return shortestHolder;
}
