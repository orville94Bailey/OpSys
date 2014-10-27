#include "cpuemulator.h"
#include "ui_cpuemulator.h"

CPUEmulator::CPUEmulator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CPUEmulator)
{
    ui->setupUi(this);
}

CPUEmulator::~CPUEmulator()
{
    delete ui;
}
