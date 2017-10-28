#include "PeriodData.h"

PeriodData::PeriodData(QString oScore, QString mScore)
{
    oppScore = oScore;
    ownScore = mScore;
}

QString PeriodData::getOppScore() const
{
    return oppScore;
}

void PeriodData::setOppScore(const QString &value)
{
    oppScore = value;
}

QString PeriodData::getOwnScore() const
{
    return ownScore;
}

void PeriodData::setOwnScore(const QString &value)
{
    ownScore = value;
}

