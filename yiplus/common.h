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
#define SN_Chunxi       "春熙店"
#define SN_Shuangnan    "双楠店"
#define SN_Jinhua       "锦华店"
#define SN_Jianshelu    "建设路店"
#define SN_Gaoxin       "高新店"
#define SN_Wenjiang     "温江店"
#define SN_Meishan      "眉山店"
#define SN_Lvdi         "绿地店"
#define SN_Leshan       "乐山店"
#define SN_Huafudadao   "华府大道店"

#define SC_Chunxi       "001"
#define SC_Shuangnan    "002"
#define SC_Jinhua       "003"
#define SC_Jianshelu    "004"
#define SC_Gaoxin       "005"
#define SC_Wenjiang     "006"
#define SC_Meishan      "007"
#define SC_Lvdi         "008"
#define SC_Leshan       "009"
#define SC_Huafudadao   "101"

#endif // COMMON_H
