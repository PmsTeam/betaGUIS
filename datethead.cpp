#include "datethead.h"
DateThead::DateThead(QObject *parent):
    QThread(parent)
{
    stopped = false;

}

void DateThead::stop()
{
    stopped = true;
}
void DateThead::run()
{
    QFile file("G:/study/QT/build-betaEyes-Desktop_Qt_5_9_2_MSVC2017_64bit-Debug/cache/Digest-Car.csv");
    if (file.open(QIODevice :: ReadOnly))   //  以只读的方式打开
    {
        QString line;
        line = file.readLine();
        while(!file.atEnd())
        {
            line = file.readLine();
            QStringList tempbar = line.split(",");//一行中的单元格以，区分
            qDebug()<<tempbar.at(1);
            emit sendCarNumber(tempbar.at(1));
            emit sendSpeed(tempbar.at(3));
            sleep(1);
            file.flush();

        }
    }
    stopped = false;
}
