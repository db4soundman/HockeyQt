#ifndef NCHCSCOREBOARDGUI_H
#define NCHCSCOREBOARDGUI_H

#include <QWidget>
#include <QLineEdit>
#include "NchcGameGui.h"
#include "NchcScoreboardGraphic.h"

class NchcScoreboardGui : public QWidget {
    Q_OBJECT
public:
    NchcScoreboardGui(NchcScoreboardGraphic* grph);

private slots:
    void loadGames();
    void saveGames();
    void submitAndShow();

private:
    QList<NchcGameGui*> games;
    NchcScoreboardGraphic* graphic;
    QLineEdit fridayHeader, saturdayHeader;
};

#endif // NCHCSCOREBOARDGUI_H
