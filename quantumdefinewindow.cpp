#include "quantumdefinewindow.h"
#include "ui_quantumdefinewindow.h"

QuantumDefineWindow::QuantumDefineWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuantumDefineWindow)
{
    ui->setupUi(this);

    Accept_button = ui->Accept_button;
    Cancel_button = ui->Cancel_button;
    Quantum_SpinBox = ui->Quantum_SpinBox;

    connect(Cancel_button,SIGNAL(clicked()),this,SLOT(close()));
}

QuantumDefineWindow::~QuantumDefineWindow()
{
    delete ui;
    delete Accept_button;
    delete Cancel_button;
    delete Quantum_SpinBox;
}
