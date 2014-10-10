#include "pcb.h"

PCB::PCB()
{
    nextPCB=NULL;
    prevPCB=NULL;
}

void PCB::setMem(int mem)
{
    memRequired = mem;
}

void PCB::setName(QString name)
{
    processName = name;
}

void PCB::setPriority(int priority)
{
    priorityLevel = priority;
}

void PCB::setState(PCBState newState)
{
    state = newState;
}

QString PCB::getName()
{
    return processName;
}

PCBState PCB::getState()
{
    return state;
}

int PCB::getPriority()
{
    return priorityLevel;
}

int PCB::getMem()
{
    return memRequired;
}

PCBType PCB::getPCBClass()
{
    return PCBClass;
}

void PCB::setClass(PCBType type)
{
    PCBClass = type;
}

int PCB::getPercentCPU()
{
    return percentCPU;
}

int PCB::getTimeOfArrival()
{
    return timeOfArrival;
}

int PCB::getTimeRemaining()
{
    return timeRemaining;
}

void PCB::setPercentCPU(int newPercent)
{
    percentCPU = newPercent;
}

void PCB::setTimeOfArrival(int TOA)
{
    timeOfArrival = TOA;
}

void PCB::setTimeRemaining(int timeLeft)
{
    timeRemaining = timeLeft;
}
