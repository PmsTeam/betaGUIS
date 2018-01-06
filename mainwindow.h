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

    //������Ƶ��ȫ�ֱ���
    QString videoPath;
    QVBoxLayout * layout_video;//����
    QMediaPlayer * player;   //������
    QVideoWidget * videoWidget;   //��Ƶ���ſؼ�

    //����״̬��trueΪ���ţ�falseΪ��ͣ
    bool play_state;
    //�Ƿ�����������Ƶ
    bool if_reload=false;
    //��Slider�йصĲ��ſ��Ʊ���
    QTimer * progressSlderTimer;
    int progressSlderMaxValue = 1000;//���ý����������ֵ

    QProcess coreProcess;//�����ⲿ����

    QDialog *about = new QDialog;//set about

    DateThead *thread;//set thread
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

private slots:
    void on_flowButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
