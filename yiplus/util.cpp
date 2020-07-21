#include "util.h"
#include <QFile>
#include <QDateTime>
#include <QDir>
#include <QCoreApplication>
#include <QList>
#include <QTextCodec>
#include <QNetworkAccessManager>
#include <QTimer>
#include <QNetworkReply>

LogHelper *LogHelper::m_log = NULL;
CommonUtils *CommonUtils::m_Comm = NULL;
ExcelHelper *ExcelHelper::m_Excel = NULL;

CommonUtils::CommonUtils()
{
    defAccDocPath = GetExePath("account.txt");
}

void CommonUtils::Relese(){
    delete m_Comm;
    m_Comm = NULL;
}

//外界需要free掉
char* CommonUtils::QString2Char(QString str){
    char *chStr = NULL;
     QByteArray ba = str.toLatin1();
     chStr = (char *)malloc(ba.length() + 1);
     memset(chStr, 0, ba.length());
     memcpy(chStr, ba.data(), ba.length());
     chStr[ba.length()] = '\0';
     return chStr;
}
int CommonUtils::GetAccEnableCounts(QList<Account> accounts){
    int ret = 0;
    for(int i = 0; i < accounts.size(); i++){
        if(accounts[i].isEnable()){
            ret++;
        }
    }
    return ret;
}

bool CommonUtils::IsFilorDirExist(QString path){
    QFile file(path);
    if(file.exists()){
        return true;
    }else{
        return false;
    }
}
QString CommonUtils::GetExePath(QString fileName){
    QString qexeFullPath = QCoreApplication::applicationDirPath();
    if(fileName != ""){
        qexeFullPath = qexeFullPath + "/"+fileName;
    }
    qexeFullPath =  QDir::toNativeSeparators(qexeFullPath);
    return qexeFullPath;
}

bool CommonUtils::AccountExist(QList<Account> account,QString userID, Account *retAccount){
    for(int i = 0; i < account.count(); i++){
        if(account[i].GetPoneNumber() == userID){
            if(retAccount != NULL){
                *retAccount = account[i];
            }
            return true;
        }
    }
    return false;
}
bool CommonUtils::GetProxy(QList<ProxyData>& proxyData, qint64& preGetProxyTime, int getNum){
    QString reqUrl = QString("http://http.9vps.com/getip.asp?username=visus&pwd=e35346ede433742757d2ba48550edfc8&geshi=1&fenge=3&fengefu=&getnum=%1").arg(getNum);
    qDebug()<< "GetProxyUrl:"<<reqUrl;
    QEventLoop eventLoop;
    QNetworkAccessManager manager;
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

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
    if (arry == "") {
        return false;
    }
    QString allStr(arry);
    QStringList allProxyList = allStr.split("\n",QString::SkipEmptyParts);
    bool isFail = false;
    for(int i = 0; i < allProxyList.count(); i++){
        JsonClass jsonReplay;
        ParseProxyStatus(allProxyList[i],jsonReplay);
        ProxyData tmpProxy;
        tmpProxy.proxyIp = jsonReplay.proxyStatus.ProxyIp;
        tmpProxy.proxyPort = jsonReplay.proxyStatus.ProxyPort;
        if(tmpProxy.proxyIp == "" || tmpProxy.proxyPort == 0 || jsonReplay.proxyStatus.ProxyError != ""){
            isFail = true;
        }
        proxyData.push_back(tmpProxy);
    }
    if(!isFail){
        preGetProxyTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    }
    return !isFail;
}

bool CommonUtils::TryGetProxy(QList<ProxyData>& proxyData, qint64& preGetProxyTime,int getNum) {
    int cnt = 0;
    proxyData.clear();
    preGetProxyTime = 0;
    while (!GetProxy(proxyData,preGetProxyTime,getNum)) {
        cnt++;
        if (cnt >= 10) {
            LogHelper::Instance()->AppendLogList("获取代理IP失败！","主线程");
            return false;
        }
        QEventLoop loop;
        QTimer::singleShot(1000,&loop,SLOT(quit()));
        loop.exec();
    }
    return true;
}

bool CommonUtils::ImportAccount(QString filePath, QList<Account> *accountList){
    QFile File(filePath);
    if(!File.open(QIODevice::ReadOnly | QIODevice::Text)){
        return false;
    }
    QByteArray allTxt = File.readAll();
    if(allTxt == ""){
        File.close();
        return false;
    }
    QString allStr(allTxt);
    QStringList allAccountList = allStr.split("\n",QString::SkipEmptyParts);
    if(allAccountList.count() <= 0){
        File.close();
        return false;
    }

    for(int i = 0; i < allAccountList.count(); i++){
        QString accountStr = allAccountList[i];
        QStringList splitAccount = accountStr.split(",",QString::SkipEmptyParts);
        if(splitAccount.count() <= 0){
            File.close();
            return false;
        }
        if(splitAccount.count() == 3){
            Account newAccount(splitAccount[0],splitAccount[1],splitAccount[2].toUtf8());
            if(!AccountExist(*accountList,newAccount.GetPoneNumber())){
                accountList->push_back(newAccount);
                LogHelper::Instance()->AppendLogList(splitAccount[0]+"-"+splitAccount[1]+"-"+splitAccount[2].toUtf8());
            }
        }else{
            LogHelper::Instance()->AppendLogList("初始化账户集失败，account.txt中格式不正确");
        }
    }
    if(File.isOpen())
        File.close();

    if(accountList->count() <= 0){
        return false;
    }
    return true;
}

QString CommonUtils::ConvertStore(QString str, bool code){
    if(code){
        if(str == "001"){return "春熙店";}
        if(str == "002"){return "双楠店";}
        if(str == "003"){return "锦华店";}
        if(str == "004"){return "建设路店";}
        if(str == "005"){return "高新店";}
        if(str == "006"){return "温江店";}
        if(str == "007"){return "眉山店";}
        if(str == "008"){return "绿地店";}
        if(str == "009"){return "乐山店";}
        if(str == "101"){return "华府大道店";}else{return "";}
    }else{
        if(str == "春熙店"){return "001";}
        if(str == "双楠店"){return "002";}
        if(str == "锦华店"){return "003";}
        if(str == "建设路店"){return "004";}
        if(str == "高新店"){return "005";}
        if(str == "温江店"){return "006";}
        if(str == "眉山店"){return "007";}
        if(str == "绿地店"){return "008";}
        if(str == "乐山店"){return "009";}
        if(str == "华府大道店"){return "101";}else{return "";}
    }
}

bool CommonUtils::UpdateAccountToFile(QList<Account> *accountList, QString filePath){
    if(filePath == ""){
        filePath = GetExePath("account.txt");
    }
    if(QFile::remove(filePath)){
        QFile accountFile(filePath);
        if(!accountFile.open(QIODevice::ReadWrite | QIODevice::Append)){
            return false;
        }
        for(QList<Account>::iterator iter = accountList->begin(); iter != accountList->end(); iter++){
            QString str = iter->GetPoneNumber()+","+iter->GetPassWord()+","+iter->GetStore()+"\n";
            accountFile.write(str.toUtf8());//写入文件中
        }
        accountFile.close();
    }
    return false;
}

bool CommonUtils::InsertDefAccountDoc(Account account, QList<Account> *accountList){
    QString writeStr = account.GetPoneNumber()+","+account.GetPassWord()+","+account.GetStore()+"\n";
    Account* existAccount = new Account("","","");
    if(!AccountExist(*accountList,account.GetPoneNumber(),existAccount)){
        delete existAccount;
        //如果账号不存在
        QFile accountFile(defAccDocPath);
        if(!accountFile.open(QIODevice::ReadWrite | QIODevice::Append)){
            return false;
        }

        accountFile.write(writeStr.toUtf8());//写入文件中
        accountList->push_back(account);//加入缓存中
        if(accountFile.isOpen())
            accountFile.close();
        return true;
    }else{
        //如果账号存在，检查密码
        if(account.GetPassWord() != existAccount->GetPassWord()){
            //密码已改
            delete existAccount;
            if(QFile::remove(defAccDocPath)){
                QFile accountFile(defAccDocPath);
                if(!accountFile.open(QIODevice::ReadWrite | QIODevice::Append)){
                    return false;
                }
                for(QList<Account>::iterator iter = accountList->begin(); iter != accountList->end(); iter++){
                    if(iter->GetPoneNumber() == account.GetPoneNumber()){
                        iter->SetPassWord(account.GetPassWord());
                    }
                    QString str = iter->GetPoneNumber()+","+iter->GetPassWord()+","+iter->GetStore()+"\n";
                    accountFile.write(writeStr.toUtf8());//写入文件中
                }
                accountFile.close();
            }else{
                return false;
            }
        }
    }

    return true;
}


QJsonObject CommonUtils::GetJsonObject(QString JsonStr){
    QJsonParseError parseJsonErr;
     QJsonObject jsonObject;
        QJsonDocument document = QJsonDocument::fromJson(JsonStr.toUtf8(),&parseJsonErr);
        if(!(parseJsonErr.error == QJsonParseError::NoError))
        {
            //LogHelper::Instance()->AppendLogList("解析Json失败:"+parseJsonErr.errorString());
            return jsonObject;
        }
        jsonObject = document.object();
        return jsonObject;
}


bool CommonUtils::ParseLoginJson(QString loginStr, JsonClass& ReplayJson){
    QJsonObject loginObj = GetJsonObject(loginStr);
    if(loginObj.keys().count() <= 0){
        return false;
    }
    if(loginObj.contains("flag")){
        QJsonValue value = loginObj.value("flag");
        bool ret = value.toBool();
        if(ret){
            ReplayJson.loginJson.ResFlag = "true";
        }else{
            ReplayJson.loginJson.ResFlag = "false";
        }
    }
    if(loginObj.contains("result")){
        QJsonValue resultValue = loginObj.value("result");
        if(resultValue.isObject()){
            QJsonObject resultObj = resultValue.toObject();
            if(resultObj.contains("phoneNumber")){
                QJsonValue value = resultObj.value("phoneNumber");
                ReplayJson.loginJson.PhoneNumber = value.toString();
            }
            if(resultObj.contains("memberid")){
                QJsonValue value = resultObj.value("memberid");
                ReplayJson.loginJson.MemberId = value.toString();
            }
            if(resultObj.contains("token")){
                QJsonValue value = resultObj.value("token");
                ReplayJson.loginJson.Token = value.toString();
            }
        }
    }
    return true;
}

bool CommonUtils::ParseHomePageJson(QString homeStr,JsonClass& ReplayJson){
    QJsonObject homeObj = GetJsonObject(homeStr);
    if(homeObj.keys().count() <= 0){
        return false;
    }

    if(homeObj.contains("flag")){
        QJsonValue value = homeObj.value("flag");
        bool ret = value.toBool();
        if(ret){
            ReplayJson.homePageJson.ResFlag = "true";
        }else{
            ReplayJson.homePageJson.ResFlag = "false";
        }
    }
    if(homeObj.contains("message")){
        QJsonValue value = homeObj.value("message");
        QString str = value.toString();
        ReplayJson.homePageJson.Message = str;
    }
    if(homeObj.contains("result")){
        QJsonValue resValue = homeObj.value("result");
        if(resValue.isObject()){
            QJsonObject resObj = resValue.toObject();
            if(resObj.contains("isExpired")){
                QJsonValue value = resObj.value("isExpired");
                ReplayJson.homePageJson.IsExpired = value.toString();
            }
            if(resObj.contains("nextRoad")){
                QJsonValue value = resObj.value("nextRoad");
                if(value.isObject()){
                    QJsonObject obj = value.toObject();
                    if(obj.contains("changeList")){
                        QJsonValue value = obj.value("changeList");
                        ReplayJson.homePageJson.NextRoad_ChangeList.ChangeList = value.toString();
                    }
                }
            }
            if(resObj.contains("spikeunit")){
                QJsonValue value = resObj.value("spikeunit");
                ReplayJson.homePageJson.Spikeunit = value.toString();
            }
        }
    }

    return true;
}

bool CommonUtils::ParseGoodListsJson(QString goodsListStr, JsonClass& ReplayJson){
    QJsonObject GoodsObj = GetJsonObject(goodsListStr);
    if(GoodsObj.keys().count() <= 0){
        return false;
    }

    if(GoodsObj.contains("flag")){
        QJsonValue value = GoodsObj.value("flag");
        bool ret = value.toBool();
        if(ret){
            ReplayJson.goodListJson.ResFlag = "true";
        }else{
            ReplayJson.goodListJson.ResFlag = "false";
        }
    }

    if(GoodsObj.contains("message")){
        QJsonValue value = GoodsObj.value("message");
        QString str = value.toString();
        ReplayJson.goodListJson.Message = str;
    }

    if(GoodsObj.contains("result")){
        QJsonValue resValue = GoodsObj.value("result");
        if(resValue.isObject()){
            QJsonObject resultObj = resValue.toObject();
            if(resultObj.contains("isExpired")){
                QJsonValue value = resultObj.value("isExpired");
                if(value.isString()){
                    ReplayJson.goodListJson.IsExpired = value.toString();
                }
            }
            if(resultObj.contains("exchangeList")){
                QJsonValue value = resultObj.value("exchangeList");
                if(value.isObject()){
                    QJsonObject obj = value.toObject();
                    if(obj.contains("recordid")){
                        QJsonValue value = obj.value("recordid");
                        ReplayJson.goodListJson.MoutaiItem.Recoidid = value.toString();
                    }
                    if(obj.contains("goodsName")){
                        QJsonValue value = obj.value("goodsName");
                        ReplayJson.goodListJson.MoutaiItem.GoodsName = value.toString();
                    }
                    if(obj.contains("pointsChange")){
                        QJsonValue value = obj.value("pointsChange");
                        ReplayJson.goodListJson.MoutaiItem.PointsChange = value.toString();
                    }
                    if(obj.contains("goodsPreview")){
                        QJsonValue value = obj.value("goodsPreview");
                        ReplayJson.goodListJson.MoutaiItem.GoodsPreview = value.toString();
                    }
                    if(obj.contains("goodsCount")){
                        QJsonValue value = obj.value("goodsCount");
                        ReplayJson.goodListJson.MoutaiItem.GoodsCount = value.toString();
                    }
                    if(obj.contains("changeCount")){
                        QJsonValue value = obj.value("changeCount");
                        ReplayJson.goodListJson.MoutaiItem.ChangeCount = value.toString();
                    }
                    if(obj.contains("changeLimit")){
                        QJsonValue value = obj.value("changeLimit");
                        ReplayJson.goodListJson.MoutaiItem.changeLimit = value.toString();
                    }
                    if(obj.contains("level")){
                        QJsonValue value = obj.value("level");
                        ReplayJson.goodListJson.MoutaiItem.Level = value.toString();
                    }
                    if(obj.contains("goodsId")){
                        QJsonValue value = obj.value("goodsId");
                        ReplayJson.goodListJson.MoutaiItem.GoodsId = value.toString();
                    }
                    if(obj.contains("eid")){
                        QJsonValue value = obj.value("eid");
                        ReplayJson.goodListJson.MoutaiItem.Eid = value.toString();
                    }
                    if(obj.contains("isspike")){
                        QJsonValue value = obj.value("isspike");
                        ReplayJson.goodListJson.MoutaiItem.Isspike = value.toString();
                    }
                    if(obj.contains("effectivepoint")){
                        QJsonValue value = obj.value("effectivepoint");
                        ReplayJson.goodListJson.MoutaiItem.Effectivepoint = value.toString();
                    }
                }
            }
            if(resultObj.contains("nextRoad")){
                QJsonValue value = resultObj.value("nextRoad");
                if(value.isObject()){
                    QJsonObject obj = value.toObject();
                    if(obj.contains("detail")){
                        QJsonValue value = obj.value("detail");
                        ReplayJson.goodListJson.NextRoad.Detail = value.toString();
                    }
                    if(obj.contains("status")){
                        QJsonValue value = obj.value("status");
                        ReplayJson.goodListJson.NextRoad.Status = value.toString();
                    }
                }
            }
        }
    }
    return true;
}

bool CommonUtils::ParseGoodItemJson(QString goodItemStr, JsonClass& ReplayJson){
    QJsonObject itemObj = GetJsonObject(goodItemStr);
    if(itemObj.keys().count() <= 0){
        return false;
    }
    if(itemObj.contains("flag")){
        QJsonValue value = itemObj.value("flag");
        bool ret = value.toBool();
        if(ret){
            ReplayJson.moutaiJson.ResFlag = "true";
        }else{
            ReplayJson.moutaiJson.ResFlag = "false";
        }
    }

    if(itemObj.contains("message")){
        QJsonValue value = itemObj.value("message");
        QString str = value.toString();
        ReplayJson.moutaiJson.Message = str;
    }

    if(itemObj.contains("result")){
        QJsonValue value = itemObj.value("result");
        if(value.isObject()){
            QJsonObject obj = value.toObject();
            if(obj.contains("isExpired")){
                QJsonValue value = obj.value("isExpired");
                if(value.isString()){
                    ReplayJson.moutaiJson.IsExpired = value.toString();
                }
            }
            if(obj.contains("nextRoad")){
                QJsonValue value = obj.value("nextRoad");
                if(value.isObject()){
                    QJsonObject obj = value.toObject();
                    if(obj.contains("check")){
                        QJsonValue value = obj.value("check");
                        ReplayJson.moutaiJson.nextRoad.Check = value.toString();
                    }
                    if(obj.contains("change")){
                        QJsonValue value = obj.value("change");
                        ReplayJson.moutaiJson.nextRoad.Change = value.toString();
                    }
                    if(obj.contains("setStatus")){
                        QJsonValue value = obj.value("setStatus");
                        ReplayJson.moutaiJson.nextRoad.setStatus = value.toString();
                    }
                }
            }
        }
    }
}

bool CommonUtils::ParseChangeGoodJson(QString changeStr, JsonClass& ReplayJson){
    QJsonObject changeObj = GetJsonObject(changeStr);
    if(changeObj.keys().count() <= 0){
        return false;
    }
    if(changeObj.contains("flag")){
        QJsonValue value = changeObj.value("flag");
        bool ret = value.toBool();
        if(ret){
            ReplayJson.goodChangedJson.flag = "true";
        }else{
            ReplayJson.goodChangedJson.flag = "false";
        }
    }
    if(changeObj.contains("message")){
        QJsonValue value = changeObj.value("message");
        ReplayJson.goodChangedJson.Message = value.toString();
    }
    if(changeObj.contains("result")){
        QJsonValue value = changeObj.value("result");
        if(value.isString()){
            ReplayJson.goodChangedJson.Result = value.toString();
        }else if(value.isObject()){
            QJsonObject obj = value.toObject();
            if(obj.contains("isExpired")){
                QJsonValue val = obj.value("isExpired");
                if(val.isString()){
                    ReplayJson.goodChangedJson.IsExpired = val.toString();
                }
            }
        }
    }
}

bool CommonUtils::ParseProxyStatus(QString proxyStr, JsonClass& ReplayJson,QString userID){
    if(proxyStr == ""){
        LogHelper::Instance()->AppendLogList("获取代理服务器失败",userID);
        return false;
    }
    QStringList ip_port_list = proxyStr.split(":");
    if(ip_port_list.count() <= 1){
        QStringList error = proxyStr.split("!");
        if(error.count() <= 1 || error.count() > 4){
            LogHelper::Instance()->AppendLogList("获取代理服务器失败",userID);
            ReplayJson.proxyStatus.ProxyError = "解析代理服务器返回值错误";
            return false;
        }
        if(error.count() == 2){
            ReplayJson.proxyStatus.ProxyError = QTextCodec::codecForName("GBK")->toUnicode(error[1].toUtf8());
            return true;
        }
        if(error.count() >2 && error.count() <= 4){
            QByteArray arry = error[2].toUtf8();
            ReplayJson.proxyStatus.ProxyError = QTextCodec::codecForName("GBK")->toUnicode(error[2].toUtf8());
            return true;
        }
    }
    ReplayJson.proxyStatus.ProxyIp = ip_port_list[0];
    ReplayJson.proxyStatus.ProxyPort = ip_port_list[1].toInt();
    return true;
}

bool CommonUtils::WriteReplayLog(JsonClass replayJson, QString path){
    QString fullPath = "";
    if(path == ""){
       fullPath = GetExePath(replayJson.loginJson.PhoneNumber+".txt");
    }else{
        fullPath = GetExePath() + "/" +path;
    }
    fullPath = QDir::toNativeSeparators(fullPath);
    QFile file(fullPath);
    if(!file.open(QIODevice::Text| QIODevice::Append)){
        return false;
    }
    QString writeStr = "";
    QDateTime nowTime = QDateTime::currentDateTime();
    QString nowTimeStr = nowTime.toString("yyyy-MM-dd hh:mm::ss.zzz");
    writeStr += "\n\n\n\n\n";
    writeStr += "==========================================\n";
    writeStr += nowTimeStr+"\n";
    writeStr += "ProxyIp:" + replayJson.proxyStatus.ProxyIp + ":" + QString::number(replayJson.proxyStatus.ProxyPort) +"\n";
    writeStr += "ProxyError:" + replayJson.proxyStatus.ProxyError + "\n";
    QString proxyStatus = "不启用代理";
    if(replayJson.proxyStatus.Enable){
        proxyStatus = "启用代理";
    }
    writeStr += proxyStatus + "\n";
    writeStr += "==========================================\n";

    //基本信息
    writeStr += "获取登录信息\n";
    writeStr += "phoneNumber:"+replayJson.loginJson.PhoneNumber+ ",\n";
    writeStr += "memberid:" + replayJson.loginJson.MemberId + ",\n";
    writeStr += "token:" + replayJson.loginJson.Token + ",\n";
    writeStr += "flag:" + replayJson.loginJson.ResFlag + ",\n";
    writeStr += "message:" + replayJson.loginJson.Message + ";\n\n";

    //获取首页信息
    writeStr += "获取首页信息\n";
    writeStr += "flag:" + replayJson.homePageJson.ResFlag + ",\n";
    writeStr += "isExpired:" + replayJson.homePageJson.IsExpired + ",\n";
    writeStr += "changeList:" + replayJson.homePageJson.NextRoad_ChangeList.ChangeList + ",\n";
    writeStr += "message:" + replayJson.homePageJson.Message + ";\n\n";

    //获取商品列表
    writeStr += "获取商品列表\n";
    writeStr += "flag:" + replayJson.goodListJson.ResFlag + ",\n";
    writeStr += "detail:" + replayJson.goodListJson.NextRoad.Detail + ",\n";
    writeStr += "message:" + replayJson.goodListJson.Message + ";\n\n";

    //获取茅台信息
    writeStr += "获取茅台信息\n";
    writeStr += "flag:" + replayJson.moutaiJson.ResFlag + ",\n";
    writeStr += "check:" + replayJson.moutaiJson.nextRoad.Check +",\n";
    writeStr += "change:" + replayJson.moutaiJson.nextRoad.Change + ",\n";
    writeStr += "recordid:" + replayJson.moutaiJson.Recoidid + ",\n";
    writeStr += "goodsName:" + replayJson.moutaiJson.GoodsName + ",\n";
    writeStr += "goodsCount:" + replayJson.moutaiJson.GoodsCount + ",\n";
    writeStr += "changeCount:" + replayJson.moutaiJson.ChangeCount + ",\n";
    writeStr += "changeLimit:" + replayJson.moutaiJson.changeLimit + ",\n";
    writeStr += "message:" + replayJson.moutaiJson.Message + ";\n\n";

    //兑换信息
    writeStr += "兑换信息\n";
    writeStr += "flag:" + replayJson.goodChangedJson.flag + ",\n";
    writeStr += "message:" + replayJson.goodChangedJson.Message + ",\n";
    writeStr += "result:" + replayJson.goodChangedJson.Result + ";\n";
    file.write(writeStr.toUtf8());
    file.close();
}


LogHelper::LogHelper(){
    logListModel = nullptr;
    isPrintLog = false;
    logFile = nullptr;
}

bool LogHelper::OpenAllLogsFile(){
   if(logFile){
        if(logFile->isOpen()){
            logFile->close();
        }
        delete logFile;
        logFile = nullptr;
   }

    logFile = new QFile(CommonUtils::Instance()->GetExePath("AllLogs.txt"));
    if(logFile->open(QIODevice::ReadWrite | QIODevice::Append)){
        return true;
    }
    return false;
}

bool LogHelper::CloseAllLogsFile(){
    if(logFile){
        if(logFile->isOpen()){
            logFile->close();
        }
        delete logFile;
        logFile = nullptr;
    }
}

bool LogHelper::AppendLogList(QString item,QString userID){
    if(logListModel == nullptr){
        return false;
    }
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
    item = time + " --" + userID + "-- " + item;

    QStandardItem *stItem = new QStandardItem(item);
    QString writeStr = item + "\n";
    if(logFile && logFile->isOpen()){
        logFile->write(writeStr.toUtf8());
    }else{
        OpenAllLogsFile();
    }
    if(!isPrintLog){
        return true;
    }
    logListModel->appendRow(stItem);
    return true;
}
