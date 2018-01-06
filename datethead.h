#ifndef DATETHEAD_H
#define DATETHEAD_H
#include <QThread>
#include <QDebug>
#include <QFile>
#include <QTextStream>

class DateThead:public QThread
{
        Q_OBJECT
public:
    explicit DateThead(QObject *parent = 0);
    void stop();

protected:
    void run();

private:
    volatile bool stopped;
    int kind;

signals:
    void sendLine(const QString &carNumber);//输出一行

public slots:
    void chooseKind(int kind);
};

#endif // DATETHEAD_H
