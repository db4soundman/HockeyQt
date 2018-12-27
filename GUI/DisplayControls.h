#ifndef DISPLAYCONTROLS_H
#define DISPLAYCONTROLS_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include "HockeyGame.h"
#include "StandingsGraphic.h"
#include "CommercialGraphic.h"
#include "NchcScoreboardGraphic.h"
#include "schedulegraphic.h"
#include "ComparisonGraphic.h"
#include "PastGamesGraphic.h"
#include "Ticker.h"
#include "identifierl3rd.h"

class DisplayControls : public QWidget {
    Q_OBJECT
public:
    DisplayControls(HockeyGame* game, StandingsGraphic* graphic,
                    CommercialGraphic* comGraphic, NchcScoreboardGraphic* sbGraphic,
                    ScheduleGraphic* schedGraphic, ComparisonGraphic* comparisonGraphic,
                    Ticker *ticker, IdentifierL3rd *idL3rd, PastGamesGraphic* pastGamesGraphic = NULL );

public slots:
    void prepareCustomText();

signals:
    void showCustomText(QString text);

private:
    QLineEdit customtext;
    QPushButton customButton, announcersButton, commericalButton, sbButton, hideButton, sponsorButton, hideLT;
    QString sponsorText;
};

#endif // DISPLAYCONTROLS_H
