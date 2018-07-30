#include "Scoreboard.h"
#include <QGraphicsScene>
#include <QMessageBox>
#include <QFontMetrics>
#include <QFontInfo>
#include "GraphicChooser.txt"
#include "MiamiAllAccessHockey.h"

// Flat look
#define GRADIENT_LEVEL .5

#define TEAM_GRADIENT_LEVEL .4
#define SCOREBOARD_GRADIENT_LEVEL .9


#define AWAY_PP 1
#define HOME_PP 2
#define NEUTRAL 3
#define TEAM_NAME_WIDTH 310
#define SCOREBOARD_HEIGHT 44
#define SCORE_WIDTH 78
#define TEAM_WIDTH (TEAM_NAME_WIDTH + SCORE_WIDTH)
#define RANK_WIDTH 30
#define TEAM_BOX_Y 0
#define TEAM_BOX_HEIGHT 44
#define V_TEAM_BOX_STARTX 180
#define H_TEAM_BOX_STARTX (V_TEAM_BOX_STARTX + TEAM_WIDTH + 5)
#define LOGO_WIDTH 50
#define SCOREBOARD_WIDTH 1182
#define CLOCK_FIELD_X (H_TEAM_BOX_STARTX + TEAM_WIDTH)
#define CLOCK_FIELD_WIDTH 221
#define PP_BAR_HEIGHT 38
#define TOP_BAR_WIDTH (SCOREBOARD_WIDTH - 40)
#define TOP_BAR_HEIGHT 39

Scoreboard::Scoreboard(QString sponsorText, Clock* clock, QString pAwayRank, QString pHomeRank) :
    homeColor(MiamiAllAccessHockey::homeSchool.getPrimaryColor()), awayColor(MiamiAllAccessHockey::awaySchool.getPrimaryColor()) {
    QFont font("Arial", 28, QFont::Bold);
    font.setCapitalization(QFont::SmallCaps);
    QFont sponsorFont("Arial", 20, QFont::Bold);
    sponsorFont.setCapitalization(QFont::SmallCaps);
#ifdef Q_OS_OSX
    font.setPointSize(40);
    sponsorFont.setPointSize(28);
#endif

    nchctv = (MiamiAllAccessHockey::getImgFromResources(":/images/NCHCTV.png",42));
    defaultSponsorText = sponsorFont;
    show = false;
    setRect(0,0,SCOREBOARD_WIDTH, TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT + TOP_BAR_HEIGHT + 5);
    homeLogo = new QPixmap(MiamiAllAccessHockey::homeSchool.getLogo());
    awayLogo = new QPixmap(MiamiAllAccessHockey::awaySchool.getLogo());
    altAwayLogoBg = false;
    *homeLogo = homeLogo->scaledToHeight(TEAM_BOX_HEIGHT, Qt::SmoothTransformation);
    if (homeLogo->width() > LOGO_WIDTH)
        *homeLogo = homeLogo->scaledToWidth(LOGO_WIDTH, Qt::SmoothTransformation);
    homeLogoOffset = (TEAM_BOX_HEIGHT - homeLogo->height()) / 2;

    *awayLogo = awayLogo->scaledToHeight(TEAM_BOX_HEIGHT, Qt::SmoothTransformation);
    if (awayLogo->width() > LOGO_WIDTH)
        *awayLogo = awayLogo->scaledToWidth(LOGO_WIDTH, Qt::SmoothTransformation);
    awayLogoOffset = (TEAM_BOX_HEIGHT - awayLogo->height()) / 2;

    useClock = true;
    awayName = new QGraphicsTextItem(MiamiAllAccessHockey::awaySchool.getFullName());
    homeName = new QGraphicsTextItem(MiamiAllAccessHockey::homeSchool.getFullName());
    awayName->setFont(font);
    homeName->setFont(font);
    awayScore = new QGraphicsTextItem("0");
    awayScore->setFont(font);
    homeScore = new QGraphicsTextItem("0");
    homeScore->setFont(font);
    topBarText = new QGraphicsTextItem(sponsorText);
    this->sponsorText = sponsorText;
    topBarText->setFont(defaultSponsorText);

    homeGradient.setStart(0, TOP_BAR_HEIGHT + TEAM_BOX_Y);
    awayGradient.setStart(0, TOP_BAR_HEIGHT + TEAM_BOX_Y);
    homeGradient.setFinalStop(0,TOP_BAR_HEIGHT + TEAM_BOX_HEIGHT);
    awayGradient.setFinalStop(0,TOP_BAR_HEIGHT + TEAM_BOX_HEIGHT);
    homeLogoGradient.setStart(0, TOP_BAR_HEIGHT + TEAM_BOX_Y);
    awayLogoGradient.setStart(0, TOP_BAR_HEIGHT + TEAM_BOX_Y);
    homeLogoGradient.setFinalStop(0,TOP_BAR_HEIGHT + TEAM_BOX_HEIGHT);
    awayLogoGradient.setFinalStop(0,TOP_BAR_HEIGHT + TEAM_BOX_HEIGHT);
    mainGradient.setStart(0,TOP_BAR_HEIGHT);
    mainGradient.setFinalStop(0, TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT);
    clockGradient.setStart(0,1 + TOP_BAR_HEIGHT);
    clockGradient.setFinalStop(0, TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT - 2);
    ppGradient.setStart(0, TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT);
    ppGradient.setFinalStop(0, TOP_BAR_HEIGHT + 92);
    scoreGradient.setStart(0, TOP_BAR_HEIGHT + TEAM_BOX_Y);
    scoreGradient.setFinalStop(0, TOP_BAR_HEIGHT + TEAM_BOX_Y + 44);
    prepareColor();
    // penalty gradient
    penaltyGradient.setStart(0, TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT);
    penaltyGradient.setFinalStop(0, TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT + PP_BAR_HEIGHT);
    awayPPGradient.setStart(0,TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT);
    awayPPGradient.setFinalStop(0,PP_BAR_HEIGHT+TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT);

    homePPGradient.setStart(0,TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT);
    homePPGradient.setFinalStop(0,PP_BAR_HEIGHT+TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT);

    neutralPPGradient.setStart(0,TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT);
    neutralPPGradient.setFinalStop(0,PP_BAR_HEIGHT+TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT);


    QFont rankFont("Arial", 14, QFont::Bold);
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
    showPP = true;
    sponsor = true;
    showPdAndClockFields = true;
    showClock = true;
    useTransparency = false;
    awayPP = false;
    homePP = false;
    neutralPP = false;

    this->clock = clock;
    connect(clock, SIGNAL(clockUpdated()), this, SLOT(updateClock()));
    prepareAwayName();
    serialPP = false;
    serialPpClock="";
}


void
Scoreboard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (show) {

        //painter->setBrush(*(new QBrush(mainGradient)));
        if (!useTransparency)
            //painter->drawPixmap(0,-49,SCOREBOARD_WIDTH,49, *topBar);
            painter->fillRect(20,0,TOP_BAR_WIDTH, TOP_BAR_HEIGHT, QBrush(QColor(20,20,20)));
        painter->fillRect(0,TOP_BAR_HEIGHT,SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT,mainGradient);
        painter->drawPixmap(2,TOP_BAR_HEIGHT,nchctv);
        //Clock - Game time...draw clock first since default color is black
        painter->setFont(homeName->font());
        painter->setPen(QColor(230,230,230));
        //painter->fillRect(CLOCK_FIELD_X, 1 + TOP_BAR_HEIGHT, CLOCK_FIELD_WIDTH,SCOREBOARD_HEIGHT-2, clockGradient);
        if (useClock && showPdAndClockFields) {
            painter->drawText(CLOCK_FIELD_X + 10, TOP_BAR_HEIGHT, CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT, Qt::AlignVCenter, period);
            painter->drawText(CLOCK_FIELD_X, TOP_BAR_HEIGHT, CLOCK_FIELD_WIDTH-10, SCOREBOARD_HEIGHT, Qt::AlignRight | Qt::AlignVCenter,
                              showClock? clock->toString() : "INT");
        }
        else {
            painter->drawText(CLOCK_FIELD_X, TOP_BAR_HEIGHT, CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT, Qt::AlignCenter, centeredTimeText);
        }
        // Away text
        painter->setPen(QColor(255,255,255));
        //painter->drawRect(V_TEAM_BOX_STARTX - 1, TEAM_BOX_Y - 1, TEAM_WIDTH + 1, TEAM_BOX_HEIGHT+1);
        painter->fillRect(V_TEAM_BOX_STARTX, TOP_BAR_HEIGHT + TEAM_BOX_Y, TEAM_WIDTH, TEAM_BOX_HEIGHT, awayGradient );
        // Away logo
        painter->fillRect(V_TEAM_BOX_STARTX, TOP_BAR_HEIGHT + TEAM_BOX_Y, LOGO_WIDTH, TEAM_BOX_HEIGHT, awayLogoGradient);
        painter->drawPixmap(V_TEAM_BOX_STARTX, TOP_BAR_HEIGHT + TEAM_BOX_Y + awayLogoOffset, *awayLogo);
        painter->setOpacity(1);
        painter->setFont(awayRank->font());
        painter->setPen(QColor(255, 255, 255));
        painter->drawText(V_TEAM_BOX_STARTX + LOGO_WIDTH, TOP_BAR_HEIGHT + TEAM_BOX_Y, awayRankOffset - LOGO_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignCenter,  awayRank->toPlainText());
        painter->setFont(awayName->font());
        painter->drawText(V_TEAM_BOX_STARTX + 3 + awayRankOffset, TOP_BAR_HEIGHT + TEAM_BOX_Y, TEAM_NAME_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignVCenter, awayName->toPlainText());
        // Away Score
        painter->setFont(awayScore->font());
        painter->drawText(V_TEAM_BOX_STARTX + TEAM_NAME_WIDTH, TOP_BAR_HEIGHT + TEAM_BOX_Y, SCORE_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignCenter, awayScore->toPlainText());

        // Home Text
        painter->setPen(QColor(255,255,255));
        painter->fillRect(H_TEAM_BOX_STARTX, TOP_BAR_HEIGHT + TEAM_BOX_Y, TEAM_WIDTH, TEAM_BOX_HEIGHT, homeGradient);
        painter->fillRect(H_TEAM_BOX_STARTX, TOP_BAR_HEIGHT + TEAM_BOX_Y, LOGO_WIDTH, TEAM_BOX_HEIGHT, homeLogoGradient);
        // Home logo
        painter->drawPixmap(H_TEAM_BOX_STARTX, TOP_BAR_HEIGHT + TEAM_BOX_Y + homeLogoOffset, *homeLogo);
        painter->setOpacity(1);
        painter->setFont(homeRank->font());
        painter->drawText(H_TEAM_BOX_STARTX + LOGO_WIDTH, TOP_BAR_HEIGHT + TEAM_BOX_Y, homeRankOffset - LOGO_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignCenter, homeRank->toPlainText());
        painter->setFont(homeName->font());
        painter->drawText(H_TEAM_BOX_STARTX + 5 + homeRankOffset, TOP_BAR_HEIGHT + TEAM_BOX_Y, TEAM_NAME_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignVCenter, homeName->toPlainText());
        // Home Score
        painter->setFont(homeScore->font());
        painter->drawText(H_TEAM_BOX_STARTX + TEAM_NAME_WIDTH, TOP_BAR_HEIGHT + TEAM_BOX_Y, SCORE_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignCenter, homeScore->toPlainText());
        if (sponsor) {
            //StatBarText
            painter->setPen(QColor(255, 255, 255));
            painter->setFont(topBarText->font());
            painter->drawText(20,0,TOP_BAR_WIDTH,TOP_BAR_HEIGHT, Qt::AlignCenter, topBarText->toPlainText());
        }

        if (showPP) {
            painter->setFont(defaultSponsorText);
            // Away ppbar
            if(awayPP) {
                painter->fillRect(V_TEAM_BOX_STARTX, TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT, 345, PP_BAR_HEIGHT, awayPPGradient);
                painter->setPen(QColor(196, 213, 242));
                painter->drawRect(V_TEAM_BOX_STARTX, TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT, 345, PP_BAR_HEIGHT);
                painter->setPen(QColor(230,230,230));
                //painter->drawPixmap(V_TEAM_BOX_STARTX - 3,SCOREBOARD_HEIGHT, *ppBar);
                painter->drawText(V_TEAM_BOX_STARTX + 5, TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT, 345, PP_BAR_HEIGHT, Qt::AlignLeft | Qt::AlignVCenter, ppDescription);
                if (useClock)
                    painter->drawText(V_TEAM_BOX_STARTX, TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT, 331, PP_BAR_HEIGHT,
                                      Qt::AlignRight | Qt::AlignVCenter, serialPP? serialPpClock : ppClock->toStringPP());
            }
            //Home ppbar
            else if (homePP) {
                painter->fillRect(H_TEAM_BOX_STARTX, TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT, 345, PP_BAR_HEIGHT, homePPGradient);
                painter->setPen(QColor(196, 213, 242));
                painter->drawRect(H_TEAM_BOX_STARTX, TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT, 345, PP_BAR_HEIGHT);
                painter->setPen(QColor(230,230,230));
                painter->drawText(H_TEAM_BOX_STARTX + 4, TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT, 345, PP_BAR_HEIGHT, Qt::AlignLeft | Qt::AlignVCenter, ppDescription);
                if (useClock)
                    painter->drawText(H_TEAM_BOX_STARTX + 4, TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT, 331, PP_BAR_HEIGHT,
                                      Qt::AlignRight | Qt::AlignVCenter, serialPP? serialPpClock : ppClock->toStringPP());
            }
            //Neutral
            else if (neutralPP){
                painter->fillRect(CLOCK_FIELD_X, TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT, CLOCK_FIELD_WIDTH, PP_BAR_HEIGHT, neutralPPGradient);
                painter->setPen(QColor(196, 213, 242));
                painter->drawRect(CLOCK_FIELD_X, TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT, CLOCK_FIELD_WIDTH, PP_BAR_HEIGHT);
                painter->setPen(QColor(230,230,230));
                painter->drawText(CLOCK_FIELD_X + 8, TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT, CLOCK_FIELD_WIDTH, PP_BAR_HEIGHT, Qt::AlignLeft | Qt::AlignVCenter, ppDescription);
                if (useClock)
                    painter->drawText(CLOCK_FIELD_X, TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT,  CLOCK_FIELD_WIDTH - 10, PP_BAR_HEIGHT,
                                      Qt::AlignRight | Qt::AlignVCenter, serialPP? serialPpClock : ppClock->toStringPP());
            }
        }

        if (penalty) {
            // Penalty Indicator
            painter->fillRect(CLOCK_FIELD_X,TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT, CLOCK_FIELD_WIDTH - 10, PP_BAR_HEIGHT, penaltyGradient);
            painter->setPen(QColor(1,1,1));
            painter->setFont(defaultSponsorText);
            painter->drawText(CLOCK_FIELD_X, TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT,CLOCK_FIELD_WIDTH - 10,PP_BAR_HEIGHT, Qt::AlignCenter, "PENALTY");
        }
        painter->setPen(QColor(196, 213, 242));
        painter->drawRect(0,TOP_BAR_HEIGHT,SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT);
        painter->setPen(QColor(255, 255, 255));

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
    homeGradient.setColorAt(0, homeColor);
   // homeGradient.setColorAt(.6, homeColor);
    homeGradient.setColorAt(1, end);
    //homeGradient.setColorAt(0, end);
    homePPGradient.setColorAt(0, homeColor);
    homePPGradient.setColorAt(1, end);

    red = -1*awayColor.red() *TEAM_GRADIENT_LEVEL + awayColor.red();
    green = -1*awayColor.green() *TEAM_GRADIENT_LEVEL + awayColor.green();
    blue = -1*awayColor.blue() *TEAM_GRADIENT_LEVEL + awayColor.blue();
    QColor end2(red, green, blue);
    if (end2 == QColor(0,0,0))
        end2 = QColor(1,1,1);
    awayGradient.setColorAt(0, awayColor);
    //awayGradient.setColorAt(.6, awayColor);
    awayGradient.setColorAt(1, end2);
    //awayGradient.setColorAt(0, end2);
    awayPPGradient.setColorAt(0, awayColor);
    awayPPGradient.setColorAt(1, end2);


    // Logo gradients
    red = -1*MiamiAllAccessHockey::homeSchool.getPrimaryLogoBg().red() *TEAM_GRADIENT_LEVEL + MiamiAllAccessHockey::homeSchool.getPrimaryLogoBg().red();
    green = -1*MiamiAllAccessHockey::homeSchool.getPrimaryLogoBg().green() *TEAM_GRADIENT_LEVEL + MiamiAllAccessHockey::homeSchool.getPrimaryLogoBg().green();
    blue = -1*MiamiAllAccessHockey::homeSchool.getPrimaryLogoBg().blue() *TEAM_GRADIENT_LEVEL + MiamiAllAccessHockey::homeSchool.getPrimaryLogoBg().blue();

    QColor end5(red, green, blue);
    if (end5 == QColor(0,0,0))
        end5 = QColor(1,1,1);
    homeLogoGradient.setColorAt(0, MiamiAllAccessHockey::homeSchool.getPrimaryLogoBg());
    homeLogoGradient.setColorAt(1, end5);

    red = -1*MiamiAllAccessHockey::awaySchool.getPrimaryLogoBg().red() *TEAM_GRADIENT_LEVEL + MiamiAllAccessHockey::awaySchool.getPrimaryLogoBg().red();
    green = -1*MiamiAllAccessHockey::awaySchool.getPrimaryLogoBg().green() *TEAM_GRADIENT_LEVEL + MiamiAllAccessHockey::awaySchool.getPrimaryLogoBg().green();
    blue = -1*MiamiAllAccessHockey::awaySchool.getPrimaryLogoBg().blue() *TEAM_GRADIENT_LEVEL + MiamiAllAccessHockey::awaySchool.getPrimaryLogoBg().blue();
    QColor end4(red, green, blue);
    if (end4 == QColor(0,0,0))
        end4 = QColor(1,1,1);
    awayLogoGradient.setColorAt(0, MiamiAllAccessHockey::awaySchool.getPrimaryLogoBg());
    awayLogoGradient.setColorAt(1, end4);


    //mainGradient, clockGradient, ppGradient, scoreGradient
    QColor sbRed(20,20,20);
    red = -1*sbRed.red() *SCOREBOARD_GRADIENT_LEVEL + sbRed.red();
    green = -1*sbRed.green() *SCOREBOARD_GRADIENT_LEVEL + sbRed.green();
    blue = -1*sbRed.blue() *SCOREBOARD_GRADIENT_LEVEL + sbRed.blue();

    QColor end3(red, green, blue);
    if (end3 == QColor(0,0,0))
        end3 = QColor(1,1,1);

    mainGradient.setColorAt(0, QColor(41, 70, 91));
    //mainGradient.setColorAt(1, QColor(1,1,1));
    mainGradient.setColorAt(1, QColor(23, 41, 53));
    //mainGradient.setColorAt(.6, QColor(50,50,50));
    neutralPPGradient.setColorAt(0, QColor(41, 70, 91));
    neutralPPGradient.setColorAt(1, QColor(23, 41, 53));

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

    bgGradient.setStart(0,0);
    bgGradient.setFinalStop(0,SCOREBOARD_HEIGHT);
    bgGradient.setColorAt(0, QColor(45,45,45));
    bgGradient.setColorAt(1, QColor(45,45,45));
    bgGradient.setColorAt(.5, QColor(50,50,50));

    penaltyGradient.setColorAt(1, QColor(255, 255, 0));
    penaltyGradient.setColorAt(0, QColor(188, 188, 0));

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
    scene()->update(this->x() + CLOCK_FIELD_X, this->y() + TOP_BAR_HEIGHT + 3, 242, 50);
    if (awayPP) {
        scene()->update(this->x() + V_TEAM_BOX_STARTX - 3, this->y() + TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT, 350, PP_BAR_HEIGHT);
    }
    else if (homePP) {
        scene()->update(this->x() + H_TEAM_BOX_STARTX + 4, this->y() + TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT, 350, PP_BAR_HEIGHT);
    }
    else if (neutralPP) {
        scene()->update(this->x() + CLOCK_FIELD_X, this->y() + TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT, CLOCK_FIELD_WIDTH + 4, PP_BAR_HEIGHT);
    }
}

void
Scoreboard::preparePowerplayClock(int pos, Clock *clock, QString description) {
    // Clear off current board.
    awayPP = false;
    homePP = false;
    neutralPP = false;
    ppClock = clock;
    if (ppClock != NULL) {
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
    }
    ppDescription = description;
    scene()->update(this->x(), this->y() + TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT,
                    SCOREBOARD_WIDTH + 4, PP_BAR_HEIGHT+1);
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
    this->pd=pd;
    switch (pd) {
    case 1:
        period = "1st";
        showPdAndClockFields = true;
        if (!useClock) {
            centeredTimeText = period + " PD";
        }
        break;
    case 2:
        period = "2nd";
        if (!useClock) {
            centeredTimeText = period + " PD";
        }
        break;
    case 3:
        period = "3rd";
        if (!useClock) {
            centeredTimeText = period + " PD";
        }
        break;
    case 4:
        period = "OT";
        showPdAndClockFields = true;
        if (!useClock) {
            centeredTimeText = "OVERTIME";
        }
        break;
    case 5:
        period = "3x3OT";
        showPdAndClockFields = true;
        if (!useClock) {
            centeredTimeText = "OVERTIME";
        }
        break;
    case 6:
        centeredTimeText = "SHOOTOUT";
        showPdAndClockFields = false;
        break;
    default:
        period = "";
        showPdAndClockFields = false;
        break;
    }
    scene()->update(x() + CLOCK_FIELD_X, y() + TOP_BAR_HEIGHT, CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT);
}

void
Scoreboard::showPd() {
    showPdAndClockFields = true;
    scene()->update(x() + CLOCK_FIELD_X, y() + TOP_BAR_HEIGHT, CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT);
}

void
Scoreboard::final() {
    showPdAndClockFields = false;
    centeredTimeText = "FINAL";
    scene()->update(x() + CLOCK_FIELD_X, y() + TOP_BAR_HEIGHT, CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT);
}

void
Scoreboard::changeTopBarText(QString text) {
    topBarText->setPlainText(text);
    int subtraction = 1;
    QFont f("Arial", 20, QFont::Bold);
    f.setCapitalization(QFont::SmallCaps);
    topBarText->setFont(f);
    topBarText->font().setCapitalization(QFont::SmallCaps);
    QFontMetrics fontSize(topBarText->font());
    while (fontSize.width(text) > TOP_BAR_WIDTH - 10) {
        QFont tempFont("Arial", defaultSponsorText.pointSize() - subtraction, QFont::Bold);
        tempFont.setCapitalization(QFont::SmallCaps);
        subtraction++;
        topBarText->setFont(tempFont);
        QFontMetrics temp(topBarText->font());
        fontSize = temp;
    }
    scene()->update(x()+20, y(),TOP_BAR_WIDTH,TOP_BAR_HEIGHT);
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
    scene()->update(x()+20, y(), TOP_BAR_WIDTH,TOP_BAR_HEIGHT);
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
        emit transparentField(x()+20,y(),TOP_BAR_WIDTH,TOP_BAR_HEIGHT);
    emit addNoTransparencyZone(QRect(x() + V_TEAM_BOX_STARTX, y() + TOP_BAR_HEIGHT + TEAM_BOX_Y, TEAM_WIDTH, TEAM_BOX_HEIGHT));
    scene()->update();
}

void Scoreboard::togglePpClocks()
{
    showPP = !showPP;
    scene()->update(this->x(), this->y() + TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT,
                    SCOREBOARD_WIDTH + 4 , PP_BAR_HEIGHT+1);
}

void
Scoreboard::hideBoard() {
    if (show) {
        show = false;
        emit removeTransparentField(x()+20, y(), TOP_BAR_WIDTH,TOP_BAR_HEIGHT);
        emit removeNoTransparencyZone(QRect(x() + V_TEAM_BOX_STARTX, y() + TOP_BAR_HEIGHT + TEAM_BOX_Y, TEAM_WIDTH, TEAM_BOX_HEIGHT));
        scene()->update();
    }
}

void
Scoreboard::intermission() {
    if (useClock) {
    showPdAndClockFields = true;
    showClock = false;
    }
    else {
       centeredTimeText = period + " " + "INT";
    }
    scene()->update(x() + CLOCK_FIELD_X, y() + TOP_BAR_HEIGHT, CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT);
}

void
Scoreboard::displayClock() {
    if (useClock) {
    showPdAndClockFields = true;
    }
    else {
        updatePeriod(pd);
    }
    showClock = true;
    scene()->update(x() + CLOCK_FIELD_X, y() + TOP_BAR_HEIGHT, CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT);
}

void Scoreboard::changeUseClock(bool uc)
{
    useClock = uc;
    updatePeriod(pd);
}

void Scoreboard::toggleAwayLogoBg(bool on)
{
    altAwayLogoBg = on;
    if (show) {
        scene()->update(this->x(), this->y(), SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT + TOP_BAR_HEIGHT);
    }
}

void Scoreboard::usingAllSport()
{
    serialPP = true;
}

void Scoreboard::usingInternalClocks()
{
    serialPP = false;
}

bool Scoreboard::getShowClock() const
{
    return showClock;
}

void Scoreboard::setSerialPowerPlay(int pos, QString clock, QString description)
{
    awayPP = false;
    homePP = false;
    neutralPP = false;
    if (!clock.isEmpty()) {
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
    }
    ppDescription = description;
    serialPpClock = clock;
    scene()->update(this->x(), this->y() + TOP_BAR_HEIGHT + SCOREBOARD_HEIGHT,
                    SCOREBOARD_WIDTH + 4, PP_BAR_HEIGHT+1);

}
