
#include "yiplusmain.h"
#include "ui_YiPlusMain.h"
#include <QErrorMessage>
#include <QMessageBox>
#include <QDir>
#include "util.h"
#include "qaesencryption.h"

YiPlusMain::YiPlusMain(QWidget *parent) : QWidget(parent)
{
    ui = new Ui::YiPlusMain;
    ui->setupUi(this);
    {
        LogListItem = new QStandardItemModel(this);
        ui->List_Logs->setModel(LogListItem);
    }
    LogHelper::Instance()->SetLogListModel(LogListItem);

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
    int iRow = ui->Table_AllAccount->rowCount();
    ui->Table_AllAccount->insertRow(iRow+1);
    //ui->Table_AllAccount->setEditTriggers(QAbstractItemView::NoEditTriggers);
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








void YiPlusMain::on_Btn_StartRob_clicked()
{
    memberInfo_t *memberInfo = new memberInfo_t;
    /*
    memberInfo->userID = ui->Table_AllAccount->item(1,0)->text();
    memberInfo->memberID = ui->Table_AllAccount->item(1,1)->text();
    memberInfo->passWord = ui->Table_AllAccount->item(1,2)->text();
    memberInfo->token = ui->Table_AllAccount->item(1,3)->text();
    */
    memberInfo->userID = "15002326234";
    memberInfo->memberID = "9520017000830";
    memberInfo->passWord = "GCN0kn9VEM5pc7zPakk2YA==";
    //memberInfo->token = ui->Table_AllAccount->item(1,3)->text();

    changeThread *myThread = new changeThread(memberInfo);

    myThread->start();
}
