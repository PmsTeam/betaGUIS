#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->playButton->setEnabled(false);
    ui->fullButton->setEnabled(false);

    connect(player,&QMediaPlayer::metaDataAvailableChanged,this,&MainWindow::metaDataAvailableChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openVideoButton()
{
    //选择视频文件
    videoPath = QFileDialog::getOpenFileName(this,tr("选择视频文件"),".",tr("视频格式(*.avi *.mp4 *.flv *.mkv *.wmv)"));
    QFile file(videoPath);
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
    player->setMedia(QUrl::fromLocalFile(videoPath));
    //play_state为true表示播放，false表示暂停
    play_state = true;
    //启用播放/暂停按钮，并将其文本设置为“暂停”
    ui->playButton->setEnabled(true);

    ui->videoName->setText(title);
    ui->videoTime->setText(date);
    ui->videoLength->setText(videoPath);

    //播放器开启
    player->play();
}

void MainWindow::on_openButton_clicked()
{
   //选择视频文件
   videoPath = QFileDialog::getOpenFileName(this,tr("选择视频文件"),".",tr("视频格式(*.avi *.mp4 *.flv *.mkv *.wmv)"));
   QFile file(videoPath);
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
   player->setMedia(QUrl::fromLocalFile(videoPath));
   //play_state为true表示播放，false表示暂停
   play_state = true;
   //启用播放/暂停按钮，并将其文本设置为“暂停”
   ui->playButton->setEnabled(true);

   ui->videoName->setText(title);
   ui->videoTime->setText(date);
   ui->videoLength->setText(videoPath);

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

void MainWindow::metaDataAvailableChanged(bool available)
{
    if(available)
    {
        title = player ->metaData("Title").toString();
        date = player ->metaData("date").toString();
    }
}

void MainWindow::on_pedestrianButton_clicked()
{
    core->start("G:/study/QT/build-betaEyes-Desktop_Qt_5_9_2_MSVC2017_64bit-Debug/Tracking-t.exe");
//    QString program = "/PeopleAndVehicleDetevtionTracking.exe";
//    QStringList argument;
//    arguments << "-p" << videoPath;

//    core -> start(program,argument);
//    core->waitForFinished();
}
