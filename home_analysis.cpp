#include "home_analysis.h"
#include "ui_home_analysis.h"

Home_Analysis::Home_Analysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_Analysis)
{
    ui->setupUi(this);
}

Home_Analysis::~Home_Analysis()
{
    delete ui;
}

void Home_Analysis::on_returnButton_clicked()
{
    emit display(0);
}
