#ifndef NCHCSCOREBOARDGUI_H
#define NCHCSCOREBOARDGUI_H

#include <QWidget>
#include "NchcGameGui.h"
#include "NchcScoreboardGraphic.h"

class NchcScoreboardGui : public QWidget {
    Q_OBJECT
public:
    NchcScoreboardGui(NchcScoreboardGraphic* grph);

private slots:
    void loadGames();
    void saveGames();
    void submitGamesToGui();

private:
    QList<NchcGameGui*> games;
    NchcScoreboardGraphic* graphic;
};

#endif // NCHCSCOREBOARDGUI_H
