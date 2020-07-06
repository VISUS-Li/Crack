#include "mainwidget.h"
#include "ui_mainwidget.h"

Form::Form(QJsonDocument logInReturn, QWidget *signIN, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    this->setWindowTitle("yiplus");

    this->logInReturn = logInReturn;

    ui->lb_runNotice->setStyleSheet("color:green;");
    ui->lb_runNotice->setText("解析登录返回的数据...");
    ui->tE_runningStat->setText(logInReturn.toJson());

    showTime = new QTimer(this);
    connect(showTime, SIGNAL(timeout()), this, SLOT(changeTime()));
    showTime->start(1000);

    QJsonObject obj = logInReturn.object();

    if ( obj.contains("result") ) {
        QJsonObject result = obj.take("result").toObject();
        if( result.contains("phoneNumber") ) {
            phoneNumber  = result.take("phoneNumber").toString();
            ui->lb_showPhone->setText(phoneNumber);
        }
        if ( result.contains("memberid") ) {
            memberId = result.take("memberid").toString();
            ui->lb_showMemID->setText(memberId);
        } else {
            QMessageBox::information(this, "ERROR", "没有解析到用户ID，无法进行下一步");
            this->close();
            signIN->show();
        }
        if ( result.contains("token") ) {
            token = result.take("token").toString();
            ui->lb_showToken->setText(token);
        } else {
            QMessageBox::information(this, "ERROR", "没有解析到token，无法进行下一步");
            this->close();
            signIN->show();
        }
    }

}

Form::~Form()
{
    delete ui;
}

void Form::getHomePage()
{
    ui->lb_runNotice->setText("获取首页信息...");
    QNetworkAccessManager *homePageManager = new QNetworkAccessManager(this);
    QString paramURl = \
    QString("start=0&length=15&store=001&memberid=%1&memberId=%2&mobile=%3&token=%4&language=zh")\
            .arg(memberId).arg(memberId).arg(phoneNumber).arg(token);

    homePageURL = homePageURL + paramURl;

    QNetworkRequest request(homePageURL);
    QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart *formdata = new QHttpPart;

    formdata->setHeader(QNetworkRequest::ContentDispositionHeader,
                        QVariant(QString("form-data; start=\"0\";length=\"15==\";store=\"001\";memberid=\"%1\";memberid=\"%2\"; mobile=\"%3\";token=\"%4\";language=\"zh\"")\
                                 .arg(memberId).arg(memberId).arg(phoneNumber).arg(token)));
     multi_part->append(*formdata);
     QNetworkReply *reply = homePageManager->get(request);

     //连接请求结束信号
     connect(homePageManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyHomePage(QNetworkReply*)));
     //连接响应时返回数据信号
     connect(reply, SIGNAL(readyRead()), this, SLOT(on_readyRead()));

    return ;
}

void Form::changeTime()
{
    ui->lb_showTime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}



void Form::replyHomePage(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();

    QJsonParseError json_error;
    QJsonDocument document = QJsonDocument::fromJson(data, &json_error);

    if(json_error.error == QJsonParseError::NoError)
    {
        ui->tE_runningStat->append(document.toJson());
        qDebug() << document;
        if(document.isObject())
        {
            QJsonObject obj = document.object();
            //解析反馈请求结果
            if(obj.contains("flag")) {
                 bool flag = obj.take("flag").toBool();
                 qDebug() << "主页请求返回结果：" << flag;
                 if ( true != flag) {
                     ui->lb_runNotice->setStyleSheet("color:red;");
                     ui->lb_runNotice->setText("请求获取主页失败！");
                     return;
                 } else  {
                    homePageReturn = document;
                    qDebug() << homePageReturn;
                 }
            }
            if(obj.contains("result")) {
                QJsonObject resultObj = obj.take("result").toObject();
                if( resultObj.contains("nextRoad") ) {
                    QJsonObject nextroadObj = resultObj.take("nextRoad").toObject();
                    if ( nextroadObj.contains("changeList") ) {
                        changeList = nextroadObj.take("changeList").toString();
                    }
                }
            }
        }
    }
}

/*
 * 按下获取主页按钮，获取主页信息
 * 将返回的json数据放在homePageReturn中
 */
void Form::on_pB_getHomePage_clicked()
{
    getHomePage();
}



//获取商品列表返回
void Form::replyGoodsList(QNetworkReply *reply)
{
    ui->lb_runNotice->setText("获取兑换商品列表返回...");
    QByteArray data = reply->readAll();

    QJsonParseError json_error;
    QJsonDocument document = QJsonDocument::fromJson(data, &json_error);

    if(json_error.error == QJsonParseError::NoError)
    {
        ui->tE_runningStat->setText(document.toJson());
        qDebug() << document;
        if(document.isObject())
        {
            QJsonObject obj = document.object();
            //解析反馈请求结果
            if(obj.contains("flag"))
            {
                 bool flag = obj.take("flag").toBool();
                 qDebug() << "商品列表请求返回结果：" << flag;
                 if ( true != flag) {
                     ui->lb_runNotice->setStyleSheet("color:red;");
                     ui->lb_runNotice->setText("请求获取商品列表失败！");
                     return;
                 } else  {
                    goodsListReturn = document;
                    qDebug() << goodsListReturn;
                 }
            }
            if( obj.contains("result") ) {
                QJsonObject resultObj = obj.take("result").toObject();
                if( resultObj.contains("nextRoad") ) {
                    QJsonObject nextRoadObj = resultObj.take("nextRoad").toObject();
                    if( nextRoadObj.contains("detail") ) {
                        detail = nextRoadObj.take("detail").toString();
                    }
                }

            }
        }
    }
}

/*
 *  按钮获取兑换商品列表
 *  将返回的json数据放在goodsListReturn中
 *  将商品信息填充在tabel widget中
 */
void Form::on_pB_getGoodsList_clicked()
{
    ui->lb_runNotice->setText("获取兑换商品列表...");
    QNetworkAccessManager *goodsListManager = new QNetworkAccessManager(this);
    QString paramURl = \
    QString("giftKbn=-1&orderBy=3&storeCode=001&memberid=%1&memberId=%2&mobile=%3&token=%4&language=zh&store=001")\
            .arg(memberId).arg(memberId).arg(phoneNumber).arg(token);

    goodsListURL = goodsListURL + changeList + "?";
    goodsListURL = goodsListURL + paramURl;

    QNetworkRequest request(goodsListURL);
    QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart *formdata = new QHttpPart;

    formdata->setHeader(QNetworkRequest::ContentDispositionHeader,
                        QVariant(QString("form-data; giftKbn=\"-1\";orderBy=\"3\";storeCode=\"001\";memberid=\"%1\";memberid=\"%2\"; mobile=\"%3\";token=\"%4\";language=\"zh\";store=\"001\";")\
                                 .arg(memberId).arg(memberId).arg(phoneNumber).arg(token)));
     multi_part->append(*formdata);
     QNetworkReply *reply = goodsListManager->get(request);

     //连接请求结束信号
     connect(goodsListManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyGoodsList(QNetworkReply*)));
     //连接响应时返回数据信号
     connect(reply, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
}



void Form::replyGoodInfo(QNetworkReply * reply)
{
    QByteArray data = reply->readAll();

    QJsonParseError json_error;
    QJsonDocument document = QJsonDocument::fromJson(data, &json_error);

    if(json_error.error == QJsonParseError::NoError)
    {
        ui->tE_runningStat->setText(document.toJson());
        qDebug() << document;
        if(document.isObject())
        {
            QJsonObject obj = document.object();
            //解析反馈请求结果
            if(obj.contains("flag"))
            {
                 bool flag = obj.take("flag").toBool();
                 qDebug() << "商品详细信息请求返回结果：" << flag;
                 if ( true != flag) {
                     ui->lb_runNotice->setStyleSheet("color:red;");
                     ui->lb_runNotice->setText("请求商品详细信息失败！");
                     return;
                 } else  {
                    goodInfoReturn = document;
                    qDebug() << goodInfoReturn;
                 }
            }
        }
    }
}


void Form::on_pBgetGoodsInfo_clicked()
{
    ui->lb_runNotice->setText("获取商品详细信息...");
    QNetworkAccessManager *goodInfoManager = new QNetworkAccessManager(this);
    //测试，获取指甲钳商品详细信息
    QString paramURl = \
    QString("recordid=535&level=1&storeId=001&goodsId=585&eid=978&pikeId=&isspike=0&memberid=%1&memberId=%2&mobile=%3&token=%4&language=zh&store=001")\
            .arg(memberId).arg(memberId).arg(phoneNumber).arg(token);

    goodInfoURL = goodInfoURL + detail + "?";
    goodInfoURL = goodInfoURL + paramURl;

    QNetworkRequest request(goodInfoURL);
    QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart *formdata = new QHttpPart;

    formdata->setHeader(QNetworkRequest::ContentDispositionHeader,
                        QVariant(QString("recordid=\"535\";level=\"1\";storeId=\"001\";goodsId=\"585\";eid=\"978\";pikeId=\"\";isspike=\"0\";memberid=\"%1\""
                                         "memberid=\"%2\";mobile=\"%3\";token=\"%4\";language=\"zh\";store=\"001\";")\
                                 .arg(memberId).arg(memberId).arg(phoneNumber).arg(token)));

     multi_part->append(*formdata);
     QNetworkReply *reply = goodInfoManager->post(request, multi_part);

     //连接请求结束信号
     connect(goodInfoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyGoodInfo(QNetworkReply*)));
     //连接响应时返回数据信号
     connect(reply, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
}










