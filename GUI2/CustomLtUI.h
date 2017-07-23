#ifndef CUSTOMLTUI_H
#define CUSTOMLTUI_H

#include <QObject>
#include <QPixmap>
#include <QLabel>
#include "LowerThirdCreator.h"

class CustomLtUI : public LowerThirdCreator
{
    Q_OBJECT
public:
    CustomLtUI(LowerThird* lt, LowerThird *previewLt);

public slots:
    void updatePreview();

private:
    LowerThird * previewLt;
    QPixmap previewPixmap;
    QLabel preview;

};

#endif // CUSTOMLTUI_H
