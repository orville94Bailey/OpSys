#ifndef QPCBCONTROLLER_H
#define QPCBCONTROLLER_H

#include "pcblist.h"
#include <QTextStream>
#include <QString>
#include <QWidget>
#include "enums.h"
#include "processschedulers.h"
#include <QObject>
#include "quantumdefinewindow.h"
#include "ticketdefine.h"

namespace Ui {
class QPCBController;
}

class QPCBController : public QWidget
{
    Q_OBJECT

public:
    explicit QPCBController(QWidget *parent = 0);
    PCB* setupPCB(QString processName,QString pcbClass="A", int priority=0,int memory=0,int timeRemaining=0,int timeOfArrival=0,int cpuPercent=1);//done
    PCB* allocatePCB();//done
    PCB* findPCB(QString name);//done
    void freePCB(PCB*nodeToKill);//done
    bool insertPCB(PCB*nodeToInsert);//done
    void removePCB(PCB*nodeToRemove);//done
    void readFile(QString);
    void step(SchedulerType);
    void insertNewArrivals();
    void setAsRunning(PCB*);
    PCB *shortestJob();
    PCB *highestPriority();

    PCBList readyList,blockedList;
    ~QPCBController();

public slots:
    void setCurrentScheduler(SchedulerType);
    void defineQuantum();
    void defineTickets();
    void setSchedulerSFJ();
    void setSchedulerFIFO();
    void setSchedulerSTCF();
    void setSchedulerFPPS();
    void setSchedulerRR();
    void setSchedulerMLFQ();
    void setSchedulerLS();
    void setSchedulerNOTSET();

private:
    Ui::QPCBController *ui;
    int systemTime;
    int totalTurnaround;
    int numOfPCB;
    int quantum;
    int tickets;
    PCB* runningPCB;
    SchedulerType currentScheduler;
    processSchedulers schedulerWindow;
    QuantumDefineWindow quantumWindow;
    ticketDefine ticketWindow;

    PCB* checkForArrivals();
    void setCurrentQuantum();
    void setCurrentTickets();
    void changePriorities();


};

#endif // QPCBCONTROLLER_H
