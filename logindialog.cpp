// logindialog.cpp

// 1. 包含必要的头文件
#include "logindialog.h"   // 包含我们自己的LoginDialog类的声明
#include <QVBoxLayout>      // 包含【垂直布局】类
#include <QHBoxLayout>      // 包含【水平布局】类
#include <QGridLayout>      // 包含【栅格/网格布局】类
#include <QSpacerItem>      // 包含【空白项/弹簧】类
#include <QLabel>           // 包含【标签】类，用于显示静态文本和图片
#include <QLineEdit>        // 包含【单行输入框】类，用于接收用户输入
#include <QPushButton>      // 包含【按钮】类
#include <QMouseEvent>      // 包含【鼠标事件】类，用于处理鼠标点击、移动等

/*
 * 创建自定义输入框
 * “账号”和“密码”输入框的结构一样

 *   - const QString& iconPath:  图标的资源路径 (":/a/zhanghao.png")
 *   - const QString& text:      要显示的文字 (例如 "账号")
 *   - QLineEdit*& lineEdit:      一个【引用类型的指针】。这是一个高级技巧，意味着函数
 *                               内部创建的QLineEdit实例，会直接赋值给我们外部传入的
 *                               成员变量(如 usernameEdit)，非常高效。
 * 返回值:
 *   - QWidget*: 返回一个包含了所有零件的、可以直接使用的【组合控件】。
 */
QWidget* createInputWidget(const QString& iconPath, const QString& text, QLineEdit*& lineEdit)
{
    // --- 步骤 1: 创建最外层的“容器盒子” ---
    // 我们用一个 QWidget 作为“盘子”，来装下图标、文字、输入框等所有“菜”。
    QWidget* container = new QWidget();
    container->setObjectName("inputContainer"); // 【第1处修改】给它设置一个 objectName
    // 给这个“盘子”一个固定的尺寸，确保它看起来和设计稿一致。
    container->setFixedSize(336, 44);

    // --- 步骤 2: 创建内部的“零件” ---
    QLabel* iconLabel = new QLabel();

    // 从资源路径加载图片，并把它缩放到合适的大小(16x16)，同时保持长宽比。
    iconLabel->setPixmap(QPixmap(iconPath).scaled(13, 14, Qt::KeepAspectRatio));

    QLabel* textLabel = new QLabel(text); // 创建文字标签
    textLabel->setStyleSheet("color: #96E2E4; background: transparent; border: none;");

    // 创建一条垂直分隔线
    QFrame* separatorLine = new QFrame();
    separatorLine->setFrameShape(QFrame::VLine);    // 设置形状为垂直线
    separatorLine->setFrameShadow(QFrame::Sunken);  // 设置阴影效果（可选）
    separatorLine->setFixedWidth(2);                // 设置线条宽度为2像素

    // 【关键】创建真正的输入框，并把它赋值给我们从外部传入的指针。
    lineEdit = new QLineEdit();
    // 用样式表让输入框本身“隐形”，只留下打字功能。
    lineEdit->setStyleSheet("background: transparent; border: none; color: white;");

    // --- 步骤 3: 用【水平布局】把零件组装起来 ---
    // new QHBoxLayout(container) 的意思是：创建一个水平布局，并让'container'这个QWidget使用它。
    QHBoxLayout* layout = new QHBoxLayout(container);
    layout->setContentsMargins(10, 0, 10, 0); // 设置内边距 (左10, 上0, 右10, 下0)
    layout->setSpacing(6);                    // 设置零件之间的间距为6像素

    // 按顺序把零件从左到右放入布局中
    layout->addWidget(iconLabel);
    layout->addWidget(textLabel);
    layout->addWidget(separatorLine);
    layout->addWidget(lineEdit); // 【重要】输入框也要放入布局，否则看不见！

    // --- 步骤 4: 给外层容器设置整体外观 ---
    container->setStyleSheet(
        "#inputContainer { "
        "    background-color: rgba(0, 0, 0, 0.2); " // 半透明黑色背景
        "    border: 1px solid #5BCCF2; "             // 蓝色边框
        "    border-radius: 5px; "                    // 8像素的圆角
        "}"
        );

    // 函数结束，返回这个已经组装好的、可以直接使用的“组合控件”。
    return container;
}


/*
 * 构造函数
 * 创建所有子控件、设置它们的属性、搭建布局，完成窗口的初始化。
 */
LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent)
{
    // --- 窗口级别的基本设置 ---
    setWindowFlags(Qt::FramelessWindowHint); // 设置窗口为无边框模式
    // 用样式表设置整个对话框的背景色。这比paintEvent性能更好。
    this->setStyleSheet("QDialog { background-color: rgb(4, 39, 57); }");

    //this->resize(1920, 1080);

    // ======================== 阶段 1: 创建所有独立的控件 ========================

    // --- 创建顶部标题部分的所有 QLabel ---
    QLabel* emblemLabel = new QLabel();
    emblemLabel->setPixmap(QPixmap(":/a/emblem.png")); //国徽图片

    QLabel* titleLabel = new QLabel("刑侦现场还原系统");
    titleLabel->setStyleSheet("color: white; font-size: 28px; font-weight: bold; font-family: 'Microsoft YaHei';");

    QLabel* versionLabel = new QLabel("V2.0");
    versionLabel->setStyleSheet("color: white; font-size: 12px; font-family: 'Microsoft YaHei';");
    versionLabel->setAlignment(Qt::AlignBottom); // 垂直方向底部对齐

    QLabel* subtitleLabel = new QLabel("CRIME SCENE RECONSTRUCTION SYSTEM");
    subtitleLabel->setStyleSheet("color: #5BCCF2; font-size: 10px; font-family: 'Arial';");

    // --- 创建登录面板部分的控件 ---
    QLabel* loginTitleLabel = new QLabel("用户登录");
    loginTitleLabel->setStyleSheet("color: white; font-size: 18px; font-weight: bold;");

    // 【调用辅助函数】创建账号和密码输入框，同时初始化了成员变量 usernameEdit 和 passwordEdit
    QWidget* accountWidget = createInputWidget(":/a/ren.png", "账号", usernameEdit);
    QWidget* passwordWidget = createInputWidget(":/a/suo.png", "密码", passwordEdit);
    passwordEdit->setEchoMode(QLineEdit::Password); // 将密码框设置为密码模式 (显示为小黑点)

    // 创建登录按钮
    loginButton = new QPushButton("登录");
    loginButton->setFixedSize(336, 44);
    // 设置按钮的默认样式和鼠标悬浮(:hover)时的样式
    loginButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #1C7F82;"
        "    border-radius: 8px;"
        "    color: white;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {" //鼠标三态 普通 悬停 点击 （禁用）
        "    background-color: #2CB0B4;" // 鼠标悬浮时变亮
        "}"
        );

    // ======================== 阶段 2: 搭建局部布局 (像把积木拼成小模块) ========================

    // --- 搭建“标题部分”的布局 ---
    // 这是一个【水平布局】，从左到右依次是：弹簧-> 国徽 -> (一个垂直布局) -> 弹簧
    QHBoxLayout* titleLayout = new QHBoxLayout();
    titleLayout->addStretch();
    titleLayout->setSpacing(15);
    titleLayout->addWidget(emblemLabel);

    // 这是一个【垂直布局】，用来装主标题行和副标题行
    QVBoxLayout* titleTextLayout = new QVBoxLayout();
    titleTextLayout->setSpacing(2);
    // 这是一个【水平布局】，用来装 "刑侦现场还原系统" 和 "V2.0"
    QHBoxLayout* mainTitleLayout = new QHBoxLayout();
    mainTitleLayout->setSpacing(8);

    //mainTitleLayout->addStretch();
    mainTitleLayout->addWidget(titleLabel);
    mainTitleLayout->addWidget(versionLabel);
    mainTitleLayout->addStretch(); // 添加一个弹簧，会把前面的控件推到最左边

    titleTextLayout->addLayout(mainTitleLayout); // 把主标题行布局加入
    titleTextLayout->addWidget(subtitleLabel);   // 把副标题加入

    titleLayout->addLayout(titleTextLayout); // 把整个文字区布局加入
    titleLayout->addStretch(); // 添加一个弹簧，确保整个标题区靠左

    // --- 搭建“登录面板”的核心布局 ---
    // 这是一个【垂直布局】，从上到下依次是：登录标题 -> 账号框 -> 密码框 -> 登录按钮
    QVBoxLayout* loginVLayout = new QVBoxLayout();
    loginVLayout->setSpacing(20); // 设置它们之间的垂直间距
    loginVLayout->setAlignment(Qt::AlignCenter); // 让它内部的所有控件都尝试在水平方向居中
    loginVLayout->addWidget(loginTitleLabel, 0, Qt::AlignCenter); // 强制这个label居中
    loginVLayout->addWidget(accountWidget);
    loginVLayout->addWidget(passwordWidget);
    loginVLayout->addWidget(loginButton);


    // ======================== 阶段 3: 搭建主布局 (把所有小模块拼成最终模型) ========================

    // --- 使用“布局嵌套”和“弹簧”来实现完美的居中效果 ---

    // 创建一个“中央面板” QWidget，它像一个透明的画板，用来承载我们所有的内容。
    QWidget* centerPanel = new QWidget();
    // 在这个画板上应用一个垂直布局。
    QVBoxLayout* mainVLayout = new QVBoxLayout(centerPanel);

    mainVLayout->setAlignment(Qt::AlignCenter);

    // 在内容区的【上方】添加一个弹簧，伸展因子为2 (数字越大，占的空间比例越多)
    mainVLayout->addStretch(2);
    mainVLayout->addLayout(titleLayout); // 添加我们搭好的标题模块
    mainVLayout->addSpacing(60);         // 添加一个30像素的固定间距
    mainVLayout->addLayout(loginVLayout);  // 添加我们搭好的登录模块
    // 在内容区的【下方】添加一个弹簧，伸展因子为3，这样内容区会稍微偏上，符合视觉习惯
    mainVLayout->addStretch(3);

    // 【最终组合】
    // 在整个对话框(this)上，应用一个水平布局。
    QHBoxLayout* finalLayout = new QHBoxLayout(this);
    finalLayout->addStretch(); // 在【左边】添加一个弹簧
    finalLayout->addWidget(centerPanel); // 把我们精心制作的“中央面板”放进去
    finalLayout->addStretch(); // 在【右边】添加一个弹簧
    // 左右两个弹簧会平分水平方向的空白，从而把 `centerPanel` 挤到水平居中。
    // 而 `centerPanel` 内部的上下两个弹簧，会把它里面的内容挤到垂直居中（略微偏上）。


    // ======================== 阶段 4: 连接信号与槽 (让控件响应用户操作) ========================
    // 将登录按钮的 clicked() 信号，连接到我们自己的 onLoginClicked() 槽函数上。
    // 意思就是：“当按钮被点击时，请执行 onLoginClicked() 函数里的代码”。
    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
}


/*
 * LoginDialog 的【析构函数】(Destructor)
 * 当 LoginDialog 对象被销毁时 (例如对话框关闭后)，这个函数会被调用。
 * 我们在这里通常释放手动 new 出来的、且没有父对象的内存。
 * 但在这个例子中，所有 new 出来的 QWidget 和 QLayout 都有了父对象(this 或其他控件)，
 * Qt 的父子机制会自动管理它们的内存，所以这个函数可以是空的。
 */
LoginDialog::~LoginDialog() {}


/*
 * 这是一个【槽函数】(Slot)，专门用来响应 `loginButton` 的 `clicked` 信号。
 */
void LoginDialog::onLoginClicked()
{
    // accept() 是 QDialog 特有的函数，它会关闭对话框，并返回 QDialog::Accepted。
    // main.cpp 中可以通过检查这个返回值，来判断用户是成功登录了还是取消了。
    accept();
}


/*
 * 这是一个【事件处理器】(Event Handler)，用于处理鼠标按下事件。
 * 我们重写(override)了父类的这个函数，来实现无边框窗口的拖动。
 */
void LoginDialog::mousePressEvent(QMouseEvent *event)
{
    // 如果是鼠标左键按下了
    if (event->button() == Qt::LeftButton) {
        // 记录下当前鼠标相对于屏幕的全局坐标 和 窗口左上角的坐标 的差值。
        // 这个差值就是鼠标在窗口内部的相对位置。
        dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept(); // 表示这个事件我们已经处理了，不要再往上传递。
    }
}


/*
 * 这是一个【事件处理器】，用于处理鼠标移动事件。
 */
void LoginDialog::mouseMoveEvent(QMouseEvent *event)
{
    // 如果是按着鼠标左键在移动
    if (event->buttons() & Qt::LeftButton) {
        // 将窗口移动到新的位置：新的鼠标全局坐标 - 我们之前记录下的那个差值。
        move(event->globalPosition().toPoint() - dragPosition);
        event->accept();
    }
}
