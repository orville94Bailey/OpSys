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
    
private:
    Ui::MainWindow *ui;
    QPushButton *dateDisplayButton,
                *directoryDisplayButton,
                *helpButton,
                *quitButton,
                *pcbToolButton;
    QLineEdit *helpLineEdit;

    quitWindow exitWindow;
    dateWindow dateShower;
    directoryWindow directoryShower;
    //helpWindow helpShower;
    pcbWindow pcbTools;
};

#endif // MAINWINDOW_H
