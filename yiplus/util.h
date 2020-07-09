#ifndef UTIL_H
#define UTIL_H
#include <QString>
#include <QAxObject>
#include <QStandardItemModel>
#include <QFile>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "account.h"
namespace Utils {
    class CommonUtils;
    class ExcelHelper;
    class LogHelper;
}

class JsonClass{
    typedef struct stu_LoginJson{
       QString ResFlag;//请求结果
       QString Message;
       QString PhoneNumber;
       QString MemberId;
       QString Token;

       stu_LoginJson(){
           ResFlag = "";
           Message = "";
           PhoneNumber = "";
           MemberId = "";
           Token = "";
       }
    }LoginJson;


    typedef struct stu_NextRoad{
        QString Detail;
        QString Status;

        QString ChangeList;

        QString Check;
        QString Change;
        QString setStatus;

        stu_NextRoad(){
            Detail = "";
            Status = "";
            ChangeList = "";
            Check = "";
            Change = "";
            setStatus = "";
        }
    }NextRoad;

    typedef struct stu_HomePageJson{
        QString ResFlag;
        QString IsExpired;
        NextRoad NextRoad_ChangeList;
        QString Spikeunit;

        stu_HomePageJson(){
            ResFlag = "";
            IsExpired = "";
            Spikeunit = "";
        }
    }HomeJson;

    //兑换商品项
    typedef struct stu_GoodsItem{
        QString ResFlag;
        QString Recoidid;
        QString GoodsName;
        QString PointsChange;//兑换积分数
        QString GoodsPreview;
        QString GoodsCount;//商品剩余数
        QString ChangeCount;
        QString changeLimit;
        QString Level;
        QString GoodsId;
        QString Eid;
        QString Isspike;
        QString Effectivepoint;
        NextRoad nextRoad;

        stu_GoodsItem(){
            ResFlag = "";
            Recoidid = "";
            GoodsName = "";
            PointsChange = "";
            GoodsPreview = "";
            GoodsCount = "";
            ChangeCount = "";
            changeLimit = "";
            Level = "";
            GoodsId = "";
            Eid = "";
            Isspike = "";
            Effectivepoint = "";
        }
    }MoutaiGood,GoodsItem;


    typedef struct stu_GoodsListJson{
        QString ResFlag;
        MoutaiGood MoutaiItem;
        NextRoad NextRoad;

        stu_GoodsListJson(){
            ResFlag = "";
        }
    } GoodListJson;

    typedef struct stu_ChangeGoodsJson{
        QString flag;
        QString Message;
        QString Result;
        stu_ChangeGoodsJson(){
            flag = "";
            Message = "";
            Result = "";
        }
    }ChangeJson;
public:
    LoginJson loginJson;
    NextRoad nextRoadJson;
    HomeJson homePageJson;
    MoutaiGood moutaiJson;
    GoodListJson goodListJson;
    ChangeJson goodChangedJson;//兑换后返回的信息
};
class CommonUtils
{
public:
    CommonUtils();
    static CommonUtils* Instance(){
        if(NULL == m_Comm){
            m_Comm = new CommonUtils();
        }
        return m_Comm;
    }
    void Relese();
    bool IsFilorDirExist(QString path);
    bool ImportAccount(QString filePath, QList<Account> *accountList);
    bool InsertDefAccountDoc(Account account);
    bool WriteReplayLog(JsonClass replayJson, QString path = "");//每个账号单独写一个文件

    bool ParseLoginJson(QString loginStr);//登录返回的json
    bool ParseHomePageJson(QString homeStr);//获取主页返回的json
    bool ParseGoodListsJson(QString goodsListStr);//获取商品列表返回的json
    bool ParseGoodItemJson(QString goodItemStr);//获取商品详情返回的json
    bool ParseChangeGoodJson(QString changeStr);//兑换商品返回的json
    inline JsonClass GetReplayJson(){
        return ReplayJson;
    }
    void inline SetDefAccDocPath(QString path){
        defAccDocPath = path;
    }
private:
    QJsonObject GetJsonObject(QString JsonStr);
    static CommonUtils* m_Comm;

    QFile *File;
    QFile *DefualtFile;
    QString defAccDocPath;//默认的账户文档地址

    JsonClass ReplayJson;
};



class ExcelHelper{
public:
    ExcelHelper();
    static ExcelHelper* Instance(){
        if(NULL == m_Excel){
            m_Excel = new ExcelHelper();
        }
        return m_Excel;
    }
    inline void SetLogListModel(QStandardItemModel* model){
        logListModel = model;
    }

    bool InitExcel(bool init = true);

    bool OpenExcel(QString strPath, QAxObject* pExcel, QAxObject* pWorkSheets);//打开Excel表
    bool CloseExcel(QString strPath, QAxObject* pExcel, QAxObject *pWorkBook);//关闭Excel表

    bool SetCell(QAxObject* pSheet, int row, int column, QString value);//根据行列设置单元格数据
    bool SetCell(QAxObject* pSheet, QString number, QString value);//根据行列的编号设置单元格数据，如A1:B1
    bool GetCell(QAxObject* pSheet, QString number, QString &strCell);//根据编号获得单元格数据
    bool GetCell(QAxObject* pSheet, int row, int column, QString &strCell);//根据行列获取单元格数据
private:


    static ExcelHelper* m_Excel;
        QString DefaultExcelPath;
        QAxObject *InitExcelObj;
        QStandardItemModel *logListModel;
};



class LogHelper{
public:
    LogHelper();
    static LogHelper* Instance(){
        if(m_log == NULL){
            m_log = new LogHelper();
        }
        return m_log;
    }
    inline void SetLogListModel(QStandardItemModel* model){
        logListModel = model;
    }
    bool AppendLogList(QString item);
private:
    static LogHelper* m_log;
    QStandardItemModel *logListModel;


};




#endif // UTIL_H
