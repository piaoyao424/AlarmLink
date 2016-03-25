#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AddLog("程序启动！");
    //新建定时器
    QTimer *timer = new QTimer(this);
    //关联信号槽
    connect(timer,SIGNAL(timeout()),this,SLOT(TimerUpdate()));
    //timer->start(1000);

    InitDb();
    AddLog("数据库初始化完成！");

    Alarm_HC alarm = Alarm_HC(this);
   bool b = alarm.M_NET_DVR_Init();
   if(b)
   {
       AddLog("报警主机初始化完成！");
   }
   else
   {
       AddLog("报警主机初始化失败！");
   }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TimerUpdate()
{
    //QMessageBox::information(this, "Caption", tr("Hello你好吗"), QMessageBox::Ok);
    AddLog("测试");
}

void MainWindow::AddLog(QString str)
{
  QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
  QString  _str = time.toString("yyyy-MM-dd hh:mm:ss ddd") + "  " + str ; //设置显示格式
  qDebug()<<"槽函数响应的结果是：x的值为："<<str;
  ui->Txt_Log->append(_str)   ;//在标签上显示时间
  //写入文本文件
  QFile log("Log.txt");
  if(log.open(QIODevice::Text | QFile::WriteOnly | QIODevice::Append))
  {
    QTextStream out(&log);
    out << _str << endl ;
  }
}

void MainWindow::InitDb()
{

    //添加数据库驱动
    QSqlDatabase  db = QSqlDatabase::addDatabase("QSQLITE");
    //数据库连接命名
    //db.setDatabaseName(":memory:"); 放置在内存的临时数据库
    db.setHostName("localhost"); //设置数据库主机名
    db.setDatabaseName("Db_AlarmLink.db"); //设置数据库名
    db.setUserName("root"); //设置数据库登入用户名
    db.setPassword("123456"); //设计数据库登入密码
    //打开数据库
    if(!db.open())
    {
        qDebug()<< "数据库打开失败" ;
        return ;
    }

    QSqlQuery query;
    //新建表，id设置为主键，
   query.exec("create table t_ini(id int primary key,AlarmID int,SpeakWord varchar,LEDWord varchar)");
   //插入4条记录
    query.exec("insert into t_ini values(1,1,'第一防区','东围墙')");
    query.exec("insert into t_ini values(2,2,'第二防区','南围墙')");
    query.exec("insert into t_ini values(3,3,'第三防区','西围墙')");
    query.exec("insert into t_ini values(4,4,'第四防区','北围墙')");

    query.prepare("select id,AlarmID,SpeakWord,LEDWord from t_ini where id > 2");//分行写的时候注意空格不能少
    if(!query.exec())
    {
       qDebug()<< query.lastError();
       return;
    }
    //取出来的指针停留住第一条数据前面，必须要后移
    while(query.next())
    {
        int ele0 = query.value(0).toInt();
        int ele1 = query.value(1).toInt();
        QString ele2 = query.value(2).toString();
        QString ele3 = query.value(3).toString();
        //输入值
        qDebug()<<ele0<<ele1<<ele2<<ele3 ;
     }
}

void MainWindow::on_Btn_Quit_clicked()
{
   QApplication *app;
   app->quit();
}

void CALLBACK MessageCallback(LONG lCommand, NET_DVR_ALARMER *pAlarmer, char *pAlarmInfo, DWORD dwBufLen, void*
pUser)
{
    int i;
    NET_DVR_ALARMINFO struAlarmInfo;
    memcpy(&struAlarmInfo, pAlarmInfo, sizeof(NET_DVR_ALARMINFO));
    switch(lCommand)
    {
        case COMM_ALARM:
        {
            switch (struAlarmInfo.dwAlarmType)
            {
                case 0: //信号量侦测
                for (i=0; i<8; i++) //#define MAX_CHANNUM 8 //最大通道数
                {
                    if (struAlarmInfo.dwChannel[i] == 1)
                    {
                        printf("发生移动侦测报警的通道号 %d\n", i+1);
                    }
                } break;
                default: break;
            }
        } break;
        default: break;
    }
}
