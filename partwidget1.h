#ifndef PARTWIDGET1_H
#define PARTWIDGET1_H

#include <QWidget>
#include "iwidget.h"

namespace Ui {
class PartWidget1;
}

class PartWidget1 : public IWidget
{
    Q_OBJECT

public:
    explicit PartWidget1(QWidget *parent = nullptr);
    ~PartWidget1();

public:
    void initMiddle();
    void startAnimation();
private:
    Ui::PartWidget1 *ui;

};

#endif // PARTWIDGET1_H
