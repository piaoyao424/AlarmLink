#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stable.h"
#include "alarm_hc.h"
#include "AlarmClass.h"
#include "TextSpeech.h"
#include <time.h>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

//全局,用于回调函数使用

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void AddLog(QString str);
    bool InitDb();    
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QSqlDatabase    db;
    QList<AlarmClass*>  lt_AlarmClass;

private slots:
    void TimerUpdate();
    void on_Btn_Quit_clicked();
};

#endif // MAINWINDOW_H
