#ifndef COMPARISONCREATOR_H
#define COMPARISONCREATOR_H

#include <QObject>
#include <QWidget>

#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

#include "HockeyGame.h"
#include "ComparisonGraphic.h"

class ComparisonCreator : public QWidget
{
    Q_OBJECT
public:
    ComparisonCreator(HockeyGame* game, bool standAlone=true, QWidget *parent = 0);

    QGridLayout* getLayout(bool standAlone);

signals:

public slots:

protected slots:
    void submitCompGraphic();
    void clearFields();

protected:
    QComboBox colorSelector;
    QLineEdit topLabel, botLabel, topStat1, botStat1, topStat2, botStat2, statLabel;
    QPushButton clear, show, previewButton;

    ComparisonGraphic* graphic;
};

#endif // COMPARISONCREATOR_H
