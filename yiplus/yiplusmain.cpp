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

    ui->Table_AllAccount->horizontalHeader()->setDefaultSectionSize(180);
    ui->Table_AllAccount->setColumnCount(4);
    ui->Table_AllAccount->setHorizontalHeaderLabels(tableHeader);
    ui->Table_AllAccount->verticalHeader()->setVisible(false);
    ui->Table_AllAccount->setShowGrid(false);
    ui->Table_AllAccount->horizontalHeader()->setStyleSheet("QHeaderView::section{background::skyblue;}");
    ui->Table_AllAccount->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int iRow = ui->Table_AllAccount->rowCount();
    ui->Table_AllAccount->insertRow(iRow+1);
    //ui->Table_AllAccount->setEditTriggers(QAbstractItemView::NoEditTriggers);

    OnInit();
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

void YiPlusMain::OnInit(){
    QString accPath = CommonUtils::Instance()->GetExePath("account.txt");
    CommonUtils::Instance()->ImportAccount(accPath,&Accounts);

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
    for(int i = 0; i < Accounts.size(); i++){
        memberInfo_t *memberInfo = new memberInfo_t;
        memberInfo->userID = Accounts[i].GetPoneNumber();
        memberInfo->passWord = Accounts[i].GetPassWord();
        memberInfo->store = Accounts[i].GetStore();
        changeThread *myThread = new changeThread(memberInfo);
        ThreadPool.push_back(myThread);

        myThread->start();
    }


}
