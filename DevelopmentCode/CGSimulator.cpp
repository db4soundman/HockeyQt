#include "CGSimulator.h"
#include <QFormLayout>
CGSimulator::CGSimulator(QWidget *parent) : QWidget(parent)
{
    clockHasChanged= h1HasChanged= h2HasChanged= a1HasChanged= a2HasChanged = false;
    start.setText("Start CG");
    stop.setText("Stop CG");
    QVBoxLayout* masterLayout = new QVBoxLayout();
    clockStopped.setChecked(true);
    QFormLayout* myLayout = new QFormLayout();
    myLayout->addRow("Time", &time);
    myLayout->addRow("Away Score", &awayScore);
    myLayout->addRow("Home Score", &homeScore);
    myLayout->addRow("Clock Stopped", &clockStopped);
//    myLayout->addRow("Away TOL", &awayTol);
//    myLayout->addRow("Home TOL", &homeTol);
    myLayout->addRow("Away SOG", &aSog);
    myLayout->addRow("Home SOG", &hSog);
    myLayout->addRow("Away Ply 1", &awayP1);
    myLayout->addRow("Away Pen 1", &awayClock1);
    myLayout->addRow("Away Ply 2", &awayP2);
    myLayout->addRow("Away Pen 2", &awayClock2);
    myLayout->addRow("Home Ply 1", &homeP1);
    myLayout->addRow("Home Pen 1", &homeClock1);
    myLayout->addRow("Home Ply 2", &homeP2);
    myLayout->addRow("Home Pen 2", &homeClock2);

    masterLayout->addLayout(myLayout);
    masterLayout->addWidget(&start);
    masterLayout->addWidget(&stop);

    setLayout(masterLayout);

    timer.setInterval(100);
    connect(&timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    connect(&h1, SIGNAL(clockExpired()), this, SLOT(h1Expired()));
    connect(&h2, SIGNAL(clockExpired()), this, SLOT(h2Expired()));
    connect(&a1, SIGNAL(clockExpired()), this, SLOT(a1Expired()));
    connect(&a2, SIGNAL(clockExpired()), this, SLOT(a2Expired()));

    connect(&homeClock1, SIGNAL(textChanged(QString)), this, SLOT(h1Edited()));
    connect(&homeClock2, SIGNAL(textChanged(QString)), this, SLOT(h2Edited()));
    connect(&awayClock1, SIGNAL(textChanged(QString)), this, SLOT(a1Edited()));
    connect(&awayClock2, SIGNAL(textChanged(QString)), this, SLOT(a2Edited()));
    connect(&time, SIGNAL(textChanged(QString)), this, SLOT(clockEdited()));

    connect(&start, SIGNAL(clicked(bool)), this, SLOT(startClicked()));
    connect(&stop, SIGNAL(clicked(bool)), this, SLOT(stopClicked()));
    h1.setClock(0,0,0);
    h2.setClock(0,0,0);
    a1.setClock(0,0,0);
    a2.setClock(0,0,0);
    gameClock.usingSerialClock();
}

void CGSimulator::sendCgConnected()
{
    emit serialConnected();
}

void CGSimulator::handleTimeout()
{
    if (!clockStopped.isChecked()) {
        gameClock.tick();
        h1.tick();
        h2.tick();
        a1.tick();
        a2.tick();
    }
    QString output = " ";
    output += gameClock.toStringDebug().rightJustified(7,' ');
    output += clockStopped.isChecked() ? "s":" ";
    output += homeScore.text().rightJustified(2,'0');
    output += awayScore.text().rightJustified(2,'0');
    output += "11"; //home and away TOL
    output += hSog.text().rightJustified(2,'0');
    output += aSog.text().rightJustified(2,'0');
    output += " 1"; //period
    output += homeP1.text().rightJustified(2,h1.getTimeLeft() <= 0 ? ' ' : '0');
    output += h1.toStringPPDebug().rightJustified(5, ' ');
    output += homeP2.text().rightJustified(2,h2.getTimeLeft() <= 0 ? ' ' : '1');
    output += h2.toStringPPDebug().rightJustified(5, ' ');
    output += awayP1.text().rightJustified(2,a1.getTimeLeft() <= 0 ? ' ' : '0');
    output += a1.toStringPPDebug().rightJustified(5, ' ');
    output += awayP2.text().rightJustified(2,a2.getTimeLeft() <= 0 ? ' ' : '1');
    output += a2.toStringPPDebug().rightJustified(5, ' ');
    output += " "; // end character
    QByteArray data;
    data.append(output);
    emit dataReceived(data);
}

void CGSimulator::clockEdited()
{
    clockHasChanged = true;
}

void CGSimulator::h1Edited()
{
    h1HasChanged=true;
}

void CGSimulator::h2Edited()
{
    h2HasChanged=true;
}

void CGSimulator::a1Edited()
{
    a1HasChanged=true;
}

void CGSimulator::a2Edited()
{
    a2HasChanged=true;
}

void CGSimulator::h1Expired()
{
    homeP1.setText("");
}

void CGSimulator::h2Expired()
{
   homeP2.setText("");
}

void CGSimulator::a1Expired()
{
    awayP1.setText("");
}

void CGSimulator::a2Expired()
{
    awayP2.setText("");
}

void CGSimulator::startClicked()
{
    if (clockHasChanged) {
        gameClock.setClock(time.text());
    }
    if (h1HasChanged) {
        h1.setClockDebug(homeClock1.text());
    }
    if (a1HasChanged) {
        a1.setClockDebug(awayClock1.text());
    }
    if (h2HasChanged) {
        h2.setClockDebug(homeClock2.text());
    }
    if (a2HasChanged) {
        a2.setClockDebug(awayClock2.text());
    }
    clockHasChanged= h1HasChanged= h2HasChanged= a1HasChanged= a2HasChanged = false;
    timer.start();
}

void CGSimulator::stopClicked()
{
    timer.stop();
}
