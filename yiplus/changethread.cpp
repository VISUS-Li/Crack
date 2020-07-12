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
        if( requestRet && loginRet) {
            if( !changeRet) {
                usleep(100000);
                getHomePage();
                cnt++;
                qDebug() << "请求结果:" << changeRet <<"请求兑换次数: " << cnt;
            }
        }
        if(!requestRet || !loginRet){
            signIN();
        }
         CommonUtils::Instance()->WriteReplayLog(jsonReplay,userID+".txt");
    }

}

QByteArray changeThread::Post(QString uri, QString header)
{
    QEventLoop eventLoop;
    QNetworkAccessManager manager;
    QUrl url(uri);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkReply *reply = manager.post(request, header.toUtf8());
    eventLoop.exec();
    QByteArray arry = reply->readAll();
    //LogHelper::Instance()->AppendLogList(arry);
    return arry;
}

QByteArray changeThread::Get(QString uri)
{
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QUrl url(uri);
    QNetworkRequest req(url);
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec();
    QByteArray arry = reply->readAll();
    return arry;
}


void changeThread::changeGoods()
{
    QString changeURL = CtrlURL;
        QString paramUrl = "changeCount="+changeCount+"&recordid="+recordid+"&goodsId="+goodid+"&storeId="+store+"&eid="+eid+"&pikeId=&isspike="+isspike+"&validate=&memberid="+memberID+"&memberId="+memberID+"&mobile="+userID+"&token="+token+"&language=zh&store="+store+"";
        changeURL = changeURL + change + "?";
        changeURL = changeURL + paramUrl;
        qDebug() << "changeURL:"+changeURL;

        QByteArray arry = Post(changeURL,paramUrl);
        replyGoodChange(arry);

}


void changeThread::signIN()
{
    //qDebug() << "logInURL" << logInURL;
    QString headerStr = "phoneNumber=" + userID + "&password=" + passWord;
    QByteArray replyArry = Post(logInURL,headerStr);
    replyFinished(replyArry);
}


void changeThread::replyFinished(QByteArray arry)
{

    qDebug() << "登录请求返回";

    QString replyStr(arry);
    CommonUtils::Instance()->ParseLoginJson(replyStr,jsonReplay);
    token = jsonReplay.loginJson.Token;
    memberID = jsonReplay.loginJson.MemberId;
    userID = jsonReplay.loginJson.PhoneNumber;

    {
        LogHelper::Instance()->AppendLogList("memberID:"+memberID);
        LogHelper::Instance()->AppendLogList("token:" + token);
    }

    if(jsonReplay.loginJson.ResFlag == "true"){
        requestRet = true;
        isExpired = false;
        loginRet = true;
    }else{
        requestRet = false;
        loginRet = false;
        return;
    }
}


void changeThread::getHomePage()
{
    qDebug() << "开始请求主页";
       QString paramUrl = "start=0&length=15&store="+store+"&memberid="+memberID+"&memberId="+memberID+"&mobile="+userID+"&token="+token+"&language=zh";
       homePageURL = homePageURL + paramUrl;
       QByteArray arry = Get(homePageURL);
       replyHomePage(arry);
}


void changeThread::replyHomePage(QByteArray arry)
{
    qDebug() << "请求主页返回";
    QString replyStr(arry);
    CommonUtils::Instance()->ParseHomePageJson(replyStr,jsonReplay);
    changeList = jsonReplay.homePageJson.NextRoad_ChangeList.ChangeList;

    {
        LogHelper::Instance()->AppendLogList("changeList:"+changeList);
    }

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
        QString paramUrl = "giftKbn=-1&orderBy=3&storeCode="+store+"&memberid="+memberID+"&memberId="+memberID+"&mobile="+userID+"&token="+token+"&language=zh&store="+store+"";
        QString homeCtrlURL = CtrlURL;
        homeCtrlURL = homeCtrlURL + changeList + "?";
        homeCtrlURL = homeCtrlURL + paramUrl;
        QByteArray arry = Get(homeCtrlURL);
        replyGoodsList(arry);
}

void changeThread::replyGoodsList(QByteArray arry)
{
    QString replyStr(arry);
    CommonUtils::Instance()->ParseGoodListsJson(replyStr,jsonReplay);
    detail = jsonReplay.goodListJson.NextRoad.Detail;

    {
        LogHelper::Instance()->AppendLogList("detail:"+detail);
    }

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
        //测试，获取指甲钳商品详细信息
        QString paramUrl = "recordid="+recordid+"&level=1&storeId="+store+"&goodsId="+goodid+"&eid="+eid+"&pikeId=&isspike="+isspike+"&memberid="+memberID+"&memberId="+memberID+"&mobile="+userID+"&token="+token+"&language=zh&store="+store+"";
        QString homeCtrlURL = CtrlURL;
        homeCtrlURL = homeCtrlURL + detail + "?";
        homeCtrlURL = homeCtrlURL + paramUrl;
        QByteArray arry = Post(homeCtrlURL,paramUrl);
        replyGoodInfo(arry);
}

void changeThread::replyGoodInfo(QByteArray arry)
{
    QString replyStr(arry);
    qDebug()<< "goodinfo:"+replyStr;
    CommonUtils::Instance()->ParseGoodItemJson(replyStr,jsonReplay);
    change = jsonReplay.moutaiJson.nextRoad.Change;

    {
        LogHelper::Instance()->AppendLogList("change:"+change);
    }

    if(jsonReplay.moutaiJson.ResFlag == "true"){
        requestRet = true;
        changeGoods();
    }else{
        requestRet = false;
        return;
    }
}

void changeThread::replyGoodChange(QByteArray arry)
{
    QString replyStr(arry);
    CommonUtils::Instance()->ParseChangeGoodJson(replyStr,jsonReplay);
    if(jsonReplay.goodChangedJson.flag == "true"){
        requestRet = true;
        changeRet = true;
    }else{
        changeRet = false;
    }
    if(jsonReplay.goodChangedJson.Message == "用户信息过期" || jsonReplay.goodChangedJson.Message == "002"){
        isExpired = true;
    }
}
