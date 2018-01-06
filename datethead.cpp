#include "datethead.h"
#include <QDir>
#include <QCoreApplication>
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
    QString fileName;
    switch (kind)
    {
    case 1:
        fileName = "/cache/Digest-Car.csv";
        break;
    case 2:
        fileName = "/cache/Digest-People.csv";
        break;
    default:
        fileName = "/cache/Car-People.csv";
    }
    if(fileName == "")
          return;
    QFile file(QCoreApplication::applicationDirPath()+fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<file.errorString();
    }
    else
    {
        QString line;
        line = file.readLine();
        while(!file.atEnd())
        {
            line = file.readLine();
            qDebug()<<line;
            emit sendLine(line);
            sleep(1);
            file.flush();
        }
        file.close();
    }
    stopped = false;
}

void DateThead::chooseKind(int kind)
{
    this->kind = kind;
}
