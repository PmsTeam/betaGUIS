#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QFont>
#include <QFontDatabase>

class CommonHelper
{
public:
    static void setStyle(const QString &style)
    {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //CommonHelper::setStyle("G:/study/QT/betaEyes/style.qss");//设置style

    MainWindow w;
    w.setWindowTitle("YourEyes");
    w.show();

    return a.exec();
}
