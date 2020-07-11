#ifndef ACCOUNT_H
#define ACCOUNT_H

#include<QString>

class Account
{
public:
    Account(QString phone, QString pwd, QString store);

    QString AesEncrypt();
    inline QString GetPoneNumber(){
        return m_QStrPhoneNumber;
    }
    inline QString GetPassWord(){
        return m_QStrPassWord;
    }
    inline void SetPhoneNumber(QString newPhone){
        m_QStrPhoneNumber = newPhone;
    }
    inline void SetPassWord(QString newPwd){
        m_QStrPassWord = newPwd;
    }
    inline QString GetStore(){
        return m_QStrStore;
    }
    inline void SetStore(QString store){
        m_QStrStore = store;
    }
    //外界需要free掉
    inline char* QString2Char(QString str){
        char *chStr = NULL;
         QByteArray ba = str.toLatin1();
         chStr = (char *)malloc(ba.length() + 1);
         memset(chStr, 0, ba.length());
         memcpy(chStr, ba.data(), ba.length());
         chStr[ba.length()] = '\0';
         return chStr;
    }

    inline void setEnable(bool flag){
        Enable = flag;
    }

    inline bool isEnable(){
        return Enable;
    }
private:
    QString m_QStrPhoneNumber;
    QString m_QStrPassWord;
    QString m_QStrStore;//要兑换的店铺
    bool Enable;
};

#endif // ACCOUNT_H
