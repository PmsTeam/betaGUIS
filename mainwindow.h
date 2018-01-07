#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVBoxLayout>
#include <QVideoWidget>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTimer>
#include <QTime>
#include <QProcess>
#include <QDialog>
#include <QDebug>
#include <QThread>
#include <QMouseEvent>
#include <QToolButton>
#include "datethead.h"
#include "customslider.h"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //播放视频的全局变量
    QString videoPath;
    QVBoxLayout * layout_video;//布局
    QMediaPlayer * player;   //播放器
    QVideoWidget * videoWidget;   //视频播放控件

    //播放状态，true为播放，false为暂停
    bool play_state;
    //是否重新载入视频
    bool if_reload=false;
    //与Slider有关的播放控制变量
    QTimer * videoSlderTimer;
    int maxValue = 1000;//设置进度条的最大值
    //与Slider有关的播放控函数
    QDialog *about = new QDialog;//set about

    DateThead *datethread;//set datethread
    int kind;
    void readCarText();

signals:
    void sendKind(int kind);
public slots:
    void openVideo();
    void showAbout();
    void setLine(QString line);

    void on_playButton_clicked();
    void on_pedestrianButton_clicked();
    void on_vehicleButton_clicked();

    void onTimerOut();
    void horizontalSlider_clicked();
    void horizontalSlider_moved();
    void horizontalSlider_released();
    void on_flowButton_clicked();

private:
    Ui::MainWindow *ui;

    void initDate(QString initString);
    void runCoreProcess(int kind);
};

#endif // MAINWINDOW_H
