#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QKeyEvent>

#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void ConnectSlot();
    void SendSlot();
    void DisConnectSlot();

    void update_time();

    void on_pushButton_2_pressed();
    void on_pushButton_2_released();
    void on_pushButton_6_pressed();
    void on_pushButton_6_released();
    void on_pushButton_4_pressed();
    void on_pushButton_4_released();
    void on_pushButton_5_pressed();
    void on_pushButton_5_released();
    void on_pushButton_3_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_9_pressed();
    void on_pushButton_9_released();
    void on_pushButton_10_pressed();
    void on_pushButton_10_released();
    void on_pushButton_12_pressed();
    void on_pushButton_12_released();
    void on_pushButton_11_pressed();
    void on_pushButton_11_released();

    void on_pushButton_8_clicked();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    //socket对象
    QTcpSocket *client;

    QTime *time;
    QTimer *timer;
    bool IsConnect;

    bool lock_up;
    bool lock_down;
    bool lock_left;
    bool lock_right;
};
#endif // MAINWINDOW_H
