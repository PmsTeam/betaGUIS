#ifndef HOME_H
#define HOME_H

#include <QWidget>

namespace Ui {
class Home;
}

class Home : public QWidget
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = 0);
    ~Home();

signals:
    void display(int number);

private slots:
    void on_pushButton_clicked();//点击视频分析

private:
    Ui::Home *ui;
};

#endif // HOME_H
