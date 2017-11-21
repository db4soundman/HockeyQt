#ifndef SEASONXMLHANDLER_H
#define SEASONXMLHANDLER_H

#include <QXmlDefaultHandler>
#include "HockeyTeam.h"

class SeasonXMLHandler : public QXmlDefaultHandler {
public:
    SeasonXMLHandler(HockeyTeam* t);

    void parseFile(QString filename);

    bool startElement(const QString &namespaceURI, const QString &localName,
                      const QString &qName, const QXmlAttributes &atts);
    bool endElement(const QString &namespaceURI, const QString &localName,
                    const QString &qName);
    bool characters(const QString &str);
    bool fatalError(const QXmlParseException &exception);

private:
    HockeyTeam* team;
    bool inPlayer, inTotals, inOpponent, foundGoalie;
    HockeyPlayer* currPlayer;

    QString correctName(QString name);
};

#endif // SEASONXMLHANDLER_H
