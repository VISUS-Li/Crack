#include "account.h"

Account::Account(QString phone, QString pwd)
{
    m_QStrPhoneNumber = phone;
    m_QStrPassWord = pwd;
}

QString Account::AesEncrypt(){
}
