#ifndef HOME_ANALYSIS_H
#define HOME_ANALYSIS_H

#include <QWidget>

namespace Ui {
class Home_Analysis;
}

class Home_Analysis : public QWidget
{
    Q_OBJECT

public:
    explicit Home_Analysis(QWidget *parent = 0);
    ~Home_Analysis();
signals:
    void display(int number);
private slots:
    void on_returnButton_clicked();

private:
    Ui::Home_Analysis *ui;
};

#endif // HOME_ANALYSIS_H
