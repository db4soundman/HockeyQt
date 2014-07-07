#ifndef CLOCK_H
#define CLOCK_H

#include <QObject>
#include <QString>

class Clock : public QObject {
    Q_OBJECT
public:
    Clock();
    Clock(int minutes);

    void setClock(int m, int s, int t);

    QString toString();
    QString toStringPP();

    int getTimeLeft();

public slots:
    void tick();
    void resetClock(bool ot);

signals:
    void clockExpired();
    void clockUpdated();

private:
    int minutes, seconds, tenths;
    int regulationLength;
    int otLength;
    bool gameClock;
};

#endif // CLOCK_H
