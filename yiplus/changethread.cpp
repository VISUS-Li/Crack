#include "changethread.h"
#include "common.h"

changeThread::changeThread(QTableWidget *table, int Row)
{
    this->table = table;
    currentRow  = Row;

    userID = table->item(currentRow, 0)->text();
    memberID = table->item(currentRow, 1)->text();
    passWord = table->item(currentRow, 2)->text();
    token = table->item(currentRow, 3)->text();

}

void  changeThread::run()
{


}



bool changeThread::returnURLCheck(QJsonDocument document)
{

    return true;
}

