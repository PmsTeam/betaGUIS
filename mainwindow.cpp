#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->playButton->setEnabled(false);
    ui->fullButton->setEnabled(false);
    ui->vehicleButton->setEnabled(false);
    ui->pedestrianButton->setEnabled(false);


    connect(ui->actionOpen,SIGNAL(triggered(bool)),this,SLOT(openVideo()));
    connect(ui->aboutUs,SIGNAL(triggered(bool)),this,SLOT(showAbout()));
    //connect(player,&QMediaPlayer::metaDataAvailableChanged,this,&MainWindow::metaDataAvailableChanged);
}

MainWindow::~MainWindow()
{
    delete thread;
}


void MainWindow::showAbout()
{
    QLabel *teamName = new QLabel("teamName:PMS");
    QGridLayout *gLayout = new QGridLayout;
    gLayout->addWidget(teamName,0,1,1,1);


    about->setFixedSize(300,100);
    about->setWindowTitle("About us");
    about->setLayout(gLayout);
    about->show();
}
void MainWindow::openVideo()
{

    //选择视频文件
    videoPath = QFileDialog::getOpenFileName(this,tr("选择视频文件"),".",tr("视频格式(*.avi *.mp4 *.flv)"));
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
    ui->vehicleButton->setEnabled(true);
    ui->pedestrianButton->setEnabled(true);
    ui->playButton->setEnabled(true);

//    ui->labelVideoName->setText(videoTitle);
//    ui->labelVideoTime->setText(videoDate);

    ui->labelVideoLength->setText(videoPath);
    ui->labelVideoLength->adjustSize();
    ui->labelVideoLength->setGeometry(QRect(328, 240, 329, 27*4));  //四倍行距
    ui->labelVideoLength->setWordWrap(true);
    ui->labelVideoLength->setAlignment(Qt::AlignTop);


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
        videoTitle = player ->metaData("Title").toString();
        videoDate = player ->metaData("date").toString();
    }
}

void MainWindow::on_vehicleButton_clicked()
{
    QString program = "./TOTEL-SE.exe";
    QStringList argument;
    argument << "-c" << videoPath;

    coreProcess.start(program,argument);

    thread = new DateThead();
    connect(thread,SIGNAL(sendCarNumber(QString)),this,SLOT(setCarNumber(QString)));
    thread->start();
    ui->summaryButton->setEnabled(true);
}

void MainWindow::setCarNumber(QString carNumber)
{
    ui->labelCarNumber->setText(carNumber);
}

void MainWindow::on_pedestrianButton_clicked()
{
    QString program = "./TOTEL-SE.exe";
    QStringList argument;
    argument << "-p" << videoPath;

    coreProcess.start(program,argument);
    thread = new DateThead();
    connect(thread,SIGNAL(sendCarNumber(QString)),this,SLOT(setCarNumber(QString)));
    thread->start();
    ui->summaryButton->setEnabled(true);
}
void MainWindow::setPeopleNumber(QString peopleNumber)
{
    ui->labelPeopleNumber->setText(peopleNumber);
}
void MainWindow::setSpeed(QString speed)
{
    ui->labelSpeed->setText(speed);
}

void MainWindow::on_summaryButton_clicked()
{
    if(thread->isRunning())
    {
        thread->stop();
        ui->summaryButton->setEnabled(false);
    }
//    QProcess sum;
//    QString program = "./video_abstract.exe";
//    QStringList argument;
//    argument  << videoPath;
//    sum.start(program,argument);
}
