#ifndef PCBCONTROLLER_H
#define PCBCONTROLLER_H

#include "pcblist.h"
#include "processschedulers.h"
#include <QTextStream>
#include <QString>

class PCBController
{
public:
    PCBController();

    PCB* setupPCB(QString processName,QString pcbClass="S", int priority=0,int memory=0,int timeRemaining=0,int timeOfArrival=0,int cpuPercent=1);//done
    PCB* allocatePCB();//done
    PCB* findPCB(QString name);//done
    void freePCB(PCB*nodeToKill);//done
    bool insertPCB(PCB*nodeToInsert);//done
    void RemovePCB(PCB*nodeToRemove);//done
    void readFile(QString);

    PCBList readyList,blockedList;
    processSchedulers scheduler;
};

#endif // PCBCONTROLLER_H
