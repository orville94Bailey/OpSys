#ifndef PCBLIST_H
#define PCBLIST_H

#include "pcb.h"

class PCBList
{
public:
    PCBList();
    void push(PCB*);
    PCB* pop();
    int listLength();
    PCB* findPCB(QString);
    void removePCB(PCB*nodeToRemove);
    PCB* shortestToCompletion();
    PCB *firstNode,*lastNode;
    //User Commands

};

#endif // PCBLIST_H
