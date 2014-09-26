#ifndef PCBWINDOW_H
#define PCBWINDOW_H

#include <QWidget>
#include "pcbcontroller.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QSpinBox>
#include "pcbshower.h"
#include "processschedulers.h"

namespace Ui {
class pcbWindow;
}

class pcbWindow : public QWidget
{
    Q_OBJECT

public:
    explicit pcbWindow(QWidget *parent = 0);
    PCBController control;
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
                *reqMemLEdit;

    QCheckBox   *suspendCBox;

    QPushButton *createButton,
                *deleteButton,
                *blockButton,
                *unblockButton,
                *suspendButton,
                *resumeButton,
                *priorityButton,
                *pcbShowButton,
                *quitButton,
                *showBlockedButton,
                *showReadyButton;
    QSpinBox    *prioritySBox;
    pcbShower showWindow;
    processSchedulers scheduler;

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
};

#endif // PCBWINDOW_H
