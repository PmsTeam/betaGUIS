#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->playButton->setEnabled(false);//播放按钮先用不了
    ui->fullButton->setEnabled(false);//全屏按钮先用不了
    ui->vehicleButton->setEnabled(false);//车辆识别按钮先用不了
    ui->pedestrianButton->setEnabled(false);//行人识别按钮先用不了
    ui->summaryButton->setEnabled(false);//视频摘要按钮先用不了
    ui->flowButton->setEnabled(false);//人车识别按钮先用不了

    connect(ui->actionOpen,SIGNAL(triggered(bool)),this,SLOT(openVideo()));//打开视频按键的信号槽连接
    connect(ui->about,SIGNAL(triggered(bool)),this,SLOT(showAbout()));//关于按键的信号槽链接
}

MainWindow::~MainWindow()
{
    delete thread;
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
    videoPath = QFileDialog::getOpenFileName(this,tr("选择视频文件"),".",tr("视频格式(*.avi *.mp4 *.flv)"));
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
    //播放器开启
    player->play();
}
//点击播放按钮的行为
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
//点击车辆识别按钮行为
void MainWindow::on_vehicleButton_clicked()
{//初始化车数、人数、速率文本
    ui->labelCarNumber->setText("NONE");
    ui->labelSpeed->setText("NONE");
    ui->labelPeopleNumber->setText("NONE");

    QString program = "TOTEL-SE.exe";//打开外部程序
    QStringList argument;
    argument << "-c" << videoPath;

    coreProcess.start(program,argument);

    thread = new DateThead();
    connect(thread,SIGNAL(sendLine(QString)),this,SLOT(setLine(QString)));
    connect(this,SIGNAL(sendKind(int)),thread,SLOT(chooseKind(int)));
    kind = 1;
    emit sendKind(kind);
    thread->start();
}

void MainWindow::on_pedestrianButton_clicked()
{
    ui->labelCarNumber->setText("NONE");
    ui->labelSpeed->setText("NONE");
    ui->labelPeopleNumber->setText("NONE");

    QString program = "./TOTEL-SE.exe";
    QStringList argument;
    argument << "-p" << videoPath;

    coreProcess.start(program,argument);
    thread = new DateThead();
    connect(thread,SIGNAL(sendLine(QString)),this,SLOT(setLine(QString)));
    connect(this,SIGNAL(sendKind(int)),thread,SLOT(chooseKind(int)));
    kind =2;
    emit sendKind(kind);
    thread->start();
    ui->summaryButton->setEnabled(true);
}

void MainWindow::on_flowButton_clicked()
{
    ui->labelCarNumber->setText("NONE");
    ui->labelSpeed->setText("NONE");
    ui->labelPeopleNumber->setText("NONE");

    QString program = "./TOTEL-SE.exe";
    QStringList argument;
    argument << "-d" << videoPath;

    coreProcess.start(program,argument);

    thread = new DateThead();
    connect(thread,SIGNAL(sendLine(QString)),this,SLOT(setLine(QString)));
    connect(this,SIGNAL(sendKind(int)),thread,SLOT(chooseKind(int)));
    kind = 3;
    emit sendKind(kind);
    thread->start();
    ui->summaryButton->setEnabled(true);
}

void MainWindow::setLine(QString line)
{
    QStringList temp = line.split(",");
    switch (kind)
    {
        case 1:
        {
            if(!temp.isEmpty())
            {
                ui->labelCarNumber->setText(temp.at(1));
                ui->labelSpeed->setText(temp.at(3));
            }
            break;
        }
        case 2:
        {
            if(!temp.isEmpty())
                ui->labelPeopleNumber->setText(temp.at(1));
        }
        default:
        {
            if(!temp.isEmpty())
            {
                ui->labelCarNumber->setText(temp.at(1));
                ui->labelPeopleNumber->setText(temp.at(3));
            }
            break;
        }
    }
}
