#ifndef YIPLUSMAIN_H
#define YIPLUSMAIN_H

#include <QWidget>
#include <QFile>
#include <QAxObject>
#include <QStandardItemModel>
#include <QDebug>
#include <QThread>
#include <QFile>
#include <QFileDialog>

#include "changethread.h"
#include "account.h"
#include "common.h"

namespace Ui {
    class YiPlusMain;
}
class YiPlusMain : public QWidget
{
    Q_OBJECT
public:
    explicit YiPlusMain(QWidget *parent = nullptr);
    ~ YiPlusMain();

private:

    void OnInit();
    void ShowAccountInTable();
    void StartAllThread();
    void StopAllThread();

private:
    Ui::YiPlusMain *ui;
    QStandardItemModel *LogListItem;
    QStandardItemModel *tableModel;//用户表格
    QList<Account> Accounts;//所有用户
    QTimer *timer;
    QList<changeThread*> ThreadPool;//用于统一销毁线程
    Account *selectedAccount;//当前选中的账号
    qint64 preProxyTime;//上次获取代理的时间
    QList<ProxyData> proxyData;//获取到的代理列表
	long long ProxyTimeOut;//代理使用的超时时间
    bool isStart = false;
signals:

private slots:
    void on_Btn_AddAccount_clicked();
    void on_Btn_StartRob_clicked();
    void on_Btn_LoginTest_clicked();
    void on_Btn_StopAll_clicked();
    void on_Btn_ClearLog_clicked();
    void on_ckBox_useProxy_stateChanged(int arg1);
    void view_select_check();//表格被选中
    void TimerFunc();
    void on_Btn_ImportAccount_clicked();
    void on_Btn_DelAccount_clicked();
    void on_Btn_EnableAccount_clicked();
};


#endif // YIPLUSMAIN_H
