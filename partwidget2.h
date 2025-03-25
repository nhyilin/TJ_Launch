#ifndef PARTWIDGET2_H
#define PARTWIDGET2_H

#include "iwidget.h"
#include <QWidget>

namespace Ui {
class PartWidget2;
}

class PartWidget2 : public IWidget
{
    Q_OBJECT

public:
    explicit PartWidget2(QWidget *parent = nullptr);
    ~PartWidget2();

public:
    void initMiddle();
    void startAnimation();

private:
    Ui::PartWidget2 *ui;



};


#endif // PARTWIDGET2_H
