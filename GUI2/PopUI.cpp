#include "PopUI.h"
#include <QVBoxLayout>

PopUI::PopUI(HockeyGame *game, bool home, QWidget *parent) : QWidget(parent),
    goalPopUi(game, home), penaltyPopUi(game, home),
    statPopUi(game, home)
{
    QVBoxLayout* myLayout = new QVBoxLayout();
    myLayout->addWidget(&statPopUi);
    myLayout->addWidget(&penaltyPopUi);
    myLayout->addWidget(&goalPopUi);

    setLayout(myLayout);
}
