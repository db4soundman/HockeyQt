#include "PastGamesUI.h"
#include <QVBoxLayout>
PastGamesUI::PastGamesUI(PastGamesGraphic *graphic, HockeyTeam *team, bool home, QWidget *parent) : QWidget(parent)
{
    showButton.setText("Show");
    QVBoxLayout* manager = new QVBoxLayout();
    manager->addWidget(&numToShow);
    manager->addWidget(&showButton);
    this->home=home;
    this->team = team;

    numToShow.setValue(std::min(2, team->getGameHistory().size()));
    numToShow.setMaximum(std::min(8, team->getGameHistory().size()));
    numToShow.setMinimum(1);
    connect(this, SIGNAL(show(bool,int)), graphic, SLOT(receiveData(bool,int)));
    connect(&showButton, SIGNAL(clicked()), this, SLOT(prepareToShow()));
    connect(team, SIGNAL(rosterChanged()), this, SLOT(updateUi()));
    //connect(&showButton, SIGNAL(clicked()), this, SLOT(close()));
    setLayout(manager);
}

void PastGamesUI::prepareToShow()
{
    emit show(home, numToShow.value());
}

void PastGamesUI::updateUi()
{
    numToShow.setValue(std::min(2, team->getGameHistory().size()));
    numToShow.setMaximum(std::min(8, team->getGameHistory().size()));
}
