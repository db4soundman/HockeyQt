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
    QHBoxLayout* labelLayout = new QHBoxLayout();
    QVBoxLayout* friday = new QVBoxLayout();
    QVBoxLayout* saturday = new QVBoxLayout();
    fridayHeader.setText("Friday's Games");
    saturdayHeader.setText("Saturday's Games");
    for (int i = 0; i < 6; i++) {
        NchcGameGui* fri = new NchcGameGui();
        NchcGameGui* sat = new NchcGameGui();
        connect(fri, SIGNAL(awayNameUpdated(QString)),
                sat, SLOT(updateAwayName(QString)));
        connect(fri, SIGNAL(homeNameUpdated(QString)),
                sat, SLOT(updateHomeName(QString)));
        connect(fri, SIGNAL(confGameUpdated(bool)),
                sat, SLOT(updateConfGame(bool)));
        friday->addWidget(fri);
        saturday->addWidget(sat);
        games.append(fri);
        games.append(sat);
    }
    labelLayout->addWidget(&fridayHeader);
    labelLayout->addWidget(&saturdayHeader);
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
    //buttonLayout->addWidget(submit);
    realLayout->addLayout(labelLayout);
    realLayout->addLayout(mainLayout);
    realLayout->addLayout(buttonLayout);
    setLayout(realLayout);

    //connect(display, SIGNAL(clicked()), graphic, SLOT(showImg()));
    connect(display, SIGNAL(clicked()), this, SLOT(submitAndShow()));
}

void NchcScoreboardGui::loadGames()
{
    QFile file(QFileDialog::getOpenFileName(0, "Select Friday file", MiamiAllAccessHockey::getAppDirPath()));
    file.open(QFile::ReadOnly);
    QTextStream reader(&file);
    int i = 0;
    while (!reader.atEnd()) {
        NchcGameGui* game = games.at(i);
        game->updateAwayName(reader.readLine());
        game->setAwayScore(reader.readLine());
        game->updateHomeName(reader.readLine());
        game->setHomeScore(reader.readLine());
        QString conf = reader.readLine();
        game->setConf(conf == "True");
        game->setTimeAndPd(reader.readLine());
        i ++;
        game = games.at(i);
        game->updateAwayName(reader.readLine());
        game->setAwayScore(reader.readLine());
        game->updateHomeName(reader.readLine());
        game->setHomeScore(reader.readLine());
        conf = reader.readLine();
        game->setConf(conf == "True");
        game->setTimeAndPd(reader.readLine());
        i ++;

    }

}

void NchcScoreboardGui::saveGames()
{
    QFile file(MiamiAllAccessHockey::getAppDirPath() + "/" + QDate::currentDate().toString("MMM.dd") + ".maa");
    file.open(QFile::WriteOnly);
    QTextStream writer(&file);
    for (int i = 0; i < games.size(); i ++) {
        NchcGameGui* game = games.at(i);
        if (!game->getAway().isEmpty()) {
            writer << game->getAway() << endl;
            writer << game->getAwayScore() << endl;
            writer << game->getHome() << endl;
            writer << game->getHomeScore() << endl;
            writer << (game->isConf() ? "True"  : "False") << endl;
            writer << game->getTimeAndPd() << endl;
        }
    }
    file.close();
}

void NchcScoreboardGui::submitAndShow()
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
    }
    graphic->setFridayGames(friday);
    graphic->setSaturdayGames(saturday);
    graphic->setLeftHeader(fridayHeader.text());
    graphic->setRightHeader(saturdayHeader.text());
    graphic->showImg();
}
