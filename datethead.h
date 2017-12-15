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
    void sendCarNumber(const QString &carNumber);
    void sendPeopleNumber(const QString &peopleNumber);
    void sendSpeed(const QString& speed);

private slots:
    void chooseKind();
};

#endif // DATETHEAD_H
