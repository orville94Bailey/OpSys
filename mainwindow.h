#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include "quitwindow.h"
#include "datewindow.h"
#include "directorywindow.h"
#include "helpwindow.h"
#include "pcbwindow.h"
#include "processschedulers.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void quitClicked();

    void dateClicked();

    void helpClicked();

    void directoryClicked();

    void pcbToolsClicked();

    void schedulerButtonClicked();
    
private:
    Ui::MainWindow *ui;
    QPushButton *dateDisplayButton,
                *directoryDisplayButton,
                *helpButton,
                *quitButton,
                *pcbToolButton,
                *schedulerButton;
    QLineEdit *helpLineEdit;

    quitWindow exitWindow;
    dateWindow dateShower;
    directoryWindow directoryShower;
    //helpWindow helpShower;
    pcbWindow pcbTools;
    processSchedulers schedulerWindow;


};

#endif // MAINWINDOW_H
