#include "changethread.h"
#include "common.h"

changeThread::changeThread(memberInfo_t *memInfo)
{

    userID = memInfo->userID;
    //memberID = memInfo->memberID;
    passWord = memInfo->passWord;
    //token = memInfo->token;

}

void  changeThread::run()
{
    int cnt=0;
    signIN();
    while (1) {
        if( requestRet ) {
            if( !changeRet) {
                usleep(100000);
                changeGoods();
                cnt++;
                qDebug() << "请求结果:" << changeRet <<"请求兑换次数: " << cnt;
            }
        }
    }

}

void changeThread::changeGoods()
{
    QString changeURL = CtrlURL;
    QNetworkAccessManager *changeGoodsManager = new QNetworkAccessManager(this);
        QString paramURl = \
        QString("recordid=218&level=1&storeId=001&goodsId=467&eid=544&pikeId=&isspike=2&memberid=%1&memberId=%2&mobile=%3&token=%4&language=zh&store=001")\
                .arg(memberID).arg(memberID).arg(userID).arg(token);

        changeURL = changeURL + change + "?";
        changeURL = changeURL + paramURl;

        QNetworkRequest request(changeURL);
        QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        QHttpPart *formdata = new QHttpPart;

        formdata->setHeader(QNetworkRequest::ContentDispositionHeader,
                            QVariant(QString("form-data; changeCount=\"2\";recordid=\"218\";goodsId=\"467\";storeId=\"001\";eid=\"544\";pikeId=\"\";isspike=\"2\";validate=\"\""
                                             "memberid=\"%1\";memberid=\"%2\"; mobile=\"%3\";token=\"%4\";language=\"zh\";store=\"001\";")\
                                     .arg(memberID).arg(memberID).arg(userID).arg(token)));
         multi_part->append(*formdata);
         QNetworkReply *reply = changeGoodsManager->post(request, multi_part);

         //连接请求结束信号
         connect(changeGoodsManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyGoodChange(QNetworkReply *)));
         //连接响应时返回数据信号
         connect(reply, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
}


void changeThread::signIN()
{
    /* create url */
    logInURL = logInURL + "phoneNumber=" + userID + "&";
    logInURL = logInURL + "password=" + "GCN0kn9VEM5pc7zPakk2YA==";



    qDebug() << "logInURL" << logInURL;

    //create url request
    QNetworkRequest request(logInURL);
    QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart *formdata = new QHttpPart;
    formdata->setHeader(QNetworkRequest::ContentDispositionHeader,
                        QVariant(QString("form-data; phoneNumber=\"15002326234\";password=\"GCN0kn9VEM5pc7zPakk2YA==\";")));
    multi_part->append(*formdata);
    QNetworkAccessManager *netWorkManager = new QNetworkAccessManager;

    QNetworkReply *reply = netWorkManager->post(request, multi_part);

    //连接请求结束信号
    connect(netWorkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    //连接响应时返回数据信号
    connect(reply, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
}


void changeThread::replyFinished(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();

    QJsonParseError json_error;
    QJsonDocument document = QJsonDocument::fromJson(data, &json_error);

    if(json_error.error == QJsonParseError::NoError)
    {
        qDebug() << document;
        if(document.isObject())
        {
            QJsonObject obj = document.object();
            //解析反馈请求结果
            if(obj.contains("flag"))
            {
                 bool flag = obj.take("flag").toBool();
                 qDebug() << "登录请求返回结果：" << flag;
                 if ( true != flag) {
                     requestRet = false;
                     return;
                 } else  {
                   return;
                 }
            }
            if ( obj.contains("result") ) {
                    QJsonObject result = obj.take("result").toObject();
                    if( result.contains("phoneNumber") ) {
                        userID  = result.take("phoneNumber").toString();
                        qDebug() << "账号:" << userID;
                    }
                    if ( result.contains("memberid") ) {
                        memberID = result.take("memberid").toString();
                        qDebug() << "会员ID: " << memberID;
                    }
                    if ( result.contains("token") ) {
                        token = result.take("token").toString();
                        qDebug() << "token:" << token;
                    }
                }
        }
    }
    getHomePage();
}


void changeThread::getHomePage()
{
    QNetworkAccessManager *homePageManager = new QNetworkAccessManager(this);
       QString paramURl = \
       QString("start=0&length=15&store=001&memberid=%1&memberId=%2&mobile=%3&token=%4&language=zh")\
               .arg(memberID).arg(memberID).arg(userID).arg(token);

       homePageURL = homePageURL + paramURl;

       QNetworkRequest request(homePageURL);
       QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);
       QHttpPart *formdata = new QHttpPart;

       formdata->setHeader(QNetworkRequest::ContentDispositionHeader,
                           QVariant(QString("form-data; start=\"0\";length=\"15==\";store=\"001\";memberid=\"%1\";memberid=\"%2\"; mobile=\"%3\";token=\"%4\";language=\"zh\"")\
                                    .arg(memberID).arg(memberID).arg(userID).arg(token)));
        multi_part->append(*formdata);
        QNetworkReply *reply = homePageManager->get(request);

        //连接请求结束信号
        connect(homePageManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyHomePage(QNetworkReply*)));
        //连接响应时返回数据信号
        connect(reply, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
}


void changeThread::replyHomePage(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();

        QJsonParseError json_error;
        QJsonDocument document = QJsonDocument::fromJson(data, &json_error);

        if(json_error.error == QJsonParseError::NoError)
        {
            qDebug() << document;
            if(document.isObject())
            {
                QJsonObject obj = document.object();
                //解析反馈请求结果
                if(obj.contains("flag")) {
                     bool flag = obj.take("flag").toBool();
                     qDebug() << "主页请求返回结果：" << flag;
                     if ( true != flag) {
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
        getGoodsList();
}


void changeThread::getGoodsList()
{
    QNetworkAccessManager *goodsListManager = new QNetworkAccessManager(this);
        QString paramURl = \
        QString("giftKbn=-1&orderBy=3&storeCode=001&memberid=%1&memberId=%2&mobile=%3&token=%4&language=zh&store=001")\
                .arg(memberID).arg(memberID).arg(userID).arg(token);
        QString homeCtrlURL = CtrlURL;
        homeCtrlURL = homeCtrlURL + changeList + "?";
        homeCtrlURL = homeCtrlURL + paramURl;

        QNetworkRequest request(homeCtrlURL);
        QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        QHttpPart *formdata = new QHttpPart;

        formdata->setHeader(QNetworkRequest::ContentDispositionHeader,
                            QVariant(QString("form-data; giftKbn=\"-1\";orderBy=\"3\";storeCode=\"001\";memberid=\"%1\";memberid=\"%2\"; mobile=\"%3\";token=\"%4\";language=\"zh\";store=\"001\";")\
                                     .arg(memberID).arg(memberID).arg(userID).arg(token)));
         multi_part->append(*formdata);
         QNetworkReply *reply = goodsListManager->get(request);

         //连接请求结束信号
         connect(goodsListManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyGoodsList(QNetworkReply*)));
         //连接响应时返回数据信号
         connect(reply, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
}

void changeThread::replyGoodsList(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();

        QJsonParseError json_error;
        QJsonDocument document = QJsonDocument::fromJson(data, &json_error);

        if(json_error.error == QJsonParseError::NoError)
        {
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
        getGoodsInfo();
}


void changeThread::getGoodsInfo()
{
    QNetworkAccessManager *goodInfoManager = new QNetworkAccessManager(this);
        //测试，获取指甲钳商品详细信息
        QString paramURl = \
        QString("recordid=535&level=1&storeId=001&goodsId=585&eid=978&pikeId=&isspike=0&memberid=%1&memberId=%2&mobile=%3&token=%4&language=zh&store=001")\
                .arg(memberID).arg(memberID).arg(userID).arg(token);
        QString homeCtrlURL = CtrlURL;
        homeCtrlURL = homeCtrlURL + detail + "?";
        homeCtrlURL = homeCtrlURL + paramURl;

        QNetworkRequest request(homeCtrlURL);
        QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        QHttpPart *formdata = new QHttpPart;

        formdata->setHeader(QNetworkRequest::ContentDispositionHeader,
                            QVariant(QString("recordid=\"218\";level=\"1\";storeId=\"001\";goodsId=\"467\";eid=\"544\";pikeId=\"\";isspike=\"2\";memberid=\"%1\""
                                             "memberid=\"%2\";mobile=\"%3\";token=\"%4\";language=\"zh\";store=\"001\";")\
                                     .arg(memberID).arg(memberID).arg(userID).arg(token)));

         multi_part->append(*formdata);
         QNetworkReply *reply = goodInfoManager->post(request, multi_part);

         //连接请求结束信号
         connect(goodInfoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyGoodInfo(QNetworkReply*)));
         //连接响应时返回数据信号
         connect(reply, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
}

void changeThread::replyGoodInfo(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();

       QJsonParseError json_error;
       QJsonDocument document = QJsonDocument::fromJson(data, &json_error);

       if(json_error.error == QJsonParseError::NoError)
       {

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

                        return;
                    } else  {
                       goodInfoReturn = document;
                       qDebug() << goodInfoReturn;

                       if( obj.contains("result") ) {
                           QJsonObject resultObj = obj.take("result").toObject();
                           if( resultObj.contains("nextRoad") ) {
                               QJsonObject nextRoadObj = resultObj.take("nextRoad").toObject();
                               if( nextRoadObj.contains("change") ) {
                                   change = nextRoadObj.take("change").toString();
                               }
                           }

                       }
                    }
               }
           }
       }
       requestRet = true;
}

void changeThread::replyGoodChange(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();

    QJsonParseError json_error;
    QJsonDocument document = QJsonDocument::fromJson(data, &json_error);

    if(json_error.error == QJsonParseError::NoError)
    {
        qDebug() << document;
        if(document.isObject())
        {
            QJsonObject obj = document.object();
            //解析反馈请求结果
            if(obj.contains("flag"))
            {
                 bool flag = obj.take("flag").toBool();
                 qDebug() << "登录请求返回结果：" << flag;
                 if ( true != flag) {
                     changeRet = false;
                     return;
                 } else  {
                    changeRet = true;
                    return;
                 }
            }
        }
    }
}


void changeThread::on_readyRead()
{

}

