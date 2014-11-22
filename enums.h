#ifndef ENUMS_H
#define ENUMS_H

enum PCBType
{
    APPLICATION,
    SYSTEM
};

enum PCBState
{
    RUNNING,
    READY,
    BLOCKED,
    SUSPENDEDREADY,
    SUSPENDEDBLOCKED
};

enum SchedulerType
{
    SJF,
    FIFO,
    STCF,
    FPPS,
    RR,
    MLFQ,
    LS,
    NOTSET
};

#endif
