#include "changethread.h"
#include "common.h"
#include "util.h"
changeThread::changeThread(memberInfo_t *memInfo)
{

    userID = memInfo->userID;
    //memberID = memInfo->memberID;
    passWord = memInfo->passWord;
    //token = memInfo->token;
    store = memInfo->store;
    if(memInfo){
        delete memInfo;
        memInfo = NULL;
    }

}

void  changeThread::run()
{
    jsonReplay.Reset();
    int cnt=0;
    signIN();
    while (1) {
        if( requestRet ) {
            if( !changeRet) {
                usleep(100000);
                changeGoods();
                if(isExpired){
                    signIN();
                }
                cnt++;
                qDebug() << "请求结果:" << changeRet <<"请求兑换次数: " << cnt;
            }
        }
         CommonUtils::Instance()->WriteReplayLog(jsonReplay);
    }

}

void changeThread::changeGoods()
{
    QString changeURL = CtrlURL;
    QNetworkAccessManager *changeGoodsManager = new QNetworkAccessManager(this);
        QString paramURl = \
        QString("recordid=%1&level=1&storeId=%2&goodsId=%3&eid=%4&pikeId=&isspike=%5&memberid=%6&memberId=%7&mobile=%8&token=%9&language=zh&store="+store+"")\
                .arg(recordid).arg(store).arg(goodid).arg(eid).arg(isspike).arg(memberID).arg(memberID).arg(userID).arg(token);

        changeURL = changeURL + change + "?";
        changeURL = changeURL + paramURl;

        QNetworkRequest request(changeURL);
        QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        QHttpPart *formdata = new QHttpPart;

        formdata->setHeader(QNetworkRequest::ContentDispositionHeader,
                            QVariant(QString("form-data; changeCount=\"%1\";recordid=\"%2\";goodsId=\"%3\";storeId=\"%4\";eid=\"%5\";pikeId=\"\";isspike=\"%6\";validate=\"\""
                                             "memberid=\"%7\";memberid=\"%8\"; mobile=\"%9\";token=\""+token+"\";language=\"zh\";store=\""+store+"\";")\
                                     .arg(changeCount).arg(recordid).arg(store).arg(goodid).arg(eid).arg(isspike).arg(memberID).arg(memberID).arg(userID)));
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
    logInURL = logInURL + "password=" +passWord;



    qDebug() << "logInURL" << logInURL;

    //create url request
    QNetworkRequest request(logInURL);

    QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart *formdata = new QHttpPart;
    QString formStr = "form-data; phoneNumber=\""+userID+"\";password=\""+passWord+"\";";
    formdata->setHeader(QNetworkRequest::ContentDispositionHeader,
                        QVariant(formStr));
    multi_part->append(*formdata);
    QNetworkAccessManager *netWorkManager = new QNetworkAccessManager;

    QNetworkReply *reply = netWorkManager->post(request, multi_part);

    //连接请求结束信号

    connect(netWorkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)),Qt::DirectConnection);

    //connect(netWorkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    //连接响应时返回数据信号
    connect(reply, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
}


void changeThread::replyFinished(QNetworkReply *reply)
{

    qDebug() << "登录请求返回";

    QByteArray data = reply->readAll();
    QString replyStr(data);
    CommonUtils::Instance()->ParseLoginJson(replyStr,jsonReplay);
    token = jsonReplay.loginJson.Token;
    if(jsonReplay.loginJson.ResFlag == "true"){
        requestRet = true;
        isExpired = false;
        getHomePage();
    }else{
        requestRet = false;
        return;
    }
}


void changeThread::getHomePage()
{
    qDebug() << "开始请求主页";
    QNetworkAccessManager *homePageManager = new QNetworkAccessManager(this);
       QString paramURl = \
       QString("start=0&length=15&store=%1&memberid=%2&memberId=%3&mobile=%4&token=%5&language=zh")\
               .arg(store).arg(memberID).arg(memberID).arg(userID).arg(token);

//       QString homePage = homePageURL;
//       homePage = homePage + paramURl;

//       QNetworkRequest request(homePage);


       homePageURL = homePageURL + paramURl;

       QNetworkRequest request(homePageURL);

       QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);
       QHttpPart *formdata = new QHttpPart;
       QString formStr = QString("form-data; start=\"0\";length=\"15==\";store=\"%1\";memberid=\"%2\";memberid=\"%3\"; mobile=\"%4\";token=\"%5\";language=\"zh\"")\
               .arg(store).arg(memberID).arg(memberID).arg(userID).arg(token);
       formdata->setHeader(QNetworkRequest::ContentDispositionHeader,
                           QVariant(formStr));
        multi_part->append(*formdata);
        QNetworkReply *reply = homePageManager->get(request);

        //连接请求结束信号
        connect(homePageManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyHomePage(QNetworkReply*)));
        //连接响应时返回数据信号
        connect(reply, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
}


void changeThread::replyHomePage(QNetworkReply *reply)
{

    qDebug() << "请求主页返回";

    QByteArray data = reply->readAll();
    QString replyStr(data);
    CommonUtils::Instance()->ParseHomePageJson(replyStr,jsonReplay);
    changeList = jsonReplay.homePageJson.NextRoad_ChangeList.ChangeList;
    if(jsonReplay.homePageJson.ResFlag == "true"){
        requestRet = true;
        getGoodsList();
    }else{
        requestRet = false;
        return;
    }

}


void changeThread::getGoodsList()
{
    QNetworkAccessManager *goodsListManager = new QNetworkAccessManager(this);

        QString paramURl = \
        QString("giftKbn=-1&orderBy=3&storeCode=%1&memberid=%2&memberId=%3&mobile=%4&token=%5&language=zh&store=%6")\
                .arg(store).arg(memberID).arg(memberID).arg(userID).arg(token).arg(store);
        QString homeCtrlURL = CtrlURL;
        homeCtrlURL = homeCtrlURL + changeList + "?";
        homeCtrlURL = homeCtrlURL + paramURl;

        QNetworkRequest request(homeCtrlURL);
        QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        QHttpPart *formdata = new QHttpPart;

        formdata->setHeader(QNetworkRequest::ContentDispositionHeader,
                            QVariant(QString("form-data; giftKbn=\"-1\";orderBy=\"3\";storeCode=\"%1\";memberid=\"%2\";memberid=\"%3\"; mobile=\"%4\";token=\"%5\";language=\"zh\";store=\"%6\";")\
                                     .arg(store).arg(memberID).arg(memberID).arg(userID).arg(token).arg(store)));
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

    QString replyStr(data);
    CommonUtils::Instance()->ParseGoodListsJson(replyStr,jsonReplay);
    detail = jsonReplay.goodListJson.NextRoad.Detail;
    if(jsonReplay.goodListJson.ResFlag == "true"){
        requestRet = true;
        getGoodsInfo();
    }else{
        requestRet = false;
        return;
    }

}


void changeThread::getGoodsInfo()
{
    QNetworkAccessManager *goodInfoManager = new QNetworkAccessManager(this);
        //测试，获取指甲钳商品详细信息
        QString paramURl = \
        QString("recordid=%1&level=1&storeId=%2&goodsId=%3&eid=%4&pikeId=&isspike=%5&memberid=%6&memberId=%7&mobile=%8&token=%9&language=zh&store="+store+"")\
                .arg(recordid).arg(store).arg(goodid).arg(eid).arg(isspike).arg(memberID).arg(memberID).arg(userID).arg(token);
        QString homeCtrlURL = CtrlURL;
        homeCtrlURL = homeCtrlURL + detail + "?";
        homeCtrlURL = homeCtrlURL + paramURl;

        QNetworkRequest request(homeCtrlURL);
        QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        QHttpPart *formdata = new QHttpPart;
        QString formStr = QString("recordid=\"%1\";level=\"1\";storeId=\"%2\";goodsId=\"%3\";eid=\"%4\";pikeId=\"\";isspike=\"%5\";memberid=\"%6\""
                                  "memberid=\"%7\";mobile=\"%8\";token=\"%9\";language=\"zh\";store=\""+store+"\";")\
                          .arg(recordid).arg(store).arg(goodid).arg(eid).arg(isspike).arg(memberID).arg(memberID).arg(userID).arg(token);
        formdata->setHeader(QNetworkRequest::ContentDispositionHeader,
                            QVariant(formStr));

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
    QString replyStr(data);
    CommonUtils::Instance()->ParseGoodItemJson(replyStr,jsonReplay);
    change = jsonReplay.moutaiJson.nextRoad.Change;
    if(jsonReplay.moutaiJson.ResFlag == "true"){
        requestRet = true;
    }else{
        requestRet = false;
        return;
    }
}

void changeThread::replyGoodChange(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();

    QString replyStr(data);
    CommonUtils::Instance()->ParseChangeGoodJson(replyStr,jsonReplay);
    if(jsonReplay.goodChangedJson.flag == "true"){
        changeRet = true;
    }else{
        changeRet = false;
    }
    if(jsonReplay.goodChangedJson.Message == "用户信息裹起"){
        isExpired = true;
    }
}


void changeThread::on_readyRead()
{

}

