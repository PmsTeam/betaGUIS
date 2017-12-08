#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->playButton->setEnabled(false);
    ui->fullButton->setEnabled(false);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_clicked()
{
    //选择视频文件
       QString filename = QFileDialog::getOpenFileName(this,tr("选择视频文件"),".",tr("视频格式(*.avi *.mp4 *.flv *.mkv)"));
       QFile file(filename);
       if(!file.open(QIODevice::ReadOnly))
       {
           QMessageBox::information(NULL, "Title", "Content", QMessageBox::Ok, QMessageBox::Ok);
           return;
       }
       if(if_reload)
       {//重新加载视频时，重置以下变量
           delete layout_video;
           delete player;
           delete videoWidget;
           delete timer;
       }
       if_reload = true;

       //实例化三个全局变量
       layout_video = new QVBoxLayout;
       player = new QMediaPlayer;
       videoWidget = new QVideoWidget;
       //设置视频播放区域与Label的边距
       layout_video->setMargin(1);
       //根据label_player尺寸设置播放区域
       videoWidget->resize(ui->videoLabel->size());
       layout_video->addWidget(videoWidget);
       ui->videoLabel->setLayout(layout_video);
       player->setVideoOutput(videoWidget);

       //设置播放器
       player->setMedia(QUrl::fromLocalFile(filename));
       //play_state为true表示播放，false表示暂停
       play_state = true;
       //启用播放/暂停按钮，并将其文本设置为“暂停”
       ui->playButton->setEnabled(true);


       //播放器开启
       player->play();
}

void MainWindow::on_playButton_clicked()
{
    //反转播放状态
        if(play_state)
        {
            player->pause();
            ui->playButton->setText("播放");
        }
        else
        {
            player->play();
            ui->playButton->setText("暂停");
        }

        play_state = !play_state;
}
