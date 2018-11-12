#include "PenaltyUI.h"
#include <QVBoxLayout>

PenaltyUI::PenaltyUI(HockeyGame *game, bool home, QWidget *parent):
    QWidget(parent),
    penaltyUi(game, home), compUi(game)
{
    QVBoxLayout* myLayout = new QVBoxLayout();
    myLayout->addWidget(&penaltyUi);
    myLayout->addWidget(&compUi);

    setLayout(myLayout);
}
