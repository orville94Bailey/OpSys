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
    PCB* findPCB(std::string);
    void removePCB(PCB*nodeToRemove);
    PCB *firstNode,*lastNode;
    //User Commands

};

#endif // PCBLIST_H
