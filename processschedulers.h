#ifndef PROCESSSCHEDULERS_H
#define PROCESSSCHEDULERS_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class processSchedulers;
}

class processSchedulers : public QWidget
{
    Q_OBJECT

private slots:
    void setTextSJF();
    void setTextFIFO();
    void setTextSTCF();
    void setTextFPPS();
    void setTextRR();
    void setTextMLFQ();
    void setTextLS();
    void setTextNOTSET();
public:
    explicit processSchedulers(QWidget *parent = 0);
    ~processSchedulers();
    QPushButton *quitButton,
                *SJHButton,
                *FIFO_button,
                *STCF_button,
                *FPPS_button,
                *RR__button,
                *MLFQ_button,
                *LS_button,
                *NONE_button;
    QLabel* CurScheduler_Label;
private:
    Ui::processSchedulers *ui;
};

#endif // PROCESSSCHEDULERS_H
