#include "account.h"

Account::Account(QString phone, QString pwd, QString store)
{
    Enable = true;
    m_QStrPhoneNumber = phone;
    m_QStrPassWord = pwd;
    m_QStrStore = store;
    Status = "未开始";
    if(store == ""){
        m_QStrStore = "001";//默认春熙路
    }
}

