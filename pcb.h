#ifndef PCB_H
#define PCB_H

#include <QString>
#include "enums.h"


class PCB
{
public:
    PCB();
    void setName(QString);
    void setClass(PCBType);
    void setPriority(int);
    void setState(PCBState);
    void setMem(int);

    void setTimeRemaining(int);
    void setTimeOfArrival(int);
    void setPercentCPU(int);

    QString getName();
    PCBType getPCBClass();
    int getPriority();
    PCBState getState();
    int getMem();

    int getTimeRemaining();
    int getTimeOfArrival();
    int getPercentCPU();

    PCB *nextPCB,*prevPCB;

private:
    QString processName;
    PCBType PCBClass;
    int priorityLevel;
    PCBState state;
    int memRequired;

    int timeRemaining,
        timeOfArrival,
        percentCPU;
};

#endif // PCB_H
