#include "SeasonXMLHandler.h"
#include <QString>

SeasonXMLHandler::SeasonXMLHandler(HockeyTeam* t) {
    team = t;
    inPlayer = inTotals = inOpponent = foundGoalie =  false;
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
        team->addPlayer(currPlayer);
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
        return name.toUpper();
    }
    QString goodName = (name.mid(name.indexOf(",")) + " " +
                        name.left(name.indexOf(",")));
    return goodName.toUpper().trimmed();
}
