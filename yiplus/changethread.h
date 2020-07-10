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

class changeThread : public QThread
{
    Q_OBJECT
public:
    changeThread(memberInfo_t *memInfo);
    bool returnURLCheck(QJsonDocument );

private:
    QTableWidget *table;
    int currentRow;
    QString userID, memberID, passWord, token, changeList,detail, change;

    bool requestRet = false, changeRet = false;

    QJsonDocument logInReturn;
    QJsonDocument homePageReturn;
    QJsonDocument goodsListReturn;
    QJsonDocument goodInfoReturn;
    QJsonDocument exchangeGoodReturn;

    void signIN();
    void getHomePage();
    void getGoodsList();
    void getGoodsInfo();
    void changeGoods();

private slots:
    void replyFinished(QNetworkReply*);
    void replyHomePage(QNetworkReply*);
    void replyGoodsList(QNetworkReply *);
    void replyGoodInfo(QNetworkReply *);
    void replyGoodChange(QNetworkReply *reply);
    void on_readyRead();


protected:
    void run();
};

#endif // CHANGETHREAD_H
