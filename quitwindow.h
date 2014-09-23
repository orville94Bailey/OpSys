#ifndef QUITWINDOW_H
#define QUITWINDOW_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class quitWindow;
}

class quitWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit quitWindow(QWidget *parent = 0);
    ~quitWindow();
    
private:
    Ui::quitWindow *ui;
    QDialog *exampleDialog;
    QPushButton *closeButton;
    QPushButton *cancelButton;

private slots:
    void quitButtonClicked();
};

#endif // QUITWINDOW_H
