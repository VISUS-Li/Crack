#ifndef UTIL_H
#define UTIL_H
#include <QString>
#include <QAxObject>
#include <QStandardItemModel>
namespace Utils {
    class CommonUtils;
    class ExcelHelper;
    class LogHelper;
}
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

    bool IsFilorDirExist(QString path);
private:
    static CommonUtils* m_Comm;
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
