#ifndef ALARM_HC_H
#define ALARM_HC_H

#include "stable.h"
#include "HCSDK\HCNetSDK.h"
#include <QLibrary>

class Alarm_HC
{
public:
    Alarm_HC(QWidget *parent);

//    BOOL __stdcall NET_DVR_Init();
        typedef bool (*NET_DVR_Init)();
        NET_DVR_Init fun_NET_DVR_Init;
        bool  M_NET_DVR_Init();

//    BOOL __stdcall NET_DVR_Cleanup();
        typedef bool (*NET_DVR_Cleanup)();
        NET_DVR_Cleanup fun_NET_DVR_Cleanup;
        bool  M_NET_DVR_Cleanup();

//    BOOL __stdcall NET_DVR_SetConnectTime(DWORD dwWaitTime = 3000, DWORD dwTryTimes = 3);
        typedef bool (*NET_DVR_SetConnectTime)(DWORD,DWORD);
        NET_DVR_SetConnectTime fun_NET_DVR_SetConnectTime;
        bool  M_NET_DVR_SetConnectTime(DWORD dwWaitTime = 3000, DWORD dwTryTimes = 3);

//    BOOL __stdcall NET_DVR_SetReconnect(DWORD dwInterval = 30000, BOOL bEnableRecon = TRUE);
        typedef bool (*NET_DVR_SetReconnect)(DWORD,BOOL);
        NET_DVR_SetReconnect fun_NET_DVR_SetReconnect;
        bool  M_NET_DVR_SetReconnect(DWORD dwInterval = 30000, BOOL bEnableRecon = TRUE);

//    LONG __stdcall NET_DVR_Login_V30(char *sDVRIP, WORD wDVRPort, char *sUserName, char *sPassword, LPNET_DVR_DEVICEINFO_V30 lpDeviceInfo);
        typedef long (*NET_DVR_Login_V30)(char *,WORD,char *,char *,LPNET_DVR_DEVICEINFO_V30);
        NET_DVR_Login_V30 fun_NET_DVR_Login_V30;
        long  M_NET_DVR_Login_V30(char *sDVRIP, WORD wDVRPort, char *sUserName, char *sPassword, LPNET_DVR_DEVICEINFO_V30 lpDeviceInfo);

//    BOOL __stdcall NET_DVR_SetDVRMessageCallBack_V30(MSGCallBack fMessageCallBack, void* pUser);
        typedef bool (*NET_DVR_SetDVRMessageCallBack_V30)(MSGCallBack,void*);
        NET_DVR_SetDVRMessageCallBack_V30 fun_NET_DVR_SetDVRMessageCallBack_V30;
        bool  M_NET_DVR_SetDVRMessageCallBack_V30(MSGCallBack fMessageCallBack, void* pUser);

//    LONG __stdcall NET_DVR_StartListen_V30(char *sLocalIP, WORD wLocalPort, MSGCallBack DataCallback, void* pUserData = NULL);
        typedef long (*NET_DVR_StartListen_V30)(char *,WORD,MSGCallBack,void*);
        NET_DVR_StartListen_V30 fun_NET_DVR_StartListen_V30;
        long  M_NET_DVR_StartListen_V30(char *sLocalIP, WORD wLocalPort, MSGCallBack DataCallback, void* pUserData = NULL);

//    BOOL __stdcall NET_DVR_Logout_V30(LONG lUserID);
        typedef bool (*NET_DVR_Logout_V30)(LONG);
        NET_DVR_Logout_V30 fun_NET_DVR_Logout_V30;
        bool  M_NET_DVR_Logout_V30(LONG lUserID);

//    BOOL __stdcall NET_DVR_StopListen_V30(LONG lListenHandle);
        typedef bool (*NET_DVR_StopListen_V30)(LONG);
        NET_DVR_StopListen_V30 fun_NET_DVR_StopListen_V30;
        bool  M_NET_DVR_StopListen_V30(LONG lListenHandle);

private:
        QWidget *parent ;
        bool   IsLoad;
};

#endif // ALARM_HC_H
