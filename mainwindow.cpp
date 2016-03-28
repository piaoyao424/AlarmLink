#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AddLog("程序启动！");
    //新建定时器
    //QTimer *timer = new QTimer(this);
    //关联信号槽
    //connect(timer,SIGNAL(timeout()),this,SLOT(TimerUpdate()));
    //timer->start(1000);


    if (InitDb())
    {
        AddLog("数据库初始化完成！");
    }
    else
    {
        AddLog("数据库初始化失败！");
    }

    TextSpeech* tts = new TextSpeech(this);

    Alarm_HC alarm = Alarm_HC(this);
    tts->speak("报警主机初始化失败！");
    QTime t;
    t.start();
    while(t.elapsed()<2000)
    QCoreApplication::processEvents();


    if(alarm.M_NET_DVR_Init())
    {
        AddLog("报警主机初始化完成！");
        tts->speak("报警主机初始化完成！");
    }
    else
    {
        AddLog("报警主机初始化失败！");
        tts->speak("报警主机初始化失败！");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    //销毁对象指针，避免内存泄露
    QListIterator<AlarmClass*> i(lt_AlarmClass);
    while(i.hasNext())
    {
        delete(i.next());
    }
}

void MainWindow::TimerUpdate()
{
    QMessageBox::information(this, "Caption", tr("Hello！你好吗"), QMessageBox::Ok);
    AddLog("测试");
}

bool MainWindow::InitDb()
{

    //添加数据库驱动
    db = QSqlDatabase::addDatabase("QSQLITE");
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
        return false ;
    }

    QSqlQuery query;
    //检查table是否存在
    //bool IsTableExist = query.exec(QString("select count(*) from sqlite_master where type='table' and name='%1'").arg("t_ini")) ;

    //新建表，id设置为主键
    bool IsTableExist = query.exec(" create table if not exists t_ini(id integer primary key autoincrement not null,AlarmID int,SpeakWord varchar,LEDWord varchar,VoicePath varchar)");
    qDebug()<< IsTableExist;

    //获取数据,填充容器
    //        //插入4条记录
    //        query.exec("insert into t_ini values(1,1,'第一防区','东围墙')");
    //        query.exec("insert into t_ini values(2,2,'第二防区','南围墙')");
    //        query.exec("insert into t_ini values(3,3,'第三防区','西围墙')");
    //        query.exec("insert into t_ini values(4,4,'第四防区','北围墙')");

    query.prepare("select id,AlarmID,SpeakWord,LEDWord,VoicePath from t_ini where 1 = 1");
    if(!query.exec())
    {
        qDebug()<< query.lastError();
        return false ;
    }

    int cnt = 0;
    //取出来的指针停留住第一条数据以前，必须要后移
    while(query.next())
    {
        try{

            int ele0 = query.value(0).toInt();
            int AlarmID = query.value(1).toInt();
            QString SpeakWord = query.value(2).toString();
            QString LEDWord = query.value(3).toString();
            QString VoicePath = query.value(4).toString();
            //输入值
            qDebug()<<ele0<<AlarmID<<SpeakWord<<LEDWord<<VoicePath ;
            //
            AlarmClass* alarm = new AlarmClass();
            alarm->SetAlarmID(AlarmID);
            alarm->SetSpeakWord(SpeakWord);
            alarm->SetLEDWord(LEDWord);
            alarm->SetVoicePath(VoicePath);
            lt_AlarmClass.append(alarm);
            cnt+=1;

        }catch(...)
        {
            AddLog("异常!");
        }
    }
    AddLog("共加载"+ QString::number(cnt, 10)+"个防区！");
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
    QString s_SpeakWord,s_LEDWord;
    switch(lCommand)
    {
    case COMM_ALARM:
    {
        switch (struAlarmInfo.dwAlarmType)
        {
        case 0: //信号量侦测
            for (i=0; i<8; i++) //#define MAX_CHANNUM 8 //最大通道数
            {
                //                //遍历对象，查找AlarmID
                //                QListIterator<AlarmClass*> j( this->lt_AlarmClass);
                //                while(j.hasNext())
                //                {
                //                    if (struAlarmInfo.dwChannel[i] == (DWORD)j.next()->GetAlarmID())
                //                    {
                //                        s_SpeakWord +=  j.next()->GetSpeakWord();
                //                        s_LEDWord += j.next()->GetLEDWord();
                //                        //printf("发生移动侦测报警的通道号 %d\n", i+1);
                //                    }
                //                }


            } break;
        default: break;
        }
    } break;
    default: break;
    }
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
