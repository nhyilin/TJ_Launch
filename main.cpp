#if defined(_MSC_VER)&&(_MSC_VER >= 1600)
    #pragma execution_character_set("utf-8")
#endif

#include "mainwidget.h"
#include "startsoftwarewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    // 设置默认语言环境为中文
    QLocale::setDefault(QLocale(QLocale::Chinese, QLocale::China));


    QApplication a(argc, argv);
    //StartSoftwareWidget s;
    //s.show();
    MainWidget w;
    w.show();
    return a.exec();
}
