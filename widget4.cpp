#include "widget4.h"
#include "ui_widget4.h"

Widget4::Widget4(QWidget *parent)
    : IWidget(parent)
    , ui(new Ui::Widget4)
{
    ui->setupUi(this);
    initVariables();
    initMiddle();
}

void Widget4::initVariables()
{
    // ====== 初始化软件描述 ======
    softwareName.append("1111111");
    softwareIcon.append(":/images/a3.jpg");
    softwareURL.append("D:/WeChat/WeChat.exe");

    softwareName.append("222222");
    softwareIcon.append(":/images/a3.jpg");
    softwareURL.append("D:/Tencent/QQNT/QQ.exe");


    softwareName.append("3333333");
    softwareIcon.append(":/images/a1.jpg");
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

    // ====== 初始化参数列表 ======
    currentIndex = 0;   // 当前第一个可见方框索引
    totalFrames = softwareName.size();    // 总方框数量
    visibleFrames = 4;  // 每次可见的方框数量
    frameWidth = 250;   // 每个方框的宽度
    frameHeight = 350;        // 每个系统描述框的高度
    scrollAreaWidth = (frameWidth+30)*4;   // 滚动区域宽度
    scrollAreaHeight = 500;   // 滚动区域高度
}

void Widget4::initMiddle()
{


    QVBoxLayout *mainLayout = new QVBoxLayout(ui->frame);
    mainLayout->setSpacing(10);

    // ========== 左侧按钮 ==========
    leftButton = new QPushButton(ui->frame);
    leftButton->setFixedSize(40, 60);
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
    frameLeftButton->setGeometry(15, 20, 10, 20);  // 设置矩形框的大小和位置
    frameLeftButton->setStyleSheet("border: 2px solid rgba(173, 216, 230, 150);");  // 设置蓝色边框
    frameLeftButton->show();
    connect(leftButton, &QPushButton::clicked, this, &Widget4::scrollLeft);



    // ========== 右侧按钮 ==========
    rightButton = new QPushButton(ui->frame);
    rightButton->setFixedSize(40, 60);
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
    frameRightButton->setGeometry(15, 20, 10, 20);  // 设置矩形框的大小和位置
    frameRightButton->setStyleSheet("border: 2px solid rgba(173, 216, 230, 150);");  // 设置蓝色边框
    frameRightButton->show();
    connect(rightButton, &QPushButton::clicked, this, &Widget4::scrollRight);

    // ========== 滚动区域 ==========
    scrollArea = new QScrollArea(ui->frame);
    scrollArea->setFixedSize(scrollAreaWidth, scrollAreaHeight);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setStyleSheet("QScrollArea { background: transparent; border: none; }");

    // ========== 滚动内容窗口 ==========
    scrollWidget = new QWidget();
    layout = new QHBoxLayout(scrollWidget);
    layout->setSpacing(35);

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
        QPixmap pixmap(renderer.defaultSize() * 3);
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
        openButton->setFixedSize(80, 30);
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
bool Widget4::eventFilter(QObject *watched, QEvent *event)
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
void Widget4::scrollLeft()
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
void Widget4::scrollRight()
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
void Widget4::smoothScrollTo(int targetPosition)
{
    QPropertyAnimation *animation = new QPropertyAnimation(scrollArea->horizontalScrollBar(), "value");
    animation->setDuration(400);
    animation->setStartValue(scrollArea->horizontalScrollBar()->value());
    animation->setEndValue(targetPosition);
    animation->setEasingCurve(QEasingCurve::InOutQuad);  // 设置缓动曲线，使动画效果更加平滑
    animation->start(QAbstractAnimation::DeleteWhenStopped);  // 启动动画，动画结束时自动删除
}

Widget4::~Widget4()
{
    delete ui;
}



