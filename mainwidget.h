#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QApplication>
#include <QDebug>
#include <QTcpSocket>
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QJsonDocument logInReturn, QWidget *signIN, QWidget *parent = nullptr);
    ~Form();

    void getHomePage();

private:
    Ui::Form *ui;

    QTimer *showTime;

    QJsonDocument logInReturn;
    QJsonDocument homePageReturn;
    QJsonDocument goodsListReturn;
    QJsonDocument goodInfoReturn;
    QJsonDocument exchangeGoodReturn;

    QString phoneNumber, memberId, token, giftKbn, orderBy, storeCode, store;
    QString changeList, detail;

    QString homePageURL = "https://crm.iy-cd.com/wns-ciycrmapp/appHomeController/getHomePage?";
    QString goodsListURL = "https://crm.iy-cd.com/wns-ciycrmapp/appHomeController/";
    QString goodInfoURL = "https://crm.iy-cd.com/wns-ciycrmapp/appHomeController/";
    QString exchangeGoodURL = "https://crm.iy-cd.com/wns-ciycrmapp/appHomeController/";

private slots:
    void changeTime();
    void replyHomePage(QNetworkReply*);
    void replyGoodsList(QNetworkReply *);
    void replyGoodInfo(QNetworkReply *);
    //void exchangeGoodReturn(QNetworkReply *);

    void on_pB_getHomePage_clicked();
    void on_pB_getGoodsList_clicked();
    void on_pBgetGoodsInfo_clicked();
};

#endif // MAINWIDGET_H
