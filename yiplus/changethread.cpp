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

void changeThread::setStopValue(bool value){
    isStop = value;
    emit UserStop();
}

void  changeThread::run()
{
    getProxyIp(proxyIp,proxyPort);
    jsonReplay.Reset();
    int cnt=0;
    if(isLogInTest){
            signIN();
            CommonUtils::Instance()->WriteReplayLog(jsonReplay,userID+".txt");
            if(jsonReplay.loginJson.ResFlag == "true"){
                LogHelper::Instance()->AppendLogList("账号:"+userID+",密码:"+passWord+",登录测试成功!,token:"+jsonReplay.loginJson.Token);
                getHomePage();
            }else{
                LogHelper::Instance()->AppendLogList("账号:"+userID+",密码:"+passWord+",登录测试失败!,token:"+jsonReplay.loginJson.Token);
            }
            isLogInTest = false;
            return;
    }else{
        signIN();
        while (1) {
            if(loginRet && !changeRet) {//如果账号登录了，并且没有兑换成功，开始兑换流程
                    changeRet = getHomePage();
                    cnt++;
            }
            mutex.lock();
            if(isStop){
                break;
            }
            mutex.unlock();

            if((!loginRet && !changeRet) || cnt > 5){
                cnt = 0;
                signIN();
            }
            if(!changeRet){
                jsonReplay.proxyStatus.Enable = useProxy;
                CommonUtils::Instance()->WriteReplayLog(jsonReplay,userID+".txt");
            }
        }
    }
}


bool changeThread::getProxyIp(QString &proxyIp, int &proxyPort){
    QString reqUrl = ProxyUrl + "username=visus&pwd=e35346ede433742757d2ba48550edfc8&geshi=1&fenge=3&fengefu=&getnum=1";

    QEventLoop eventLoop;
    QNetworkAccessManager manager;
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QObject::connect(this,SIGNAL(changeThread::UserStop),&eventLoop,SLOT(quit()));

    QUrl url(reqUrl);
    QNetworkRequest req(url);
    QTimer::singleShot(1000,&eventLoop,SLOT(quit()));
    QNetworkReply *reply = manager.get(req);
    eventLoop.exec();
    QByteArray arry = reply->readAll();
    if(reply){
        delete reply;
        reply = NULL;
    }

    //解析返回的IP
    CommonUtils::Instance()->ParseProxyStatus(arry,jsonReplay);
    proxyIp = jsonReplay.proxyStatus.ProxyIp;
    proxyPort = jsonReplay.proxyStatus.ProxyPort;
}

QByteArray changeThread::Post(QString uri, QString header)
{
    QEventLoop eventLoop;
    QNetworkAccessManager manager;

    if(useProxy && (proxyIp != "" && proxyPort != 0)){
        QNetworkProxy proxy;
        proxy.setType(QNetworkProxy::HttpProxy);      
        proxy.setHostName(proxyIp);
        proxy.setPort(proxyPort);
        manager.setProxy(proxy);
    }

    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QObject::connect(this,SIGNAL(changeThread::UserStop),&eventLoop,SLOT(quit()));

    QUrl url(uri);
    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "Mozilla/5.0 (iPhone; CPU iPhone OS 13_5_1 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Mobile/15E148 Html5Plus/1.0 (Immersed/44)");
    //request.setRawHeader("Accept","application/json,text/javascript,*/*;q=0.01");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QTimer::singleShot(500,&eventLoop,SLOT(quit()));
    QNetworkReply *reply = manager.post(request, header.toUtf8());
    eventLoop.exec();
    QByteArray arry = reply->readAll();
    if(reply){
        delete reply;
        reply = NULL;
    }
    //LogHelper::Instance()->AppendLogList(arry);
    return arry;
}

QByteArray changeThread::Post_FormData(QString uri, QString form){
    QEventLoop eventLoop;
    QNetworkAccessManager manager;
    if(useProxy && (proxyIp != "" && proxyPort != 0)){
        QNetworkProxy proxy;
        proxy.setType(QNetworkProxy::HttpProxy);
        proxy.setHostName(proxyIp);
        proxy.setPort(proxyPort);
        manager.setProxy(proxy);
    }

    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QObject::connect(this,SIGNAL(changeThread::UserStop()),&eventLoop,SLOT(quit()));

    QUrl url(uri);
    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "Mozilla/5.0 (iPhone; CPU iPhone OS 13_5_1 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Mobile/15E148 Html5Plus/1.0 (Immersed/44)");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/form-data");

    QTimer::singleShot(500,&eventLoop,SLOT(quit()));
    QNetworkReply *reply = manager.post(request, form.toUtf8());
    eventLoop.exec();
    QByteArray arry = reply->readAll();
    if(reply){
        delete reply;
        reply = NULL;
    }
    //LogHelper::Instance()->AppendLogList(arry);
    return arry;
}



QByteArray changeThread::Get(QString uri)
{
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    if(useProxy && (proxyIp != "" && proxyPort != 0)){
        QNetworkProxy proxy;
        proxy.setType(QNetworkProxy::HttpProxy);
        proxy.setHostName(proxyIp);
        proxy.setPort(proxyPort);
        mgr.setProxy(proxy);
    }

    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QObject::connect(this,SIGNAL(changeThread::UserStop),&eventLoop,SLOT(quit()));

    QUrl url(uri);
    QNetworkRequest req(url);
    QTimer::singleShot(1500,&eventLoop,SLOT(quit()));
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec();
    QByteArray arry = reply->readAll();
    if(reply){
        delete reply;
        reply = NULL;
    }
    return arry;
}


bool changeThread::changeGoods()
{
    QString changeURL = CtrlURL;
        QString paramUrl = "changeCount="+changeCount+"&recordid="+recordid+"&goodsId="+goodid+"&storeId="+store+"&eid="+eid+"&pikeId=&isspike="+isspike+"&validate=&memberid="+memberID+"&memberId="+memberID+"&mobile="+userID+"&token="+token+"&language=zh&store="+store+"";
        changeURL = changeURL + change + "?";
        changeURL = changeURL + paramUrl;
        qDebug() << "changeURL:"+changeURL;

        QByteArray arry = Post_FormData(changeURL,paramUrl);
        return replyGoodChange(arry);
}


bool changeThread::signIN()
{
    QString headerStr = "phoneNumber=" + userID + "&password=" + passWord;
    QByteArray replyArry = Post(logInURL,headerStr);
    return replyFinished(replyArry);
}


bool changeThread::replyFinished(QByteArray arry)
{

    qDebug() << "登录请求返回";
    QString replyStr(arry);
    CommonUtils::Instance()->ParseLoginJson(replyStr,jsonReplay);
    token = jsonReplay.loginJson.Token;
    memberID = jsonReplay.loginJson.MemberId;
    {
        LogHelper::Instance()->AppendLogList("memberID:"+memberID);
        LogHelper::Instance()->AppendLogList("token:" + token);
        LogHelper::Instance()->AppendLogList("loginMessage:"+jsonReplay.loginJson.Message);
    }

    if(jsonReplay.loginJson.ResFlag == "true"){
        requestRet = true;
        isExpired = false;
        loginRet = true;
        return true;
    }else{
        requestRet = false;
        loginRet = false;
    }
    return false;
}


bool changeThread::getHomePage()
{
    qDebug() << "开始请求主页";
    QString paramUrl = "start=0&length=15&store="+store+"&memberid="+memberID+"&memberId="+memberID+"&mobile="+userID+"&token="+token+"&language=zh";
    QString targetUrl = homePageURL + paramUrl;
    qDebug()<<"请求主页:"<<targetUrl;
    QByteArray arry = Get(targetUrl);
    return replyHomePage(arry);
}


bool changeThread::replyHomePage(QByteArray arry)
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
        return getGoodsList();
    }else{
        LogHelper::Instance()->AppendLogList("请求主页失败，message："+jsonReplay.homePageJson.Message);
        requestRet = false;
    }
    if(jsonReplay.homePageJson.Message == "用户信息过期" || jsonReplay.homePageJson.IsExpired == "02"){
        loginRet = false;
    }
    return false;
}


bool changeThread::getGoodsList()
{
        QString paramUrl = "giftKbn=-1&orderBy=3&storeCode="+store+"&memberid="+memberID+"&memberId="+memberID+"&mobile="+userID+"&token="+token+"&language=zh&store="+store+"";
        QString homeCtrlURL = CtrlURL;
        homeCtrlURL = homeCtrlURL + changeList + "?";
        homeCtrlURL = homeCtrlURL + paramUrl;
        qDebug()<<"请求商品列表:"<<homeCtrlURL;
        QByteArray arry = Get(homeCtrlURL);
        return replyGoodsList(arry);
}

bool changeThread::replyGoodsList(QByteArray arry)
{
    QString replyStr(arry);
    CommonUtils::Instance()->ParseGoodListsJson(replyStr,jsonReplay);
    detail = jsonReplay.goodListJson.NextRoad.Detail;

    {
        LogHelper::Instance()->AppendLogList("detail:"+detail);
    }

    if(jsonReplay.goodListJson.ResFlag == "true"){
        requestRet = true;
        return getGoodsInfo();
    }else{
        LogHelper::Instance()->AppendLogList("请求商品列表失败，message："+jsonReplay.goodListJson.Message);
        requestRet = false;
    }
    if(jsonReplay.goodListJson.Message == "用户信息过期" || jsonReplay.goodListJson.IsExpired == "02"){
        loginRet = false;
    }
    return false;
}


bool changeThread::getGoodsInfo()
{
        //测试，获取指甲钳商品详细信息
        QString paramUrl = "recordid="+recordid+"&level=1&storeId="+store+"&goodsId="+goodid+"&eid="+eid+"&pikeId=&isspike="+isspike+"&memberid="+memberID+"&memberId="+memberID+"&mobile="+userID+"&token="+token+"&language=zh&store="+store+"";
        QString homeCtrlURL = CtrlURL;
        homeCtrlURL = homeCtrlURL + detail + "?";
        homeCtrlURL = homeCtrlURL + paramUrl;
        qDebug()<<"请求商品信息:"<<homeCtrlURL;
        QByteArray arry = Post_FormData(homeCtrlURL,paramUrl);
        return replyGoodInfo(arry);
}

bool changeThread::replyGoodInfo(QByteArray arry)
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
        return changeGoods();
    }else{
        LogHelper::Instance()->AppendLogList("请求商品详细信息失败，message："+jsonReplay.moutaiJson.Message);
        requestRet = false;
    }
    if(jsonReplay.moutaiJson.Message == "用户信息过期" || jsonReplay.moutaiJson.IsExpired == "02"){
        loginRet = false;
    }
    return false;
}

bool changeThread::replyGoodChange(QByteArray arry)
{
    QString replyStr(arry);
    CommonUtils::Instance()->ParseChangeGoodJson(replyStr,jsonReplay);
    if(jsonReplay.goodChangedJson.flag == "true" && jsonReplay.goodChangedJson.Message == "兑换成功"){
        requestRet = true;
        return true;
    }else{
        LogHelper::Instance()->AppendLogList("兑换商品失败，message："+jsonReplay.goodChangedJson.Message);
        //getGoodsInfo();
    }
    if(jsonReplay.goodChangedJson.Message == "用户信息过期" || jsonReplay.goodChangedJson.IsExpired == "02"){
        isExpired = true;
        loginRet = false;
    }
    return false;
}
