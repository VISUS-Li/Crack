#include "util.h"
#include <QFile>
#include <QDateTime>
#include <QDir>
#include <QCoreApplication>

LogHelper *LogHelper::m_log = NULL;
CommonUtils *CommonUtils::m_Comm = NULL;
ExcelHelper *ExcelHelper::m_Excel = NULL;

CommonUtils::CommonUtils()
{}

bool CommonUtils::IsFilorDirExist(QString path){
    QFile file(path);
    if(file.exists()){
        return true;
    }else{
        return false;
    }
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

//    InitExcelObj = new QAxObject();
//    if(InitExcelObj->setControl("Excel.Application")){
//        LogHelper::Instance()->AppendLogList("加载Excel成功!");
//    }else{
//        if(InitExcelObj->setControl("ket.Application")){
//            LogHelper::Instance()->AppendLogList("加载WPS-Excel成功");
//        }else{
//            LogHelper::Instance()->AppendLogList("加载Excel或WPS-Excel失败");
//            return false;
//        }
//    }

//    InitExcelObj->setProperty("Visible",false);//不显示窗体

//    QAxObject *workBooks = InitExcelObj->querySubObject("WorkBooks");//获取工作蒲集合
//    if(!CommonUtils::Instance()->IsFilorDirExist(DefaultExcelPath)){
//        workBooks->dynamicCall("Add");
//        QAxObject *_workBook = InitExcelObj->querySubObject("ActiveWorkBook");//获取当前工作蒲
//        QVariant savVar = _workBook->dynamicCall("SaveAs(const QString&)",DefaultExcelPath);
//        QAxObject *A1Range = _workBook->querySubObject("Range(const QString&)","A1:A1");
//        bool setStatus = A1Range->setProperty("Value","会员ID");
//        QAxObject *B1Range = _workBook->querySubObject("Range(const QString&)","B1:B1");
//        setStatus = B1Range->setProperty("Value","m");
//        QAxObject *C1Range = _workBook->querySubObject("Range(const QString&)","C1:C1");
//        setStatus = C1Range->setProperty("Value","i");
//        //_workBook->dynamicCall("SaveAs(const QString&)",DefaultExcelPath);
//        workBooks->dynamicCall("Save()");
//        workBooks->dynamicCall("Close()");

//    }
//    workBooks->dynamicCall("Open(const QString&)", DefaultExcelPath);//打开已存在的excel
//    QAxObject *workBook = InitExcelObj->querySubObject("ActiveWorkBook");//获取当前工作蒲
//    QAxObject *sheets = workBook->querySubObject("Sheets");//获取工作表集合
//    QAxObject *sheet = workBook->querySubObject("WorkSheets(int)",1);//获取工作表1，sheet1
//    QAxObject *range = sheet->querySubObject("UsedRange");//获取该sheet的使用范围对象
//    QVariant var = range->dynamicCall("Value");
//    delete range;

//    QVariantList varRows = var.toList();//得到表格中的所有数据
//    if(varRows.isEmpty()){
//        AppendLog(DefaultExcelPath+" 中的数据为空");
//    }else{
//        const int rowCount = varRows.size();
//        for(int i = 1; i < rowCount; i++){
//            QVariantList rowData = varRows[i].toList();

//        }
//    }
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
