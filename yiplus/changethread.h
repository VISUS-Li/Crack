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

#include "common.h"
#include "util.h"

class changeThread : public QThread
{
    Q_OBJECT
public:
    changeThread(memberInfo_t *memInfo);
    bool returnURLCheck(QJsonDocument );

private:
    QTableWidget *table;
    int currentRow;
    QString userID, memberID, passWord, token, changeList, detail, change, store;
    QString recordid = "535", goodid = "585", eid = "978", isspike = "0", changeCount = "2";
    JsonClass jsonReplay;

    bool loginRet = false/*登录状态*/, requestRet = false/*各个请求的统一状态*/, changeRet = false, isExpired = false;//用户信息过期

    QByteArray Post(QString uri, QString header);
    QByteArray Get(QString uri);

    void signIN();
    void getHomePage();
    void getGoodsList();
    void getGoodsInfo();
    void changeGoods();

private slots:
    void replyFinished(QByteArray arry);
    void replyHomePage(QByteArray arry);
    void replyGoodsList(QByteArray arry);
    void replyGoodInfo(QByteArray arry);
    void replyGoodChange(QByteArray arrys);


protected:
    void run();
};

#endif // CHANGETHREAD_H
