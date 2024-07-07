#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client=new QTcpSocket(this);
    IsConnect = false;

    lock_up = false;
    lock_down = false;
    lock_left = false;
    lock_right = false;

    //接收消息
    //connect(client,&QTcpSocket::readyRead,this,&MainWindow::RecvSlot);
    //发送消息
    //connect(client,&QTcpSocket::bytesWritten,this,&MainWindow::SendSlot);
    //连接成功消息
    connect(client,&QTcpSocket::connected,this,&MainWindow::ConnectSlot);
    //连接断开消息
    connect(client,&QTcpSocket::disconnected,this,&MainWindow::DisConnectSlot);

    QString path = ":/new/prefix1/main.jpg";
    this->ui->label_3->setScaledContents(true);
    this->ui->label_3->setPixmap(QPixmap(path));

    this->time=new QTime(0,0,0,0);
    //初始化Timer对象
    this->timer=new QTimer(this);
    //设置定时器
    timer->start(1000);
    //用connect函数连接信号与槽
    connect(timer,&QTimer::timeout,this,&MainWindow::update_time);
}
void MainWindow::update_time(){
      this->ui->label_7->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if(event->isAutoRepeat())//防止自动一直触发
        return;
    if(!IsConnect){
        QMainWindow::keyPressEvent(event);
        return;
    }
    char a[5];  // 定义一个长度为5的数组，用于存储数据
    a[0] = (char)0xFF;
    a[1] = (char)0x00;
    a[2] = (char)0x00;
    a[3] = (char)0x00;
    a[4] = (char)0xFF;
    int key = event->key();
    switch (key) {
        case Qt::Key_W:
        case Qt::Key_Up:
            lock_up = true;
            a[2] = (char)0x01;
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            lock_down = true;
            a[2] = (char)0x02;
            break;
        case Qt::Key_A:
        case Qt::Key_Left:
            lock_left = true;
            a[2] = (char)0x03;
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            lock_right = true;
            a[2] = (char)0x04;
            break;
        default:
            QMainWindow::keyPressEvent(event);
            return;
    }
    if(lock_up && lock_left){
        a[2] = (char)0x05;
    }else if(lock_up && lock_right){
        a[2] = (char)0x07;
    }else if(lock_down && lock_left){
        a[2] = (char)0x06;
    }else if(lock_down && lock_right){
        a[2] = (char)0x08;
    }else if(lock_up && lock_left && lock_right){
        a[2] = (char)0x01;
    }else if(lock_up && lock_left && lock_down){
        a[2] = (char)0x03;
    }else if(lock_right && lock_left && lock_down){
        a[2] = (char)0x02;
    }else if(lock_right && lock_up && lock_down){
        a[2] = (char)0x04;
    }else if((lock_right && lock_up && lock_down && lock_left) || (lock_right && lock_left) || (lock_down && lock_up)){
        //应该没人会闲着无聊 4个键位都按
        a[2] = (char)0x00;
    }
    client->write(a,sizeof(a));
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if(event->isAutoRepeat())//防止自动一直触发
        return;
    if(!IsConnect){
        QMainWindow::keyReleaseEvent(event);
        return;
    }
    char a[5];
    a[0] = (char)0xFF;
    a[1] = (char)0x00;
    a[2] = (char)0x00;
    a[3] = (char)0x00;
    a[4] = (char)0xFF;
    int key = event->key();
    switch (key) {
        case Qt::Key_W:
        case Qt::Key_Up:
            lock_up = false;
            if(lock_down){
                a[2] = (char)0x02;
            }else if(lock_left){
                a[2] = (char)0x03;
            }else if(lock_right){
                a[2] = (char)0x04;
            }else if(lock_left && lock_down){
                a[2] = (char)0x06;
            }else if(lock_right && lock_down){
                a[2] = (char)0x08;
            }else if(lock_right && lock_left){
                a[2] = (char)0x00;
            }else if(lock_right && lock_down && lock_left){
                a[2] = (char)0x02;
            }
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            lock_down = false;
            if(lock_up){
                a[2] = (char)0x01;
            }else if(lock_left){
                a[2] = (char)0x03;
            }else if(lock_right){
                a[2] = (char)0x04;
            }else if(lock_left && lock_up){
                a[2] = (char)0x05;
            }else if(lock_right && lock_up){
                a[2] = (char)0x07;
            }else if(lock_right && lock_left){
                a[2] = (char)0x00;
            }else if(lock_right && lock_up && lock_left){
                a[2] = (char)0x01;
            }
            break;
        case Qt::Key_A:
        case Qt::Key_Left:
            lock_left = false;
            if(lock_down){
                a[2] = (char)0x02;
            }else if(lock_up){
                a[2] = (char)0x01;
            }else if(lock_right){
                a[2] = (char)0x04;
            }else if(lock_up && lock_right){
                a[2] = (char)0x07;
            }else if(lock_right && lock_down){
                a[2] = (char)0x08;
            }else if(lock_up && lock_down){
                a[2] = (char)0x00;
            }else if(lock_right && lock_down && lock_up){
                a[2] = (char)0x04;
            }
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            lock_right = false;
            if(lock_down){
                a[2] = (char)0x02;
            }else if(lock_left){
                a[2] = (char)0x03;
            }else if(lock_up){
                a[2] = (char)0x01;
            }else if(lock_left && lock_up){
                a[2] = (char)0x05;
            }else if(lock_left && lock_down){
                a[2] = (char)0x06;
            }else if(lock_up && lock_down){
                a[2] = (char)0x00;
            }else if(lock_up && lock_down && lock_left){
                a[2] = (char)0x03;
            }
            break;
        default:
            QMainWindow::keyReleaseEvent(event);
            return;
    }
    client->write(a,sizeof(a));
}

void MainWindow::on_pushButton_clicked()
{
    QString ip = this->ui->lineEdit->text();
    int port = this->ui->lineEdit_2->text().toInt();
    client->connectToHost(ip,port);
}


void MainWindow::ConnectSlot(){
    IsConnect = true;
    this->ui->label_5->setStyleSheet("background-color: green");
    this->ui->label_5->setText("已连接");
    QMessageBox::information(this,"提示","连接成功！");
}
void MainWindow::SendSlot(){
    QMessageBox::information(this,"提示","发送成功！");
}
void MainWindow::DisConnectSlot(){
    IsConnect = false;
    this->ui->label_5->setStyleSheet("background-color: red");
    this->ui->label_5->setText("已断开");
    QMessageBox::information(this,"提示","连接已经断开！");  //
}

void MainWindow::on_pushButton_2_pressed()
{
    char a[]={(char)0xFF,(char)0x00,(char)0x01,(char)0x00,(char)0xFF};
    client->write(a,sizeof(a));
}
void MainWindow::on_pushButton_2_released()
{
    char a[]={(char)0xFF,(char)0x00,(char)0x00,(char)0x00,(char)0xFF};
    client->write(a,sizeof(a));
}
void MainWindow::on_pushButton_6_pressed()
{
    char a[]={(char)0xFF,(char)0x00,(char)0x03,(char)0x00,(char)0xFF};
    client->write(a,sizeof(a));
}
void MainWindow::on_pushButton_6_released()
{
    char a[]={(char)0xFF,(char)0x00,(char)0x00,(char)0x00,(char)0xFF};
    client->write(a,sizeof(a));
}

void MainWindow::on_pushButton_4_pressed()
{
    char a[]={(char)0xFF,(char)0x00,(char)0x04,(char)0x00,(char)0xFF};
    client->write(a,sizeof(a));
}
void MainWindow::on_pushButton_4_released()
{
    char a[]={(char)0xFF,(char)0x00,(char)0x00,(char)0x00,(char)0xFF};
    client->write(a,sizeof(a));
}
void MainWindow::on_pushButton_5_pressed()
{
    char a[]={(char)0xFF,(char)0x00,(char)0x02,(char)0x00,(char)0xFF};
    client->write(a,sizeof(a));
}
void MainWindow::on_pushButton_5_released()
{
    char a[]={(char)0xFF,(char)0x00,(char)0x00,(char)0x00,(char)0xFF};
    client->write(a,sizeof(a));
}
void MainWindow::on_pushButton_9_pressed()
{
    char a[]={(char)0xFF,(char)0x00,(char)0x05,(char)0x00,(char)0xFF};
    client->write(a,sizeof(a));
}
void MainWindow::on_pushButton_9_released()
{
    char a[]={(char)0xFF,(char)0x00,(char)0x00,(char)0x00,(char)0xFF};
    client->write(a,sizeof(a));
}
void MainWindow::on_pushButton_10_pressed()
{
    char a[]={(char)0xFF,(char)0x00,(char)0x07,(char)0x00,(char)0xFF};
    client->write(a,sizeof(a));
}
void MainWindow::on_pushButton_10_released()
{
    char a[]={(char)0xFF,(char)0x00,(char)0x00,(char)0x00,(char)0xFF};
    client->write(a,sizeof(a));
}
void MainWindow::on_pushButton_12_pressed()
{
    char a[]={(char)0xFF,(char)0x00,(char)0x06,(char)0x00,(char)0xFF};
    client->write(a,sizeof(a));
}
void MainWindow::on_pushButton_12_released()
{
    char a[]={(char)0xFF,(char)0x00,(char)0x00,(char)0x00,(char)0xFF};
    client->write(a,sizeof(a));
}
void MainWindow::on_pushButton_11_pressed()
{
    char a[]={(char)0xFF,(char)0x00,(char)0x08,(char)0x00,(char)0xFF};
    client->write(a,sizeof(a));
}
void MainWindow::on_pushButton_11_released()
{
    char a[]={(char)0xFF,(char)0x00,(char)0x00,(char)0x00,(char)0xFF};
    client->write(a,sizeof(a));
}

void MainWindow::on_pushButton_3_clicked()
{
    if(!IsConnect){
        QMessageBox::information(this,"提示","未连接！");
        return;
    }
    char a[]={(char)0xFF,(char)0x00,(char)0x00,(char)0x00,(char)0xFF};
    client->write(a,sizeof(a));
    client->close();
}

void MainWindow::on_pushButton_7_clicked()
{
    char a[]={(char)0xFF,(char)0x00,(char)0x00,(char)0x00,(char)0xFF};
    client->write(a,sizeof(a));
}

void MainWindow::on_pushButton_8_clicked()
{
    if(!IsConnect){
        QMessageBox::information(this,"提示","未连接！");
        return;
    }
    QString str = this->ui->plainTextEdit->toPlainText();
    QByteArray arr;
    arr.append(str);
    client->write(arr);
    arr.clear();
    ui->plainTextEdit->clear();
}

