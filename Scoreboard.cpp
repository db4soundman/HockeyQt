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
#define SCORE_WIDTH 78
#define RANK_WIDTH 30
#define TEAM_BOX_Y 0
#define TEAM_BOX_HEIGHT 44
#define V_TEAM_BOX_STARTY 0
#define H_TEAM_BOX_STARTY V_TEAM_BOX_STARTY + TEAM_BOX_HEIGHT
#define LOGO_WIDTH 50
#define SOG_WIDTH 50
#define CLOCK_FIELD_X 0
#define CLOCK_FIELD_WIDTH 200
#define TEAM_WIDTH (LOGO_WIDTH + SOG_WIDTH + SCORE_WIDTH)
#define V_TEAM_BOX_STARTX CLOCK_FIELD_WIDTH
#define H_TEAM_BOX_STARTX CLOCK_FIELD_WIDTH
#define PP_BAR_HEIGHT TEAM_BOX_HEIGHT
#define POP_BAR_WIDTH (SCOREBOARD_WIDTH - 40)
#define POP_BAR_HEIGHT 39
#define POP_BAR_X 0
#define POP_BAR_Y 0
#define V_TEAM_SOG_X (V_TEAM_BOX_STARTX + LOGO_WIDTH + SCORE_WIDTH)
#define H_TEAM_SOG_X (V_TEAM_BOX_STARTX + LOGO_WIDTH + SCORE_WIDTH)
#define SCOREBOARD_WIDTH (CLOCK_FIELD_WIDTH + LOGO_WIDTH + SCORE_WIDTH + SOG_WIDTH)
#define SCOREBOARD_HEIGHT TEAM_BOX_HEIGHT * 2

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
    setRect(0,0,SCOREBOARD_WIDTH + CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT + PP_BAR_HEIGHT + 5);
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
    awayLogoHeightOffset = (TEAM_BOX_HEIGHT - awayLogo->height()) / 2;
    awayLogoWidthOffset = (LOGO_WIDTH - awayLogo->width()) / 2;

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

    homeGradient.setStart(0, H_TEAM_BOX_STARTY);
    awayGradient.setStart(0, V_TEAM_BOX_STARTY);
    homeGradient.setFinalStop(0 ,H_TEAM_BOX_STARTY + TEAM_BOX_HEIGHT);
    awayGradient.setFinalStop(0, V_TEAM_BOX_STARTY + TEAM_BOX_HEIGHT);
    homeLogoGradient.setStart(0, H_TEAM_BOX_STARTY);
    awayLogoGradient.setStart(0, V_TEAM_BOX_STARTY);
    homeLogoGradient.setFinalStop(0,H_TEAM_BOX_STARTY + TEAM_BOX_HEIGHT);
    awayLogoGradient.setFinalStop(0,V_TEAM_BOX_STARTY + TEAM_BOX_HEIGHT);
    mainGradient.setStart(0,0);
    mainGradient.setFinalStop(0, SCOREBOARD_HEIGHT);

//    clockGradient.setStart(0,1 + POP_BAR_HEIGHT);
//    clockGradient.setFinalStop(0, POP_BAR_HEIGHT + SCOREBOARD_HEIGHT - 2);

    ppGradient.setStart(0, POP_BAR_HEIGHT + SCOREBOARD_HEIGHT);
    ppGradient.setFinalStop(0, POP_BAR_HEIGHT + 92);
    scoreGradient.setStart(0, POP_BAR_HEIGHT + TEAM_BOX_Y);
    scoreGradient.setFinalStop(0, POP_BAR_HEIGHT + TEAM_BOX_Y + 44);
    prepareColor();
    // penalty gradient
    penaltyGradient.setStart(0, 0);
    penaltyGradient.setFinalStop(0, SCOREBOARD_HEIGHT);

    awayPPGradient.setStart(0, 0);
    awayPPGradient.setFinalStop(0, TEAM_BOX_HEIGHT);

    homePPGradient.setStart(0, H_TEAM_BOX_STARTY);
    homePPGradient.setFinalStop(0, SCOREBOARD_HEIGHT);

    neutralPPGradient.setStart(0, 0);
    neutralPPGradient.setFinalStop(0, SCOREBOARD_HEIGHT);


    QFont rankFont("Arial", 14, QFont::Bold);
    rankFont.setCapitalization(QFont::SmallCaps);
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
    sponsor = false;
    showPdAndClockFields = true;
    showClock = true;
    useTransparency = false;
    awayPP = false;
    homePP = false;
    neutralPP = false;
    hSog = 0;
    aSog = 0;

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

        painter->fillRect(0, 0, SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT, mainGradient);
        painter->drawPixmap((CLOCK_FIELD_WIDTH - nchctv.width()) / 2, 0,nchctv);
        //Clock -
        painter->setFont(homeName->font());
        painter->setPen(QColor(240,240,240));

        if (useClock && showPdAndClockFields) {
            painter->drawText(CLOCK_FIELD_X + 5, H_TEAM_BOX_STARTY, CLOCK_FIELD_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignVCenter | Qt::AlignLeft, period);
            painter->drawText(CLOCK_FIELD_X, H_TEAM_BOX_STARTY, CLOCK_FIELD_WIDTH - 5, TEAM_BOX_HEIGHT, Qt::AlignVCenter | Qt::AlignRight,
                              showClock? clock->toString() : "INT");
        }
        else {
            painter->drawText(CLOCK_FIELD_X, H_TEAM_BOX_STARTY, CLOCK_FIELD_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignCenter, centeredTimeText);
        }
        // Away text
        painter->setPen(QColor(240,240,240));
        //painter->drawRect(V_TEAM_BOX_STARTX - 1, TEAM_BOX_Y - 1, TEAM_WIDTH + 1, TEAM_BOX_HEIGHT+1);
        painter->fillRect(V_TEAM_BOX_STARTX, V_TEAM_BOX_STARTY, TEAM_WIDTH, TEAM_BOX_HEIGHT, awayGradient);
        // Away logo
        painter->fillRect(V_TEAM_BOX_STARTX, V_TEAM_BOX_STARTY, LOGO_WIDTH, TEAM_BOX_HEIGHT, awayLogoGradient);
        painter->drawPixmap(V_TEAM_BOX_STARTX + awayLogoWidthOffset, V_TEAM_BOX_STARTY + awayLogoHeightOffset, *awayLogo);

//        painter->setFont(awayRank->font());
//        painter->setPen(QColor(240, 240, 240));
//        painter->drawText(V_TEAM_BOX_STARTX + LOGO_WIDTH, POP_BAR_HEIGHT + TEAM_BOX_Y, awayRankOffset - LOGO_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignCenter,  awayRank->toPlainText());
//        painter->setFont(awayName->font());
//        painter->drawText(V_TEAM_BOX_STARTX + 10 + awayRankOffset, POP_BAR_HEIGHT + TEAM_BOX_Y, TEAM_NAME_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignVCenter, awayName->toPlainText());


        // Away Score
        painter->setFont(awayScore->font());
        painter->drawText(V_TEAM_BOX_STARTX + LOGO_WIDTH, V_TEAM_BOX_STARTY, SCORE_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignCenter, awayScore->toPlainText());


        // Home Text
        painter->setPen(QColor(240,240,240));
        painter->fillRect(H_TEAM_BOX_STARTX, H_TEAM_BOX_STARTY, TEAM_WIDTH, TEAM_BOX_HEIGHT, homeGradient);
        painter->fillRect(H_TEAM_BOX_STARTX, H_TEAM_BOX_STARTY, LOGO_WIDTH, TEAM_BOX_HEIGHT, homeLogoGradient);

        // Home logo
        painter->drawPixmap(H_TEAM_BOX_STARTX, H_TEAM_BOX_STARTY + homeLogoOffset, *homeLogo);

//        painter->setFont(homeRank->font());
//        painter->drawText(H_TEAM_BOX_STARTX + LOGO_WIDTH, POP_BAR_HEIGHT + TEAM_BOX_Y, homeRankOffset - LOGO_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignCenter, homeRank->toPlainText());
//        painter->setFont(homeName->font());
//        painter->drawText(H_TEAM_BOX_STARTX + 10 + homeRankOffset, POP_BAR_HEIGHT + TEAM_BOX_Y, TEAM_NAME_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignVCenter, homeName->toPlainText());

        // Home Score
        painter->setFont(homeScore->font());
        painter->drawText(H_TEAM_BOX_STARTX + LOGO_WIDTH, H_TEAM_BOX_STARTY, SCORE_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignCenter, homeScore->toPlainText());

        // SOG BG
        painter->fillRect(V_TEAM_SOG_X, V_TEAM_BOX_STARTY, SOG_WIDTH, SCOREBOARD_HEIGHT, QColor(1,1,1,80));

        // Away SOG
        painter->setFont(awayRank->font());
        painter->drawText(V_TEAM_SOG_X, V_TEAM_BOX_STARTY, SOG_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignCenter, QString::number(aSog));

        // Home SOG
        painter->setFont(awayRank->font());
        painter->drawText(H_TEAM_SOG_X, H_TEAM_BOX_STARTY, SOG_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignCenter, QString::number(hSog));

        // SOG Label
        painter->drawText(H_TEAM_SOG_X, V_TEAM_BOX_STARTY, SOG_WIDTH, SCOREBOARD_HEIGHT*23/24, Qt::AlignCenter, "sog");


        if (sponsor) {
            painter->fillRect(20,0,POP_BAR_WIDTH, POP_BAR_HEIGHT, QBrush(QColor(20,20,20)));
            //StatBarText
            painter->setPen(QColor(255, 255, 255));
            painter->setFont(topBarText->font());
            painter->drawText(20,0,POP_BAR_WIDTH,POP_BAR_HEIGHT, Qt::AlignCenter, topBarText->toPlainText());
        }

        if (showPP) {
            painter->setFont(defaultSponsorText);
            // Away ppbar
            if(awayPP) {
                painter->fillRect(SCOREBOARD_WIDTH, V_TEAM_BOX_STARTY, CLOCK_FIELD_WIDTH, PP_BAR_HEIGHT, awayGradient);
                painter->setPen(QColor(196, 213, 242));
                painter->drawRect(SCOREBOARD_WIDTH, V_TEAM_BOX_STARTY, CLOCK_FIELD_WIDTH, PP_BAR_HEIGHT);
                painter->setPen(QColor(230,230,230));
                //painter->drawPixmap(V_TEAM_BOX_STARTX - 3,SCOREBOARD_HEIGHT, *ppBar);
                painter->drawText(SCOREBOARD_WIDTH + 5, V_TEAM_BOX_STARTY, CLOCK_FIELD_WIDTH, PP_BAR_HEIGHT, Qt::AlignLeft | Qt::AlignVCenter, ppDescription);
                if (useClock)
                    painter->drawText(SCOREBOARD_WIDTH, V_TEAM_BOX_STARTY, CLOCK_FIELD_WIDTH - 5, PP_BAR_HEIGHT,
                                      Qt::AlignRight | Qt::AlignVCenter, serialPP? serialPpClock : ppClock->toStringPP());
            }
            //Home ppbar
            else if (homePP) {
                painter->fillRect(SCOREBOARD_WIDTH, H_TEAM_BOX_STARTY, CLOCK_FIELD_WIDTH, PP_BAR_HEIGHT, homeGradient);
                painter->setPen(QColor(196, 213, 242));
                painter->drawRect(SCOREBOARD_WIDTH, H_TEAM_BOX_STARTY, CLOCK_FIELD_WIDTH, PP_BAR_HEIGHT);
                painter->setPen(QColor(230,230,230));
                painter->drawText(SCOREBOARD_WIDTH + 5, H_TEAM_BOX_STARTY, CLOCK_FIELD_WIDTH, PP_BAR_HEIGHT, Qt::AlignLeft | Qt::AlignVCenter, ppDescription);
                if (useClock)
                    painter->drawText(SCOREBOARD_WIDTH, H_TEAM_BOX_STARTY, CLOCK_FIELD_WIDTH - 5, PP_BAR_HEIGHT,
                                      Qt::AlignRight | Qt::AlignVCenter, serialPP? serialPpClock : ppClock->toStringPP());
            }
            //Neutral
            else if (neutralPP){
                painter->fillRect(SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT/4, CLOCK_FIELD_WIDTH, PP_BAR_HEIGHT, neutralPPGradient);
                painter->setPen(QColor(196, 213, 242));
                painter->drawRect(SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT/4, CLOCK_FIELD_WIDTH, PP_BAR_HEIGHT);
                painter->setPen(QColor(230,230,230));
                painter->drawText(SCOREBOARD_WIDTH + 5, SCOREBOARD_HEIGHT/4, CLOCK_FIELD_WIDTH, PP_BAR_HEIGHT, Qt::AlignLeft | Qt::AlignVCenter, ppDescription);
                if (useClock)
                    painter->drawText(SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT/4,  CLOCK_FIELD_WIDTH - 5, PP_BAR_HEIGHT,
                                      Qt::AlignRight | Qt::AlignVCenter, serialPP? serialPpClock : ppClock->toStringPP());
            }
        }

        if (penalty) {
            // Penalty Indicator
            painter->fillRect(CLOCK_FIELD_X, SCOREBOARD_HEIGHT, CLOCK_FIELD_WIDTH, PP_BAR_HEIGHT, penaltyGradient);
            painter->setPen(QColor(1,1,1));
            painter->setFont(defaultSponsorText);
            painter->drawText(CLOCK_FIELD_X, SCOREBOARD_HEIGHT, CLOCK_FIELD_WIDTH, PP_BAR_HEIGHT, Qt::AlignCenter, "PENALTY");
        }
        painter->setPen(QColor(196, 213, 242));
        painter->drawRect(0,0,SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT);
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
    scene()->update(this->x() + CLOCK_FIELD_X, this->y() + H_TEAM_BOX_STARTY, CLOCK_FIELD_WIDTH, TEAM_BOX_HEIGHT);
    if (awayPP) {
        scene()->update(this->x() + SCOREBOARD_WIDTH, this->y() + V_TEAM_BOX_STARTY, CLOCK_FIELD_WIDTH, TEAM_BOX_HEIGHT);
    }
    else if (homePP) {
        scene()->update(this->x() + SCOREBOARD_WIDTH, this->y() + H_TEAM_BOX_STARTY, CLOCK_FIELD_WIDTH, TEAM_BOX_HEIGHT);
    }
    else if (neutralPP) {
        scene()->update(this->x() + SCOREBOARD_WIDTH, this->y() + SCOREBOARD_HEIGHT/4, CLOCK_FIELD_WIDTH, TEAM_BOX_HEIGHT);
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
            emit removeNoTransparencyZone(getAwayPPRectCoords());
            emit addNoTransparencyZone(getAwayPPRectCoords());
            break;
        case HOME_PP:
            emit removeNoTransparencyZone(getAwayPPRectCoords());
            homePP = true;
            break;
        case NEUTRAL:
            emit removeNoTransparencyZone(getAwayPPRectCoords());
            neutralPP = true;
            break;
        default:
            emit removeNoTransparencyZone(getAwayPPRectCoords());
            break;
        }
    } else {
        emit removeNoTransparencyZone(getAwayPPRectCoords());
    }
    ppDescription = description;
    scene()->update(this->x() + SCOREBOARD_WIDTH, this->y() + V_TEAM_BOX_STARTY,
                    CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT);
}

QRect
Scoreboard::getAwayPPRectCoords() {
    return QRect(x() + SCOREBOARD_WIDTH, y() + V_TEAM_BOX_STARTY, CLOCK_FIELD_WIDTH, TEAM_BOX_HEIGHT);
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
        centeredTimeText = "SO";
        showPdAndClockFields = false;
        break;
    default:
        period = "";
        showPdAndClockFields = false;
        break;
    }
    scene()->update(getClockRectCoords());
}

QRect
Scoreboard::getClockRectCoords() {
    return QRect(x() + CLOCK_FIELD_X, y() + H_TEAM_BOX_STARTY, CLOCK_FIELD_WIDTH, TEAM_BOX_HEIGHT);
}

void
Scoreboard::showPd() {
    showPdAndClockFields = true;
    scene()->update(getClockRectCoords());
}

void
Scoreboard::final() {
    showPdAndClockFields = false;
    centeredTimeText = "FINAL";
    scene()->update(getClockRectCoords());
}

void
Scoreboard::changeTopBarText(QString text) {
    topBarText->setPlainText(text);
    sponsor = true;
    int subtraction = 1;
    QFont f("Arial", 20, QFont::Bold);
    f.setCapitalization(QFont::SmallCaps);
    topBarText->setFont(f);
    topBarText->font().setCapitalization(QFont::SmallCaps);
    QFontMetrics fontSize(topBarText->font());
    while (fontSize.width(text) > POP_BAR_WIDTH - 10) {
        QFont tempFont("Arial", defaultSponsorText.pointSize() - subtraction, QFont::Bold);
        tempFont.setCapitalization(QFont::SmallCaps);
        subtraction++;
        topBarText->setFont(tempFont);
        QFontMetrics temp(topBarText->font());
        fontSize = temp;
    }
    emit transparentField(x()+20,y(),POP_BAR_WIDTH,POP_BAR_HEIGHT);
    scene()->update(x()+20, y(),POP_BAR_WIDTH,POP_BAR_HEIGHT);
}

void
Scoreboard::displaySponsor() {
//    topBarText->setPlainText(sponsorText);
//    int subtraction = 1;
//    topBarText->setFont(defaultSponsorText);
//    QFontMetrics fontSize(topBarText->font());
//    while (fontSize.width(sponsorText) > POP_BAR_WIDTH - 10) {
//        QFont tempFont("Arial", defaultSponsorText.pointSize() - subtraction, QFont::Bold);
//        //topBarText->font().setPointSize(defaultSponsorText.pointSize()-subtraction);
//        subtraction++;
//        topBarText->setFont(tempFont);
//        QFontMetrics temp(topBarText->font());
//        fontSize = temp;
//    }
    sponsor = false;
    emit removeTransparentField(x()+20, y(), POP_BAR_WIDTH,POP_BAR_HEIGHT);
    scene()->update(x()+20, y(), POP_BAR_WIDTH,POP_BAR_HEIGHT);
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
    return SCOREBOARD_WIDTH + CLOCK_FIELD_WIDTH;
}


void
Scoreboard::toggleShowBoard() {
    show = true;
    if (useTransparency) {
        if (sponsor)
            emit transparentField(x()+20,y(),POP_BAR_WIDTH,POP_BAR_HEIGHT);
        if(awayPP)
            emit addNoTransparencyZone(getAwayPPRectCoords());
    }
    emit addNoTransparencyZone(QRect(x() + V_TEAM_BOX_STARTX, y() + V_TEAM_BOX_STARTY, TEAM_WIDTH, TEAM_BOX_HEIGHT));
    scene()->update();
}

void Scoreboard::togglePpClocks()
{
    showPP = !showPP;
    emit removeNoTransparencyZone(getAwayPPRectCoords());
    scene()->update(this->x() + SCOREBOARD_WIDTH, this->y(),
                    CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT);
}

void
Scoreboard::hideBoard() {
    if (show) {
        show = false;
        emit removeTransparentField(x()+20, y(), POP_BAR_WIDTH,POP_BAR_HEIGHT);
        emit removeNoTransparencyZone(QRect(x() + V_TEAM_BOX_STARTX, y() + V_TEAM_BOX_STARTY, TEAM_WIDTH, TEAM_BOX_HEIGHT));
        emit removeNoTransparencyZone(getAwayPPRectCoords());
        //emit removeNoTransparencyZone(QRect(x() + V_TEAM_BOX_STARTX, y() + POP_BAR_HEIGHT + SCOREBOARD_HEIGHT, 345, PP_BAR_HEIGHT));
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
    scene()->update(getClockRectCoords());
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
    scene()->update(x() + CLOCK_FIELD_X, y() + H_TEAM_BOX_STARTY, CLOCK_FIELD_WIDTH, TEAM_BOX_HEIGHT);
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
        scene()->update(this->x(), this->y(), SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT);
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

void Scoreboard::awaySogUpdated(int sog)
{
    updateSog(false, sog);
}

void Scoreboard::homeSogUpdated(int sog)
{
    updateSog(true, sog);
}

void Scoreboard::updateSog(bool isHome, int sog)
{
    if (isHome) {
        hSog = sog;
    }
    else {
        aSog = sog;
    }
    scene()->update(x() + V_TEAM_BOX_STARTX + TEAM_WIDTH - SOG_WIDTH, y() + V_TEAM_BOX_STARTY, SOG_WIDTH, SCOREBOARD_HEIGHT);
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
            emit removeNoTransparencyZone(getAwayPPRectCoords());
            if (show) emit addNoTransparencyZone(getAwayPPRectCoords());
            break;
        case HOME_PP:
            emit removeNoTransparencyZone(getAwayPPRectCoords());
            homePP = true;
            break;
        case NEUTRAL:
            emit removeNoTransparencyZone(getAwayPPRectCoords());
            neutralPP = true;
            break;
        default:
            emit removeNoTransparencyZone(getAwayPPRectCoords());
            break;
        }
    } else {
        emit removeNoTransparencyZone(getAwayPPRectCoords());
    }
    ppDescription = description;
    serialPpClock = clock;
    scene()->update(this->x() + SCOREBOARD_WIDTH, this->y(),
                    CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT);

}

