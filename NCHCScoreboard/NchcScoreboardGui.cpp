#include "NchcScoreboardGui.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

NchcScoreboardGui::NchcScoreboardGui(NchcScoreboardGraphic* grph) {
    graphic = grph;
    QVBoxLayout* realLayout = new QVBoxLayout();
    QHBoxLayout* mainLayout = new QHBoxLayout();
    QVBoxLayout* friday = new QVBoxLayout();
    QVBoxLayout* saturday = new QVBoxLayout();

    for (int i = 0; i < 7; i++) {
        NchcGameGui* fri = new NchcGameGui( i == 0);
        NchcGameGui* sat = new NchcGameGui(i == 0);
        connect(fri, SIGNAL(awayNameUpdated(QString)),
                sat, SLOT(updateAwayName(QString)));
        connect(fri, SIGNAL(homeNameUpdated(QString)),
                sat, SLOT(updateHomeName(QString)));
        friday->addWidget(fri);
        saturday->addWidget(sat);
        games.append(fri);
        games.append(sat);

    }
    mainLayout->addLayout(friday);
    mainLayout->addLayout(saturday);
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* load = new QPushButton("Load");
    connect(load, SIGNAL(clicked()), this, SLOT(loadGames()));
    QPushButton* save = new QPushButton("Save");
    connect(save, SIGNAL(clicked()), this, SLOT(saveGames()));
    QPushButton* submit = new QPushButton("Submit");
    connect(submit, SIGNAL(clicked()), this, SLOT(hide()));
    QPushButton* display = new QPushButton("Show");
    // connect display to the show() of graphic later...
    buttonLayout->addWidget(load);
    buttonLayout->addWidget(save);
    buttonLayout->addWidget(display);
    buttonLayout->addWidget(submit);
    realLayout->addLayout(mainLayout);
    realLayout->addLayout(buttonLayout);
    setLayout(realLayout);

    connect(display, SIGNAL(clicked()), graphic, SLOT(showImg()));
    connect(submit, SIGNAL(clicked()), this, SLOT(submitGamesToGui()));
}

void NchcScoreboardGui::loadGames()
{

}

void NchcScoreboardGui::saveGames()
{

}

void NchcScoreboardGui::submitGamesToGui()
{
    QList<NchcScoreEntry> friday, saturday;
    for (int i = 0; i < games.size(); i++) {
        if (!games.at(i)->getAwayScore().isEmpty()) {
            NchcGameGui* gui = games.at(i);
            NchcScoreEntry game(gui->getAway(), gui->getHome(), gui->getAwayScore(), gui->getHomeScore(), gui->getTimeAndPd(), gui->isConf());
            if (i % 2 == 0) {
                friday.append(game);
            }
            else {
                saturday.append(game);
            }
        }
        graphic->setFridayGames(friday);
        graphic->setSaturdayGames(saturday);
    }
}
