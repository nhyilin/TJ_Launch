
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
    //initMiddleVariables();

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
/*
void MainWidget::initMiddleVariables()
{

    loadConfig();
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

*/

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


    // ====== 初始化界面 =======
    stackedWidget = new QStackedWidget(frameRight);

    // 获取frameRight的大小
    QRect frameRect = frameRight->rect();

    int x = (frameRect.width() - stackedWidget->width()) / 2; // 水平居中
    int y = (frameRect.height() - stackedWidget->height()) / 2; // 垂直居中

    stackedWidget->move(0, 50);


    // 界面初始化
    partWidget1 = new PartWidget1();
    partWidget2 = new PartWidget2();
    partWidget3 = new PartWidget3();

    partWidgetTest = new PartWidgetTest();


    // 界面入栈
    //stackedWidget->addWidget(startSoftwareWidget);
    stackedWidget->addWidget(partWidgetTest);
    stackedWidget->addWidget(partWidget1);
    stackedWidget->addWidget(partWidget2);
    stackedWidget->addWidget(partWidget3);



    // 多态：存储子类界面的容器
    //changeWidget.append(startSoftwareWidget);
    //changeWidget.append(partwidget2);
    //changeWidget.append(partWidgetTest);

    // 设置当前界面
    stackedWidget->setCurrentWidget(partWidget1);







    // ============================================================================

    QVector<QString> widgetNameList;

    widgetNameList.append(QString::fromUtf8("展示"));
    widgetNameList.append(QString::fromUtf8("工具"));
    widgetNameList.append(QString::fromUtf8("基础"));

    QString normalImages = ":/images/u62.png";
    QString hoverImages = ":/images/u62_mouseOver.png";
    QString clickImages = ":/images/u62_click.png";
    int buttonHeight = 100;  // 按钮的高度
    int buttonSpacing = 50;  // 按钮间距
    int totalHeight = frameLeft->height() - 2 * buttonSpacing;  // 使用 frameLeft 的高度

    // 等分按钮的垂直位置
    int buttonY = buttonSpacing;



    QButtonGroup *buttonGroup = new QButtonGroup(this); // 创建按钮组

    // 设置按钮的选中方式为单选（只允许选择一个）
    buttonGroup->setExclusive(true);

    for (int i = 0; i < 3; ++i) {
        // 创建按钮
        QPushButton *button = new QPushButton(widgetNameList[i], frameLeft);
        button->setFixedSize(frameLeftWidth * 0.9, buttonHeight);  // 设置按钮大小
        button->move(frameLeftWidth * 0.05, buttonY);  // 设置按钮位置（X轴居中，Y轴等分）

        // 设置按钮的默认样式
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
            )").arg(normalImages, hoverImages));

        // 更新下一个按钮的位置
        buttonY += buttonHeight + buttonSpacing;

        // 将按钮添加到按钮组中
        buttonGroup->addButton(button, i);

        // 将按钮点击信号连接到槽函数，并传递按钮的索引（i）
        connect(button, &QPushButton::clicked, [this, i, button, buttonGroup, normalImages, hoverImages, clickImages]() {  // 在捕获列表中添加 buttonGroup
            // 取消所有按钮的选中状态
            foreach (QAbstractButton *btn, buttonGroup->buttons()) {
                btn->setChecked(false);
                // 恢复默认样式
                btn->setStyleSheet(QString(R"(
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
            )").arg(normalImages, hoverImages));
            }

            // 设置当前按钮为选中状态，并改变样式
            button->setChecked(true);
            // 设置选中按钮的样式（比如加边框或改变背景颜色）
            button->setStyleSheet(QString(R"(
            QPushButton {
                    border: none;
                    background: transparent;
                    image: url(%1);
                    color: #00FFF0;
                    font: bold 25px "SimHei";
            }
                QPushButton:hover {
                    image: url(%2);
                }
            )").arg(clickImages, hoverImages));

            // 调用槽函数
            onChangeButtonClicked(i);  // 将按钮的索引作为参数传递给槽函数
        });
    }


}


/*
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
*/
void MainWidget::onChangeButtonClicked(int control)
{

    switch (control) {
    case 0:
        stackedWidget->setCurrentWidget(partWidget1);  // 切换到界面 1
        partWidget1->startAnimation();
        //scrollShow();
        break;
    case 1:{

        stackedWidget->setCurrentWidget(partWidget2);
        partWidget2->startAnimation();
        break;
    }
    case 2:
        stackedWidget->setCurrentWidget(partWidget3);  // 切换到界面 2
        partWidget3->startAnimation();
        //scrollBase();
        break;
    default:
        break;
    }
}
/*
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

