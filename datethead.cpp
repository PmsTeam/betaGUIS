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
    QProcess coreProcess;
    QString program = "TOTEL-SE.exe";
    QStringList arguments;
    switch (kind)
    {
    case 1:
        arguments << "-c";
        break;
    case 2:
        arguments << "-p";
    default:
        arguments << "-d";
        break;
    }
    arguments << videoPath;
    coreProcess.start(program,arguments);
    while(coreProcess.waitForReadyRead(3000))
    {
        QString line = coreProcess.readAllStandardOutput();
        emit sendLine(line);
    }
    stopped = false;
}

void DateThead::chooseKind(int kind)
{
    this->kind = kind;
}

void DateThead::setVideoPath(QString path)
{
    this->videoPath = path;
}
