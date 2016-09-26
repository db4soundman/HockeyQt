#ifndef SCORECONTROL_H
#define SCORECONTROL_H

#include <QGroupBox>
#include <QPushButton>
#include "HockeyGame.h"

class ScoreControl : public QGroupBox {
    Q_OBJECT
public:
    ScoreControl(HockeyGame* game);

public slots:
    void disableControls();
    void enableControls();

private:
    QPushButton ag, hg, am, hm;
};

#endif // SCORECONTROL_H
