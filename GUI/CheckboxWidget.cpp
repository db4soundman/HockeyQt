#include "CheckboxWidget.h"
#include <QVBoxLayout>

CheckBoxWidget::CheckBoxWidget(HockeyGame *pgame)
{
    statcrew = new QCheckBox("Stat Crew");
    statcrew->setChecked(true);
    connect(statcrew, SIGNAL(clicked()), pgame, SIGNAL(toggleStatCrew()));
    connect(pgame, SIGNAL(statusOfStatCrew(bool)), statcrew, SLOT(setChecked(bool)));
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(statcrew);
    setLayout(layout);
}
