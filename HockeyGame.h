#ifndef HOCKEYGAME_H
#define HOCKEYGAME_H

#include <QObject>
#include "Clock.h"
#include <QString>
#include <QTimer>
#include "Scoreboard.h"
#include "LowerThird.h"
#include "HockeyTeam.h"


class HockeyGame : public QObject {
    Q_OBJECT
public:
    HockeyGame(QString awayName, QString homeName, QColor awayColor, QColor homeColor,
               QString awayXML, QString homeXML, QString sponsor, QString announcers,
               QString awayRank, QString homeRank, int screenWidth, QString awayLogo,
               QString hsName, QString asName);

    Scoreboard* getSb();
    LowerThird* getLt();

    QString getSponsor() const;
    void setSponsor(const QString& value);

    QString getAnnouncers() const;
    void setAnnouncers(const QString& value);

    QString getHomeName() const;
    void setHomeName(const QString& value);

    QString getAwayName() const;
    void setAwayName(const QString& value);

    HockeyTeam* getHomeTeam() const;

    HockeyTeam* getAwayTeam() const;

    Clock* getGameClock();


    QList<Clock*> getAwayPenalty() const;
    void setAwayPenalty(const QList<Clock*>& value);

    QList<Clock*> getHomePenalty() const;
    void setHomePenalty(const QList<Clock*>& value);

    QString getHomeRank() const;
    void setHomeRank(const QString& value);

    QString getAwayRank() const;
    void setAwayRank(const QString& value);

    QColor getHomeColor() const;
    void setHomeColor(const QColor& value);

    QColor getAwayColor() const;
    void setAwayColor(const QColor& value);

    int getAwayScore() const;
    void setAwayScore(int value);

    int getHomeScore() const;
    void setHomeScore(int value);

    int getPeriod() const;
    void setPeriod(int value);

    bool getIsFinal() const;
    void setIsFinal(bool value);

    int getHomeSOG() const;
    void setHomeSOG(int value);

    int getAwaySOG() const;
    void setAwaySOG(int value);

public slots:
    void homeGoal();
    void awayGoal();
    void homeLoseGoal();
    void awayLoseGoal();
    void advancePeriod();
    void rewindPeriod();
    void addHomePenalty(int time);
    void addAwayPenalty(int time);
    void homePenaltyExpired();
    void awayPenaltyExpired();
    void toggleClock();
    void addHomeSOG();
    void addAwaySOG();
    void subHomeSOG();
    void subAwaySOG();
    void showAnnouncers();
    void gatherHomeSeasonStatsLt(int index);
    void gatherHomeSeasonStatsSb(int index);
    void gatherHomeGameStatsLt(int index);
    void gatherAwayStatsLt(int index);
    void gatherHomeGameStatsSb(int index);
    void gatherAwayGameStatsSb(int index);
    void prepareHomeGoalText(int scorer, int a1, int a2);
    void prepareAwayGoalText(int scorer, int a1, int a2);
    void prepareHomePenaltyText(int pIndex, QString penalty);
    void prepareAwayPenaltyText(int pIndex, QString penalty);
    void gatherPpStats();
    void determinePpClockForScoreboard();
    void displayPenaltyEditor();
    void makeFinal();

signals:
    void homeScoreChanged(int score);
    void awayScoreChanged(int score);
    void periodChanged(int pd);
    void penaltyChanged(int pos, Clock* clock, QString description);
    void clockIsRunning(bool isRunning);
    void awaySogChanged(int sog);
    void homeSogChanged(int sog);
    void checkScoreboardPp();

private slots:
    void deleteExpiredPenalties();

private:
    QString homeName, homeShortName, awayName, awayShortName, sponsor, announcers, timeEventHappened, homeRank,
    awayRank;
    int awayScore, homeScore, period, homeSOG, awaySOG, homePlayersOnIce, awayPlayersOnIce;
    Clock gameClock;
    QList<Clock*> awayPenalty, homePenalty;
    QTimer timer;
    bool clockRunning, isFinal, useClock;
    QColor homeColor, awayColor;
    HockeyTeam* homeTeam;
    HockeyTeam* awayTeam;
    Scoreboard sb;
    LowerThird lt;
    // GUI is separate class
    // GraphicsVars


    Clock* getLowestPpClock();
};

#endif // HOCKEYGAME_H
