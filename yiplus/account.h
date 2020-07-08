#ifndef ACCOUNT_H
#define ACCOUNT_H

#include<QString>

class Account
{
public:
    Account(QString phone, QString pwd);

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
private:
    QString m_QStrPhoneNumber;
    QString m_QStrPassWord;
};

#endif // ACCOUNT_H
