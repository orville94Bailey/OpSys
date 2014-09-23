#include "pcblist.h"

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
}

PCB* PCBList::pop()
{
    PCB* holder;
    holder = firstNode;

    firstNode=firstNode->nextPCB;
    firstNode->prevPCB=NULL;

    return holder;
}
