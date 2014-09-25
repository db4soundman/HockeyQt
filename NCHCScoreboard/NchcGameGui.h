#ifndef NCHCGAMEGUI_H
#define NCHCGAMEGUI_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>

class NchcGameGui : public QWidget {
    Q_OBJECT
public:
    NchcGameGui(bool firstGui = false);

    QString getAway() const { return away.text(); }
    QString getHome() const { return home.text(); }
    QString getAwayScore() const { return awayScore.text(); }
    QString getHomeScore() const { return homeScore.text(); }
    QString getTimeAndPd() const { return timeAndPd.text(); }
    bool isConf() const { return confGame.isChecked(); }

    void setConf(bool pConf);
    void setTimeAndPd(QString tap);
    void setAwayScore(QString scr);
    void setHomeScore(QString scr);


signals:
    void awayNameUpdated(QString name);
    void homeNameUpdated(QString home);

public slots:
    void updateAwayName(QString name);
    void updateHomeName(QString name);

private:
    QLineEdit away, home, awayScore, homeScore, timeAndPd;
    QCheckBox confGame;

};

#endif // NCHCSCOREBOARDGUI_H
