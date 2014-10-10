#ifndef PCB_H
#define PCB_H

#include <QString>
#include "enums.h"


class PCB
{
public:
    PCB();
    void setName(QString);
    void setState(PCBState);
    void setPriority(int);
    void setMem(int);
    void setClass(PCBType);
    void setTimeRemaining(int);
    void setTimeOfArrival(int);
    void setPercentCPU(int);

    QString getName();
    PCBState getState();
    int getPriority();
    int getMem();
    PCBType getPCBClass();
    int getTimeRemaining();
    int getTimeOfArrival();
    int getPercentCPU();

    PCB *nextPCB,*prevPCB;

private:
    QString processName;
    PCBState state;
    int priorityLevel;
    int memRequired;
    PCBType PCBClass;
    int timeRemaining,
        timeOfArrival,
        percentCPU;
};

#endif // PCB_H
