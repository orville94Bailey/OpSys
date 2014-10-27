#ifndef QPCBCONTROLLER_H
#define QPCBCONTROLLER_H

#include "pcblist.h"
#include <QTextStream>
#include <QString>
#include <QWidget>

namespace Ui {
class QPCBController;
}

class QPCBController : public QWidget
{
    Q_OBJECT

public:
    explicit QPCBController(QWidget *parent = 0);
    PCB* setupPCB(QString processName,QString pcbClass="S", int priority=0,int memory=0,int timeRemaining=0,int timeOfArrival=0,int cpuPercent=1);//done
    PCB* allocatePCB();//done
    PCB* findPCB(QString name);//done
    void freePCB(PCB*nodeToKill);//done
    bool insertPCB(PCB*nodeToInsert);//done
    void RemovePCB(PCB*nodeToRemove);//done
    void readFile(QString);
    void step();
    PCBList readyList,blockedList;
    ~QPCBController();

public slots:
    void shortestJobFirst();



private:
    Ui::QPCBController *ui;
    int systemTime;
    int totalTurnaround;
    int numOfPCB;
    PCB* runningPCB;
    SchedulerType currentScheduler;
    PCB* checkForArrivals();
};

#endif // QPCBCONTROLLER_H
