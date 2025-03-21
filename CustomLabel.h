#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

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


class CustomLabel : public QLabel {
    Q_OBJECT
public:
    explicit CustomLabel(QWidget *parent = nullptr)
        : QLabel(parent) {
        setAttribute(Qt::WA_OpaquePaintEvent);  // 设置为不透明
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);  // 启用抗锯齿

        // 绘制背景图片
        QPixmap backgroundPixmap(":/images/u8.jpg");
        painter.drawPixmap(0, 0, width(), height(), backgroundPixmap.scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

        // 绘制红色圆角矩形框
        painter.setPen(QPen(Qt::blue, 4));  // 设置蓝色边框，边框宽度为4
        painter.setBrush(Qt::transparent);  // 填充颜色为透明
        int radius = 15;  // 圆角半径为15
        painter.drawRoundedRect(0, 0, width(), height(), radius, radius);  // 绘制圆角矩形
    }
};


#endif // CUSTOMLABEL_H
