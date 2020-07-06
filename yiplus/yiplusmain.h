#ifndef YIPLUSMAIN_H
#define YIPLUSMAIN_H

#include <QWidget>
#include <QFile>
#include <QAxObject>
#include <QStandardItemModel>

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
    QAxObject *ExcelObj;
    QString FileAccoutnPath;
    QStandardItemModel *LogListItem;
    QString DefaultExcelPath;
    bool InitAccounts();
    bool InitExcel();
    void AppendLog(QString item);
    bool IsFilorDirExist(QString path);

signals:

private slots:
    void on_Btn_AddAccount_clicked();
};

#endif // YIPLUSMAIN_H
