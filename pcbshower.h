#ifndef PCBSHOWER_H
#define PCBSHOWER_H

#include <QDialog>
#include "pcb.h"
#include <QLabel>

namespace Ui {
class pcbShower;
}

class pcbShower : public QDialog
{
    Q_OBJECT
    
public:
    explicit pcbShower(QWidget *parent = 0);
    ~pcbShower();
public slots:
    void updateDisplay(PCB*);
    void showNext();
    void showPrev();

    
private:
    Ui::pcbShower *ui;
    QPushButton* quitButton,
                *nextPCB,
                *prevPCB;
    QLabel *nameText,
            *priorityText,
            *classText,
            *stateText;
    PCB *currentNode;
};

#endif // PCBSHOWER_H
