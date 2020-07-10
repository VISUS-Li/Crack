
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
    Ui::YiPlusMain *ui;
    QFile *File_Account;
    QFile *File_RequestLog;
    QString FileAccoutnPath;
    QStandardItemModel *LogListItem;

    memberInfo_t *memberInfo;

    bool InitAccounts();

signals:

private slots:
    void on_Btn_AddAccount_clicked();
    void on_Btn_StartRob_clicked();
};


#endif // YIPLUSMAIN_H
