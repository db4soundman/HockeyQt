#include "ComparisonCreator.h"
#include <QGridLayout>
#include <QLabel>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

ComparisonCreator::ComparisonCreator(HockeyGame *game, QWidget *parent) : QWidget(parent)
{
     colorSelector.addItem("Away & Home");
     colorSelector.addItem("Away & Away");
     colorSelector.addItem("Home & Home");
     clear.setText("Clear");
     show.setText("Show");

     QGridLayout* myLayout = new QGridLayout();

     QFormLayout* colorPickerLayout = new QFormLayout();
     colorPickerLayout->addRow("Comparison Type:", &colorSelector);
     colorPickerLayout->addRow("Graphic Header:", &statLabel);

     myLayout->addLayout(colorPickerLayout,0,0);

     QHBoxLayout* labelRow = new QHBoxLayout();
     labelRow->addWidget(new QLabel("Name:"));
     labelRow->addWidget(new QLabel("Stat 1:"));
     labelRow->addWidget(new QLabel("Stat 2:"));

     QHBoxLayout* topRowFields = new QHBoxLayout();
     topRowFields->addWidget(&topLabel);
     topRowFields->addWidget(&topStat1);
     topRowFields->addWidget(&topStat2);

     QHBoxLayout* botRowFields = new QHBoxLayout();
     botRowFields->addWidget(&botLabel);
     botRowFields->addWidget(&botStat1);
     botRowFields->addWidget(&botStat2);

     myLayout->addLayout(labelRow,1,0);
     myLayout->addLayout(topRowFields, 2,0);
     myLayout->addLayout(botRowFields,3,0);

     myLayout->addWidget(&clear, 4,1);
     myLayout->addWidget(&show, 4,2);

     setLayout(myLayout);

     graphic = game->getComparisonGraphic();

     connect(&show, SIGNAL(clicked(bool)), this, SLOT(submitCompGraphic()));
}

void ComparisonCreator::submitCompGraphic()
{
    QList<QString> stats;
    stats.append(topStat1.text());
    stats.append(botStat1.text());
    if (!topStat2.text().trimmed().isEmpty()) {
        stats.append(topStat1.text());
        stats.append(topStat1.text());
    }
    graphic->prepareComp(topLabel.text().trimmed(),botLabel.text().trimmed(),
                         stats, statLabel.text().trimmed(), colorSelector.currentIndex());
    this->hide();
}

void ComparisonCreator::clearFields()
{
    colorSelector.setCurrentIndex(0);
    statLabel.setText("");
    topLabel.setText("");
    topStat1.setText("");
    topStat2.setText("");
    botLabel.setText("");
    botStat1.setText("");
    botStat2.setText("");

}

