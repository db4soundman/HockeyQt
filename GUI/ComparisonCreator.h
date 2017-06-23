#ifndef COMPARISONCREATOR_H
#define COMPARISONCREATOR_H

#include <QObject>
#include <QWidget>

#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

#include "HockeyGame.h"
#include "ComparisonGraphic.h"

class ComparisonCreator : public QWidget
{
    Q_OBJECT
public:
    ComparisonCreator(HockeyGame* game,QWidget *parent = 0);

signals:

public slots:

private slots:
    void submitCompGraphic();
    void clearFields();

private:
    QComboBox colorSelector;
    QLineEdit topLabel, botLabel, topStat1, botStat1, topStat2, botStat2, statLabel;
    QPushButton clear, show;

    ComparisonGraphic* graphic;
};

#endif // COMPARISONCREATOR_H
