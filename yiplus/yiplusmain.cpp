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
    tableHeader << "账号" << "密码" << "启用？";

    ui->Table_AllAccount->horizontalHeader()->setDefaultSectionSize(180);
    ui->Table_AllAccount->setColumnCount(3);
    ui->Table_AllAccount->setHorizontalHeaderLabels(tableHeader);
    ui->Table_AllAccount->verticalHeader()->setVisible(true);
    ui->Table_AllAccount->setShowGrid(true);
    ui->Table_AllAccount->horizontalHeader()->setStyleSheet("QHeaderView::section{background::skyblue;}");
    ui->Table_AllAccount->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int iRow = ui->Table_AllAccount->rowCount();
    ui->Table_AllAccount->insertRow(iRow+1);
    //ui->Table_AllAccount->setEditTriggers(QAbstractItemView::NoEditTriggers);

    OnInit();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(TimerFunc()));
    timer->start(600);
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
    if(timer->isActive()){
        timer->stop();
    }
}
void YiPlusMain::TimerFunc(){
    //监听是否打日志
    LogHelper::Instance()->SetIsPrintLog(ui->ckBox_PrintLog->isChecked());
}
void YiPlusMain::OnInit(){
    QString accPath = CommonUtils::Instance()->GetExePath("account.txt");
    CommonUtils::Instance()->ImportAccount(accPath,&Accounts);
    ShowAccountInTable();

}

void YiPlusMain::ShowAccountInTable(){
    ui->Table_AllAccount->clear();
    int row = 0;
    for(QList<Account>::iterator iter = Accounts.begin(); iter != Accounts.end(); iter++){
        int col = 0;
        for(int i = 0; i < 3; i++){
            QTableWidgetItem* item;
            if(i != 2){
                item = new QTableWidgetItem(iter->GetPoneNumber());
            }else{
                QString enable = "不启用";
                if(iter->isEnable()){
                    enable = "启用";
                }
                item = new QTableWidgetItem(enable);
            }
            ui->Table_AllAccount->setItem(row,col,item);
            col++;
        }
        row++;
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
    Account newAccount(userName,passWord,"001");
    CommonUtils::Instance()->InsertDefAccountDoc(newAccount,&Accounts);
    ShowAccountInTable();
}


void YiPlusMain::on_Btn_StartRob_clicked()
{
    QString accPath = CommonUtils::Instance()->GetExePath("account.txt");
    CommonUtils::Instance()->ImportAccount(accPath,&Accounts);
    if(Accounts.size() <= 0 || CommonUtils::Instance()->GetAccEnableCounts(Accounts) <= 0){
        LogHelper::Instance()->AppendLogList("可用账户为空");
    }
    if(ThreadPool.size() <= 0 ){
        for(int i = 0; i < Accounts.size(); i++){
            if(Accounts[i].GetPoneNumber() == ""){
                LogHelper::Instance()->AppendLogList("账户电话号码为空");
            }else if(Accounts[i].GetPassWord() == ""){
                LogHelper::Instance()->AppendLogList("账户密码为空");
            }else{
                memberInfo_t *memberInfo = new memberInfo_t;
                memberInfo->userID = Accounts[i].GetPoneNumber();
                memberInfo->passWord = Accounts[i].GetPassWord();
                memberInfo->store = Accounts[i].GetStore();
                changeThread *myThread = new changeThread(memberInfo);
                bool isChecked = ui->ckBox_useProxy->isChecked();
                myThread->setUseProxy(isChecked);
                ThreadPool.push_back(myThread);

                myThread->start();

                QEventLoop eventloop;
                QTimer::singleShot(300, &eventloop, SLOT(quit()));
                eventloop.exec();
            }
        }
    }
}

void YiPlusMain::on_Btn_LoginTest_clicked()
{
    QString userName = ui->Edit_UserName->text();
    QString passWord = ui->Edit_Password->text();
    Account newAccount(userName,passWord,"001");
    memberInfo_t *memberInfo = new memberInfo_t;
    memberInfo->userID = userName;
    memberInfo->passWord = passWord;
    memberInfo->store = "001";
    changeThread *myThread = new changeThread(memberInfo);
    bool isChecked = ui->ckBox_useProxy->isChecked();
    myThread->setUseProxy(isChecked);
    myThread->setIsLoginTest(true);
    ThreadPool.push_back(myThread);
    myThread->start();
}

void YiPlusMain::on_Btn_StopAll_clicked()
{
    if(ThreadPool.size() > 0){
        for(int i = 0; i <= ThreadPool.size(); i++){
            changeThread *myThread = ThreadPool.front();
            if(!myThread->getStopStatus()){
                myThread->setStopValue(true);
            }
            myThread->wait();
            ThreadPool.pop_front();
        }
    }
}

void YiPlusMain::on_Btn_ClearLog_clicked()
{
    QStandardItemModel *model = dynamic_cast<QStandardItemModel*>(ui->List_Logs->model());
    int rowCount = ui->List_Logs->model()->rowCount();
    for(int i = 0; i < rowCount; i++){
        model->removeRow(i);
    }
}

void YiPlusMain::on_ckBox_useProxy_stateChanged(int arg1)
{
    bool isChecked = ui->ckBox_useProxy->isChecked();
    for(int i = 0; i < ThreadPool.count(); i++){
        ThreadPool[i]->setUseProxy(isChecked);
    }
}
