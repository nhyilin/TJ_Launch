#ifndef WIDGET4_H
#define WIDGET4_H
#include "iwidget.h"

#include <QWidget>
#include <QApplication>
#include <QLabel>
#include <QSvgRenderer>
#include <QPixmap>
#include <QPainter>
#include <QDebug>

namespace Ui {
class Widget4;
}

class Widget4 : public IWidget
{
    Q_OBJECT

public:
    explicit Widget4(QWidget *parent = nullptr);
    ~Widget4();

    virtual void initMiddle();
    virtual void initVariables();

public:
    bool eventFilter(QObject *watched, QEvent *event);  // 捕获系统描述框
    void smoothScrollTo(int targetPosition);    // 增加滚动效果
private slots:
    void scrollLeft();   // 左侧滚动
    void scrollRight();  // 右侧滚动


private:    // middle 参数
    QScrollArea *scrollArea;  // 滚动区域
    QWidget *scrollWidget;    // 容纳所有方框的滚动容器
    QHBoxLayout *layout;      // 水平布局
    QPushButton *leftButton;  // 向左滚动按钮
    QPushButton *rightButton; // 向右滚动按钮

    int currentIndex;   // 当前第一个可见方框索引
    int totalFrames;    // 总方框数量
    int visibleFrames;    // 每次可见的方框数量
    int frameWidth;    // 方框的宽度
    int frameHeight;        // 每个系统描述框的高度
    int scrollAreaWidth;   // 滚动区域宽度
    int scrollAreaHeight;   // 滚动区域高度

    QVector<QString> softwareName;  // 软件名
    QVector<QString> softwareEnglishName;  // 软件英文名
    QVector<QString> softwareIcon;  // 软件图标
    QVector<QString> softwareFileName;  // .exe 文件名
    QVector<QString> softwareURL;   // .exe 路径
private:
    Ui::Widget4 *ui;
};

#endif // WIDGET4_H
