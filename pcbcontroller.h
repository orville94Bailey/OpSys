#ifndef PCBCONTROLLER_H
#define PCBCONTROLLER_H

#include "pcblist.h"

class PCBController
{
public:
    PCBController();
    PCB* setupPCB(std::string, int priority, PCBState state);//done
    PCB* allocatePCB();//done
    PCB* findPCB(std::string name);//done
    void freePCB(PCB*nodeToKill);//done
    bool insertPCB(PCB*nodeToInsert);//done
    void RemovePCB(PCB*nodeToRemove);//done

    PCBList readyList,blockedList;
};

#endif // PCBCONTROLLER_H
