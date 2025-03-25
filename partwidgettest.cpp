#include "partwidgettest.h"
#include "ui_partwidgettest.h"

#if defined(_MSC_VER)&&(_MSC_VER >= 1600)
#pragma execution_character_set("utf-8")
#endif


PartWidgetTest::PartWidgetTest(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PartWidgetTest)
{
    ui->setupUi(this);

    loadConfig();
    initVariables();
    initMiddle();
}



void PartWidgetTest::loadConfig()
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

void PartWidgetTest::initVariables()
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
    qDebug() << "showWidgetWidth"<<showWidgetWidth<<"showWidgetHeight"<<showWidgetHeight;
    //ui->showFrame = new QFrame(this);  // 创建 QFrame
    ui->showFrame->setGeometry(0, 0, showWidgetWidth, showWidgetHeight);  // 设置位置和大小
    // ====== 初始化参数列表 ======
    scrollAreaWidth = 1100;
    scrollAreaHeight = 500;

    // 计算 Show 容器的框宽度和间距
    int showCount = softwareShow.size();
    int showFrameWidth = 250;
    int showSpacing = 170;
    //int showSpacing = (scrollAreaWidth - (showCount * showFrameWidth)) / (showCount-1);

    // 计算 Tool 容器的框宽度和间距
    int toolCount = softwareTool.size();
    int toolFrameWidth = 200;
    int toolSpacing = 25;
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



// ========== 捕获系统描述框 ==========
bool PartWidgetTest::eventFilter(QObject *watched, QEvent *event)
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


void PartWidgetTest::initMiddle()
{

    QVBoxLayout *mainLayout = new QVBoxLayout(ui->showFrame);
    mainLayout->setSpacing(10);
    int frameHeight = 350;

    // ====== 滚动区域初始化 ======
    scrollArea = new QScrollArea(ui->showFrame);
    scrollArea->setFixedSize(1100, 500);
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
        qDebug() << frameCounts[0]<<"frameCounts[0]";
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
        QString imagePath = softwareShow[i].icon;
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
        QLabel *nameLabel = new QLabel(softwareShow[i].name, frame);
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
            QProcess::startDetached(softwareShow[i].path);
        });


        vLayout->addWidget(openButton, 0, Qt::AlignCenter);  // **让按钮居中**


        frame->setLayout(vLayout);
        frame->installEventFilter(this);

        // **保存 frame 以便后续动画**
        frames.append(frame);

        // 为每个框添加间距
        if (i > 0 && i < frameCounts[0]) {
            layout->addSpacerItem(new QSpacerItem(frameSpacings[0], 0, QSizePolicy::Fixed, QSizePolicy::Fixed));  // 添加间距
        }
        else if(i == frameCounts[0]){
            layout->addSpacerItem(new QSpacerItem(50, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
        }


        layout->addWidget(frame);  // 添加到滚动布局
    }

    // 设置滚动区域布局
    scrollWidget->setLayout(layout);
    scrollArea->setWidget(scrollWidget);
    scrollWidget->setStyleSheet("background: transparent;");
    scrollArea->setWidgetResizable(true);

    setLayout(mainLayout);
}


PartWidgetTest::~PartWidgetTest()
{
    delete ui;
}






