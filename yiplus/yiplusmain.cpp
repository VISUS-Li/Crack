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

bool YiPlusMain::InitAccounts(){
    ////创建或打开账户列表文件
    QString qexeFullPath = QCoreApplication::applicationDirPath();
    FileAccoutnPath = qexeFullPath + "accounts.txt";
    File_Account = new QFile(FileAccoutnPath);
    //文件不存在则创建
    if(!File_Account->exists(FileAccoutnPath)){
        if(!File_Account->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)){
            QString msg = "打开accoutns.txt文件失败，路径为:"+FileAccoutnPath;
            QMessageBox::warning(NULL,"打开文件",msg);
        }
        File_Account->close();
    }
    if(!File_Account->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)){
        QString msg = "打开accoutns.txt文件失败，路径为:"+FileAccoutnPath;
        QMessageBox::warning(NULL,"打开文件",msg);
    }
}


void YiPlusMain::on_Btn_AddAccount_clicked()
{
    QString userName = ui->Edit_UserName->text();
    QString passWord = ui->Edit_Password->text();
    if(userName == "" || passWord == ""){
        QMessageBox::information(NULL,"添加用户","用户名或密码不能为空");
        return;
    }

}







