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

void PCB::setName(std::string name)
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

std::string PCB::getName()
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
