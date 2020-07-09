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
    QString qexeFullPath = QCoreApplication::applicationDirPath();
    defAccDocPath = qexeFullPath + "/account.txt";
    defAccDocPath =  QDir::toNativeSeparators(defAccDocPath);
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
bool CommonUtils::IsFilorDirExist(QString path){
    QFile file(path);
    if(file.exists()){
        return true;
    }else{
        return false;
    }
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
        Account newAccount(splitAccount[0],splitAccount[1]);
        accountList->push_back(newAccount);
        InsertDefAccountDoc(newAccount);
        LogHelper::Instance()->AppendLogList(splitAccount[0]+"-"+splitAccount[1]);
    }
    if(accountList->count() <= 0){
        File->close();
        delete File;
        File = NULL;
        return false;
    }
    File->close();
    delete File;
    File = NULL;
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


bool CommonUtils::ParseLoginJson(QString loginStr){
    QJsonObject loginObj = GetJsonObject(loginStr);
    if(loginObj.keys().count() <= 0){
        return false;
    }
    if(loginObj.contains("flag")){
        QJsonValue value = loginObj.value("flag");
        ReplayJson.loginJson.ResFlag = value.toString();
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

bool CommonUtils::ParseHomePageJson(QString homeStr){
    QJsonObject homeObj = GetJsonObject(homeStr);
    if(homeObj.keys().count() <= 0){
        return false;
    }

    if(homeObj.contains("flag")){
        QJsonValue value = homeObj.value("flag");
        ReplayJson.homePageJson.ResFlag = value.toString();
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

bool CommonUtils::ParseGoodListsJson(QString goodsListStr){
    QJsonObject GoodsObj = GetJsonObject(goodsListStr);
    if(GoodsObj.keys().count() <= 0){
        return false;
    }

    if(GoodsObj.contains("flag")){
        QJsonValue value = GoodsObj.value("flag");
        ReplayJson.goodListJson.ResFlag = value.toString();
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

bool CommonUtils::ParseGoodItemJson(QString goodItemStr){
    QJsonObject itemObj = GetJsonObject(goodItemStr);
    if(itemObj.keys().count() <= 0){
        return false;
    }
    if(itemObj.contains("flag")){
        QJsonValue value = itemObj.value("flag");
        ReplayJson.moutaiJson.ResFlag = value.toString();
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

bool CommonUtils::ParseChangeGoodJson(QString changeStr){
    QJsonObject changeObj = GetJsonObject(changeStr);
    if(changeObj.keys().count() <= 0){
        return false;
    }
    if(changeObj.contains("flag")){
        QJsonValue value = changeObj.value("flag");
        ReplayJson.goodChangedJson.flag = value.toString();
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
    if(path == ""){
        QString qexeFullPath = QCoreApplication::applicationDirPath();
        path =  QDir::toNativeSeparators(qexeFullPath);
    }
    QString fullPath = path + "/" +replayJson.loginJson.PhoneNumber;
    fullPath = QDir::toNativeSeparators(fullPath);
    QFile file(fullPath);
    if(!file.open(QIODevice::Text| QIODevice::Append)){
        return false;
    }
    QString writeStr = "";
    QDateTime nowTime = QDateTime::currentDateTime();
    QString nowTimeStr = nowTime.toString("yyyy-MM-dd hh:mm::ss.zzz");
    writeStr += "\n\n\n\n\n";
    writeStr += nowTimeStr+"\n";

    //基本信息
    writeStr += "获取登录信息\n";
    writeStr += "phoneNumber:"+replayJson.loginJson.PhoneNumber+ ",\n";
    writeStr += "memberid" + replayJson.loginJson.MemberId + ",\n";
    writeStr += "token" + replayJson.loginJson.Token + ",\n";
    writeStr += "flag" + replayJson.loginJson.ResFlag + ",\n";
    writeStr += "message" + replayJson.loginJson.Message + ";\n\n";

    //获取首页信息
    writeStr += "获取首页信息\n";
    writeStr += "flag" + replayJson.homePageJson.ResFlag + ",\n";
    writeStr += "isExpired" + replayJson.homePageJson.IsExpired + ",\n";
    writeStr += "changeList" + replayJson.homePageJson.NextRoad_ChangeList.ChangeList + ";\n\n";

    //获取商品列表
    writeStr += "获取商品列表\n";
    writeStr += "flag" + replayJson.goodListJson.ResFlag + ",\n";
    writeStr += "detail" + replayJson.goodListJson.NextRoad.Detail + ";\n\n";

    //获取茅台信息
    writeStr += "获取茅台信息\n";
    writeStr += "flag" + replayJson.moutaiJson.ResFlag + ",\n";
    writeStr += "check" + replayJson.moutaiJson.nextRoad.Check +",\n";
    writeStr += "change" + replayJson.moutaiJson.nextRoad.Change + ",\n";
    writeStr += "recordid" + replayJson.moutaiJson.Recoidid + ",\n";
    writeStr += "goodsName" + replayJson.moutaiJson.GoodsName + ",\n";
    writeStr += "goodsCount" + replayJson.moutaiJson.GoodsCount + ",\n";
    writeStr += "changeCount" + replayJson.moutaiJson.ChangeCount + ",\n";
    writeStr += "changeLimit" + replayJson.moutaiJson.changeLimit + ";\n\n";

    //兑换信息
    writeStr += "兑换信息\n";
    writeStr += "flag" + replayJson.goodChangedJson.flag + ",\n";
    writeStr += "message" + replayJson.goodChangedJson.Message + ",\n";
    writeStr += "result" + replayJson.goodChangedJson.Result + ";\n";
}

ExcelHelper::ExcelHelper(){
    logListModel = nullptr;
}
bool ExcelHelper::InitExcel(bool init){
    LogHelper::Instance()->SetLogListModel(logListModel);

    if(init){
        QString qexeFullPath = QCoreApplication::applicationDirPath();
        DefaultExcelPath = qexeFullPath + "/DefaultExcel.xlsx";
        DefaultExcelPath =  QDir::toNativeSeparators(DefaultExcelPath);
    }
    QAxObject * pWorkBook = NULL;
    if(!OpenExcel(DefaultExcelPath,InitExcelObj, pWorkBook)){
        LogHelper::Instance()->AppendLogList("打开Excel表失败");
    }
   // QAxObject *pWorkSheets = pWorkBook->querySubObject("Sheets");
    QAxObject * sheet1 = pWorkBook->querySubObject("WorkSheets(int)",1);//获得sheet1；
    SetCell(sheet1,1,1,"a");
    CloseExcel(DefaultExcelPath,InitExcelObj,pWorkBook);
}

bool ExcelHelper::OpenExcel(QString strPath, QAxObject* pExcel, QAxObject* _pWorkbook){

    pExcel = new(std::nothrow) QAxObject();
    if(pExcel == nullptr){
        return false;
    }
    try {
        if(pExcel->setControl("Excel.Application")){
            LogHelper::Instance()->AppendLogList("加载Excel成功!");
        }else{
            if(pExcel->setControl("ket.Application")){
                LogHelper::Instance()->AppendLogList("加载WPS-Excel成功");
            }else{
                LogHelper::Instance()->AppendLogList("加载Excel或WPS-Excel失败");
                return false;
            }
        }

        pExcel->setProperty("Visible",false);

        //打开WorkBooks
        QAxObject *pWorkBooks = pExcel->querySubObject("WorkBooks");

        if(!CommonUtils::Instance()->IsFilorDirExist(strPath)){
            pWorkBooks->dynamicCall("Add");
            //获得活跃的workbook
            _pWorkbook = pExcel->querySubObject("ActiveWorkBook");
            QVariant savVar = _pWorkbook->dynamicCall("SaveAs(const QString&)",DefaultExcelPath);
        }else{
            pWorkBooks->dynamicCall("Open(const QString&)", DefaultExcelPath);//打开已存在的excel
        }

        //获得活跃的workbook
        _pWorkbook = pExcel->querySubObject("ActiveWorkBook");

        //获得workbook中的所有worksheet
        //pWorkSheets = _pWorkbook->querySubObject("WorkSheets");

    } catch (...) {
     return false;
    }
    return true;
}

bool ExcelHelper::CloseExcel(QString strPath, QAxObject *pExcel, QAxObject *pWorkBook){

    if(pWorkBook){
        pWorkBook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(strPath));
        pWorkBook->dynamicCall("Close()");
        delete pWorkBook;
        pWorkBook = NULL;
    }
    if(pExcel){
        pExcel->dynamicCall("Quit()");
        delete pExcel;
        pExcel = NULL;
    }
    return true;
}


bool ExcelHelper::SetCell(QAxObject* pSheet, int row, int column, QString value){
    try {
        QAxObject* pCell = pSheet->querySubObject("Cells(int,int)",row,column);//获取指定行列的单元格
        if(pCell != nullptr){
            pCell->setProperty("Value",value);
        }else{
            return false;
        }
    } catch (...) {
        LogHelper::Instance()->AppendLogList("写入单元格失败");
        return false;
    }
    return true;
}


bool ExcelHelper::SetCell(QAxObject* pSheet, QString number, QString value){
    try{
        QAxObject* pCell = pSheet->querySubObject("Range(QString)",number);
        if(pCell != nullptr){
            pCell->setProperty("Value",value);
        }else{
            return false;
        }

    }catch(...){
        LogHelper::Instance()->AppendLogList("写入单元格失败");
        return false;
    }
    return true;
}


bool ExcelHelper::GetCell(QAxObject* pSheet, QString number, QString& strCell){
    try {
        QAxObject* pCell = pSheet->querySubObject("Range(QString)",number);
        if(pCell != nullptr){
            strCell = pCell->property("Value").toString();
        }else{
            return false;
        }
    } catch (...) {
        LogHelper::Instance()->AppendLogList("获取单元格数据失败");
        return false;
    }
    return true;
}

bool ExcelHelper::GetCell(QAxObject* pSheet, int row, int column, QString &strCell){
    try {
        QAxObject* pCell = pSheet->querySubObject("Cells(int, int)", row, column);
        if(pCell != nullptr){
            strCell = pCell->property("Value").toString();
        }else{
            return false;
        }
    } catch (...) {
        LogHelper::Instance()->AppendLogList("获取单元格数据失败");
        return false;
    }
    return true;
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
