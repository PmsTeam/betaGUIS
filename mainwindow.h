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
#include <QProcess>

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
    QTimer * timer;
    int maxValue = 1000;//设置进度条的最大值

    QString title;
    QString date;

    QProcess * coreProcess = new QProcess(this);
public slots:
    void openVideo();

private slots:
    void on_openButton_clicked();

    void on_playButton_clicked();

    void metaDataAvailableChanged(bool available);


    void on_pedestrianButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
