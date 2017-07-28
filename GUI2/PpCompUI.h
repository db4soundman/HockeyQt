#ifndef PPCOMPUI_H
#define PPCOMPUI_H

#include <QObject>
#include "PowerPlayUpdaters.h"
#include <QLabel>
#include <QPixmap>
#include "ComparisonCreator.h"

class PpCompUI : public PowerPlayUpdaters
{
    Q_OBJECT
public:
    PpCompUI(HockeyGame *game);

public slots:
    void updatePreview();

private:
    QLabel previewHomePp, previewAwayPp;
    QPixmap homePpPixmap, awayPpPixmap;
    ComparisonGraphic* comparisonGraphic;

    HockeyGame* game;
};

#endif // PPCOMPUI_H
