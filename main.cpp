// main.cpp
#include "mainwindow.h"
#include "logindialog.h" // 包含登录对话框的头文件
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Generated code
        LoginDialog loginDialog;
    //loginDialog.showFullScreen();

    // 如果登录成功
    if (loginDialog.exec() == QDialog::Accepted) {
        // 就显示主窗口
        MainWindow w;
        w.showFullScreen();
        return a.exec();
    } else {
        // 否则程序直接退出
        return 0;
    }
    //Use code with caution.
}
