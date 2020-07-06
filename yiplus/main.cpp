#include "widget.h"

#include <QApplication>
#include "yiplusmain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    YiPlusMain yiPlus;
    yiPlus.show();
    return a.exec();
}
