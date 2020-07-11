#include "account.h"

Account::Account(QString phone, QString pwd, QString store)
{
    m_QStrPhoneNumber = phone;
    m_QStrPassWord = pwd;
    m_QStrStore = store;
    if(store == ""){
        m_QStrStore = "001";//默认春熙路
    }
}

QString Account::AesEncrypt(){
}
