// logindialog.cpp
#include "logindialog.h"
#include <QLineEdit>
#include <QPushButton>
#include <QPainter> //
#include <QPixmap>
#include <QMouseEvent>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(1280, 720);

    usernameEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    loginButton = new QPushButton(this);


    // 定义样式表字符串，并加入 padding-left 属性
    QString lineEditStyle =
        "QLineEdit {"
        "    background: transparent;"   // 背景透明
        "    border: none;"             // 无边框
        "    color: #5BCCF2;"            // 字体颜色
        "    font-size: 16px;"          // 字体大小
        "    padding-left: 42px;"       // 左内边距，用于调整光标起始位置
        "}";

    // 将样式表应用到两个输入框
    usernameEdit->setStyleSheet(lineEditStyle);
    passwordEdit->setStyleSheet(lineEditStyle);


    // 微调这些坐标以匹配你的UI
    usernameEdit->setGeometry(540, 325, 200, 30);
    passwordEdit->setGeometry(540, 375, 200, 30);
    loginButton->setGeometry(510, 420, 260, 60);
    //loginButton->setFlat(true);
    loginButton->setStyleSheet("QPushButton { background: transparent; border: none; }");

    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
}

LoginDialog::~LoginDialog() {}


void LoginDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this); //

    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), QColor(4, 39, 57)); // 保持背景色


    // 绘制国徽
    painter.drawPixmap(475, 183, QPixmap(":/a/emblem.png"));


    // 分段绘制主标题

    // 绘制 "刑侦现场还原系统
    QString mainTitleText = "刑侦现场还原系统  "; // 末尾有空格
    QFont mainTitleFont("Microsoft YaHei", 24, QFont::Bold);
    painter.setFont(mainTitleFont);
    painter.setPen(QColor("#FFFFFF"));

    // 计算第一部分文字占据的矩形大小，这对于定位第二部分至关重要
    QFontMetrics fm(mainTitleFont);
    QRect mainTitleRect = fm.boundingRect(mainTitleText);

    // 定义第一部分的绘制起点
    QPoint mainTitleStartPoint(535, 212); // (x, y) - y坐标设置为垂直居中点
    painter.drawText(mainTitleStartPoint, mainTitleText);


    // 绘制 "V2.0"
    QString versionText = "V2.0";
    QFont versionFont("Microsoft YaHei", 14, QFont::Normal); // 字体更小，不加粗
    painter.setFont(versionFont);
    // 颜色可以保持白色，或者稍微变灰以作区分
    // painter.setPen(QColor("#DDDDDD"));

    // 计算第二部分的绘制起点
    // x = 第一部分的起点x + 第一部分的宽度
    // y = 和第一部分对齐，但需要根据字体大小做微调，让底部对齐
    QPoint versionStartPoint(mainTitleStartPoint.x() + mainTitleRect.width(),
                             mainTitleStartPoint.y());
    painter.drawText(versionStartPoint, versionText);


    // 绘制副标题 "CRIME SCENE RECONSTRUCTION SYSTEM"
    QFont subtitleFont("Arial", 10);
    painter.setFont(subtitleFont);
    painter.setPen(QColor("#5BCCF2"));
    QRectF subtitleRect(535, 210, 400, 30);
    painter.drawText(subtitleRect, Qt::AlignLeft | Qt::AlignVCenter, "CRIME SCENE RECONSTRUCTION SYSTEM");



    // 绘制其他UI元素
    painter.drawPixmap(440, 250, QPixmap(":/a/yonghudenlu.png"));
    painter.drawPixmap(505, 320, QPixmap(":/a/zhanghao.png"));
    painter.drawPixmap(505, 370, QPixmap(":/a/mima.png"));
    painter.drawPixmap(500, 420, QPixmap(":/a/denluanniu.png"));
}

void LoginDialog::onLoginClicked()
{
    accept();
    //if (usernameEdit->text() == "admin" && passwordEdit->text() == "123456") {
        //accept();
    //} else {
        //QMessageBox::warning(this, "登录失败", "账号或密码错误！");
    //}
}

void LoginDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void LoginDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}
