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
#include <QTime>
#include <QFile>

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
    void step();
    void insertNewArrivals();
    void setAsRunning(PCB*);
    PCB *shortestJob();
    PCB *highestPriority();
    int generateNumber(int low, int high);
    int quantum;
    int tickets;
    SchedulerType currentScheduler;

    PCBList readyList,blockedList;
    ~QPCBController();

public slots:
    void setCurrentScheduler(SchedulerType);
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
    PCB* runningPCB;
    QTime time;
    QFile logFile;
    QTextStream log;

    PCB* checkForArrivals();
    void setCurrentQuantum();
    void setCurrentTickets();
    void changePriorities();
    void logProcessFinished(QString);
    void logStateChange(QString, PCBState state);
    void logProcessEnter(QString);


};

#endif // QPCBCONTROLLER_H
