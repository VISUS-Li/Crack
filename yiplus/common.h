#ifndef COMMON_H
#define COMMON_H

#include <QJsonDocument>

static QString homePageURL = "https://crm.iy-cd.com/wns-ciycrmapp/appHomeController/getHomePage?";
static QString homeCtrlURL = "https://crm.iy-cd.com/wns-ciycrmapp/appHomeController/";

typedef struct _memberInfo_t {
    QString userID;
    QString memberID;
    QString passWord;
    QString token;

}memberInfo_t;

#endif // COMMON_H
