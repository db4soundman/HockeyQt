#ifndef TEXTUALROSTERINPUT_H
#define TEXTUALROSTERINPUT_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QRegularExpression>

#include "HockeyTeam.h"
class TextualRosterInput : public QWidget
{
    Q_OBJECT
public:
    explicit TextualRosterInput(HockeyTeam* myTeam,QWidget *parent = nullptr);

signals:


public slots:
    void parseRoster();
    void convertText();

private:
    QPushButton submit, convert;
    QTextEdit rosterInput;
    QRegularExpression numberName, nameNumber;

    HockeyTeam* team;
};

#endif // TEXTUALROSTERINPUT_H
