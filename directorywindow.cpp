#include "directorywindow.h"
#include "ui_directorywindow.h"



directoryWindow::directoryWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::directoryWindow)
{
    ui->setupUi(this);
    doneButton = ui->pushButton;
    tree = ui->treeView;

    connect(doneButton, SIGNAL(clicked()), this, SLOT(hide()));
    addFiles();
}

directoryWindow::~directoryWindow()
{
    delete ui;
    delete doneButton;
    delete tree;
}

void directoryWindow::addFiles() //shows the files from the working directory of the application
{
    QFileSystemModel *model = new QFileSystemModel;
    QString dir(QCoreApplication::applicationDirPath());
    model->setRootPath(dir);
    tree->setModel(model);
    tree->setRootIndex(model->index((dir)));
    tree->show();
}
