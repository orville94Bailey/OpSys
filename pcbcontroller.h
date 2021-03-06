#ifndef PCBCONTROLLER_H
#define PCBCONTROLLER_H

#include "pcblist.h"
#include <QTextStream>
#include <QString>
#include <QWidget>

namespace Ui {
class PCBController;
}

class PCBController : public QWidget
{
    Q_OBJECT

public:
    explicit PCBController();

    PCB* setupPCB(QString processName,QString pcbClass="S", int priority=0,int memory=0,int timeRemaining=0,int timeOfArrival=0,int cpuPercent=1);//done
    PCB* allocatePCB();//done
    PCB* findPCB(QString name);//done
    void freePCB(PCB*nodeToKill);//done
    bool insertPCB(PCB*nodeToInsert);//done
    void RemovePCB(PCB*nodeToRemove);//done
    void readFile(QString);
    PCBList readyList,blockedList;

public slots:

    void shortestJobFirst();


};

#endif // PCBCONTROLLER_H
