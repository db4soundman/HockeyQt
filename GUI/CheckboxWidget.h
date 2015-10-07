#ifndef CHECKBOXWIDGET_H
#define CHECKBOXWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include "HockeyGame.h"

class CheckBoxWidget : public QWidget
{
    Q_OBJECT
public:
    CheckBoxWidget(HockeyGame *pgame);

private:
    QCheckBox* statcrew;
};

#endif // CHECKBOXWIDGET_H
