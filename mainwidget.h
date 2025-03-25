#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "iwidget.h"

#include "partwidget1.h"
#include "partwidget2.h"
#include "partwidget3.h"
#include "partwidgettest.h"

#include <QWidget>

#include <QApplication>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QPalette>
#include <QPainter>
#include <QPixmap>
#include <QFrame>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QScrollBar>
#include <QMovie>
#include <QTimer>
#include <QProcess>
#include <QSplitter>
#include <QStackedWidget>
#include <QSvgRenderer>
#include <QButtonGroup>
#include <QScreen>
#include <QResizeEvent>
#include <QFont>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE
class StartSoftwareWidget;



class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

public:
    void resizeEvent(QResizeEvent *event);


    void initTop();
    //void initBottom();
    void initMiddle();
    void initFrameLeft();
    void initFrameRight();

private:
    Ui::MainWidget *ui;
    QStackedWidget *stackedWidget;      //存放界面(暂时不用)
    StartSoftwareWidget* startSoftwareWidget;       //界面1
    PartWidget1* partWidget1;                   //测试界面2
    PartWidget2* partWidget2;                   //测试界面2
    PartWidget3* partWidget3;                   //测试界面2
    PartWidgetTest* partWidgetTest;                   //测试界面2
private:    //left 参数
    QVector<QPushButton*> changePushButton;
    QVector<QString> changeButtonIcon;

private:    // top 参数
    QLabel *u2ImageLabel;  // 用于显示图片
    QLabel *titleLabel;   // 用于显示文字
    QLabel *titlelabel_1;  // 声明 titlelabel_1
    QLabel *titlelabel_2;  // 声明 titlelabel_2

private slots:
    void onChangeButtonClicked(int control);
/*
// =========== middle 参数==============
public:
    //void initMiddle();
    void initMiddleVariables();
    void loadConfig();  //读取配置文件
    bool eventFilter(QObject *watched, QEvent *event);  // 捕获系统描述框

    void smoothScrollTo(int targetPosition);    // 增加滚动效果

    QWidget* createScrollArea(const QVector<QString> &softwareName,
                              const QVector<QString> &softwareIcon,
                              const QVector<QString> &softwareURL,
                              int frameWidth,
                              int frameHeight,
                              int frameSpacing);
    void scrollShow();
    void scrollTool();
    void scrollBase();



private:

    QVector<SoftwareInfo> softwareShow, softwareTool, softwareBase;

private:    // 滚动区域
    QVector<int> currentPageIndex;  // 滚动界面索引
    QVector<int> frameCounts;  // 每个容器的框数量
    QVector<int> frameWidths;  // 每个容器框的宽度
    QVector<int> frameSpacings;  // 每个容器框之间的间距
    int scrollAreaWidth;  // 滚动区域的宽度
    int scrollAreaHeight;  // 滚动区域的高度
    QScrollArea *scrollArea;  // 滚动区域
    QWidget *scrollWidget;    // 容纳所有方框的滚动容器
    QHBoxLayout *layout;      // 水平布局

    int frameHeight;    // 框高度
*/

};

#endif // MAINWIDGET_H

