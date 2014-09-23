#ifndef DATEWINDOW_H
#define DATEWINDOW_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class dateWindow;
}

class dateWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit dateWindow(QWidget *parent = 0);
    ~dateWindow();
    
private:
    Ui::dateWindow *ui;
    QPushButton *doneButton;
};

#endif // DATEWINDOW_H
