#ifndef COMMON_H
#define COMMON_H

#include <QJsonDocument>


static  QString logInURL = "https://crm.iy-cd.com/wns-ciycrmapp/appLoginController/passwordLogin";
static  QString homePageURL = "https://crm.iy-cd.com/wns-ciycrmapp/appHomeController/getHomePage?";
static  QString CtrlURL = "https://crm.iy-cd.com/wns-ciycrmapp/appHomeController/";
static  QString ProxyUrl = "http://http.9vps.com/getip.asp?";


typedef struct _memberInfo_t {
    QString userID;
    QString memberID;
    QString passWord;
    QString token;
    QString store;//店铺ID

}memberInfo_t;

#endif // COMMON_H
