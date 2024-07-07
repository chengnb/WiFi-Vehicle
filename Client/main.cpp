#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_DisableWindowContextHelpButton); // 禁用上下文帮助按钮，禁止窗口焦点循环
    MainWindow w;
    w.show();
    return a.exec();
}
