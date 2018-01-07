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
    QProcess coreProcess;//外部程序
    QString program = "TOTEL-SE.exe";//程序名
    QStringList arguments;//命令行参数
    switch (kind)
    {
    case 1:
        arguments << "-c";//车辆识别
        break;
    case 2:
        arguments << "-p";//行人识别
        break;
    default:
        arguments << "-d";//人车识别
    }
    arguments << videoPath;
    coreProcess.start(program,arguments);//程序执行
    while(coreProcess.waitForReadyRead(3000))
    {
        QString line = coreProcess.readAllStandardOutput();//读取一行数据
        emit sendLine(line);//传送数据
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
