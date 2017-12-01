#include "SeasonXMLHandler.h"
#include <QString>

#include <QDomDocument>
#include <QFile>
#include <QXmlStreamWriter>
#include <QTextStream>


SeasonXMLHandler::SeasonXMLHandler(HockeyTeam* t) {
    team = t;
    inPlayer = inTotals = inOpponent = foundGoalie =  false;
}

void SeasonXMLHandler::parseFile(QString filename, bool emitSignal)
{
    QDomDocument doc;
    QFile file(filename);
    try {
        if (!file.open(QIODevice::ReadWrite) || !doc.setContent(&file)) {
            return;
        } else {
           team->clearRoster();
           team->clearGameHistory();
           team->clearPeriodData();
        }
        QDomElement totals = doc.elementsByTagName("hkseas").item(0).firstChildElement("totals");
        QDomElement ppStats = totals.firstChildElement("powerplay");
        team->setPpg(ppStats.attribute("ppg").toInt());
        team->setPpopp(ppStats.attribute("ppopp").toInt());
        team->setPk(ppStats.attribute("pk").toInt());
        team->setPkopp(ppStats.attribute("pkopp").toInt());
        QDomNodeList players = doc.elementsByTagName("player");
        for (int i = 0; i < players.size(); i++) {
            QDomElement playerData = players.item(i).toElement();
            HockeyPlayer player;
            if (playerData.attribute("name").toUpper() != "TEAM") {
                // Get player vitals
                player.setName(this->correctName(playerData.attribute("name")));
                player.setUni(playerData.attribute("uni"));
                player.setYear(playerData.attribute("year"));
                player.setGp(playerData.attribute("gp").toInt());
                // Shots data
                QDomElement shots= playerData.firstChildElement("shots");
                player.setGoals(shots.attribute("g").toInt());
                player.setAssists(shots.attribute("a").toInt());
                player.setPts(shots.attribute("pts").toInt());
                QDomElement penalty = playerData.firstChildElement("penalty");
                player.setPenalties(penalty.attribute("count").toInt());
                player.setPim(penalty.attribute("minutes").toInt());
                // Misc
                // TODO if we want more data from this element, save element
                player.setPlusMinus(playerData.firstChildElement("misc").attribute("plusminus"));
                // Check for goalie
                if (!playerData.firstChildElement("goalie").isNull()) {
                    QDomElement goalie=playerData.firstChildElement("goalie");
                    player.setGa(goalie.attribute("ga").toInt());
                    player.setSaves(goalie.attribute("saves").toInt());
                    player.setGaavg(goalie.attribute("gaavg"));
                    player.setWins(goalie.attribute("w").toInt());
                    player.setLosses(goalie.attribute("l").toInt());
                } else {
                    player.setGa(-1);
                    player.setSaves(-1);
                    player.setShotsFaced(-1);
                    player.setWins(-1);
                    player.setLosses(-1);
                    player.setGaavg("NG");
                }
                team->addPlayer(player);
            }
        }

        QDomElement periods = doc.firstChildElement("periods");
        for(int i = 0; i < periods.elementsByTagName("period").count(); i++) {
            QDomElement period = periods.elementsByTagName("period").item(i).toElement();
            team->addPeriod(PeriodData(period.attribute("ownscore"),period.attribute("oppscore")));
        }

        QDomElement games = doc.firstChildElement("games");
        for(int i = 0; i < games.elementsByTagName("game").count(); i++) {
            QDomElement game = games.elementsByTagName("game").item(i).toElement();
            team->addGame(GameHistory(game.attribute("oppname"),game.attribute("oppscore"),
                                      game.attribute("ownscore"),game.attribute("periods"),
                                      game.attribute("date"),game.attribute("homeaway")));
        }
        file.close();
        if (emitSignal) {
            emit team->rosterChanged();
        }
    } catch (...) {

    }
}

bool SeasonXMLHandler::startElement(const QString& namespaceURI,
                                    const QString& localName,
                                    const QString& qName,
                                    const QXmlAttributes& atts) {
    if (qName == "totals") {
        inTotals = true;
    }
    else if (qName == "opponent") {
        inOpponent = true;
    }

    else if (qName == "powerplay" && inTotals) {
        team->setPpg(atts.value("ppg").toInt());
        team->setPpopp(atts.value("ppopp").toInt());
        team->setPk(atts.value("pk").toInt());
        team->setPkopp(atts.value("pkopp").toInt());
    }

    else if (qName == "player") {
        currPlayer = new HockeyPlayer();
        inPlayer = true;
        currPlayer->setName(correctName(atts.value("name")));
        currPlayer->setUni(atts.value("uni"));
        currPlayer->setYear(atts.value("year"));
        currPlayer->setGp(atts.value("gp").toInt());
    }

    else if (qName == "shots" && inPlayer) {
        currPlayer->setGoals(atts.value("g").toInt());
        currPlayer->setAssists(atts.value("a").toInt());
        currPlayer->setPts(atts.value("pts").toInt());
    }

    else if (qName == "penalty" && inPlayer) {
        currPlayer->setPenalties(atts.value("count").toInt());
        currPlayer->setPim(atts.value("minutes").toInt());
    }

    else if (qName == "misc" && inPlayer) {
        currPlayer->setPlusMinus(atts.value("plusminus"));
    }

    else if (qName == "goalie" && inPlayer) {
        foundGoalie = true;
        currPlayer->setGa(atts.value("ga").toInt());
        currPlayer->setSaves(atts.value("saves").toInt());
        currPlayer->setGaavg(atts.value("gaavg"));
        currPlayer->setWins(atts.value("w").toInt());
        currPlayer->setLosses(atts.value("l").toInt());

    }
    else if (qName == "period") {
        team->addPeriod(PeriodData(atts.value("oppscore"), atts.value("ownscore")));
    }
    else if (qName == "game") {
        team->addGame(GameHistory(atts.value("oppname"),atts.value("oppscore"),
                                  atts.value("ownscore"),atts.value("periods"),
                                  atts.value("date"),atts.value("homeaway")));
    }

    return true;
}

bool SeasonXMLHandler::endElement(const QString& namespaceURI, const QString& localName, const QString& qName) {
    if (qName == "player") {
        if (!foundGoalie) {
            currPlayer->setGa(-1);
            currPlayer->setSaves(-1);
            currPlayer->setShotsFaced(-1);
            currPlayer->setWins(-1);
            currPlayer->setLosses(-1);
            currPlayer->setGaavg("NG");
        }
        team->addPlayer(*currPlayer);
        inPlayer = false;
        foundGoalie = false;
    }

    else if (qName == "totals") {
        inTotals = false;
    }

    else if (qName == "opponent") {
        inOpponent = false;
    }

    return true;
}

bool SeasonXMLHandler::characters(const QString& str)
{
    return true;
}

bool SeasonXMLHandler::fatalError(const QXmlParseException& exception)
{
    return false;
}

QString
SeasonXMLHandler::correctName(QString name) {
    if (!name.contains(",")) {
        name = name;
    }
    else if (name.contains(", ")){
        std::string goodName = name.toStdString();
        QString firstName = QString::fromStdString(goodName.substr(goodName.find(" ") + 1, goodName.length()));
        QString lastName = QString::fromStdString(goodName.substr(0, goodName.find(",")));
        name = firstName + " " + lastName;
    }
    else if (name.contains(",")) {
        std::string goodName = name.toStdString();
        QString firstName = QString::fromStdString(goodName.substr(goodName.find(",") + 1, goodName.length()));
        QString lastName = QString::fromStdString(goodName.substr(0, goodName.find(",")));
        name = firstName + " " + lastName;
    }
    return name;
}
