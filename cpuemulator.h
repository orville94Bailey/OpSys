#ifndef CPUEMULATOR_H
#define CPUEMULATOR_H

#include <QWidget>

namespace Ui {
class CPUEmulator;
}

class CPUEmulator : public QWidget
{
    Q_OBJECT

public:
    explicit CPUEmulator(QWidget *parent = 0);
    ~CPUEmulator();

private:
    Ui::CPUEmulator *ui;
};

#endif // CPUEMULATOR_H
