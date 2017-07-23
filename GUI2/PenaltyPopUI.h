#ifndef PENALTYPOPUI_H
#define PENALTYPOPUI_H
#include <QObject>
#include "PenaltyDisplay.h"
#include <QLabel>

class PenaltyPopUI : public PenaltyDisplay
{
    Q_OBJECT
public:
    PenaltyPopUI(HockeyGame* game, bool homeTeam);


public slots:
    void updatePreviewText();


private:
    HockeyGame* game;
    bool homeTeam;

    QLabel previewText;
};

#endif // PENALTYPOPUI_H
