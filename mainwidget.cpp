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

    setWindowTitle("天智首页");

    //初始化参数列表
    initMiddleVariables();

    // 初始化界面 上
    initTop();

    // 初始化界面 中
    initMiddle();


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
    ui->titlelabel_1->setFont(QFont("SimHei", 20, QFont::Black));
    ui->titlelabel_1->setStyleSheet("color: white;");
    ui->titlelabel_1->setAlignment(Qt::AlignCenter);

    ui->titlelabel_2->setFont(QFont("Arial", 10, QFont::Bold));
    ui->titlelabel_2->setStyleSheet("color: white;");
    ui->titlelabel_2->setAlignment(Qt::AlignCenter);

}

void MainWidget::initMiddleVariables()
{

    // ====== 初始化 Show 软件描述 ======
    softwareShowName.append(QString::fromUtf8("天智红方态势展示\n"));
    softwareShowIcon.append(":/images/a1.jpg");
    softwareShowURL.append("D:/WeChat/WeChat.exe");

    softwareShowName.append(QString::fromUtf8("天智蓝方态势展示\n"));
    softwareShowIcon.append(":/images/a2.jpg");
    softwareShowURL.append("D:/WeChat/WeChat.exe");

    softwareShowName.append(QString::fromUtf8("M太空军态势系统\n"));
    softwareShowIcon.append(":/images/a3.jpg");
    softwareShowURL.append("D:/WeChat/WeChat.exe");


    // ====== 初始化 Tool 软件描述 ======
    softwareToolName.append(QString::fromUtf8("天智航天\n想定编辑工具"));
    softwareToolIcon.append(":/images/a1.jpg");
    softwareToolURL.append("D:/WeChat/WeChat.exe");

    softwareToolName.append(QString::fromUtf8("天智航天\n体系推演平台"));
    softwareToolIcon.append(":/images/a2.jpg");
    softwareToolURL.append("D:/WeChat/WeChat.exe");

    softwareToolName.append(QString::fromUtf8("天智仿真导演台\n"));
    softwareToolIcon.append(":/images/a3.jpg");
    softwareToolURL.append("D:/WeChat/WeChat.exe");

    softwareToolName.append(QString::fromUtf8("天智交战裁决工具\n"));
    softwareToolIcon.append(":/images/a4.jpg");
    softwareToolURL.append("D:/WeChat/WeChat.exe");

    softwareToolName.append(QString::fromUtf8("天智航天\n体系分析评估工具"));
    softwareToolIcon.append(":/images/a1.jpg");
    softwareToolURL.append("D:/WeChat/WeChat.exe");



    // ====== 初始化 Base 软件描述 ======
    softwareBaseName.append(QString::fromUtf8("天智可视化通信\n交互工具"));
    softwareBaseIcon.append(":/images/a1.jpg");
    softwareBaseURL.append("D:/WeChat/WeChat.exe");

    softwareBaseName.append(QString::fromUtf8("天智模型管理工具\n"));
    softwareBaseIcon.append(":/images/a2.jpg");
    softwareBaseURL.append("D:/WeChat/WeChat.exe");

    softwareBaseName.append(QString::fromUtf8("天智模型封装开发工具\n"));
    softwareBaseIcon.append(":/images/a3.jpg");
    softwareBaseURL.append("D:/WeChat/WeChat.exe");


    // ====== 初始化参数列表 ======
    scrollAreaWidth = 1100;
    scrollAreaHeight = 500;

    // 计算 Show 容器的框宽度和间距
    int showCount = softwareShowName.size();
    int showFrameWidth = 250;
    int showSpacing = 170;
    //int showSpacing = (scrollAreaWidth - (showCount * showFrameWidth)) / (showCount-1);

    // 计算 Tool 容器的框宽度和间距
    int toolCount = softwareToolName.size();
    int toolFrameWidth = 200;
    int toolSpacing = 25;
    //int toolSpacing = (scrollAreaWidth - (toolCount * toolFrameWidth)) / (toolCount-1) ;


    // 计算 Base 容器的框宽度和间距
    int baseCount = softwareBaseName.size();
    int baseFrameWidth = 250;
    int baseSpacing = 170;
    //int baseSpacing = (scrollAreaWidth - (baseCount * baseFrameWidth)) / (baseCount-1) ;

    frameCounts = {showCount, toolCount, baseCount};  // 每个容器的框数量
    frameWidths = {showFrameWidth, toolFrameWidth, baseFrameWidth};  // 每个容器框的宽度
    frameSpacings = {showSpacing, toolSpacing, baseSpacing};  // 每个容器框之间的间距

    //currentIndex = 0;
    currentPageIndex.append(0);
    currentPageIndex.append(frameWidths[0]*frameCounts[0] + frameSpacings[0]*(frameCounts[0]-1) + 10);
    currentPageIndex.append(currentPageIndex[1] + frameWidths[1]*frameCounts[1] + frameSpacings[1]*(frameCounts[1]-1));

}



void MainWidget::initMiddle()
{

    int showWidgetWidth = ui->showWidget->width();
    int showWidgetHeight = ui->showWidget->height();

    QWidget *frameLeft = new QWidget(ui->showWidget);
    QWidget *frameRight = new QWidget(ui->showWidget);

    int frameLeftWidth = showWidgetWidth * 0.2;
    int frameRightWidth = showWidgetWidth * 0.8;

    frameLeft->setGeometry(0, showWidgetHeight*0.1, frameLeftWidth, showWidgetHeight);
    frameRight->setGeometry(frameLeftWidth, showWidgetHeight*0.1, frameRightWidth, showWidgetHeight);


    // ============================================================================

    QVector<QString> widgetNameList;

    widgetNameList.append(QString::fromUtf8("态势展示"));
    widgetNameList.append(QString::fromUtf8("仿真工具"));
    widgetNameList.append(QString::fromUtf8("模型与通信底座"));

    QStringList normalImages = {":/images/u62.png", ":/images/u62.png", ":/images/u62.png"};
    QStringList hoverImages = {":/images/u62_mouseOver.png", ":/images/u62_mouseOver.png", ":/images/u62_mouseOver.png"};

    int buttonHeight = 100;  // 按钮的高度
    int buttonSpacing = 50;  // 按钮间距
    int totalHeight = frameLeft->height() - 2 * buttonSpacing;  // 使用 frameLeft 的高度

    // 等分按钮的垂直位置
    int buttonY = buttonSpacing;

    for (int i = 0; i < 3; ++i) {
        // 创建按钮
        QPushButton *button = new QPushButton(widgetNameList[i], frameLeft);
        button->setFixedSize(frameLeftWidth * 0.9, buttonHeight);  // 设置按钮大小
        button->move(frameLeftWidth * 0.05, buttonY);  // 设置按钮位置（X轴居中，Y轴等分）

        // 设置按钮样式，包括字体和背景
        button->setStyleSheet(QString(R"(
        QPushButton {
            border: none;
            background: transparent;
            image: url(%1);
            color: white;
            font: bold 25px "SimHei";
        }
        QPushButton:hover {
            image: url(%2);
        }
    )").arg(normalImages[i]).arg(hoverImages[i]));

        // 更新下一个按钮的位置
        buttonY += buttonHeight + buttonSpacing;

        // 将按钮点击信号连接到槽函数，并传递按钮的索引（i）
        connect(button, &QPushButton::clicked, [this, i]() {
            onChangeButtonClicked(i);  // 将按钮的索引作为参数传递给槽函数
        });
    }



    //================================================================
    frameHeight = 350;
    // ====== 滚动区域初始化 ======
    scrollArea = new QScrollArea(frameRight);
    scrollArea->setFixedSize(scrollAreaWidth, scrollAreaHeight);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setStyleSheet("QScrollArea { background: transparent; border: none; }");

    // ====== 创建滚动内容窗口 ======
    scrollWidget = new QWidget();
    layout = new QHBoxLayout(scrollWidget);
    layout->setSpacing(0);
    layout->setAlignment(Qt::AlignCenter);  // 让内容居中


    // === Show容器 ===
    int showFrameWidth = frameWidths[0];


    for (int i = 0; i < frameCounts[0]; ++i) {
        QFrame *frame = new QFrame(scrollWidget);
        frame->setFixedSize(showFrameWidth, frameHeight);
        frame->setStyleSheet("border: none;");

        QLabel *backgroundLabel = new QLabel(frame);
        backgroundLabel->setGeometry(0, 0, showFrameWidth, frameHeight);

        QPixmap backgroundPixmap(":/images/u8.jpg");
        //backgroundLabel->setPixmap(backgroundPixmap.scaled(showFrameWidth, frameHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        backgroundLabel->setPixmap(backgroundPixmap.scaled(showFrameWidth, frameHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        backgroundLabel->setStyleSheet("background: transparent;");
        backgroundLabel->lower();
        backgroundLabel->show();


        QVBoxLayout *vLayout = new QVBoxLayout(frame);
        vLayout->setAlignment(Qt::AlignCenter);
        vLayout->setSpacing(10);

        // 图标
        QLabel *iconLabel = new QLabel(frame);
        QString imagePath = softwareShowIcon[i];
        QSvgRenderer renderer(imagePath);
        QPixmap pixmap(renderer.defaultSize() * 3);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        renderer.render(&painter);
        iconLabel->setPixmap(pixmap);
        iconLabel->setFixedSize(pixmap.size());
        iconLabel->setAlignment(Qt::AlignCenter);

        vLayout->addWidget(iconLabel, 0, Qt::AlignCenter);

        // 名称标签
        QLabel *nameLabel = new QLabel(softwareShowName[i], frame);
        nameLabel->setAlignment(Qt::AlignCenter);
        nameLabel->setFont(QFont("SimHei", 15, QFont::Bold));
        nameLabel->setStyleSheet("color: white; background: transparent; border: none;");
        vLayout->addWidget(nameLabel, 0, Qt::AlignCenter);

        // ========== 进入系统按钮 ==========
        QPushButton *openButton = new QPushButton(QString::fromUtf8("进入系统"), frame);
        openButton->setFixedSize(120, 30);  // 调整按钮为更扁的比例（宽：120，高：30）
        openButton->setStyleSheet(
            "QPushButton {"
            "   color: #00BFFF;"
            "   background: transparent;"
            "   border: 2px solid #00BFFF;"
            "   border-radius: 10px;"  // 圆角
            "   padding: 5px 10px;"
            "}"
            "QPushButton:hover {"
            "   background-color: rgba(30, 144, 255, 0.2);"
            "}"
            "QPushButton:pressed {"
            "   background-color: rgba(30, 144, 255, 0.3);"
            "   padding-left: 8px; padding-top: 8px;"
            "}"
            );
        connect(openButton, &QPushButton::clicked, this, [=]() {
            QProcess::startDetached(softwareShowURL[i]);
        });


        vLayout->addWidget(openButton, 0, Qt::AlignCenter);  // **让按钮居中**


        frame->setLayout(vLayout);
        frame->installEventFilter(this);

        // 为每个框添加间距
        if (i > 0 && i < frameCounts[0]) {
            layout->addSpacerItem(new QSpacerItem(frameSpacings[0], 0, QSizePolicy::Fixed, QSizePolicy::Fixed));  // 添加间距
        }
        else if(i == frameCounts[0]){
            layout->addSpacerItem(new QSpacerItem(50, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
        }

        layout->addWidget(frame);  // 添加到滚动布局
    }


    // === Tool容器 ===

    int toolFrameWidth = frameWidths[1];
    for (int i = 0; i < frameCounts[1]; ++i) {
        QFrame *frame = new QFrame(scrollWidget);
        frame->setFixedSize(toolFrameWidth, frameHeight);
        frame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        frame->setStyleSheet("border: none;");

        QLabel *backgroundLabel = new QLabel(frame);
        backgroundLabel->setGeometry(0, 0, toolFrameWidth, frameHeight);
        QPixmap backgroundPixmap(":/images/u8.jpg");
        backgroundLabel->setPixmap(backgroundPixmap.scaled(toolFrameWidth, frameHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        backgroundLabel->setStyleSheet("background: transparent;");
        backgroundLabel->lower();
        backgroundLabel->show();

        QVBoxLayout *vLayout = new QVBoxLayout(frame);
        vLayout->setAlignment(Qt::AlignCenter);
        vLayout->setSpacing(10);

        // 图标
        QLabel *iconLabel = new QLabel(frame);
        QString imagePath = softwareToolIcon[i];
        QSvgRenderer renderer(imagePath);
        QPixmap pixmap(renderer.defaultSize() * 3);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        renderer.render(&painter);
        iconLabel->setPixmap(pixmap);
        iconLabel->setFixedSize(pixmap.size());
        iconLabel->setAlignment(Qt::AlignCenter);

        vLayout->addWidget(iconLabel, 0, Qt::AlignCenter);

        // 名称标签
        QLabel *nameLabel = new QLabel(softwareToolName[i], frame);
        nameLabel->setAlignment(Qt::AlignCenter);
        nameLabel->setFont(QFont("Arial", 15, QFont::Bold));
        nameLabel->setStyleSheet("color: white; background: transparent; border: none;");
        vLayout->addWidget(nameLabel, 0, Qt::AlignCenter);

        // ========== 进入系统按钮 ==========
        QPushButton *openButton = new QPushButton(QString::fromUtf8("进入系统"), frame);
        openButton->setFixedSize(120, 30);  // 调整按钮为更扁的比例（宽：120，高：30）
        openButton->setStyleSheet(
            "QPushButton {"
            "   color: #00BFFF;"
            "   background: transparent;"
            "   border: 2px solid #00BFFF;"
            "   border-radius: 10px;"  // 圆角
            "   padding: 5px 10px;"
            "}"
            "QPushButton:hover {"
            "   background-color: rgba(30, 144, 255, 0.2);"
            "}"
            "QPushButton:pressed {"
            "   background-color: rgba(30, 144, 255, 0.3);"
            "   padding-left: 8px; padding-top: 8px;"
            "}"
            );
        connect(openButton, &QPushButton::clicked, this, [=]() {
            QProcess::startDetached(softwareShowURL[i]);
        });



        vLayout->addWidget(openButton, 0, Qt::AlignCenter);

        frame->setLayout(vLayout);
        frame->installEventFilter(this);

        // 为每个框添加间距
        if (i > 0 && i < frameCounts[1]) {
            layout->addSpacerItem(new QSpacerItem(frameSpacings[1], 50, QSizePolicy::Fixed, QSizePolicy::Fixed));  // 添加间距
        }
        else if(i == frameCounts[1]){
            layout->addSpacerItem(new QSpacerItem(50, 50, QSizePolicy::Fixed, QSizePolicy::Fixed));
        }

        layout->addWidget(frame);  // 添加到滚动布局
    }

    // === Base容器 ===
    int baseFrameWidth = frameWidths[2];
    for (int i = 0; i < frameCounts[2]; ++i) {
        QFrame *frame = new QFrame(scrollWidget);
        frame->setFixedSize(baseFrameWidth, frameHeight);
        frame->setStyleSheet("border: none;");

        QLabel *backgroundLabel = new QLabel(frame);
        backgroundLabel->setGeometry(0, 0, baseFrameWidth, frameHeight);
        QPixmap backgroundPixmap(":/images/u8.jpg");
        backgroundLabel->setPixmap(backgroundPixmap.scaled(baseFrameWidth, frameHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        backgroundLabel->setStyleSheet("background: transparent;");
        backgroundLabel->lower();
        backgroundLabel->show();

        QVBoxLayout *vLayout = new QVBoxLayout(frame);
        vLayout->setAlignment(Qt::AlignCenter);
        vLayout->setSpacing(10);

        // 图标
        QLabel *iconLabel = new QLabel(frame);
        QString imagePath = softwareBaseIcon[i];
        QSvgRenderer renderer(imagePath);
        QPixmap pixmap(renderer.defaultSize() * 3);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        renderer.render(&painter);
        iconLabel->setPixmap(pixmap);
        iconLabel->setFixedSize(pixmap.size());
        iconLabel->setAlignment(Qt::AlignCenter);

        vLayout->addWidget(iconLabel, 0, Qt::AlignCenter);

        // 名称标签
        QLabel *nameLabel = new QLabel(softwareBaseName[i], frame);
        nameLabel->setAlignment(Qt::AlignCenter);
        nameLabel->setFont(QFont("Arial", 15, QFont::Bold));
        nameLabel->setStyleSheet("color: white; background: transparent; border: none;");
        vLayout->addWidget(nameLabel, 0, Qt::AlignCenter);

        // ========== 进入系统按钮 ==========
        QPushButton *openButton = new QPushButton(QString::fromUtf8("进入系统"), frame);
        openButton->setFixedSize(120, 30);  // 调整按钮为更扁的比例（宽：120，高：30）
        openButton->setStyleSheet(
            "QPushButton {"
            "   color: #00BFFF;"
            "   background: transparent;"
            "   border: 2px solid #00BFFF;"
            "   border-radius: 10px;"  // 圆角
            "   padding: 5px 10px;"
            "}"
            "QPushButton:hover {"
            "   background-color: rgba(30, 144, 255, 0.2);"
            "}"
            "QPushButton:pressed {"
            "   background-color: rgba(30, 144, 255, 0.3);"
            "   padding-left: 8px; padding-top: 8px;"
            "}"
            );
        connect(openButton, &QPushButton::clicked, this, [=]() {
            QProcess::startDetached(softwareShowURL[i]);
        });


        vLayout->addWidget(openButton, 0, Qt::AlignCenter);

        frame->setLayout(vLayout);
        frame->installEventFilter(this);

        // 为每个框添加间距
        // 为每个框添加间距
        if (i > 0 && i < frameCounts[2]) {
            layout->addSpacerItem(new QSpacerItem(frameSpacings[2], 0, QSizePolicy::Fixed, QSizePolicy::Fixed));  // 添加间距
        }


        layout->addWidget(frame);  // 添加到滚动布局
    }

    // 设置滚动区域布局
    scrollWidget->setLayout(layout);
    scrollArea->setWidget(scrollWidget);
    scrollWidget->setStyleSheet("background: transparent;");
    scrollArea->setWidgetResizable(true);
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
                backgroundLabel->setPixmap(mouseOverPixmap.scaled(backgroundLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            }
        }
    } else if (event->type() == QEvent::Leave) {
        QFrame *frame = qobject_cast<QFrame *>(watched);
        if (frame) {
            QLabel *backgroundLabel = frame->findChild<QLabel *>();
            if (backgroundLabel) {
                QPixmap originalPixmap(":/images/u8.jpg");
                backgroundLabel->setPixmap(originalPixmap.scaled(backgroundLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            }
        }
    }

    return QWidget::eventFilter(watched, event);
}


void MainWidget::scrollShow() {

    int targetPosition = currentPageIndex[0];
    smoothScrollTo(targetPosition);
}
void MainWidget::scrollTool() {

    int targetPosition = currentPageIndex[1];
    smoothScrollTo(targetPosition);
}
void MainWidget::scrollBase() {

    int targetPosition = currentPageIndex[2];
    smoothScrollTo(targetPosition);
}
void MainWidget::onChangeButtonClicked(int control)
{
    switch (control) {
    case 0:
        scrollShow();
        break;
    case 1:
        scrollTool();
        break;
    case 2:
        scrollBase();
        break;
    default:
        break;
    }
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
*/


MainWidget::~MainWidget()
{
    delete ui;
}

