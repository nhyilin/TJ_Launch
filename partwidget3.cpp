#include "partwidget3.h"
#include "ui_partwidget3.h"

PartWidget3::PartWidget3(QWidget *parent) :
    IWidget(parent),
    ui(new Ui::PartWidget3)
{
    ui->setupUi(this);
    // 读取配置文件
    loadConfig();
    initVariables();
    initMiddle();
}



void PartWidget3::initMiddle()
{

    QVBoxLayout *mainLayout = new QVBoxLayout(showFrame);
    mainLayout->setSpacing(0);
    mainLayout->setAlignment(Qt::AlignCenter);

    showW = new QWidget(showFrame);
    QHBoxLayout *layout = new QHBoxLayout(showW);
    layout->setSpacing(0);
    layout->setAlignment(Qt::AlignCenter);  // 让内容居中


    // === Base容器 ===
    int baseFrameWidth = frameWidths[2];
    for (int i = 0; i < frameCounts[2]; ++i) {
        QFrame *frame = new QFrame(showW);
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
        QString imagePath = softwareBase[i].icon;
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
        QLabel *nameLabel = new QLabel(softwareBase[i].name, frame);
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
            QProcess::startDetached(softwareBase[i].path);
        });


        vLayout->addWidget(openButton, 0, Qt::AlignCenter);

        frame->setLayout(vLayout);
        frame->installEventFilter(this);

        //frames.append(frame);

        // 为每个框添加间距
        // 为每个框添加间距
        if (i > 0 && i < frameCounts[2]) {
            layout->addSpacerItem(new QSpacerItem(frameSpacings[2], 0, QSizePolicy::Fixed, QSizePolicy::Fixed));  // 添加间距
        }


        layout->addWidget(frame);  // 添加到滚动布局
    }

    // 设置滚动区域布局
    showW->setLayout(layout);
    showW->setStyleSheet("background: transparent;");
    mainLayout->addWidget(showW, 0, Qt::AlignCenter);
    setLayout(mainLayout);
}

void PartWidget3::startAnimation() {
    if (!showW) return;  // 确保 showW 存在

    // **1. 设置 showW 初始状态**
    QRect originalPos = showW->geometry();
    QRect startPos = originalPos.translated(0, 50);  // **初始位置下移**
    showW->setGeometry(startPos);
    showW->setVisible(true);

    // **2. 透明度动画**
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(showW);
    showW->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.0);

    QPropertyAnimation *opacityAnim = new QPropertyAnimation(opacityEffect, "opacity");
    opacityAnim->setDuration(400);
    opacityAnim->setStartValue(0.0);
    opacityAnim->setEndValue(1.0);

    // **3. 位置动画**
    QPropertyAnimation *moveAnim = new QPropertyAnimation(showW, "geometry");
    moveAnim->setDuration(400);
    moveAnim->setStartValue(startPos);
    moveAnim->setEndValue(originalPos);
    moveAnim->setEasingCurve(QEasingCurve::OutCubic);  // **缓动动画**

    // **4. 组合动画**
    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
    group->addAnimation(opacityAnim);
    group->addAnimation(moveAnim);
    group->start(QAbstractAnimation::DeleteWhenStopped);
}


PartWidget3::~PartWidget3()
{
    delete ui;
}
