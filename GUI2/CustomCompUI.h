#ifndef CUSTOMCOMPUI_H
#define CUSTOMCOMPUI_H

#include <QObject>
#include "ComparisonCreator.h"
#include <QLabel>
#include <QPixmap>

class CustomCompUI : public ComparisonCreator
{
    Q_OBJECT
public:
    CustomCompUI(HockeyGame* game);

public slots:
    void updatePreview();

private:
    HockeyGame* game;
    QLabel preview;
    QPixmap previewPixmap;
    ComparisonGraphic* previewGraphic;
};

#endif // CUSTOMCOMPUI_H
