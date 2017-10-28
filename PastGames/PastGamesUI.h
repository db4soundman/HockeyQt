#ifndef PASTGAMESUI_H
#define PASTGAMESUI_H

#include <QObject>
#include <QWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPushButton>
#include <QSpinBox>
#include "HockeyTeam.h"
#include "PastGamesGraphic.h"

class PastGamesUI : public QWidget
{
    Q_OBJECT
public:
    explicit PastGamesUI(PastGamesGraphic* graphic, HockeyTeam* team, bool home,QWidget *parent = nullptr);


signals:
    void show(bool homeTeam, int numToShow);

private slots:
    void prepareToShow();

private:
    QPushButton showButton;
    QSpinBox numToShow;
    bool home;
};

#endif // PASTGAMESUI_H
