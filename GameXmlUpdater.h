#ifndef GAMEXMLUPDATER_H
#define GAMEXMLUPDATER_H

#include <QXmlDefaultHandler>
#include <QFile>
#include "HockeyGame.h"
#include "HockeyTeam.h"

class GameXmlUpdater : public QXmlDefaultHandler
{
public:
    GameXmlUpdater(HockeyGame* game, HockeyTeam* awayTeam, HockeyTeam* homeTeam, QString fileName);

    bool startElement(const QString &namespaceURI, const QString &localName,
                      const QString &qName, const QXmlAttributes &atts);
    bool endElement(const QString &namespaceURI, const QString &localName,
                    const QString &qName);
    bool characters(const QString &str);
    bool fatalError(const QXmlParseException &exception);

    QFile* getFile();

private:
    HockeyTeam* awayTeam;
    HockeyTeam* homeTeam;
    HockeyGame* game;
    QFile file;
    HockeyPlayer* curPlayer;

    bool inTotals, inPlayer, inAwayTeam;
};

#endif // GAMEXMLUPDATER_H
