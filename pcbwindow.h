#ifndef PCBWINDOW_H
#define PCBWINDOW_H

#include <QWidget>
#include "qpcbcontroller.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QSpinBox>
#include "pcbshower.h"
#include "processschedulers.h"
#include "quantumdefinewindow.h"
#include "ticketdefine.h"

namespace Ui {
class pcbWindow;
}

class pcbWindow : public QWidget
{
    Q_OBJECT

public:
    explicit pcbWindow(QWidget *parent = 0);
    QPCBController *control;
    processSchedulers *scheduler;
    QuantumDefineWindow *quantumWindow;
    ticketDefine *ticketWindow;
    pcbShower showWindow;
    ~pcbWindow();

private:

    bool showPCB();
    void showAll();
    void showReady();
    void showBlocked();

    Ui::pcbWindow *ui;
    QLineEdit   *classLEdit,
                *nameLEdit,
                *stateLEdit,
                *reqMemLEdit,
                *fileNameLEdit;

    QCheckBox   *suspendCBox;

    QPushButton //*createButton,
                //*deleteButton,
                //*blockButton,
                //*unblockButton,
                *suspendButton,
                *resumeButton,
                *priorityButton,
                *pcbShowButton,
                *quitButton,
                *showBlockedButton,
                *showReadyButton,
                *readFileButton,
                *schedulerButton;
    QSpinBox    *prioritySBox,
                *timeRemainingSBox,
                *reqMemSBox;

private slots:
    void showPCBList();//done
    bool setPriority();//done
    void showReadyPCB();
    void showBlockedPCB();
    void createPCB();//done
    bool deletePCB();//done
    bool block();//done
    bool unblock();//done
    bool suspend();//done
    bool resume();//done
    void readFile();
    void showSchedulers();
    void setQuantum();
    void setTickets();
    void run();
};

#endif // PCBWINDOW_H
