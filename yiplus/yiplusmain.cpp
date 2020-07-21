#include "yiplusmain.h"
#include "ui_YiPlusMain.h"
#include <QErrorMessage>
#include <QMessageBox>
#include <QDir>
#include "util.h"
#include "qaesencryption.h"

YiPlusMain::YiPlusMain(QWidget *parent) : QWidget(parent)
{
	ProxyTimeOut = 300000;//五分钟，单位毫秒
    ui = new Ui::YiPlusMain;
    ui->setupUi(this);
    {
        LogListItem = new QStandardItemModel(this);
        ui->List_Logs->setModel(LogListItem);
    }
    LogHelper::Instance()->SetLogListModel(LogListItem);
    //打开日志文件
    LogHelper::Instance()->OpenAllLogsFile();
    OnInit();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(TimerFunc()));
    timer->start(600);
}

YiPlusMain::~YiPlusMain(){
    delete ui;
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

    //判断当前是否是要执行的时间
    QTime nowTime = QTime::currentTime();
    if(nowTime.hour() == 23 && nowTime.minute() == 50 && nowTime.second() == 30){
        //开始自动执行
        StartAllThread();
    }
    if(nowTime.hour() == 00 && nowTime.minute() == 10){
        //停止自动执行
        StopAllThread();
    }

    //代理超时，获取代理
    long long nowProxyTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    if((nowProxyTime - preProxyTime >= ProxyTimeOut)&&isStart){
        LogHelper::Instance()->AppendLogList("代理使用超时，重新获取","主线程");
        proxyData.clear();
        CommonUtils::Instance()->TryGetProxy(proxyData,preProxyTime,Accounts.count());
        int cnt=0;
		for(QList<changeThread*>::iterator iter = ThreadPool.begin(); iter != ThreadPool.end(); iter++){
            (*iter)->setProxyIp(proxyData[cnt].proxyIp);
            (*iter)->setProxyPort(proxyData[cnt].proxyPort);
			(*iter)->setPreProxyTime(preProxyTime);
            LogHelper::Instance()->AppendLogList("ID:"+QString::number(cnt+1)+",IP:"+proxyData[cnt].proxyIp+",Port:"+QString::number(proxyData[cnt].proxyPort),"主线程Timer");
            cnt++;
		}
    }
    ShowAccountInTable();

}
void YiPlusMain::StartAllThread(){
    //QString accPath = CommonUtils::Instance()->GetExePath("account.txt");
    //CommonUtils::Instance()->ImportAccount(accPath,&Accounts);
    if(Accounts.count() <= 0 || CommonUtils::Instance()->GetAccEnableCounts(Accounts) <= 0){
        LogHelper::Instance()->AppendLogList("可用账户为空");
    }
    proxyData.clear();
    preProxyTime = 0;
    int tryCount = 0;
    while(!CommonUtils::Instance()->TryGetProxy(proxyData,preProxyTime,Accounts.count())){
        tryCount++;
        LogHelper::Instance()->AppendLogList("获取代理列表失败,尝试次数:"+QString("%1").arg(tryCount));
    }

    if(ThreadPool.size() <= 0 ){
        for(int i = 0; i < Accounts.count(); i++){
            if(Accounts[i].GetPoneNumber() == ""){
                LogHelper::Instance()->AppendLogList("账户电话号码为空");
            }else if(Accounts[i].GetPassWord() == ""){
                LogHelper::Instance()->AppendLogList("账户密码为空");
            }else{
                memberInfo_t *memberInfo = new memberInfo_t;
                memberInfo->userID = Accounts[i].GetPoneNumber();
                memberInfo->passWord = Accounts[i].GetPassWord();
                memberInfo->store = CommonUtils::Instance()->ConvertStore(Accounts[i].GetStore(),false);
                changeThread *myThread = new changeThread(memberInfo);
                bool isChecked = ui->ckBox_useProxy->isChecked();
                myThread->setUseProxy(isChecked);
                if(proxyData[i].proxyIp != "" || proxyData[i].proxyPort != 0){
                    LogHelper::Instance()->AppendLogList("ID:"+QString::number(i+1)+",IP:"+proxyData[i].proxyIp+",Port:"+QString::number(proxyData[i].proxyPort),"主线程Start");
                    myThread->setProxyIp(proxyData[i].proxyIp);
                    myThread->setProxyPort(proxyData[i].proxyPort);
                    myThread->setPreProxyTime(preProxyTime);
                }
                ThreadPool.push_back(myThread);

                myThread->start();
                isStart = true;
                QEventLoop eventloop;
                QTimer::singleShot(1000, &eventloop, SLOT(quit()));
                eventloop.exec();
            }
        }
    }
}

void YiPlusMain::StopAllThread(){
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

void YiPlusMain::OnInit(){
    {
        tableModel = new QStandardItemModel;
        tableModel->setColumnCount(4);
        tableModel->setHeaderData(0, Qt::Horizontal, tr("账号"));
        tableModel->setHeaderData(1, Qt::Horizontal, tr("密码"));
        tableModel->setHeaderData(2, Qt::Horizontal, tr("店铺"));
        tableModel->setHeaderData(3, Qt::Horizontal, tr("兑换状态"));
        ui->Table_AllAccount->setModel(tableModel);
        ui->Table_AllAccount->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->Table_AllAccount->setColumnWidth(0, 250);
        ui->Table_AllAccount->setColumnWidth(1, 250);
        ui->Table_AllAccount->setColumnWidth(2, 250);
        ui->Table_AllAccount->setSelectionBehavior(QAbstractItemView::SelectRows);
        QItemSelectionModel * md = ui->Table_AllAccount->selectionModel();
        connect(md,SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this,SLOT(view_select_check()));
        ui->Btn_DelAccount->setEnabled(false);
        ui->Btn_EnableAccount->setEnabled(false);
    }
    QString accPath = CommonUtils::Instance()->GetExePath("account.txt");
    CommonUtils::Instance()->ImportAccount(accPath,&Accounts);
    ShowAccountInTable();
    selectedAccount = nullptr;
}
void YiPlusMain::view_select_check(){
    if(selectedAccount){
        delete selectedAccount;
        selectedAccount = nullptr;
    }

    int currentRow = ui->Table_AllAccount->currentIndex().row();
    Account *newAccount = new Account("","","");
    QModelIndex index = tableModel->index(currentRow,0);
    QVariant varNum = tableModel->data(index);
    newAccount->SetPhoneNumber(varNum.toString());

    index = tableModel->index(currentRow,1);
    QVariant varPwd = tableModel->data(index);
    newAccount->SetPassWord(varPwd.toString());

    index = tableModel->index(currentRow,2);
    QVariant varEnable = tableModel->data(index);
    if(varEnable.toString() == "不启用"){
        newAccount->setEnable(false);
        ui->Btn_EnableAccount->setText("启用");
    }else{
        ui->Btn_EnableAccount->setText("不启用");
    }

    ui->Btn_EnableAccount->setEnabled(true);
    ui->Btn_DelAccount->setEnabled(true);
    selectedAccount = newAccount;
    newAccount = nullptr;
}

void YiPlusMain::ShowAccountInTable(){
    tableModel->removeRows(0,tableModel->rowCount());
    int row = 0;
    for(QList<Account>::iterator iter = Accounts.begin(); iter != Accounts.end(); iter++){
        tableModel->insertRow(row);
        int col = 0;
        for(int i = 0; i < 4; i++){
            if(i == 0){
                tableModel->setItem(row,col,new QStandardItem(iter->GetPoneNumber()));

            }else if(i == 1){
                tableModel->setItem(row,col,new QStandardItem(iter->GetPassWord()));
            }else if(i == 2){
//                QString enable = "不启用";
//                if(iter->isEnable()){
//                    enable = "启用";
//                    //tableModel->item(row,col)->setForeground(Qt::green);
//                }
                tableModel->setItem(row,col,new QStandardItem(iter->GetStore()));
            }else if(i == 3){
                QString status = "未开始";
                for(QList<changeThread*>::iterator threadIter = ThreadPool.begin(); threadIter != ThreadPool.end(); threadIter++){
                    if((*threadIter)->getPhoneNumber() == iter->GetPoneNumber()){
                        if((*threadIter)->isChangeSucc()){
                            status = "兑换成功";
                        }else{
                            status = "正在兑换";
                        }
                    }
                }
                tableModel->setItem(row,col,new QStandardItem(status));
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
    Account newAccount(userName,passWord,"春熙店");
    CommonUtils::Instance()->InsertDefAccountDoc(newAccount,&Accounts);
    ShowAccountInTable();
}


void YiPlusMain::on_Btn_StartRob_clicked()
{
    ShowAccountInTable();
    StartAllThread();
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
    StopAllThread();
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

void YiPlusMain::on_Btn_ImportAccount_clicked()
{
    Account newaccount("","","");
    QString filename = QFileDialog::getOpenFileName(this,"Open Files", ".", "text file(*.txt)");
    QString importAccountPath = CommonUtils::Instance()->GetExePath("account.txt");
    QFile file(filename);
    if(! file.open(QIODevice::ReadOnly|QIODevice::Text)){
          LogHelper::Instance()->AppendLogList("导入账号，打开txt文件失败");
          return;
    }
    QByteArray allTxt = file.readAll();
    if(allTxt == ""){
        file.close();
        return ;
    }
    QString allStr(allTxt);
    QStringList allAccountList = allStr.split("\n",QString::SkipEmptyParts);
    if(allAccountList.count() <= 0){
        file.close();
        return ;
    }

    for(int i = 0; i < allAccountList.count(); i++){
        QString accountStr = allAccountList[i];
        QStringList splitAccount = accountStr.split(",",QString::SkipEmptyParts);
        if(splitAccount.count() <= 0){
            file.close();
            return ;
        }
        if(splitAccount.count() == 3){
            Account newAccount(splitAccount[0],splitAccount[1],splitAccount[2].toUtf8());
            CommonUtils::Instance()->InsertDefAccountDoc(newAccount, &Accounts);

        }
        if(file.isOpen())
            file.close();

    }

}


void YiPlusMain::on_Btn_DelAccount_clicked()
{
    return;
    int currentRow = ui->Table_AllAccount->currentIndex().row();
    QString num = tableModel->data(tableModel->index(currentRow,0)).toString();

    if(!selectedAccount || num == "")
        return;
    for(QList<Account>::iterator iter = Accounts.begin(); iter != Accounts.end(); ){
        if(iter->GetPoneNumber() == selectedAccount->GetPoneNumber()){
            iter = Accounts.erase(iter);
        }else{
            iter++;
        }
    }
    CommonUtils::Instance()->UpdateAccountToFile(&Accounts);
    ShowAccountInTable();
    ui->Btn_DelAccount->setEnabled(false);
    delete selectedAccount;
    selectedAccount = nullptr;
}

void YiPlusMain::on_Btn_EnableAccount_clicked()
{
    ui->Btn_EnableAccount->setEnabled(false);
    int currentRow = ui->Table_AllAccount->currentIndex().row();
    QString num = tableModel->data(tableModel->index(currentRow,0)).toString();

    if(!selectedAccount || num == "")
        return;

    bool Enable = false;
    if(selectedAccount->isEnable()){
        ui->Btn_EnableAccount->setText("不启用");
    }else{
        ui->Btn_EnableAccount->setText("启用");
        Enable = true;
    }
    for(QList<Account>::iterator iter = Accounts.begin(); iter != Accounts.end(); iter++){
        if(iter->GetPoneNumber() == selectedAccount->GetPoneNumber()){
            iter->setEnable(Enable);
        }
    }
    for(QList<changeThread*>::iterator iter = ThreadPool.begin(); iter != ThreadPool.end(); iter++){
        if((*iter)->getPhoneNumber() == selectedAccount->GetPoneNumber()){
            (*iter)->setEnable(Enable);
        }
    }
}
