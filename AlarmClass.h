#ifndef ALARMCLASS_H
#define ALARMCLASS_H

#include "stable.h"

class AlarmClass{
public:
    //设置参数
    void SetAlarmID(int m_AlarmID)
    {
        AlarmID = m_AlarmID;
    }

    void SetSpeakWord(QString m_SpeakWord)
    {
        SpeakWord = m_SpeakWord ;
    }

    void SetLEDWord(QString m_LEDWord)
    {
        LEDWord = m_LEDWord ;
    }

    void SetVoicePath(QString m_VoicePath)
    {
        VoicePath = m_VoicePath ;
    }

    //获取参数
    int GetAlarmID()
    {
        return AlarmID;
    }

    QString GetSpeakWord()
    {
        return SpeakWord;
    }

    QString GetLEDWord()
    {
        return LEDWord;
    }

    QString GetVoicePath()
    {
        return VoicePath;
    }

private:
    int  AlarmID ;
    QString  SpeakWord;
    QString LEDWord;
    QString VoicePath;
};

#endif // ALARMCLASS_H
