#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->playButton->setEnabled(false);//播放按钮先用不了
    ui->vehicleButton->setEnabled(false);//车辆识别按钮先用不了
    ui->pedestrianButton->setEnabled(false);//行人识别按钮先用不了
    ui->summaryButton->setEnabled(false);//视频摘要按钮先用不了
    ui->flowButton->setEnabled(false);//人车识别按钮先用不了
    ui->horizontalSlider->setEnabled(false);
    //播放器连接槽函数
    connect(ui->horizontalSlider,&CustomSlider::costomSliderClicked,this,&MainWindow::horizontalSlider_clicked);
    connect(ui->horizontalSlider,&CustomSlider::sliderMoved,this,&MainWindow::horizontalSlider_moved);
    connect(ui->horizontalSlider,&CustomSlider::sliderReleased,this,&MainWindow::horizontalSlider_released);

    connect(ui->actionOpen,SIGNAL(triggered(bool)),this,SLOT(openVideo()));//打开视频按键的信号槽连接
    connect(ui->about,SIGNAL(triggered(bool)),this,SLOT(showAbout()));//关于按键的信号槽链接
}

MainWindow::~MainWindow()
{

}

void MainWindow::showAbout()//显示关于
{
    QLabel *teamName = new QLabel("teamName:PMS");
    QGridLayout *gLayout = new QGridLayout;
    gLayout->addWidget(teamName,0,1,1,1);

    about->setFixedSize(300,100);
    about->setWindowTitle("About us");
    about->setLayout(gLayout);
    about->show();
}
//打开视频文件
void MainWindow::openVideo()
{
    //选择视频文件
    videoPath = QFileDialog::getOpenFileName(this,QStringLiteral("选择视频文件"),".",tr("视频格式(*.avi *.mp4 *.flv)"));
    QFile file(videoPath);//视频文件
    if(!file.open(QIODevice::ReadOnly))//如果视频打开失败
    {
        QMessageBox::information(NULL, "Title", "Content", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(if_reload)
    {//重新加载视频时，重置以下变量
        delete layout_video;
        delete player;
        delete videoWidget;
        delete videoSlderTimer;
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
    //启用播放/暂停、行人识别、车辆识别按钮、视频摘要按钮、人车识别按钮，并将其文本设置为“暂停”
    ui->vehicleButton->setEnabled(true);
    ui->pedestrianButton->setEnabled(true);
    ui->playButton->setEnabled(true);
    ui->summaryButton->setEnabled(true);
    ui->flowButton->setEnabled(true);
    //设置播放器
    ui->labelVideoLength->setText(videoPath);
    ui->labelVideoLength->adjustSize();
    ui->labelVideoLength->setGeometry(QRect(328, 240, 329, 27*4));  //四倍行距
    ui->labelVideoLength->setWordWrap(true);
    ui->labelVideoLength->setAlignment(Qt::AlignTop);

    ui->horizontalSlider->setEnabled(true);
    ui->horizontalSlider->setRange(0,maxValue);
    videoSlderTimer = new QTimer();
    videoSlderTimer->setInterval(1000);
    videoSlderTimer->start();
    connect(videoSlderTimer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
    //播放器开启
    player->play();
    initDate("unnecessary date");
}
//点击播放按钮的行为
void MainWindow::on_playButton_clicked()
{
    //反转播放状态
    if(play_state)
    {
        player->pause();
        ui->playButton->setText(QStringLiteral("播放"));
    }
    else
    {
        player->play();
        ui->playButton->setText(QStringLiteral("暂停"));
    }

    play_state = !play_state;
}

void MainWindow::on_vehicleButton_clicked()//点击车辆识别按钮行为
{
    runCoreProcess(1);
}

void MainWindow::on_pedestrianButton_clicked()//点击行人识别按钮行为
{
    runCoreProcess(2);
}

void MainWindow::on_flowButton_clicked()//点击人车识别按钮行为
{
    runCoreProcess(3);
}

void MainWindow::on_summaryButton_clicked()
{
    QProcess videoSummary;
    videoSummary.start("summary.exe");
}

void MainWindow::setLine(QString line)
{
    QStringList temp = line.split(",");
    if(!temp.isEmpty()&&temp.size()!=1)
    {
        switch (this->kind)
        {
        case 1:
        {
            ui->labelCarNumber->setText(temp.at(1));
            ui->labelSpeed->setText(temp.at(3));
            break;
        }
        case 2:
        {
            ui->labelPeopleNumber->setText(temp.at(1));
            break;
        }
        default:
        {
            ui->labelCarNumber->setText(temp.at(1));
            ui->labelPeopleNumber->setText(temp.at(3));
        }
        }
    }
}

void MainWindow::initDate(QString initString)
{
    ui->labelCarNumber->setText(initString);
    ui->labelSpeed->setText(initString);
    ui->labelPeopleNumber->setText(initString);
}

void MainWindow::runCoreProcess(int kinds)
{
    initDate("unnecessary date");
    datethread = new DateThead();
    datethread->setVideoPath(videoPath);
    connect(datethread,SIGNAL(sendLine(QString)),this,SLOT(setLine(QString)));
    connect(this,SIGNAL(sendKind(int)),datethread,SLOT(chooseKind(int)));
    kind = kinds;
    emit sendKind(kinds);

    datethread->start();
}

void MainWindow::onTimerOut()
{
    ui->horizontalSlider->setValue(player->position()*maxValue/player->duration());
}

void MainWindow::horizontalSlider_clicked()
{
    player->setPosition(ui->horizontalSlider->value()*player->duration()/maxValue);
}

void MainWindow::horizontalSlider_moved()
{
    //暂时停止计时器，在用户拖动过程中不修改slider的值
    videoSlderTimer->stop();
    player->setPosition(ui->horizontalSlider->value()*player->duration()/maxValue);
}

void MainWindow::horizontalSlider_released()
{
    //用户释放滑块后，重启定时器
    videoSlderTimer->start();
}
