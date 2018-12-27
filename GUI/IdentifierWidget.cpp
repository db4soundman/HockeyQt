#include "IdentifierWidget.h"
#include "globals.h"

#include <QVBoxLayout>
IdentifierWidget::IdentifierWidget(IdentifierL3rd *graphic)
{
    talent1.setText("Talent 1: " + Globals::announcer1 +"\t" + Globals::twitter1);
    talent2.setText("Talent 2: " + Globals::announcer2 +"\t" + Globals::twitter2);
    talent3.setText("Talent 3: " + Globals::announcer3 +"\t" + Globals::twitter3);

    pxpLeft.setText("PxP, Color");
    pxpRight.setText("Color, PxP");

    QVBoxLayout* myLayout = new QVBoxLayout();
    myLayout->addWidget(&talent1);
    myLayout->addWidget(&talent2);
    myLayout->addWidget(&talent3);
    myLayout->addWidget(&pxpLeft);
    myLayout->addWidget(&pxpRight);

    setLayout(myLayout);

    connect(this, SIGNAL(showIdGraphic(QStringList,QStringList)), graphic, SLOT(showId(QStringList,QStringList)));
    connect(&pxpLeft, SIGNAL(clicked(bool)), this, SLOT(showPxPLeft()));
    connect(&pxpRight, SIGNAL(clicked(bool)), this, SLOT(showPxpRight()));

}

void IdentifierWidget::showPxPLeft()
{
    QStringList names, twitter;
    if (Globals::announcer3.isEmpty()) {
        names << Globals::announcer1;
        twitter << Globals::twitter1;

        twitter << Globals::hashtag;

        if(!Globals::announcer2.isEmpty()) {
            names << Globals::announcer2;
            twitter << Globals::twitter2;
        }
    } else {
        QStringList names, twitter;
        names << Globals::announcer1 << Globals::announcer2 << Globals::announcer3;
        twitter << Globals::twitter1 << Globals::twitter2 << Globals::twitter3;

    }

    emit showIdGraphic(names, twitter);
}

void IdentifierWidget::showPxpRight()
{
    QStringList names, twitter;
    if (Globals::announcer3.isEmpty()) {
        names << Globals::announcer2;
        twitter << Globals::twitter2;

        twitter << Globals::hashtag;

        if(!Globals::announcer2.isEmpty()) {
            names << Globals::announcer1;
            twitter << Globals::twitter1;
        }
    } else {
        QStringList names, twitter;
        names << Globals::announcer3 << Globals::announcer2 << Globals::announcer1;
        twitter << Globals::twitter3 << Globals::twitter2 << Globals::twitter1;

    }

    emit showIdGraphic(names, twitter);
}
