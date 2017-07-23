#include "CustomCompUI.h"
#include <QVBoxLayout>
#include <QPainter>

CustomCompUI::CustomCompUI(HockeyGame *game):
    ComparisonCreator(game, false)
{
    QVBoxLayout* myLayout = new QVBoxLayout();
    myLayout->addLayout(getLayout(false));
    previewGraphic = game->getComparisonPreview();
    previewPixmap = QPixmap(previewGraphic->getWidth(), previewGraphic->getHeight());
    previewPixmap.fill(QColor(0,0,0,0));
    preview.setPixmap(previewPixmap.scaled(previewGraphic->getWidth()/2, previewGraphic->getHeight()/2));
    myLayout->addWidget(&preview);

    setLayout(myLayout);

    connect(&previewButton, SIGNAL(clicked(bool)), this, SLOT(updatePreview()));
}

void CustomCompUI::updatePreview()
{
    QList<QString> stats;
    stats.append(topStat1.text());
    stats.append(botStat1.text());
    if (!topStat2.text().trimmed().isEmpty()) {
        stats.append(topStat1.text());
        stats.append(topStat1.text());
    }
    previewGraphic->prepareComp(topLabel.text().trimmed(),botLabel.text().trimmed(),
                         stats, statLabel.text().trimmed(), colorSelector.currentIndex());
    previewPixmap.fill(QColor(0,0,0,0));
    QPainter painter(&previewPixmap);
    previewGraphic->paintPreview(&painter);
    preview.setPixmap(previewPixmap.scaled(previewGraphic->getWidth()/2, previewGraphic->getHeight()/2));

}
