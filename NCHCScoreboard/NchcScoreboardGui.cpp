#include "NchcScoreboardGui.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextStream>
#include <QFile>
#include "MiamiAllAccessHockey.h"
#include <QDate>
#include <QFileDialog>

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
    QFile file(QFileDialog::getOpenFileName(0, "Select Friday file", MiamiAllAccessHockey::getAppDirPath()));
    file.open(QFile::ReadOnly);
    QTextStream reader(&file);
    for (int i = 0; i < games.size(); i +=2) {
        NchcGameGui* game = games.at(i);
        game->updateAwayName(reader.readLine());
        game->setAwayScore(reader.readLine());
        game->updateHomeName(reader.readLine());
        game->setHomeScore(reader.readLine());
        int isConf;
        reader >> isConf;
        game->setConf((bool)isConf);
        game->setTimeAndPd("F");
    }

}

void NchcScoreboardGui::saveGames()
{
    QFile file(MiamiAllAccessHockey::getAppDirPath() + "/" + QDate::currentDate().toString("MMM.dd") + ".maa");
    file.open(QFile::WriteOnly);
    QTextStream writer(&file);
    for (int i = 0; i < games.size(); i +=2) {
        NchcGameGui* game = games.at(i);
        writer << game->getAway() << endl;
        writer << game->getAwayScore() << endl;
        writer << game->getHome() << endl;
        writer << game->getHomeScore() << endl;
        writer << game->isConf() << endl;
    }
    file.close();
}

void NchcScoreboardGui::submitGamesToGui()
{
    QList<NchcScoreEntry> friday, saturday;
    for (int i = 0; i < games.size(); i++) {
        if (!games.at(i)->getAway().isEmpty()) {
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
