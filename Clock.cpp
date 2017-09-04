#include "Clock.h"
#include <QMessageBox>

Clock::Clock() {
    minutes = 20;
    regulationLength = 20;
    otLength = 5;
    seconds = 0;
    tenths = 1;
    gameClock = true;
    useSerial = false;
    serialPP = false;
}

Clock::Clock(int minutes, bool serialPowerPlay) {
    this->minutes = minutes;
    seconds = 0;
    tenths = 9;
    gameClock = false;
    serialPP=serialPowerPlay;
}

void
Clock::setClock(int m, int s, int t) {
    minutes = m;
    seconds = s;
    tenths = t;
    emit clockUpdated();
    if (minutes == 0 && seconds == 0 && tenths == 0)
        emit clockExpired();
}

void Clock::setClock(QString serialString)
{
    QTime time = serialString.contains(".") ? QTime::fromString(serialString, "m:ss.z") :
                                              QTime::fromString(serialString, "m:ss");
    if (!time.isValid()) {
        time = QTime::fromString(serialString, "s.z");
    }
    if (time != serial) {
        serial = time;

        emit clockUpdated();
    }
}

int
Clock::getTimeLeft() {
    return minutes*600 + seconds*10 + tenths;
}

QString
Clock::toString() {
    if (useSerial) {
        return serial.minute() > 0 ? serial.toString("m:ss") :
                                     serial.toString("ss.z").left(4);
    }
    else {
        QTime clock(0, minutes, seconds, tenths);
        if (minutes > 0)
            return clock.toString("m:ss");
        else
            return clock.toString("s.z");
    }
}

QString
Clock::toStringPP() {
    QTime clock(0, minutes, seconds, tenths);
    return clock.toString("m:ss");
}

QString Clock::toStringDebug()
{
    if (useSerial) {
        return serial.minute() > 0 ? serial.toString("m:ss") :
                                     serial.toString("ss.z").left(4);
    }
    else {
        if (getTimeLeft() > 0) {
            QTime clock(0, minutes, seconds, tenths);
            if (minutes > 0)
                return clock.toString("m:ss");
            else
                return clock.toString("s.z");
        } else return "";
    }
}

QString Clock::getTimeSincePdStarted()
{
    QTime clock(0, minutes, seconds);
    if (useSerial) {
        clock = serial;
    }
    QTime pd(0, 20);
    QTime retVal(0,0);
    retVal = retVal.addSecs(clock.secsTo(pd));
    return retVal.toString("m:ss");
}

QString Clock::getTimeSinceOtStarted()
{
    QTime clock(0, minutes, seconds);
    if (useSerial) {
        clock = serial;
    }
    QTime pd(0, 5);
    QTime retVal(0,0);
    retVal = retVal.addSecs(clock.secsTo(pd));
    return retVal.toString("m:ss");
}

void
Clock::tick() {
    if (useSerial) {
        serial = serial.addMSecs(-100);
        emit clockUpdated();
    }
    if (getTimeLeft() != 0) {
        tenths --;
        if (tenths < 0) {
            tenths = 9;
            seconds --;
        }
        if (seconds < 0 && minutes > 0) {
            seconds = 59;
            minutes --;
        }
        if (minutes == 0 && seconds == 0 && tenths == 0) {
            emit clockExpired();
        }
        if (gameClock || serialPP)
            emit clockUpdated();
    }
    else if (minutes == 0 && seconds == 0 && tenths == 0) {
        emit clockExpired();
    }
}

void
Clock::resetClock(bool ot) {
    if (!ot) {
        setClock(regulationLength, 0, 1);
    }
    else {
        setClock(otLength, 0, 1);
    }
}

void Clock::usingSerialClock()
{
    useSerial = true;
}

void Clock::noLongerUsingSerialClock()
{
    useSerial = false;
}
int Clock::getTenths() const
{
    return tenths;
}

void Clock::setTenths(int value)
{
    tenths = value;
}

int Clock::getSeconds() const
{
    return seconds;
}

void Clock::setSeconds(int value)
{
    seconds = value;
}

int Clock::getMinutes() const
{
    return minutes;
}

void Clock::setMinutes(int value)
{
    minutes = value;
}

bool Clock::isGameClock() const
{
    return gameClock;
}

void Clock::setGameClock(bool value)
{
    gameClock = value;
}

