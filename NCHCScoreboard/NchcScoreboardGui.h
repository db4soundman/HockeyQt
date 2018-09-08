#ifndef NCHCSCOREBOARDGUI_H
#define NCHCSCOREBOARDGUI_H

#include <QWidget>
#include <QLineEdit>
#include "NchcGameGui.h"
#include "NchcScoreboardGraphic.h"
#include "Ticker.h"

class NchcScoreboardGui : public QWidget {
    Q_OBJECT
public:
    NchcScoreboardGui(NchcScoreboardGraphic* grph, Ticker* ticker);

private slots:
    void loadGames();
    void saveGames();
    void submitAndShow();

private:
    QList<NchcGameGui*> games;
    NchcScoreboardGraphic* graphic;
    Ticker* ticker;
    QLineEdit fridayHeader, saturdayHeader;
};

#endif // NCHCSCOREBOARDGUI_H
