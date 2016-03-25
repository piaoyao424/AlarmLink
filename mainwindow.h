#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stable.h"
#include "alarm_hc.h"
#include <time.h>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void AddLog(QString str);
    void InitDb();
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

private slots:
    void TimerUpdate();
    void on_Btn_Quit_clicked();
};

#endif // MAINWINDOW_H
