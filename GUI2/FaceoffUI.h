#ifndef FACEOFFUI_H
#define FACEOFFUI_H

#include <QObject>
#include "FaceoffControl.h"

class FaceoffUI :  public FaceoffControl
{
    Q_OBJECT
public:
    FaceoffUI(HockeyGame *game);

public slots:
    void updatePreview();

private:
    QLabel preview;
    QPixmap previewPixmap;
    HockeyGame* game;
};

#endif // FACEOFFUI_H
