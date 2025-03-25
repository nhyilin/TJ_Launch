#ifndef PARTWIDGETTEST_H
#define PARTWIDGETTEST_H

#include <QWidget>
#include "iwidget.h"

namespace Ui {
class PartWidgetTest;
}

class PartWidgetTest : public QWidget
{
    Q_OBJECT

public:
    explicit PartWidgetTest(QWidget *parent = nullptr);
    ~PartWidgetTest();


public:
    void initVariables();
    void initMiddle();
    void startAnimation();
    bool eventFilter(QObject *watched, QEvent *event);

protected:

    void loadConfig();

protected:

    QVector<SoftwareInfo> softwareShow, softwareTool, softwareBase;

    //QFrame *showFrame;
    // 设置主窗口的大小为屏幕的 95%
    int showWidgetWidth;
    int showWidgetHeight;

    QScrollArea *scrollArea;  // 滚动区域
    QWidget *scrollWidget;    // 容纳所有方框的滚动容器
    QHBoxLayout *layout;      // 水平布局
    int scrollAreaWidth;  // 滚动区域的宽度
    int scrollAreaHeight;  // 滚动区域的高度



    QVector<int> currentPageIndex;  // 滚动界面索引
    QVector<int> frameCounts;  // 每个容器的框数量
    QVector<int> frameWidths;  // 每个容器框的宽度
    QVector<int> frameSpacings;  // 每个容器框之间的间距



    int frameHeight;    // 框高度

    QList<QFrame*> frames;  // 存储多个 QFrame 指针

private:
    Ui::PartWidgetTest *ui;
};

#endif // PARTWIDGETTEST_H

