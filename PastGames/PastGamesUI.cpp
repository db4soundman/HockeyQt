#include "PastGamesUI.h"
#include <QVBoxLayout>
PastGamesUI::PastGamesUI(PastGamesGraphic *graphic, HockeyTeam *team, bool home, QWidget *parent) : QWidget(parent)
{
    showButton.setText("Show");
    QVBoxLayout* manager = new QVBoxLayout();
    manager->addWidget(&numToShow);
    manager->addWidget(&showButton);
    this->home=home;

    numToShow.setValue(std::min(2, team->getGameHistory().size()));
    numToShow.setMaximum(std::min(8, team->getGameHistory().size()));
    numToShow.setMinimum(1);
    connect(this, SIGNAL(show(bool,int)), graphic, SLOT(receiveData(bool,int)));
    connect(&showButton, SIGNAL(clicked()), this, SLOT(prepareToShow()));
    //connect(&showButton, SIGNAL(clicked()), this, SLOT(close()));
    setLayout(manager);
}

void PastGamesUI::prepareToShow()
{
    emit show(home, numToShow.value());
}
