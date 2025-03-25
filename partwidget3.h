#ifndef PARTWIDGET3_H
#define PARTWIDGET3_H

#include <QWidget>
#include "iwidget.h"

namespace Ui {
class PartWidget3;
}

class PartWidget3 : public IWidget
{
    Q_OBJECT

public:
    explicit PartWidget3(QWidget *parent = nullptr);
    ~PartWidget3();
public:
    void initMiddle();
    void startAnimation();
private:
    Ui::PartWidget3 *ui;
};

#endif // PARTWIDGET3_H
