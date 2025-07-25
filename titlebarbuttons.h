// titlebarbuttons.h
#ifndef TITLEBARBUTTONS_H
#define TITLEBARBUTTONS_H

#include <QWidget>

class QPushButton;

class TitleBarButtons : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBarButtons(QWidget *parent = nullptr);

signals:
    // 定义三个信号，当按钮被点击时，发射这些信号通知父窗口
    void minimizeClicked();
    void fullscreenClicked();
    void closeClicked();

private:
    QPushButton *minimizeButton;
    QPushButton *fullscreenButton;
    QPushButton *closeButton;
};
#endif // TITLEBARBUTTONS_H
