#include "GameXmlUpdater.h"

GameXmlUpdater::GameXmlUpdater(HockeyGame* game, HockeyTeam* awayTeam, HockeyTeam* homeTeam, QString fileName) :
    file(fileName) {
    this->game = game;
    this->awayTeam = awayTeam;
    this->homeTeam = homeTeam;

    inAwayTeam = inTotals = inPlayer = false;
}

bool
GameXmlUpdater::startElement(const QString& namespaceURI,
                                  const QString& localName,
                                  const QString& qName,
                                  const QXmlAttributes& atts) {
    if (qName == "team") {
        if (atts.value("vh") == "V") {
            inAwayTeam = true;
        }
    }

    else if (qName == "totals") {
        inTotals = true;
    }

    else if (qName == "shots" && inTotals) {
        if (inAwayTeam) {
            game->setAwaySOG(atts.value("sh").toInt());
        }
        else {
            game->setHomeSOG(atts.value("sh").toInt());
        }
    }

    else if (qName == "player" && atts.value("uni") != "TM") {
        inPlayer = true;
        if (atts.value("gp") == "1") {
            curPlayer = inAwayTeam ? awayTeam->getPlayerByNumber(atts.value("uni")) :
                                     homeTeam->getPlayerByNumber(atts.value("uni"));
        }
        else {
            curPlayer = NULL;
        }
    }

    else if (curPlayer != NULL && inPlayer) {
        if (qName == "shots") {
            curPlayer->setAssistsToday(atts.value("a").toInt());
            curPlayer->setGoalsToday(atts.value("g").toInt());
        }
        else if (qName == "penalty") {
            curPlayer->setPenaltiesToday(atts.value("count").toInt());
            curPlayer->setPimToday(atts.value("minutes").toInt());
        }
        else if (qName == "goalie" ) {
            curPlayer->setGaToday(atts.value("ga").toInt());
            curPlayer->setSavesToday(atts.value("saves").toInt());
            curPlayer->setShotsFacedToday(atts.value("ga").toInt() + atts.value("saves").toInt());
        }
    }

    return true;
}

bool GameXmlUpdater::endElement(const QString& namespaceURI, const QString& localName, const QString& qName) {

    if (qName == "totals") {
        inTotals = false;
    }

    else if (qName == "team") {
        inAwayTeam = false;
    }

    else if (qName == "player") {
        inPlayer = false;
    }

    return true;
}

bool GameXmlUpdater::characters(const QString& str)
{

    return true;
}

bool GameXmlUpdater::fatalError(const QXmlParseException& exception)
{
    return false;
}
