#ifndef GLOBALS_H
#define GLOBALS_H

#include <QString>
#include <QColor>


class Globals
{
public:
    Globals();

    static QString announcer1, announcer2, announcer3, twitter1, twitter2, twitter3, hashtag, networkLogoPath;
    static QColor white, black, nchcBrandingTop, nchcBrandingBottom, tvBrandingTop, tvBrandingBottom;
    static bool onTv;
};

#endif // GLOBALS_H
