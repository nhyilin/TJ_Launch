﻿#include "iwidget.h"
#include "ui_iwidget.h"


IWidget::IWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IWidget)
{
    ui->setupUi(this);

}

void IWidget::loadConfig()
{
    // 读取文件
    QString configPath = QCoreApplication::applicationDirPath() + "/config.json";
    QFile file(configPath);
    qDebug() << configPath;
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "无法打开配置文件";
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    if (jsonData.startsWith(QByteArray::fromRawData("\xef\xbb\xbf", 3))) {
        jsonData = jsonData.mid(3);
    }

    // 解析 JSON
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);
    if (doc.isNull()) {
        qDebug() << "JSON 解析失败，错误信息：" << parseError.errorString();
        return;
    }

    // 解析 JSON 对象
    QJsonObject jsonObj = doc.object();

    // 处理 "softwareShow" 数组
    QJsonArray softwareShowArray = jsonObj["softwareShow"].toArray();
    for (const QJsonValue &value : softwareShowArray) {
        QJsonObject software = value.toObject();
        SoftwareInfo info;
        info.name = software["name"].toString();
        info.icon = software["icon"].toString();
        info.path = software["path"].toString();
        softwareShow.append(info);
        //qDebug() <<" softwareShow"  << info.name << "  " << info.icon<< "  " << info.path;
    }

    // 处理 "softwareTool" 数组
    QJsonArray softwareToolArray = jsonObj["softwareTool"].toArray();
    for (const QJsonValue &value : softwareToolArray) {
        QJsonObject software = value.toObject();
        SoftwareInfo info;
        info.name = software["name"].toString();
        info.icon = software["icon"].toString();
        info.path = software["path"].toString();
        softwareTool.append(info);
        //qDebug() <<" softwareTool"  <<  info.name << "  " << info.icon<< "  " << info.path;
    }

    // 处理 "softwareBase" 数组
    QJsonArray softwareBaseArray = jsonObj["softwareBase"].toArray();
    for (const QJsonValue &value : softwareBaseArray) {
        QJsonObject software = value.toObject();
        SoftwareInfo info;
        info.name = software["name"].toString();
        info.icon = software["icon"].toString();
        info.path = software["path"].toString();
        softwareBase.append(info);
        //qDebug() <<" softwareBase"  <<  info.name << "  " << info.icon<< "  " << info.path;
    }

    qDebug() <<"softwareShow.size()" << softwareShow.size();
    qDebug() <<"softwareTool.size()" << softwareTool.size();
    qDebug() <<"softwareBase.size()" << softwareBase.size();

}

void IWidget::initVariables()
{
    // 初始化 showframe 大小
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();  // 获取可用屏幕尺寸
    // 设置主窗口的大小为屏幕的 95%
    int width = screenGeometry.width() * 0.99;
    int height = screenGeometry.height() * 0.99;
    this->showWidgetWidth =  width * 0.98;
    this->showWidgetHeight = height * 0.8;
    this->resize(showWidgetWidth, showWidgetHeight);

    showFrame = new QFrame(this);  // 创建 QFrame
    showFrame->setGeometry(0, 0, showWidgetWidth, showWidgetHeight);  // 设置位置和大小


    // ====== 初始化参数列表 ======

    frameHeight = 350;  // 框高度

    // 计算 Show 容器的框宽度和间距
    int showCount = softwareShow.size();
    int showFrameWidth = 250;
    int showSpacing = 170;
    //int showSpacing = (scrollAreaWidth - (showCount * showFrameWidth)) / (showCount-1);

    // 计算 Tool 容器的框宽度和间距
    int toolCount = softwareTool.size();
    int toolFrameWidth = 200;
    int toolSpacing = 20;
    //int toolSpacing = (scrollAreaWidth - (toolCount * toolFrameWidth)) / (toolCount-1) ;


    // 计算 Base 容器的框宽度和间距
    int baseCount = softwareBase.size();
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


void IWidget::startAnimation() {
    /*
    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);

    qDebug() << "frames.size()" << frames.size();
    for (int i = 0; i < frames.size(); i++) {
        QFrame *frameI = frames[i];

        // ** frame 原始位置**
        QRect originalPos = frameI->geometry();

        // **设置透明度**
        QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(frameI);
        frameI->setGraphicsEffect(opacityEffect);
        frameI->setVisible(false);  // 先隐藏

        QPropertyAnimation *opacityAnim = new QPropertyAnimation(opacityEffect, "opacity");
        opacityAnim->setDuration(200);
        opacityAnim->setStartValue(1.0);
        opacityAnim->setEndValue(1.0);

        // **滑入动画**
        QRect startPos = originalPos.translated(-30, 0);  // **初始位置左移**
        QRect endPos = originalPos;  // **回到原始位置**

        QPropertyAnimation *moveAnim = new QPropertyAnimation(frameI, "geometry");
        moveAnim->setDuration(100);
        moveAnim->setStartValue(startPos);
        moveAnim->setEndValue(endPos);

        // **延迟启动每个动画**
        QTimer::singleShot(i * 50, this, [=]() {
            frameI->setGeometry(startPos);  // **确保起始位置正确**
            frameI->setVisible(true);
            QParallelAnimationGroup *frameAnimGroup = new QParallelAnimationGroup(this);
            frameAnimGroup->addAnimation(opacityAnim);
            frameAnimGroup->addAnimation(moveAnim);
            frameAnimGroup->start();
        });
    }
*/
}

// ========== 捕获系统描述框 ==========
bool IWidget::eventFilter(QObject *watched, QEvent *event)
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


void IWidget::initMiddle(){}

IWidget::~IWidget()
{
    delete ui;
}
