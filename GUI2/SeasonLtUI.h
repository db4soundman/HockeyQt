#ifndef SEASONLTUI_H
#define SEASONLTUI_H
#include <QObject>
#include "HomeStatControl.h"
#include <QPixmap>
#include <QLabel>
class SeasonLtUI : public HomeStatControl
{
    Q_OBJECT
public:
    SeasonLtUI(HockeyGame* game, bool home);

public slots:
    void updatePreview();

private:
    QLabel seasonPreview, gamePreview;
    QPixmap seasonPixmap, gamePixmap;
    HockeyGame* game;
};

#endif // SEASONLTUI_H
