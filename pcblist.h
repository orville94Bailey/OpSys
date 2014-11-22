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
    PCB *firstNode,*lastNode;

    PCB* shortestToCompletion();
    //User Commands

};

#endif // PCBLIST_H
