#ifndef COMMON_H
#define COMMON_H

#include <QJsonDocument>

static const QString logInURL = "https://crm.iy-cd.com/wns-ciycrmapp/appLoginController/passwordLogin?";
static const QString homePageURL = "https://crm.iy-cd.com/wns-ciycrmapp/appHomeController/getHomePage?";
static const QString CtrlURL = "https://crm.iy-cd.com/wns-ciycrmapp/appHomeController/";

typedef struct _memberInfo_t {
    QString userID;
    QString memberID;
    QString passWord;
    QString token;

}memberInfo_t;

#endif // COMMON_H
