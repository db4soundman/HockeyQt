#ifndef HOCKEYGAME_H
#define HOCKEYGAME_H

#include <QObject>
#include "Clock.h"
#include <QString>
#include <QTimer>
#include <QPixmap>
#include <QByteArray>
#include "Scoreboard.h"
#include "LowerThird.h"
#include "HockeyTeam.h"
#include "SerialConsole.h"
#include "ComparisonGraphic.h"
#include <QSet>
#include "CGSimulator.h"


class HockeyGame : public QObject {
    Q_OBJECT
public:
    HockeyGame(QString awayName, QString homeName, QColor awayColor, QColor homeColor,
               QString awayXML, QString homeXML, QString sponsor, QString announcers,
               QString awayRank, QString homeRank, int screenWidth, QPixmap awayLogo,
               QString hsName, QString asName);

    Scoreboard* getSb();
    LowerThird* getLt();

    void connectWithSerialHandler(SerialConsole* console);
    void connectWithSerialSimulator(CGSimulator* console);

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

    QString getAwayTri() const;
    QString getHomeTri() const;

    QTimer* getTricasterRefresh();

    void setComparisonGraphic(ComparisonGraphic *value);

    ComparisonGraphic *getComparisonGraphic() const;

    LowerThird* getPreviewLt() ;

    ComparisonGraphic* getComparisonPreview();

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
    void showSogComparison();
    QPixmap getSogComparisonPreview();
    void showAnnouncers();
    QString getSeasonPopText(int index, bool home);
    QString getGamePopText(int index, bool home);
    QPixmap getSeasonPreviewLt(int index, bool home);
    QPixmap getGamePreviewLt(int index, bool home);
    void gatherSeasonStatsLt(int index, bool home);
    void gatherSeasonStatsSb(int index, bool home);
    void gatherGameStatsLt(int index, bool home);
    //void gatherAwayStatsLt(int index);
    void gatherGameStatsSb(int index, bool home);
    //void gatherAwayGameStatsSb(int index);
    QString getGoalText(int scorer, int a1, int a2, bool home);
    void prepareHomeGoalText(int scorer, int a1, int a2);
    void prepareAwayGoalText(int scorer, int a1, int a2);
    QString getPenaltyText(int pIndex, QString penalty, bool home);
    void prepareHomePenaltyText(int pIndex, QString penalty);
    void prepareAwayPenaltyText(int pIndex, QString penalty);
    void gatherPpStats();
    void determinePpClockForScoreboard();
    void displayPenaltyEditor();
    void makeFinal();
    void changeUseClock(bool uc);
    void removeFirstHomePenalty();
    void removeFirstAwayPenalty();
    void removeNewestHomePenalty();
    void removeNewestAwayPenalty();
    void parseAllSportCG(QByteArray data);
    void prepareFaceoffComparison(int awayWins, int homeWins);
    QPixmap getFaceoffCompPreview(int awayWins, int homeWins);


signals:
    void homeScoreChanged(int score);
    void awayScoreChanged(int score);
    void periodChanged(int pd);
    void penaltyChanged(int pos, Clock* clock, QString description);
    void clockIsRunning(bool isRunning);
    void awaySogChanged(int sog);
    void homeSogChanged(int sog);
    void checkScoreboardPp();
    void clockInUse(bool uc);
    void statusOfStatCrew(bool on);
    void toggleStatCrew();
    void usingAllSport();
    void usingInternalClock();

private slots:
    void deleteExpiredPenalties();

private:
    QString homeName, homeShortName, awayName, awayShortName, sponsor, announcers, timeEventHappened, homeRank,
    awayRank;
    int awayScore, homeScore, period, homeSOG, awaySOG, homePlayersOnIce, awayPlayersOnIce, penaltyIndex;
    Clock gameClock;
    QList<Clock*> awayPenalty, homePenalty;
    QTimer timer, tricasterRefresh, cgTimer;
    bool clockRunning, isFinal, useClock, penaltiesActive;
    QColor homeColor, awayColor;
    HockeyTeam* homeTeam;
    HockeyTeam* awayTeam;
    Scoreboard sb;
    LowerThird lt, previewLt;
    SerialConsole* serialConsole;
    ComparisonGraphic* comparisonGraphic;
    ComparisonGraphic comparisonPreview;
    void toggleCgPenaltyClocks(bool isOn);
    Clock* getLowestPpClock();

    QSet<int> awayPlayersInBox, homePlayersInBox;

    void prepareSameStatComp(QList<QString> stats, QString statName, bool goLive=true);
    void triggerNewPenalty();
    void determinePpClockAllSport(QString clock="");
};

#endif // HOCKEYGAME_H
