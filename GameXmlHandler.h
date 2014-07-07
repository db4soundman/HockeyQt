#ifndef GAMEXMLHANDLER_H
#define GAMEXMLHANDLER_H

#include <QXmlDefaultHandler>
#include "HockeyTeam.h"

class GameXmlHandler : public QXmlDefaultHandler
{
public:
    GameXmlHandler(HockeyTeam* t);
    bool startElement(const QString &namespaceURI, const QString &localName,
                      const QString &qName, const QXmlAttributes &atts);
    bool endElement(const QString &namespaceURI, const QString &localName,
                    const QString &qName);
    bool characters(const QString &str);
    bool fatalError(const QXmlParseException &exception);

private:
    HockeyTeam* team;
    HockeyPlayer currPlayer;

    QString correctName(QString name);
};


#endif // GAMEXMLHANDLER_H
