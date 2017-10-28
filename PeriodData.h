#ifndef PERIODDATA_H
#define PERIODDATA_H

#include <QObject>

class PeriodData
{
public:
    PeriodData(QString oScore, QString mScore);

    QString getOppScore() const;
    void setOppScore(const QString &value);

    QString getOwnScore() const;
    void setOwnScore(const QString &value);

private:
    QString oppScore, ownScore;
};

#endif // PERIODDATA_H
