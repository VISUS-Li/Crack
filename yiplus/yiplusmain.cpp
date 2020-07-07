#include "yiplusmain.h"
#include "ui_YiPlusMain.h"
#include <QErrorMessage>
#include <QMessageBox>
#include <QDir>
#include "util.h"
#include "excelengine.h"
YiPlusMain::YiPlusMain(QWidget *parent) : QWidget(parent)
{
    ui = new Ui::YiPlusMain;
    ui->setupUi(this);
    {
        LogListItem = new QStandardItemModel(this);
        ui->List_Logs->setModel(LogListItem);
    }
<<<<<<< HEAD
    InitExcel();
    InitAccounts();

    QStringList tableHeader;
    tableHeader << "账号" << "会员ID" << "密码" << "token";

    /*tableHeader << QString::fromLocal8Bit("账号")\
                << QString::fromLocal8Bit("会员ID")\
                << QString::fromLocal8Bit("密码")\
                << QString::fromLocal8Bit("token");
    */
    ui->Table_AllAccount->horizontalHeader()->setDefaultSectionSize(180);
    ui->Table_AllAccount->setColumnCount(4);
    ui->Table_AllAccount->setHorizontalHeaderLabels(tableHeader);
    ui->Table_AllAccount->verticalHeader()->setVisible(false);
    ui->Table_AllAccount->setShowGrid(false);
    ui->Table_AllAccount->horizontalHeader()->setStyleSheet("QHeaderView::section{background::skyblue;}");
    ui->Table_AllAccount->setEditTriggers(QAbstractItemView::NoEditTriggers);
=======
    QString qexeFullPath = QCoreApplication::applicationDirPath();
    QString DefaultExcelPath = qexeFullPath + "/DefaultExcel.xlsx";
    DefaultExcelPath =  QDir::toNativeSeparators(DefaultExcelPath);
    ExcelEngine *excelInstance = ExcelEngine::getInstance();
    excelInstance->createExcelFile(DefaultExcelPath);
    excelInstance->setActiveExcel(DefaultExcelPath);
    excelInstance->writeText(3,2,"AVASASF");
    QString tmp = excelInstance->getExcelValue(3,2);

    excelInstance->saveExcel();
    excelInstance->closeActiveExcel();

>>>>>>> 4281a334907f28c0ea1a6ae90fd88123eaa2e8dd

}

YiPlusMain::~YiPlusMain(){
    delete ui;
    if(File_Account){
        File_Account->close();
        delete(File_Account);
    }
    if(File_RequestLog){
        File_RequestLog->close();
        delete(File_RequestLog);
    }
}

<<<<<<< HEAD
void YiPlusMain::AppendLog(QString item){
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
    item = time + " " + item;
    QStandardItem *stItem = new QStandardItem(item);
    LogListItem->appendRow(stItem);
}

bool YiPlusMain::InitExcel(){
    QString qexeFullPath = QCoreApplication::applicationDirPath();
    DefaultExcelPath = qexeFullPath + "DefaultExcel.xlsx";
    ExcelObj = new QAxObject(this);
    if(ExcelObj->setControl("Excel.Application")){
        AppendLog("加载Excel成功!");

    }else{
        if(ExcelObj->setControl("ket.Application")){
            AppendLog("加载WPS-Excel成功");

        }else{
            AppendLog("加载Excel或WPS-Excel失败");
            return false;
        }
    }

    ExcelObj->setProperty("Visible",false);//不显示窗体

    QAxObject *workBooks = ExcelObj->querySubObject("WorkBooks");//获取工作蒲集合
    if(!IsFilorDirExist(DefaultExcelPath)){
        workBooks->dynamicCall("Add");
        QAxObject *_workBook = ExcelObj->querySubObject("ActiveWorkBook");//获取当前工作蒲
        _workBook->dynamicCall("SaveAs(const QString&)",DefaultExcelPath);
    }
    workBooks->dynamicCall("Open(const QString&)", DefaultExcelPath);//打开已存在的excel
    QAxObject *workBook = ExcelObj->querySubObject("ActiveWorkBook");//获取当前工作蒲
    QAxObject *sheets = workBook->querySubObject("Sheets");//获取工作表集合
    QAxObject *sheet = workBook->querySubObject("WorkSheets(int)",1);//获取工作表1，sheet1
    QAxObject *range = sheet->querySubObject("UsedRange");//获取该sheet的使用范围对象
    QVariant var = range->dynamicCall("Value");
    delete range;

    QVariantList varRows = var.toList();//得到表格中的所有数据
    if(varRows.isEmpty()){
        AppendLog(DefaultExcelPath+" 中的数据为空");
        return false;
    }else{
        const int rowCount = varRows.size();
        for(int i = 1; i < rowCount; i++){
            QVariantList rowData = varRows[i].toList();

        }
        return true;
    }
}

=======
>>>>>>> 4281a334907f28c0ea1a6ae90fd88123eaa2e8dd
bool YiPlusMain::InitAccounts(){
    ////创建或打开账户列表文件
    QString qexeFullPath = QCoreApplication::applicationDirPath();
    FileAccoutnPath = qexeFullPath + "accounts.txt";
    File_Account = new QFile(FileAccoutnPath);
    //文件不存在则创建
    if(!File_Account->exists(FileAccoutnPath)){
        if(!File_Account->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)){
            QString msg = "打开accoutns.txt文件失败，路径为:"+FileAccoutnPath;
            QMessageBox::warning(nullptr,"打开文件",msg);
        }
        File_Account->close();
    }
    if(!File_Account->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)){
        QString msg = "打开accoutns.txt文件失败，路径为:"+FileAccoutnPath;
        QMessageBox::warning(nullptr,"打开文件",msg);
    }

    return false;
}


void YiPlusMain::on_Btn_AddAccount_clicked()
{
    QString userName = ui->Edit_UserName->text();
    QString passWord = ui->Edit_Password->text();
    if(userName == "" || passWord == ""){
        QMessageBox::information(nullptr,"添加用户","用户名或密码不能为空");
        return;
    }

}







