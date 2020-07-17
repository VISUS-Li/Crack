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
    //监听是否启用代理
    for(QList<changeThread*>::iterator iter = ThreadPool.begin(); iter != ThreadPool.end(); iter++){
    bool isChecked = ui->ckBox_useProxy->isChecked();
    (*iter)->setUseProxy(isChecked);
    }

}
void YiPlusMain::OnInit(){
    {
        tableModel = new QStandardItemModel;
        tableModel->setColumnCount(3);
        tableModel->setHeaderData(0, Qt::Horizontal, tr("账号"));
        tableModel->setHeaderData(1, Qt::Horizontal, tr("密码"));
        tableModel->setHeaderData(2, Qt::Horizontal, tr("启用?"));
        ui->Table_AllAccount->setModel(tableModel);
        ui->Table_AllAccount->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->Table_AllAccount->setColumnWidth(0, 250);
        ui->Table_AllAccount->setColumnWidth(1, 250);
        ui->Table_AllAccount->setColumnWidth(2, 250);
        ui->Table_AllAccount->setSelectionBehavior(QAbstractItemView::SelectRows);
        QItemSelectionModel * md = ui->Table_AllAccount->selectionModel();
        connect(md,SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this,SLOT(view_select_check));
    }
    QString accPath = CommonUtils::Instance()->GetExePath("account.txt");
    CommonUtils::Instance()->ImportAccount(accPath,&Accounts);
    ShowAccountInTable();

}
void YiPlusMain::view_select_check(){
    ui->Btn_DelAccount->setEnabled(true);
    int currentRow = ui->Table_AllAccount->currentIndex().row();
    QModelIndex index = tableModel->index(currentRow,2);
    //tableModel->
    ui->Btn_EnableAccount->setEnabled(true);
}

void YiPlusMain::ShowAccountInTable(){
    tableModel->removeRows(0,tableModel->rowCount());
    int row = 0;
    for(QList<Account>::iterator iter = Accounts.begin(); iter != Accounts.end(); iter++){
        tableModel->insertRow(row);
        int col = 0;
        for(int i = 0; i < 3; i++){
            if(i == 0){
                tableModel->setItem(row,col,new QStandardItem(iter->GetPoneNumber()));

            }else if(i == 1){
                tableModel->setItem(row,col,new QStandardItem(iter->GetPassWord()));
            }else if(i == 2){
                QString enable = "不启用";
                if(iter->isEnable()){
                    enable = "启用";
                    //tableModel->item(row,col)->setForeground(Qt::green);
                }
                tableModel->setItem(row,col,new QStandardItem(enable));
            }
            col++;
        }
        row++;
    }
}

void YiPlusMain::on_Btn_AddAccount_clicked()
{
    ShowAccountInTable();
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
    ShowAccountInTable();
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
    ShowAccountInTable();
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
    ShowAccountInTable();
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
