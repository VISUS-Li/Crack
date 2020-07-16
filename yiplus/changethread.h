#ifndef CHANGETHREAD_H
#define CHANGETHREAD_H

#include <QThread>
#include <QTableWidget>
#include <QJsonDocument>
#include <QTimer>
#include <QApplication>
#include <QDebug>
#include <QTcpSocket>
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonObject>
#include <QMutex>
#include <QNetworkProxy>
#include "common.h"
#include "util.h"

class changeThread : public QThread
{
    Q_OBJECT
public:
    changeThread(memberInfo_t *memInfo);
    bool returnURLCheck(QJsonDocument );
    bool isLogInTest = false;
    void setStopValue(bool value);
    inline bool getStopStatus(){
        return isStop;
    }
    inline void setUseProxy(bool flag){
        mutex.lock();
        useProxy = flag;
        mutex.unlock();
    }
    inline void setIsLoginTest(bool flag){
        isLogInTest = flag;
    }

private:
    bool isStop = false;
    QTableWidget *table;
    int currentRow;
    QString userID, memberID, passWord, token, changeList, detail, change, store;
    QString recordid = "544", goodid = "617", eid = "999", isspike = "0", changeCount = "1";
    QString proxyIp = "";
    int proxyPort = 0;
    bool useProxy = false;
    QMutex mutex;

    JsonClass jsonReplay;

    bool loginRet = false/*登录状态*/, requestRet = false/*各个请求的统一状态*/, changeRet = false, isExpired = false;//用户信息过期

    QByteArray Post(QString uri, QString header);
    QByteArray Post_FormData(QString uri, QString form);
    QByteArray Get(QString uri);
    QByteArray Get_IPLocationTest();

    bool signIN();
    bool getHomePage();
    bool getGoodsList();
    bool getGoodsInfo();
    bool changeGoods();

    bool getProxyIp(QString &proxyIp, int &proxyPort);

private slots:
    bool replyFinished(QByteArray arry);
    bool replyHomePage(QByteArray arry);
    bool replyGoodsList(QByteArray arry);
    bool replyGoodInfo(QByteArray arry);
    bool replyGoodChange(QByteArray arrys);

protected:
    void run();

signals:
    void UserStop();//用户停止的信号
};

#endif // CHANGETHREAD_H
