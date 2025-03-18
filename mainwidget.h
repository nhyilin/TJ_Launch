#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "iwidget.h"
#include "startsoftwarewidget.h"
#include "widget4.h"

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

#include <QScreen>
#include <QResizeEvent>
#include <QFont>


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
    //void showEvent(QShowEvent *event);  // 初始化背景
    void resizeEvent(QResizeEvent *event);
    //void paintEvent(QPaintEvent *event);

    void initVariables();   // 初始化参数
    void initTop();

    void initBottom();
    void initMiddle();

private:
    Ui::MainWidget *ui;
    QStackedWidget *stackedWidget;      //存放界面
    IWidget* startSoftwareWidget;       //界面1
    IWidget* widget3;                   //测试界面2
    IWidget* widget4;                   //测试界面2

private:    // top 参数
    QLabel *u2ImageLabel;  // 用于显示图片
    QLabel *titleLabel;   // 用于显示文字
    QLabel *titlelabel_1;  // 声明 titlelabel_1
    QLabel *titlelabel_2;  // 声明 titlelabel_2

private:    //left 参数
    QVector<QPushButton*> changePushButton;
    QVector<QString> changeButtonIcon;
    QVector<IWidget*> changeWidget;

private:    //bottom 参数
    QVector<QString> bottomFunctionButton;


};
#endif // MAINWIDGET_H

