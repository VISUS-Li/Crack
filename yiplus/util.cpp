#include "util.h"
#include <QFile>
#include <QDateTime>
#include <QDir>
#include <QCoreApplication>
#include <QList>

LogHelper *LogHelper::m_log = NULL;
CommonUtils *CommonUtils::m_Comm = NULL;
ExcelHelper *ExcelHelper::m_Excel = NULL;

CommonUtils::CommonUtils()
{
    DefualtFile = NULL;
    defAccDocPath = GetExePath("account.txt");
}

void CommonUtils::Relese(){
    delete m_Comm;
    m_Comm = NULL;
    if(DefualtFile){
        DefualtFile->close();
        delete DefualtFile;
        DefualtFile = NULL;
    }
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

bool CommonUtils::AccountExist(QList<Account> account,QString userID){
    for(int i = 0; i < account.count(); i++){
        if(account[i].GetPoneNumber() == userID){
            return true;
        }
    }
    return false;
}
bool CommonUtils::ImportAccount(QString filePath, QList<Account> *accountList){
    File = new QFile(filePath);
    if(!File->open(QIODevice::ReadOnly | QIODevice::Text)){
        delete File;
        File = NULL;
        return false;
    }
    QByteArray allTxt = File->readAll();
    if(allTxt == ""){
        File->close();
        delete File;
        File = NULL;
        return false;
    }
    QString allStr(allTxt);
    QStringList allAccountList = allStr.split("\n",QString::SkipEmptyParts);
    if(allAccountList.count() <= 0){
        File->close();
        delete File;
        File = NULL;
        return false;
    }

    for(int i = 0; i < allAccountList.count(); i++){
        QString accountStr = allAccountList[i];
        QStringList splitAccount = accountStr.split(",",QString::SkipEmptyParts);
        Account newAccount(splitAccount[0],splitAccount[1],"001");
        if(!AccountExist(*accountList,newAccount.GetPoneNumber())){
            accountList->push_back(newAccount);
        }
        InsertDefAccountDoc(newAccount);
        LogHelper::Instance()->AppendLogList(splitAccount[0]+"-"+splitAccount[1]);
    }

    File->close();
    delete File;
    File = NULL;

    if(accountList->count() <= 0){
        return false;
    }
    return true;
}

bool CommonUtils::InsertDefAccountDoc(Account account){
    if(!DefualtFile){
        DefualtFile = new QFile(defAccDocPath);
        if(!DefualtFile->open(QIODevice::ReadWrite | QIODevice::Append)){
            return false;
        }
    }
    QString writeStr = account.GetPoneNumber()+","+account.GetPassWord()+"\n";
    QByteArray allTxt = DefualtFile->readAll();
    QString allStr(allTxt);
    if(allStr == ""){
        //读出来是空文件，直接写入
        DefualtFile->write(writeStr.toUtf8());
    }else{
        //读出来非空文件，先判断是否有重复的
        int index = allStr.indexOf(writeStr, 0, Qt::CaseInsensitive);
        if(index = -1){
            DefualtFile->write(writeStr.toUtf8());
        }
    }
}


QJsonObject CommonUtils::GetJsonObject(QString JsonStr){
    QJsonParseError parseJsonErr;
     QJsonObject jsonObject;
        QJsonDocument document = QJsonDocument::fromJson(JsonStr.toUtf8(),&parseJsonErr);
        if(!(parseJsonErr.error == QJsonParseError::NoError))
        {
            LogHelper::Instance()->AppendLogList("解析Json失败:"+parseJsonErr.errorString());
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
    if(GoodsObj.contains("result")){
        QJsonValue resValue = GoodsObj.value("result");
        if(resValue.isObject()){
            QJsonObject resultObj = resValue.toObject();
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
    if(itemObj.contains("result")){
        QJsonValue value = itemObj.value("result");
        if(value.isObject()){
            QJsonObject obj = value.toObject();
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
        ReplayJson.goodChangedJson.Result = value.toString();
    }
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
    writeStr += "changeList:" + replayJson.homePageJson.NextRoad_ChangeList.ChangeList + ";\n\n";

    //获取商品列表
    writeStr += "获取商品列表\n";
    writeStr += "flag:" + replayJson.goodListJson.ResFlag + ",\n";
    writeStr += "detail:" + replayJson.goodListJson.NextRoad.Detail + ";\n\n";

    //获取茅台信息
    writeStr += "获取茅台信息\n";
    writeStr += "flag:" + replayJson.moutaiJson.ResFlag + ",\n";
    writeStr += "check:" + replayJson.moutaiJson.nextRoad.Check +",\n";
    writeStr += "change:" + replayJson.moutaiJson.nextRoad.Change + ",\n";
    writeStr += "recordid:" + replayJson.moutaiJson.Recoidid + ",\n";
    writeStr += "goodsName:" + replayJson.moutaiJson.GoodsName + ",\n";
    writeStr += "goodsCount:" + replayJson.moutaiJson.GoodsCount + ",\n";
    writeStr += "changeCount:" + replayJson.moutaiJson.ChangeCount + ",\n";
    writeStr += "changeLimit:" + replayJson.moutaiJson.changeLimit + ";\n\n";

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
}
bool LogHelper::AppendLogList(QString item){
    if(logListModel == nullptr){
        return false;
    }
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
    item = time + " " + item;
    QStandardItem *stItem = new QStandardItem(item);
    logListModel->appendRow(stItem);
    return true;
}
