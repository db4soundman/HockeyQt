#ifndef SOGUI_H
#define SOGUI_H

#include <QObject>
#include "SogControl.h"
#include <QLabel>

class SogUI : public SogControl
{
    Q_OBJECT
public:
    SogUI(HockeyGame* game);


public slots:
    void updatePreview();

private:
    QLabel compPreview;
    QPixmap previewPixmap;
    HockeyGame* game;

};

#endif // SOGUI_H
