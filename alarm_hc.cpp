#include "alarm_hc.h"

Alarm_HC::Alarm_HC(QWidget *parent)
{
  this->parent = parent;
  QLibrary HCDLL("HCNetSDK.dll");
  if(HCDLL.load())
  {
     QMessageBox::information(this->parent,"error","报警主机DLL加载失败！" + HCDLL.errorString() );
  }
  else
  {
      fun_NET_DVR_Init  = (NET_DVR_Init)HCDLL.resolve("NET_DVR_Init");
      fun_NET_DVR_Cleanup  = (NET_DVR_Cleanup)HCDLL.resolve("NET_DVR_Cleanup");
      fun_NET_DVR_SetReconnect  = (NET_DVR_SetReconnect)HCDLL.resolve("NET_DVR_SetReconnect");
      fun_NET_DVR_SetConnectTime  = (NET_DVR_SetConnectTime)HCDLL.resolve("NET_DVR_SetConnectTime");
      fun_NET_DVR_Login_V30  = (NET_DVR_Login_V30)HCDLL.resolve("NET_DVR_Login_V30");
      fun_NET_DVR_SetDVRMessageCallBack_V30  = (NET_DVR_SetDVRMessageCallBack_V30)HCDLL.resolve("NET_DVR_SetDVRMessageCallBack_V30");
      fun_NET_DVR_StartListen_V30  = (NET_DVR_StartListen_V30)HCDLL.resolve("NET_DVR_StartListen_V30");
      fun_NET_DVR_Logout_V30  = (NET_DVR_Logout_V30)HCDLL.resolve("NET_DVR_Logout_V30");
      fun_NET_DVR_StopListen_V30  = (NET_DVR_StopListen_V30)HCDLL.resolve("NET_DVR_StopListen_V30");
  }

}

bool Alarm_HC::M_NET_DVR_Init()
{
    if(fun_NET_DVR_Init)
    {
        return fun_NET_DVR_Init();
    }
    else
    {
        return false;
    }
}

bool Alarm_HC::M_NET_DVR_Cleanup()
{
    if(fun_NET_DVR_Cleanup)
    {
        return fun_NET_DVR_Cleanup();
    }
    else
    {
        return false;
    }
}

bool Alarm_HC::M_NET_DVR_SetConnectTime(DWORD dwWaitTime, DWORD dwTryTimes)
{

    if(fun_NET_DVR_SetConnectTime)
    {
        return fun_NET_DVR_SetConnectTime(dwWaitTime,dwTryTimes);
    }
    else
    {
        return false;
    }
}

bool Alarm_HC::M_NET_DVR_SetReconnect(DWORD dwInterval, WINBOOL bEnableRecon)
{

    if(fun_NET_DVR_SetReconnect)
    {
        return fun_NET_DVR_SetReconnect(dwInterval,bEnableRecon);
    }
    else
    {
        return false;
    }
}

long Alarm_HC::M_NET_DVR_Login_V30(char *sDVRIP, WORD wDVRPort, char *sUserName, char *sPassword, LPNET_DVR_DEVICEINFO_V30 lpDeviceInfo)
{

    if(fun_NET_DVR_Login_V30)
    {
        return fun_NET_DVR_Login_V30(sDVRIP,wDVRPort,sUserName,sPassword,lpDeviceInfo);
    }
    else
    {
        return -1;
    }
}

bool Alarm_HC::M_NET_DVR_SetDVRMessageCallBack_V30(MSGCallBack fMessageCallBack, void *pUser)
{

    if(fun_NET_DVR_SetDVRMessageCallBack_V30)
    {
        return fun_NET_DVR_SetDVRMessageCallBack_V30(fMessageCallBack,pUser);
    }
    else
    {
        return false;
    }
}

long Alarm_HC::M_NET_DVR_StartListen_V30(char *sLocalIP, WORD wLocalPort, MSGCallBack DataCallback, void *pUserData)
{

    if(fun_NET_DVR_StartListen_V30)
    {
        return fun_NET_DVR_StartListen_V30(sLocalIP,wLocalPort,DataCallback,pUserData);
    }
    else
    {
        return -1;
    }
}

bool Alarm_HC::M_NET_DVR_Logout_V30(LONG lUserID)
{

    if(fun_NET_DVR_Logout_V30)
    {
        return fun_NET_DVR_Logout_V30(lUserID);
    }
    else
    {
        return false;
    }
}

bool Alarm_HC::M_NET_DVR_StopListen_V30(LONG lListenHandle)
{

    if(fun_NET_DVR_StopListen_V30)
    {
        return fun_NET_DVR_StopListen_V30(lListenHandle);
    }
    else
    {
        return false;
    }
}
