#include "Scoreboard.h"
#include <QGraphicsScene>
#include <QMessageBox>
#include <QFontMetrics>
#include <QFontInfo>

#define GRADIENT_LEVEL .5
#define AWAY_PP 1
#define HOME_PP 2
#define NEUTRAL 3

Scoreboard::Scoreboard(QColor awayCol, QColor homeCol, QString awayTeam, QString homeTeam,
                       QString sponsorText, Clock* clock, QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent), homeColor(homeCol), awayColor(awayCol) {
    QFont font("Arial", 34, QFont::Bold);
    QFont sponsorFont("Arial", 24, QFont::Bold);
#ifdef Q_OS_OSX
    font.setPointSize(40);
    sponsorFont.setPointSize(28);
    #endif

    defaultSponsorText = sponsorFont;
    show = true;
    setPixmap(QPixmap(":/images/Scoreboard.png"));
    ppBar = new QPixmap(":/images/ppBar.png");
    topBar = new QPixmap(":/images/statbar.png");
    networkLogo = new QPixmap(":/images/M.png");
    awayName = new QGraphicsTextItem(awayTeam);
    homeName = new QGraphicsTextItem(homeTeam);
    awayName->setFont(font);
    homeName->setFont(font);
    awayScore = new QGraphicsTextItem("0");
    awayScore->setFont(font);
    homeScore = new QGraphicsTextItem("0");
    homeScore->setFont(font);
    topBarText = new QGraphicsTextItem(sponsorText);
    this->sponsorText = sponsorText;
    topBarText->setFont(defaultSponsorText);

    homeGradient.setStart(0, 6);
    awayGradient.setStart(0, 6);
    homeGradient.setFinalStop(0,43);
    awayGradient.setFinalStop(0,43);
    prepareColor();
    // penalty gradient
    penaltyGradient.setStart(0, 54);
    penaltyGradient.setFinalStop(0, 92);
    penaltyGradient.setColorAt(0, QColor(255, 255, 0));
    penaltyGradient.setColorAt(1, QColor(188, 188, 0));
    penalty = false;
    showPP = false;
    sponsor = true;
    showPdAndClock = true;
    showClock = true;
    //centeredTimeText = "BETA";

    this->clock = clock;
    connect(clock, SIGNAL(clockUpdated()), this, SLOT(updateClock()));

}

void
Scoreboard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (show) {
        painter->drawPixmap(0,-49, *topBar);
        painter->drawPixmap(0, 0, this->pixmap());
        painter->drawPixmap(34, 4, 73, 46, *networkLogo);
        //Clock - Game time...draw clock first since default color is black
        painter->setFont(homeName->font());
        if (showPdAndClock) {
            painter->drawText(838, 3, 247, 50, Qt::AlignVCenter, period);
            painter->drawText(833, 3, 242, 50, Qt::AlignRight | Qt::AlignVCenter,
                              showClock? clock->toString() : "INT");
        }
        else {
            painter->drawText(833, 3, 247, 50, Qt::AlignCenter, centeredTimeText);
        }
        // Away text
        painter->fillRect(115, 6, 260, 42, awayGradient );
        painter->setFont(awayName->font());
        painter->setPen(QColor(255, 255, 255));
        painter->drawText(118, 6, 260, 42, Qt::AlignVCenter, awayName->toPlainText());
        // Away Score
        painter->setFont(awayScore->font());
        painter->drawText(374, 6, 78, 44, Qt::AlignCenter, awayScore->toPlainText());

        // Home Text
        painter->fillRect(470, 6, 260, 42, homeGradient );
        painter->setFont(homeName->font());
        painter->drawText(475, 6, 260, 42, Qt::AlignVCenter, homeName->toPlainText());
        // Home Score
        painter->setFont(homeScore->font());
        painter->drawText(728, 6, 78, 44, Qt::AlignCenter, homeScore->toPlainText());
        if (sponsor) {
            //StatBarText
            painter->setPen(QColor(255, 255, 255));
            painter->setFont(topBarText->font());
            painter->drawText(0, -49, 1102, 49, Qt::AlignCenter, topBarText->toPlainText());
        }

        if (showPP) {
            painter->setPen(QColor(255, 255, 255));
            painter->setFont(defaultSponsorText);
            // Away ppbar
            if(awayPP) {
                painter->drawPixmap(112,52, *ppBar);
                painter->drawText(120, 52, 345, 38, Qt::AlignLeft | Qt::AlignVCenter, ppDescription);
                painter->drawText(120, 52, 331, 38, Qt::AlignRight | Qt::AlignVCenter, ppClock->toStringPP());
            }
            //Home ppbar
            else if (homePP) {
                painter->drawPixmap(466,52, *ppBar);
                painter->drawText(474, 52, 345, 38, Qt::AlignLeft | Qt::AlignVCenter, ppDescription);
                painter->drawText(474, 52, 331, 38, Qt::AlignRight | Qt::AlignVCenter, ppClock->toStringPP());
            }
            //Neutral
            else if (neutralPP){
                painter->drawPixmap(833,54,247,38, *ppBar );
                painter->drawText(841, 54, 247, 38, Qt::AlignLeft | Qt::AlignVCenter, ppDescription);
                painter->drawText(833, 54, 239, 38, Qt::AlignRight | Qt::AlignVCenter, ppClock->toStringPP());
            }
        }

        if (penalty) {
            // Penalty Indicator
            painter->fillRect(833, 52, 247, 38, penaltyGradient);
            painter->setPen(QColor(0,0,0));
            painter->setFont(defaultSponsorText);
            painter->drawText(833,54,247,38, Qt::AlignCenter, "PENALTY");
        }

    }
}

void
Scoreboard::prepareColor() {
    int red, green, blue;
    red = -1*homeColor.red() *GRADIENT_LEVEL + homeColor.red();
    green = -1*homeColor.green() *GRADIENT_LEVEL + homeColor.green();
    blue = -1*homeColor.blue() *GRADIENT_LEVEL + homeColor.blue();

    QColor end(red, green, blue);
    homeGradient.setColorAt(.4, homeColor);
    homeGradient.setColorAt(.6, homeColor);
    homeGradient.setColorAt(1, end);
    homeGradient.setColorAt(0, end);

    red = -1*awayColor.red() *GRADIENT_LEVEL + awayColor.red();
    green = -1*awayColor.green() *GRADIENT_LEVEL + awayColor.green();
    blue = -1*awayColor.blue() *GRADIENT_LEVEL + awayColor.blue();
    QColor end2(red, green, blue);
    awayGradient.setColorAt(.4, awayColor);
    awayGradient.setColorAt(.6, awayColor);
    awayGradient.setColorAt(1, end2);
    awayGradient.setColorAt(0, end2);

}

void
Scoreboard::togglePenalty() {
    penalty = !penalty;
    scene()->update();
}

void
Scoreboard::updateClock() {
    scene()->update();
}

void
Scoreboard::preparePowerplayClock(int pos, Clock *clock, QString description) {
    // Clear off current board.
    awayPP = false;
    homePP = false;
    neutralPP = false;
    ppClock = clock;
    switch (pos) {
    case AWAY_PP:
        awayPP = true;
        break;
    case HOME_PP:
        homePP = true;
        break;
    case NEUTRAL:
        neutralPP = true;
        break;
    default:
        break;
    }
    ppDescription = description;
        scene()->update();
}

void
Scoreboard::updateAwayScore(int score) {
    QString scoreText;
    awayScore->setPlainText(scoreText.setNum(score, 10));
    scene()->update();
}

void
Scoreboard::updateHomeScore(int score) {
    QString str;
    homeScore->setPlainText(str.setNum(score, 10));
    scene()->update();
}

void
Scoreboard::updatePeriod(int pd) {
    switch (pd) {
    case 1:
        period = "1st";
        break;
    case 2:
        period = "2nd";
        break;
    case 3:
        period = "3rd";
        break;
    case 4:
        period = "OT";
        showPdAndClock = true;
        break;
    case 5:
        centeredTimeText = "SHOOTOUT";
        showPdAndClock = false;
        break;
    default:
        period = "";
        break;
    }
    scene()->update();
}

void
Scoreboard::showPd() {
    showPdAndClock = true;
    scene()->update();
}

void
Scoreboard::final() {
    showPdAndClock = false;
    centeredTimeText = "FINAL";
    scene()->update();
}

void
Scoreboard::changeTopBarText(QString text) {
    topBarText->setPlainText(text);
    int subtraction = 1;
    topBarText->setFont(QFont("Arial", 34, QFont::Bold));
    QFontMetrics fontSize(topBarText->font());
    while (fontSize.width(text) > 1092) {
        QFont tempFont("Arial", defaultSponsorText.pointSize() - subtraction, QFont::Bold);
        subtraction++;
        topBarText->setFont(tempFont);
        QFontMetrics temp(topBarText->font());
        fontSize = temp;
    }
    scene()->update();
}

void
Scoreboard::displaySponsor() {
    topBarText->setPlainText(sponsorText);
    int subtraction = 1;
    topBarText->setFont(defaultSponsorText);
    QFontMetrics fontSize(topBarText->font());
    while (fontSize.width(sponsorText) > 1092) {
        QFont tempFont("Arial", defaultSponsorText.pointSize() - subtraction, QFont::Bold);
        //topBarText->font().setPointSize(defaultSponsorText.pointSize()-subtraction);
        subtraction++;
        topBarText->setFont(tempFont);
        QFontMetrics temp(topBarText->font());
        fontSize = temp;
    }
    scene()->update();
}

void
Scoreboard::toggleShowBoard() {
    show = !show;
    scene()->update();
}

void Scoreboard::togglePpClocks()
{
    showPP = !showPP;
    scene()->update();
}

void
Scoreboard::hideBoard() {
    show = false;
    scene()->update();
}

void
Scoreboard::intermission() {
    showPdAndClock = true;
    showClock = false;
    scene()->update();
}

void
Scoreboard::displayClock() {
    showPdAndClock = true;
    showClock = true;
    scene()->update();
}
