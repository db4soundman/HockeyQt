#include "Scoreboard.h"
#include <QGraphicsScene>
#include <QMessageBox>
#include <QFontMetrics>
#include <QFontInfo>

#define TEAM_GRADIENT_LEVEL .1
#define SCOREBOARD_GRADIENT_LEVEL .3
#define AWAY_PP 1
#define HOME_PP 2
#define NEUTRAL 3
#define TEAM_NAME_WIDTH 310
#define RANK_WIDTH 50
#define TEAM_BOX_Y 2
#define TEAM_BOX_HEIGHT 40
#define V_TEAM_BOX_STARTX 100
#define H_TEAM_BOX_STARTX 500
#define LOGO_WIDTH 50
#define SCOREBOARD_WIDTH 1200
#define CLOCK_FIELD_X 920
#define CLOCK_FIELD_WIDTH 260
#define SCOREBOARD_HEIGHT 44
#define PP_BAR_HEIGHT 38
#define TOP_BAR_WIDTH (SCOREBOARD_WIDTH - 40)
#define TOP_BAR_Y -39

Scoreboard::Scoreboard(QColor awayCol, QColor homeCol, QString awayTeam, QString homeTeam,
                       QString sponsorText, Clock* clock, QString pAwayRank, QString pHomeRank, QString pawayLogo) :
    homeColor(homeCol), awayColor(awayCol) {
    QFont font("Arial", 28, QFont::Bold);
    QFont sponsorFont("Arial", 20, QFont::Bold);
#ifdef Q_OS_OSX
    font.setPointSize(40);
    sponsorFont.setPointSize(28);
    #endif

    defaultSponsorText = sponsorFont;
    show = false;
    setPixmap(QPixmap(":/images/Scoreboard.png"));
    ppBar = new QPixmap(":/images/ppBar.png");
    topBar = new QPixmap(":/images/ppBar.png");
    homeLogo = new QPixmap(":/images/M.png");
    awayLogo = new QPixmap(pawayLogo);

    *homeLogo = homeLogo->scaledToHeight(TEAM_BOX_HEIGHT, Qt::SmoothTransformation);
    if (homeLogo->width() > LOGO_WIDTH)
        *homeLogo = homeLogo->scaledToWidth(LOGO_WIDTH, Qt::SmoothTransformation);
    homeLogoOffset = (TEAM_BOX_HEIGHT - homeLogo->height()) / 2;

    *awayLogo = awayLogo->scaledToHeight(TEAM_BOX_HEIGHT, Qt::SmoothTransformation);
    if (awayLogo->width() > LOGO_WIDTH)
        *awayLogo = awayLogo->scaledToWidth(LOGO_WIDTH, Qt::SmoothTransformation);
    awayLogoOffset = (TEAM_BOX_HEIGHT - awayLogo->height()) / 2;


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

    homeGradient.setStart(0, TEAM_BOX_Y);
    awayGradient.setStart(0, TEAM_BOX_Y);
    homeGradient.setFinalStop(0,TEAM_BOX_HEIGHT);
    awayGradient.setFinalStop(0,TEAM_BOX_HEIGHT);
    mainGradient.setStart(0,0);
    mainGradient.setFinalStop(0, SCOREBOARD_HEIGHT);
    clockGradient.setStart(0,3);
    clockGradient.setFinalStop(0, SCOREBOARD_HEIGHT - 3);
    ppGradient.setStart(0, SCOREBOARD_HEIGHT);
    ppGradient.setFinalStop(0, 92);
    scoreGradient.setStart(0, TEAM_BOX_Y);
    scoreGradient.setFinalStop(0, TEAM_BOX_Y + 44);
    prepareColor();
    // penalty gradient
    penaltyGradient.setStart(0, SCOREBOARD_HEIGHT);
    penaltyGradient.setFinalStop(0, SCOREBOARD_HEIGHT + PP_BAR_HEIGHT);
    penaltyGradient.setColorAt(0, QColor(255, 255, 0));
    penaltyGradient.setColorAt(1, QColor(188, 188, 0));

    QFont rankFont("Arial", 20, QFont::Bold);
    awayRank = new QGraphicsTextItem(pAwayRank);
    homeRank = new QGraphicsTextItem(pHomeRank);
    awayRank->setFont(rankFont);
    homeRank->setFont(rankFont);
    awayRankOffset = homeRankOffset = LOGO_WIDTH;
    if (!awayRank->toPlainText().isEmpty()) {
        awayRankOffset += RANK_WIDTH;
    }

    if (!homeRank->toPlainText().isEmpty()) {
        homeRankOffset += RANK_WIDTH;
    }

    penalty = false;
    showPP = false;
    sponsor = true;
    showPdAndClock = true;
    showClock = true;

    this->clock = clock;
    connect(clock, SIGNAL(clockUpdated()), this, SLOT(updateClock()));
    prepareAwayName();

}

void
Scoreboard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (show) {
        painter->setBrush(*(new QBrush(mainGradient)));
        if (!useTransparency)
            //painter->drawPixmap(0,-49,SCOREBOARD_WIDTH,49, *topBar);
            painter->fillRect(20,TOP_BAR_Y,TOP_BAR_WIDTH, TOP_BAR_Y * -1, QBrush(QColor(50,5,5)));
        //painter->drawPixmap(0, 0, this->pixmap());
        //painter->fillRect(0,0,SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT, mainGradient);

        painter->drawRoundRect(0,0,SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT,5, 100);
        //painter->drawPixmap(34, 4, 66, 50, *homeLogo);
        //Clock - Game time...draw clock first since default color is black
        painter->setFont(homeName->font());
        painter->setPen(QColor(255,255,255));
        //painter->fillRect(CLOCK_FIELD_X, 3, CLOCK_FIELD_WIDTH,48, clockGradient);
        if (showPdAndClock) {
            painter->drawText(CLOCK_FIELD_X + 5, 0, CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT, Qt::AlignVCenter, period);
            painter->drawText(CLOCK_FIELD_X, 0, 242, SCOREBOARD_HEIGHT, Qt::AlignRight | Qt::AlignVCenter,
                              showClock? clock->toString() : "INT");
        }
        else {
            painter->drawText(CLOCK_FIELD_X, 0, CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT, Qt::AlignCenter, centeredTimeText);
        }
        // Away text
        painter->setPen(QColor(255,255,255));
        painter->drawRect(V_TEAM_BOX_STARTX - 1, TEAM_BOX_Y - 1, TEAM_NAME_WIDTH + 79, TEAM_BOX_HEIGHT+1);
        painter->fillRect(V_TEAM_BOX_STARTX, TEAM_BOX_Y, TEAM_NAME_WIDTH+ 78, TEAM_BOX_HEIGHT, awayGradient );
        // Away logo
        painter->setOpacity(.99);
        painter->drawPixmap(V_TEAM_BOX_STARTX, TEAM_BOX_Y + awayLogoOffset, *awayLogo);
        painter->setOpacity(1);
        painter->setFont(awayRank->font());
        painter->setPen(QColor(255, 255, 255));
        painter->drawText(V_TEAM_BOX_STARTX + LOGO_WIDTH, TEAM_BOX_Y, awayRankOffset - LOGO_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignCenter,  awayRank->toPlainText());
        painter->setFont(awayName->font());
        painter->drawText(V_TEAM_BOX_STARTX + 3 + awayRankOffset, TEAM_BOX_Y, TEAM_NAME_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignVCenter, awayName->toPlainText());
        // Away Score
        //painter->fillRect(375, TEAM_BOX_Y, 78, 42, scoreGradient);
        //painter->drawPixmap(V_TEAM_BOX_STARTX + TEAM_NAME_WIDTH, TEAM_BOX_Y, 78, 42, *ppBar);
        painter->setFont(awayScore->font());
        painter->drawText(V_TEAM_BOX_STARTX + TEAM_NAME_WIDTH, TEAM_BOX_Y, 78, TEAM_BOX_HEIGHT, Qt::AlignCenter, awayScore->toPlainText());

        // Home Text
        painter->setPen(QColor(255,255,255));
        painter->drawRect(H_TEAM_BOX_STARTX - 1, TEAM_BOX_Y - 1, TEAM_NAME_WIDTH + 79, TEAM_BOX_HEIGHT + 1);
        painter->fillRect(H_TEAM_BOX_STARTX, TEAM_BOX_Y, TEAM_NAME_WIDTH + 78, TEAM_BOX_HEIGHT, homeGradient);
        // Home logo
        painter->setOpacity(.99);
        painter->drawPixmap(H_TEAM_BOX_STARTX, TEAM_BOX_Y + homeLogoOffset, *homeLogo);
        painter->setOpacity(1);
        painter->setFont(homeRank->font());
        painter->drawText(H_TEAM_BOX_STARTX + LOGO_WIDTH, TEAM_BOX_Y, homeRankOffset - LOGO_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignCenter, homeRank->toPlainText());
        painter->setFont(homeName->font());
        painter->drawText(H_TEAM_BOX_STARTX + 5 + homeRankOffset, TEAM_BOX_Y, TEAM_NAME_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignVCenter, homeName->toPlainText());
        // Home Score
//        painter->fillRect(730, TEAM_BOX_Y, 78, 42, scoreGradient);
        //painter->drawPixmap(H_TEAM_BOX_STARTX + TEAM_NAME_WIDTH, TEAM_BOX_Y, 78, 42, *ppBar);
        painter->setFont(homeScore->font());
        painter->drawText(H_TEAM_BOX_STARTX + TEAM_NAME_WIDTH, TEAM_BOX_Y, 78, TEAM_BOX_HEIGHT, Qt::AlignCenter, homeScore->toPlainText());
        if (sponsor) {
            //StatBarText
            painter->setPen(QColor(255, 255, 255));
            painter->setFont(topBarText->font());
            painter->drawText(20,TOP_BAR_Y,TOP_BAR_WIDTH,TOP_BAR_Y*-1, Qt::AlignCenter, topBarText->toPlainText());
        }

        if (showPP) {
            painter->setPen(QColor(255, 255, 255));
            painter->setFont(defaultSponsorText);
            // Away ppbar
            if(awayPP) {
               // painter->fillRect(112, SCOREBOARD_HEIGHT, 345, PP_BAR_HEIGHT, ppGradient);
                painter->drawPixmap(V_TEAM_BOX_STARTX - 3,SCOREBOARD_HEIGHT, *ppBar);
                painter->drawText(V_TEAM_BOX_STARTX + 5, SCOREBOARD_HEIGHT, 345, PP_BAR_HEIGHT, Qt::AlignLeft | Qt::AlignVCenter, ppDescription);
                painter->drawText(V_TEAM_BOX_STARTX, SCOREBOARD_HEIGHT, 331, PP_BAR_HEIGHT, Qt::AlignRight | Qt::AlignVCenter, ppClock->toStringPP());
            }
            //Home ppbar
            else if (homePP) {
               // painter->fillRect(466, SCOREBOARD_HEIGHT, 345, PP_BAR_HEIGHT, ppGradient);
                painter->drawPixmap(H_TEAM_BOX_STARTX - 4,SCOREBOARD_HEIGHT, *ppBar);
                painter->drawText(H_TEAM_BOX_STARTX + 4, SCOREBOARD_HEIGHT, 345, PP_BAR_HEIGHT, Qt::AlignLeft | Qt::AlignVCenter, ppDescription);
                painter->drawText(H_TEAM_BOX_STARTX + 4, SCOREBOARD_HEIGHT, 331, PP_BAR_HEIGHT, Qt::AlignRight | Qt::AlignVCenter, ppClock->toStringPP());
            }
            //Neutral
            else if (neutralPP){
                //painter->fillRect(833, SCOREBOARD_HEIGHT, CLOCK_FIELD_WIDTH, PP_BAR_HEIGHT, ppGradient);
                painter->drawPixmap(CLOCK_FIELD_X,SCOREBOARD_HEIGHT,CLOCK_FIELD_WIDTH,PP_BAR_HEIGHT, *ppBar );
                painter->drawText(CLOCK_FIELD_X + 8, SCOREBOARD_HEIGHT, CLOCK_FIELD_WIDTH, PP_BAR_HEIGHT, Qt::AlignLeft | Qt::AlignVCenter, ppDescription);
                painter->drawText(CLOCK_FIELD_X, SCOREBOARD_HEIGHT, 239, PP_BAR_HEIGHT, Qt::AlignRight | Qt::AlignVCenter, ppClock->toStringPP());
            }
        }

        if (penalty) {
            // Penalty Indicator
            painter->fillRect(CLOCK_FIELD_X, 52, CLOCK_FIELD_WIDTH, PP_BAR_HEIGHT, penaltyGradient);
            painter->setPen(QColor(1,1,1));
            painter->setFont(defaultSponsorText);
            painter->drawText(CLOCK_FIELD_X,SCOREBOARD_HEIGHT,CLOCK_FIELD_WIDTH,PP_BAR_HEIGHT, Qt::AlignCenter, "PENALTY");
        }

    }
}

void
Scoreboard::prepareColor() {
    int red, green, blue;
    red = -1*homeColor.red() *TEAM_GRADIENT_LEVEL + homeColor.red();
    green = -1*homeColor.green() *TEAM_GRADIENT_LEVEL + homeColor.green();
    blue = -1*homeColor.blue() *TEAM_GRADIENT_LEVEL + homeColor.blue();

    QColor end(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    homeGradient.setColorAt(.4, homeColor);
    homeGradient.setColorAt(.6, homeColor);
    homeGradient.setColorAt(1, end);
    homeGradient.setColorAt(0, end);

    red = -1*awayColor.red() *TEAM_GRADIENT_LEVEL + awayColor.red();
    green = -1*awayColor.green() *TEAM_GRADIENT_LEVEL + awayColor.green();
    blue = -1*awayColor.blue() *TEAM_GRADIENT_LEVEL + awayColor.blue();
    QColor end2(red, green, blue);
    if (end2 == QColor(0,0,0))
        end2 = QColor(1,1,1);
    awayGradient.setColorAt(.4, awayColor);
    awayGradient.setColorAt(.6, awayColor);
    awayGradient.setColorAt(1, end2);
    awayGradient.setColorAt(0, end2);

    //mainGradient, clockGradient, ppGradient, scoreGradient
    QColor sbRed(156,0,0);
    red = -1*sbRed.red() *SCOREBOARD_GRADIENT_LEVEL + sbRed.red();
    green = -1*sbRed.green() *SCOREBOARD_GRADIENT_LEVEL + sbRed.green();
    blue = -1*sbRed.blue() *SCOREBOARD_GRADIENT_LEVEL + sbRed.blue();

    QColor end3(red, green, blue);
    if (end3 == QColor(0,0,0))
        end3 = QColor(1,1,1);
    mainGradient.setColorAt(0, end3);
    mainGradient.setColorAt(1, sbRed);

    clockGradient.setColorAt(0, QColor(255,255,255));
    clockGradient.setColorAt(1, QColor(255,255,255));
    clockGradient.setColorAt(.45, QColor(180,180,180));
    clockGradient.setColorAt(.55, QColor(180,180,180));

    ppGradient.setColorAt(0, QColor(1,1,1));
    ppGradient.setColorAt(1, QColor(1,1,1));
    ppGradient.setColorAt(.45, QColor(50,50,50));
    ppGradient.setColorAt(.55, QColor(50,50,50));

    scoreGradient.setColorAt(0, QColor(1,1,1));
    scoreGradient.setColorAt(1, QColor(1,1,1));
    scoreGradient.setColorAt(.45, QColor(50,50,50));
    scoreGradient.setColorAt(.55, QColor(50,50,50));

}

void Scoreboard::prepareAwayName()
{
    int subtraction = 1;
    int fontPointSize = awayName->font().pointSize();
    QFontMetrics fontSize(awayName->font());
    while (fontSize.width(awayName->toPlainText()) > TEAM_NAME_WIDTH - awayRankOffset) {
        QFont tempFont("Arial", fontPointSize - subtraction, QFont::Bold);
        //topBarText->font().setPointSize(defaultSponsorText.pointSize()-subtraction);
        subtraction++;
        awayName->setFont(tempFont);
        QFontMetrics temp(awayName->font());
        fontSize = temp;
    }
}

void
Scoreboard::togglePenalty() {
    penalty = !penalty;
    scene()->update();
}

void
Scoreboard::updateClock() {
    scene()->update(this->x() + CLOCK_FIELD_X, this->y() + 3, 242, 50);
    if (awayPP) {
        scene()->update(this->x() + V_TEAM_BOX_STARTX - 3, this->y() + SCOREBOARD_HEIGHT, 350, PP_BAR_HEIGHT);
    }
    else if (homePP) {
        scene()->update(this->x() + H_TEAM_BOX_STARTX + 4, this->y() + SCOREBOARD_HEIGHT, 350, PP_BAR_HEIGHT);
    }
    else if (neutralPP) {
        scene()->update(this->x() + CLOCK_FIELD_X, this->y() + SCOREBOARD_HEIGHT, CLOCK_FIELD_WIDTH, PP_BAR_HEIGHT);
    }
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
    scene()->update(this->x() + V_TEAM_BOX_STARTX - 3, this->y() + SCOREBOARD_HEIGHT,
                    SCOREBOARD_WIDTH - V_TEAM_BOX_STARTX, PP_BAR_HEIGHT);
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
        showPdAndClock = false;
        break;
    }
    scene()->update(x() + CLOCK_FIELD_X, y(), CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT);
}

void
Scoreboard::showPd() {
    showPdAndClock = true;
    scene()->update(x() + CLOCK_FIELD_X, y(), CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT);
}

void
Scoreboard::final() {
    showPdAndClock = false;
    centeredTimeText = "FINAL";
    scene()->update(x() + CLOCK_FIELD_X, y(), CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT);
}

void
Scoreboard::changeTopBarText(QString text) {
    topBarText->setPlainText(text);
    int subtraction = 1;
    topBarText->setFont(QFont("Arial", 20, QFont::Bold));
    QFontMetrics fontSize(topBarText->font());
    while (fontSize.width(text) > TOP_BAR_WIDTH - 10) {
        QFont tempFont("Arial", defaultSponsorText.pointSize() - subtraction, QFont::Bold);
        subtraction++;
        topBarText->setFont(tempFont);
        QFontMetrics temp(topBarText->font());
        fontSize = temp;
    }
    scene()->update(x(), y()+TOP_BAR_Y,SCOREBOARD_WIDTH,TOP_BAR_Y*-1);
}

void
Scoreboard::displaySponsor() {
    topBarText->setPlainText(sponsorText);
    int subtraction = 1;
    topBarText->setFont(defaultSponsorText);
    QFontMetrics fontSize(topBarText->font());
    while (fontSize.width(sponsorText) > TOP_BAR_WIDTH - 10) {
        QFont tempFont("Arial", defaultSponsorText.pointSize() - subtraction, QFont::Bold);
        //topBarText->font().setPointSize(defaultSponsorText.pointSize()-subtraction);
        subtraction++;
        topBarText->setFont(tempFont);
        QFontMetrics temp(topBarText->font());
        fontSize = temp;
    }
    scene()->update(x(), y()+TOP_BAR_Y,SCOREBOARD_WIDTH,TOP_BAR_Y*-1);
}
bool Scoreboard::getUseTransparency() const
{
    return useTransparency;
}

void Scoreboard::setUseTransparency(bool value)
{
    useTransparency = value;
}

int Scoreboard::getRealWidth()
{
    return SCOREBOARD_WIDTH;
}


void
Scoreboard::toggleShowBoard() {
    show = true;
    if (useTransparency)
        emit transparentField(x()+10, y()-49,TOP_BAR_WIDTH,49);
    scene()->update();
}

void Scoreboard::togglePpClocks()
{
    showPP = !showPP;
    scene()->update(this->x() + V_TEAM_BOX_STARTX - 3, this->y() + SCOREBOARD_HEIGHT,
                    SCOREBOARD_WIDTH - V_TEAM_BOX_STARTX, PP_BAR_HEIGHT);
}

void
Scoreboard::hideBoard() {
    if (show) {
        show = false;
        emit removeTransparentField(x(), y()-49,SCOREBOARD_WIDTH,49);
        scene()->update();
    }
}

void
Scoreboard::intermission() {
    showPdAndClock = true;
    showClock = false;
    scene()->update(x() + CLOCK_FIELD_X, y(), CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT);
}

void
Scoreboard::displayClock() {
    showPdAndClock = true;
    showClock = true;
    scene()->update(x() + CLOCK_FIELD_X, y(), CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT);
}
