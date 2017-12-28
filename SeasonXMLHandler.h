#ifndef SEASONXMLHANDLER_H
#define SEASONXMLHANDLER_H

#include <QXmlDefaultHandler>
#include "HockeyTeam.h"

class SeasonXMLHandler : public QXmlDefaultHandler {
public:
    SeasonXMLHandler(HockeyTeam* t);

    void parseFile(QString filename, bool emitSignal=false);

    bool startElement(const QString &namespaceURI, const QString &localName,
                      const QString &qName, const QXmlAttributes &atts);
    bool endElement(const QString &namespaceURI, const QString &localName,
                    const QString &qName);
    bool characters(const QString &str);
    bool fatalError(const QXmlParseException &exception);

    static QString correctName(QString name);

private:
    HockeyTeam* team;
    bool inPlayer, inTotals, inOpponent, foundGoalie;
    HockeyPlayer* currPlayer;


};

#endif // SEASONXMLHANDLER_H
