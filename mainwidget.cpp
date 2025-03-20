#include "mainwidget.h"
#include "ui_mainwidget.h"

#if defined(_MSC_VER)&&(_MSC_VER >= 1600)
#pragma execution_character_set("utf-8")
#endif

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();  // 获取可用屏幕尺寸


    // 设置主窗口的大小为屏幕的 95%
    int width = screenGeometry.width() * 0.99;
    int height = screenGeometry.height() * 0.99;
    this->resize(width, height);

    // 设置各个控件的位置和大小（按比例调整）
    ui->bottomWidget->setGeometry(0, height * 0.75, width, height * 0.1);
    //ui->leftWidget->setGeometry(0, height * 0.1, width * 0.02, height * 0.65);
    ui->showWidget->setGeometry(0, height * 0.1, width * 0.98, height * 0.8);
    ui->topWidget->setGeometry(0, 0, width, height * 0.1);

    setWindowTitle("天控首页");

    //初始化参数列表
    initVariables();

    // 初始化界面 上
    initTop();

    // 初始化界面 中
    initMiddle();

    // 初始化界面 下
    //initBottom();

}

void MainWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // 设置背景
    QPalette palette;
    QPixmap background(":/images/u0_state0.jpg");

    QPixmap scaledBackground = background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    palette.setBrush(QPalette::Window, QBrush(scaledBackground));
    setPalette(palette);
    u2ImageLabel = new QLabel(this);
    if (u2ImageLabel) {
        QPixmap u2Image(":/images/u2.png");
        QPixmap scaledU2Image = u2Image.scaled(width(), height() / 8, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        int x = (width() - scaledU2Image.width()) / 2;
        int y = 0;
        u2ImageLabel->setPixmap(scaledU2Image);
        u2ImageLabel->setGeometry(x, y, scaledU2Image.width(), scaledU2Image.height());
    }

}


void MainWidget::initVariables()
{
    // ====== 底部功能按钮 ======
    bottomFunctionButton.append("系统通知");
    bottomFunctionButton.append("数据设置");
    bottomFunctionButton.append("系统设置");
    bottomFunctionButton.append("锁定状态");
    bottomFunctionButton.append("退出登录");

    // ====== 左侧按钮 ======
    changePushButton.append(new QPushButton(QString::fromUtf8("界面1")));
    changeButtonIcon.append(":/images/a3.jpg");

    changePushButton.append(new QPushButton(QString::fromUtf8("界面2")));
    changeButtonIcon.append(":/images/a3.jpg");

    changePushButton.append(new QPushButton(QString::fromUtf8("界面3")));
    changeButtonIcon.append(":/images/a3.jpg");

    changePushButton.append(new QPushButton(QString::fromUtf8("界面4")));
    changeButtonIcon.append(":/images/a3.jpg");


}
void MainWidget::initMiddle()
{
    // ====== 初始化界面 =======
    stackedWidget = new QStackedWidget(ui->showWidget);

    // 界面初始化
    startSoftwareWidget = new StartSoftwareWidget();
    widget4 = new Widget4();

    // 界面入栈
    stackedWidget->addWidget(startSoftwareWidget);
    stackedWidget->addWidget(widget4);

    // 多态：存储子类界面的容器
    changeWidget.append(startSoftwareWidget);
    changeWidget.append(widget4);

    // 设置当前界面
    stackedWidget->setCurrentWidget(startSoftwareWidget);

    // ====== 添加按钮 =======
    // 创建按钮
    QPushButton *button1 = new QPushButton(QString::fromUtf8("界面 1"), ui->showWidget);
    QPushButton *button2 = new QPushButton(QString::fromUtf8("界面 1"), ui->showWidget);

    // 设置按钮样式
    button1->setFixedSize(120, 40);
    button2->setFixedSize(120, 40);

    button1->setStyleSheet("QPushButton {"
                           "background-color: #4CAF50;"
                           "color: white;"
                           "border: none;"
                           "border-radius: 5px;"
                           "font-size: 16px;"
                           "}"
                           "QPushButton:hover {"
                           "background-color: #45a049;"
                           "}"
                           "QPushButton:pressed {"
                           "background-color: #3e8e41;"
                           "}");

    button2->setStyleSheet("QPushButton {"
                           "background-color: #2196F3;"
                           "color: white;"
                           "border: none;"
                           "border-radius: 5px;"
                           "font-size: 16px;"
                           "}"
                           "QPushButton:hover {"
                           "background-color: #0b7dda;"
                           "}"
                           "QPushButton:pressed {"
                           "background-color: #0a6bb8;"
                           "}");

    // 创建按钮布局
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->addWidget(button1);
    buttonLayout->addWidget(button2);
    buttonLayout->addStretch();  // **添加一个拉伸项，让按钮靠上排列**
    buttonLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);  // **让按钮始终靠上和靠左**

    QWidget *buttonWidget = new QWidget();  // **创建一个容器用于放置按钮**
    buttonWidget->setLayout(buttonLayout);
    buttonWidget->setFixedWidth(140);  // **设置左侧按钮区域的固定宽度**
    buttonWidget->setStyleSheet("background-color: #2C3E50;");  // **设置背景色**

    QHBoxLayout *mainLayout = new QHBoxLayout(ui->showWidget);  // **创建水平布局**
    mainLayout->addWidget(buttonWidget);  // **左侧按钮**
    mainLayout->addWidget(stackedWidget, 1);  // **右侧界面，占满剩余空间**

    ui->showWidget->setLayout(mainLayout);

    // 设置按钮点击事件，切换界面
    connect(button1, &QPushButton::clicked, this, [=]() {
        stackedWidget->setCurrentWidget(startSoftwareWidget);  // 切换到界面 1
    });

    connect(button2, &QPushButton::clicked, this, [=]() {
        stackedWidget->setCurrentWidget(widget4);  // 切换到界面 2
    });


}
void MainWidget::initTop()
{
    /*
    // ========== 加载动态图，暂未成功 ==========
    QLabel *label = new QLabel(this);
    QMovie *movie = new QMovie(":/images/u4.gif");
    label->setMovie(movie);
    movie->start();
    label->show();
*/
    QHBoxLayout  *layout = new QHBoxLayout (ui->topWidget);
    layout->setAlignment(Qt::AlignCenter);  // 设置子控件居中
    layout->addWidget(ui->titleFrame);

    ui->titleFrame->setStyleSheet("background: transparent;");
    ui->titleFrame->setContentsMargins(0, 0, 0, 0);  // 调整边距

    // ========== 显示文本 ==========
    ui->titlelabel_1->setFont(QFont("Arial", 20, QFont::Bold));
    ui->titlelabel_1->setStyleSheet("color: white;");
    ui->titlelabel_1->setAlignment(Qt::AlignCenter);

    ui->titlelabel_2->setFont(QFont("Arial", 10, QFont::Bold));
    ui->titlelabel_2->setStyleSheet("color: white;");
    ui->titlelabel_2->setAlignment(Qt::AlignCenter);

}

void MainWidget::initBottom()
{

    QPushButton *buttons[5];
    QLabel *labels[5];

    QHBoxLayout *mainLayout = new QHBoxLayout(ui->functionFrame_2);
    mainLayout->setSpacing(10);
    for (int i = 0; i < 5; ++i) {
        buttons[i] = new QPushButton(ui->functionFrame_2);
        buttons[i]->setFixedSize(60, 60);
        buttons[i]->setStyleSheet(R"(
            QPushButton {
                border: none;
                background: transparent;
                color: white;
                image: url(:/images/u51.jpg);
                text-align: center;
            }
            QPushButton:hover {
                image: url(:/images/u51_mouseOver.jpg);
            }
        )");
        QFrame *frameRightButton = new QFrame(buttons[i]);
        frameRightButton->setGeometry(25, 22, 10, 15);
        frameRightButton->setStyleSheet("border: 2px solid rgba(255, 255, 255, 1);");
        frameRightButton->show();

        labels[i] = new QLabel(bottomFunctionButton[i], ui->functionFrame_2);
        labels[i]->setAlignment(Qt::AlignCenter);
        labels[i]->setStyleSheet("color: white; font-size: 12px;");

        QVBoxLayout *buttonLayout = new QVBoxLayout();
        buttonLayout->addWidget(buttons[i]);
        buttonLayout->addWidget(labels[i]);
        buttonLayout->setAlignment(Qt::AlignCenter);

        mainLayout->addLayout(buttonLayout);

        // 响应点击事件
        connect(buttons[i], &QPushButton::clicked, this, [=]() {

        });
    }

    // 设置布局
    ui->functionFrame_2->setLayout(mainLayout);

}

/*
void MainWidget::initVariables_1()
{
    currentIndex = 0;   // 当前第一个可见方框索引
    totalFrames = 9;    // 总方框数量
    visibleFrames = 4;  // 每次可见的方框数量
    frameWidth = 250;   // 每个方框的宽度

    softwareName.clear();
    softwareIcon.clear();
    softwareIcon.clear();
    // ====== 初始化软件描述 ======
    softwareName.append("软件1");
    softwareIcon.append(":/images/a1.jpg");
    softwareURL.append("D:/WeChat/WeChat.exe");

    softwareName.append("管理系统");
    softwareIcon.append(":/images/a2.jpg");
    softwareURL.append("D:/Tencent/QQNT/QQ.exe");

    softwareName.append("监控系统");
    softwareIcon.append(":/images/a3.jpg");
    softwareURL.append(":/images/u0_state0.jpg");

    softwareName.append("aaa");
    softwareIcon.append(":/images/a3.jpg");
    softwareURL.append(":/images/u0_state0.jpg");

    softwareName.append("管理系统");
    softwareIcon.append(":/images/a1.jpg");
    softwareURL.append(":/images/u0_state0.jpg");

    softwareName.append("监控系统");
    softwareIcon.append(":/images/a1.jpg");
    softwareURL.append(":/images/u0_state0.jpg");

    softwareName.append("软件1");
    softwareURL.append(":/images/u0_state0.jpg");
    softwareIcon.append(":/images/a1.jpg");

    softwareName.append("管理系统");
    softwareIcon.append(":/images/a1.jpg");
    softwareURL.append(":/images/u0_state0.jpg");

    softwareName.append("监控系统");
    softwareIcon.append(":/images/a1.jpg");
    softwareURL.append(":/images/u0_state0.jpg");

}

void MainWidget::initMiddle()
{

    // ========== 统一定义大小变量 ==========
    const int buttonWidth = 40;         // 左右按钮宽度
    const int buttonHeight = 60;        // 左右按钮高度
    //const int frameWidth = 250;         // 每个系统描述框的宽度
    int frameHeight = 350;        // 每个系统描述框的高度
    int scrollAreaWidth = (frameWidth+30)*4;   // 滚动区域宽度
    int scrollAreaHeight = 500;   // 滚动区域高度

    const int borderWidth = 10;         // 小边框宽度
    const int borderHeight = 20;        // 小边框高度
    const int iconTop = 50;             // 图标距离顶部的距离
    const int nameLabel1Top = 150;      // 第一行名称的Y坐标
    const int nameLabel2Top = 170;      // 第二行名称的Y坐标
    const int buttonTop = 210;          // 进入系统按钮的Y坐标
    const int buttonInsideWidth = 80;   // 进入系统按钮的宽度
    const int buttonInsideHeight = 30;  // 进入系统按钮的高度
    const int frameSpacing = 35;        // 每个框之间的间距
    const int scrollStep = 4;           // 每次滚动的步长

    QVBoxLayout *mainLayout = new QVBoxLayout(ui->frame);
    mainLayout->setSpacing(10);

    // ========== 左侧按钮 ==========
    leftButton = new QPushButton(ui->frame);
    leftButton->setFixedSize(buttonWidth, buttonHeight);
    leftButton->setStyleSheet(R"(
        QPushButton {
            border: none;
            background: transparent;
            image: url(:/images/u8.jpg);
        }
        QPushButton:hover {
            image: url(:/images/u8_mouseOver.jpg);
        }
    )");
    QFrame *frameLeftButton = new QFrame(leftButton);
    frameLeftButton->setGeometry(15, 20, borderWidth, borderHeight);
    frameLeftButton->setStyleSheet("border: 2px solid rgba(173, 216, 230, 150);");
    frameLeftButton->show();
    connect(leftButton, &QPushButton::clicked, this, &MainWidget::scrollLeft);

    // ========== 右侧按钮 ==========
    rightButton = new QPushButton(ui->frame);
    rightButton->setFixedSize(buttonWidth, buttonHeight);
    rightButton->setStyleSheet(R"(
        QPushButton {
            border: none;
            background: transparent;
            image: url(:/images/u8.jpg);
        }
        QPushButton:hover {
            image: url(:/images/u8_mouseOver.jpg);
        }
    )");
    QFrame *frameRightButton = new QFrame(rightButton);
    frameRightButton->setGeometry(15, 20, borderWidth, borderHeight);
    frameRightButton->setStyleSheet("border: 2px solid rgba(173, 216, 230, 150);");
    frameRightButton->show();
    connect(rightButton, &QPushButton::clicked, this, &MainWidget::scrollRight);

    // ========== 滚动区域 ==========
    scrollArea = new QScrollArea(ui->frame);
    scrollArea->setFixedSize(scrollAreaWidth, scrollAreaHeight);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setStyleSheet("QScrollArea { background: transparent; border: none; }");

    // ========== 滚动内容窗口 ==========
    scrollWidget = new QWidget();
    layout = new QHBoxLayout(scrollWidget);
    layout->setSpacing(frameSpacing);

    // ========== 添加 totalFrames 个系统描述框 ==========
    for (int i = 0; i < totalFrames; ++i) {
        QFrame *frame = new QFrame(scrollWidget);
        frame->setFixedSize(frameWidth, frameHeight);
        frame->setStyleSheet("border: none;");

        // ========== 背景图片 ==========
        QLabel *backgroundLabel = new QLabel(frame);
        backgroundLabel->setGeometry(0, 0, frameWidth, frameHeight);
        QPixmap backgroundPixmap(":/images/u8.jpg");
        backgroundLabel->setPixmap(backgroundPixmap.scaled(frameWidth, frameHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        backgroundLabel->setStyleSheet("background: transparent;");
        backgroundLabel->lower();
        backgroundLabel->show();

        // ========== 创建垂直布局 ==========
        QVBoxLayout *vLayout = new QVBoxLayout(frame);
        vLayout->setAlignment(Qt::AlignCenter);  // **让所有控件整体居中**
        vLayout->setSpacing(10);  // 控件之间的间距

        // ========== 系统图标 ==========
        QLabel *iconLabel = new QLabel(frame);
        QString imagePath = softwareIcon[i];

        QSvgRenderer renderer(imagePath);
        QPixmap pixmap(renderer.defaultSize() * 2.7);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        renderer.render(&painter);
        iconLabel->setPixmap(pixmap);
        iconLabel->setFixedSize(pixmap.size());
        iconLabel->setAlignment(Qt::AlignCenter);

        vLayout->addWidget(iconLabel, 0, Qt::AlignCenter);  // **让图标水平居中**

        // ========== 名称标签 ==========
        QLabel *nameLabel = new QLabel(softwareName[i], frame);
        nameLabel->setAlignment(Qt::AlignCenter);
        nameLabel->setFont(QFont("Arial", 15, QFont::Bold));
        nameLabel->setStyleSheet("color: white; background: transparent; border: none;");

        QLabel *nameLabel2 = new QLabel(softwareName[i], frame);
        nameLabel2->setAlignment(Qt::AlignCenter);
        nameLabel2->setFont(QFont("Arial", 10, QFont::Bold));
        nameLabel2->setStyleSheet("color: white; background: transparent; border: none;");

        vLayout->addWidget(nameLabel, 0, Qt::AlignCenter);  // **让名称居中**
        vLayout->addWidget(nameLabel2, 0, Qt::AlignCenter);  // **让副名称居中**

        // ========== 进入系统按钮 ==========
        QPushButton *openButton = new QPushButton("进入系统", frame);
        openButton->setFixedSize(buttonInsideWidth, buttonInsideHeight);
        openButton->setStyleSheet(
            "QPushButton {"
            "   color: white;"
            "   background: transparent;"
            "   border: 2px solid white;"
            "   border-radius: 10px;"
            "   padding: 5px 10px;"
            "}"
            "QPushButton:hover {"
            "   background-color: rgba(255, 255, 255, 0.2);"
            "}"
            "QPushButton:pressed {"
            "   background-color: rgba(255, 255, 255, 0.3);"
            "   padding-left: 8px; padding-top: 8px;"
            "}"
            );
        connect(openButton, &QPushButton::clicked, this, [=]() {
            QProcess::startDetached(softwareURL[i]);
        });

        vLayout->addWidget(openButton, 0, Qt::AlignCenter);  // **让按钮居中**

        frame->setLayout(vLayout);  // **给 frame 设置布局**
        frame->installEventFilter(this);

        layout->addWidget(frame);  // 添加到 `QHBoxLayout` 中
    }



    scrollWidget->setLayout(layout);
    scrollArea->setWidget(scrollWidget);
    scrollWidget->setStyleSheet("background: transparent;");
    scrollArea->setWidgetResizable(true);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(leftButton);
    hLayout->addWidget(scrollArea);
    hLayout->addWidget(rightButton);
    mainLayout->addLayout(hLayout);

    setLayout(mainLayout);
}

// ========== 捕获系统描述框 ==========
bool MainWidget::eventFilter(QObject *watched, QEvent *event)
{

    if (event->type() == QEvent::Enter) {
        QFrame *frame = qobject_cast<QFrame *>(watched);
        if (frame) {
            QLabel *backgroundLabel = frame->findChild<QLabel *>();
            if (backgroundLabel) {
                QPixmap mouseOverPixmap(":/images/u8_mouseOver.jpg");
                backgroundLabel->setPixmap(mouseOverPixmap.scaled(backgroundLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }
        }
    } else if (event->type() == QEvent::Leave) {
        QFrame *frame = qobject_cast<QFrame *>(watched);
        if (frame) {
            QLabel *backgroundLabel = frame->findChild<QLabel *>();
            if (backgroundLabel) {
                QPixmap originalPixmap(":/images/u8.jpg");
                backgroundLabel->setPixmap(originalPixmap.scaled(backgroundLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }
        }
    }

    return QWidget::eventFilter(watched, event);
}


// ========== 向左滚动 ==========
void MainWidget::scrollLeft()
{
    int remainingFrames = currentIndex;
    if (remainingFrames >= 4) {
        currentIndex -= 4;
    } else {
        currentIndex = 0;
    }
    int targetPosition = currentIndex * (frameWidth + 35);
    smoothScrollTo(targetPosition);
}

// ========== 向右滚动 ==========
void MainWidget::scrollRight()
{
    int remainingFrames = totalFrames - visibleFrames - currentIndex;
    if (remainingFrames >= 4) {
        currentIndex += 4;
    } else {
        currentIndex = totalFrames - visibleFrames;
    }
    int targetPosition = currentIndex * (frameWidth + 35);
    smoothScrollTo(targetPosition);
}

// ========== 创建动画 ==========
void MainWidget::smoothScrollTo(int targetPosition)
{
    QPropertyAnimation *animation = new QPropertyAnimation(scrollArea->horizontalScrollBar(), "value");
    animation->setDuration(400);
    animation->setStartValue(scrollArea->horizontalScrollBar()->value());
    animation->setEndValue(targetPosition);
    animation->setEasingCurve(QEasingCurve::InOutQuad);  // 设置缓动曲线，使动画效果更加平滑
    animation->start(QAbstractAnimation::DeleteWhenStopped);  // 启动动画，动画结束时自动删除
}

/*
void MainWidget::initLeft()
{
    QFrame *buttonFrame = new QFrame(ui->leftWidget);
    buttonFrame->setStyleSheet("background: transparent;");
    buttonFrame->setFrameShape(QFrame::NoFrame);

    QVBoxLayout *layout = new QVBoxLayout(buttonFrame);
    layout->setSpacing(10);
    layout->setContentsMargins(0, 0, 0, 0);

    for (int i = 0; i < changePushButton.size(); ++i) {
        changePushButton[i]->setFixedSize(100, 50);  // 设置按钮大小
        changePushButton[i]->setStyleSheet(R"(
            QPushButton {
                border: none;
                background: transparent;
                image: url(:/images/u51.jpg);
            }
            QPushButton:hover {
                image: url(:/images/u51_mouseOver.jpg);
            }
            )");
        layout->addWidget(changePushButton[i]);

        connect(changePushButton[i], &QPushButton::clicked, this, [=]() {
            stackedWidget->setCurrentWidget(changeWidget[i]);
        });
    }

    // 3. 设置布局
    ui->leftWidget->setLayout(layout);

}

*/

MainWidget::~MainWidget()
{
    delete ui;
}

