#ifndef QUANTUMDEFINEWINDOW_H
#define QUANTUMDEFINEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QSpinBox>

namespace Ui {
class QuantumDefineWindow;
}

class QuantumDefineWindow : public QWidget
{
    Q_OBJECT

public:
    explicit QuantumDefineWindow(QWidget *parent = 0);
    ~QuantumDefineWindow();

    QPushButton *Accept_button,
                *Cancel_button;
    QSpinBox    *Quantum_SpinBox;

private:
    Ui::QuantumDefineWindow *ui;
};

#endif // QUANTUMDEFINEWINDOW_H
