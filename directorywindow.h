#ifndef DIRECTORYWINDOW_H
#define DIRECTORYWINDOW_H

#include <QDialog>
#include <QFileSystemModel>
#include <QTreeView>

namespace Ui {
class directoryWindow;
}

class directoryWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit directoryWindow(QWidget *parent = 0);
    ~directoryWindow();
    
private:
    Ui::directoryWindow *ui;
    QPushButton *doneButton;
    QTreeView *tree;
    void addFiles();
};

#endif // DIRECTORYWINDOW_H
