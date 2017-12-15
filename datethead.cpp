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
    QFile *file;
    switch (kind)
    {
    case 1:
        file = new QFile("./cache/Digest-Car.csv");
        break;
    case 2:
        file = new QFile("./cache/Digest-People.csv");
        break;
    default:
        file = new QFile("./cache/Car-People.csv");
        break;
    }
    if (file->open(QIODevice :: ReadOnly))   //  以只读的方式打开
    {
        QString line;
        line = file->readLine();
        while(!file->atEnd())
        {
            line = file->readLine();
            qDebug()<<line;
            emit sendLine(line);
            sleep(1);
            file->flush();

        }
    }
    file->close();
    stopped = false;
}

void DateThead::chooseKind(int kind)
{
    this->kind = kind;
}
