#ifndef IWIDGET_H
#define IWIDGET_H

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

#include <QStackedWidget>
#include <QSvgRenderer>
#include <QButtonGroup>
#include <QScreen>
#include <QResizeEvent>
#include <QParallelAnimationGroup>

#include <QButtonGroup>
#include <QScreen>
#include <QResizeEvent>
#include <QFont>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QGraphicsScale>
#include <QGraphicsEffect>

namespace Ui {
class IWidget;
}

struct SoftwareInfo {
    QString name;
    QString icon;
    QString path;
};


class IWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IWidget(QWidget *parent = nullptr);
    ~IWidget();

public:
    void initVariables();
    void initMiddle();
    void startAnimation();
    bool eventFilter(QObject *watched, QEvent *event);

protected:

    void loadConfig();

private:
    Ui::IWidget *ui;


protected:
    QWidget *showW;
    QFrame *showFrame;
    // 设置主窗口的大小为屏幕的 95%
    int showWidgetWidth;
    int showWidgetHeight;

    QVector<SoftwareInfo> softwareShow, softwareTool, softwareBase;

    QVector<int> currentPageIndex;  // 滚动界面索引
    QVector<int> frameCounts;  // 每个容器的框数量
    QVector<int> frameWidths;  // 每个容器框的宽度
    QVector<int> frameSpacings;  // 每个容器框之间的间距

    int frameHeight;    // 框高度

};


#endif // IWIDGET_H
