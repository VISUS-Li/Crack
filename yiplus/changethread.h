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

class changeThread : public QThread
{
public:
    changeThread(QTableWidget *, int );
    bool returnURLCheck(QJsonDocument );

private:
    QTableWidget *table;
    int currentRow;
    QString userID, memberID, passWord, token;

    QJsonDocument logInReturn;
    QJsonDocument homePageReturn;
    QJsonDocument goodsListReturn;
    QJsonDocument goodInfoReturn;
    QJsonDocument exchangeGoodReturn;

    void signIN();

private slots:
    void replyHomePage(QNetworkReply*);
    void replyGoodsList(QNetworkReply *);
    void replyGoodInfo(QNetworkReply *);
    void replyGoodChange(QNetworkReply *);

protected:
    void run();
};

#endif // CHANGETHREAD_H
