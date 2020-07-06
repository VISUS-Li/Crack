#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QApplication>
#include <QDebug>
#include <QTcpSocket>
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "mainwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private slots:
    void on_pB_signUp_clicked();

    void on_pB_signIn_clicked();

    void replyFinished(QNetworkReply*);

    void on_readyRead();

private:
    Ui::Widget *ui;

    QString logInURL = "https://crm.iy-cd.com/wns-ciycrmapp/appLoginController/passwordLogin?";
};
#endif // WIDGET_H
