#ifndef YIPLUSMAIN_H
#define YIPLUSMAIN_H

#include <QWidget>
#include <QFile>
#include <QAxObject>
#include <QStandardItemModel>
#include <QDebug>
#include <QThread>

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

private:
    Ui::YiPlusMain *ui;
    QFile *File_Account;
    QFile *File_RequestLog;
    QString FileAccoutnPath;
    QStandardItemModel *LogListItem;
    QList<Account> Accounts;//所有用户

    QList<changeThread*> ThreadPool;//用于同一销毁线程
signals:

private slots:
    void on_Btn_AddAccount_clicked();
    void on_Btn_StartRob_clicked();
};


#endif // YIPLUSMAIN_H
