// titlebarbuttons.cpp
#include "titlebarbuttons.h"
#include <QPushButton>
#include <QHBoxLayout>

TitleBarButtons::TitleBarButtons(QWidget *parent) : QWidget(parent)
{
    // 使用Unicode字符作为按钮文本，比图片更轻量
    minimizeButton = new QPushButton("－", this);
    fullscreenButton = new QPushButton("🗖", this); // 也可以用 "☐"
    closeButton = new QPushButton("✕", this);

    // 使用样式表 (QSS) 来美化按钮
    QString buttonStyle = R"(
        QPushButton {
            background-color: transparent;
            color: #CCCCCC;
            border: none;
            font-size: 16px;
            font-weight: bold;
            width: 35px;
            height: 35px;
        }
        QPushButton:hover {
            background-color: rgba(255, 255, 255, 20); /* 半透明白色 */
            color: white;
        }
        QPushButton:pressed {
            background-color: rgba(0, 0, 0, 50); /* 半透明黑色 */
        }
    )";
    // 对关闭按钮的悬浮颜色做特殊处理
    QString closeButtonStyle = buttonStyle + "QPushButton:hover { background-color: #E81123; }";

    minimizeButton->setStyleSheet(buttonStyle);
    fullscreenButton->setStyleSheet(buttonStyle);
    closeButton->setStyleSheet(closeButtonStyle);

    // 使用水平布局来排列按钮
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0); // 无边距
    layout->setSpacing(0);                  // 无间距
    layout->addWidget(minimizeButton);
    layout->addWidget(fullscreenButton);
    layout->addWidget(closeButton);

    // 连接按钮的 clicked 信号到我们自己定义的信号上
    connect(minimizeButton, &QPushButton::clicked, this, &TitleBarButtons::minimizeClicked);
    connect(fullscreenButton, &QPushButton::clicked, this, &TitleBarButtons::fullscreenClicked);
    connect(closeButton, &QPushButton::clicked, this, &TitleBarButtons::closeClicked);
}
