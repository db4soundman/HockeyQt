#ifndef LOWERTHIRD_H
#define LOWERTHIRD_H

#include <QGraphicsPixmapItem>
#include <QLinearGradient>
#include <QPainter>
#include <QObject>
#include <QList>
#include <QString>
#include <QFont>
#include <QColor>
#include "GraphicChooser.txt"

class LowerThird : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
#ifdef GRAPHIC_LOOK
    LowerThird(QColor awayColor, QColor homeColor, int screenWidth, QGraphicsItem* parent = 0);
#else
    LowerThird(QColor awayColor, QColor homeColor, int screenWidth, QString pawayLogo, QGraphicsItem* parent = 0);
#endif

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);



public slots:
    void hideLt();
    void showLt();
    void showPpComp();
    void prepareForDisplay(QString name, QString number, QString year, QList<QString> statLabels,
                           QList<QString> statValues, bool homeTeam);
    void prepareForCustomLt(QString name, QString number, QString year, QList<QString> statLabels,
                           QList<QString> statValues, bool homeTeam);
    void prepareForPpComp(QString awayName, QString awayLabel, QString awayStat,
                          QString homeName, QString homeLabel, QString homeStat);
private:
    QList<QString> statNames;
    QList<QString> statistics;
    QString name, number, year, firstName, lastName;
    QFont statFont, nameFont, labelFont;
    QLinearGradient gradient, statGradient, homeNameGradient, awayNameGradient, homeStatGradient, awayStatGradient;
    QColor homeTeamMain, awayTeamMain, stats;

    QString homeName, awayName, homeLabel, awayLabel, homeStat, awayStat;
#ifndef GRAPHIC_LOOK
     QPixmap* homeLogo, *awayLogo;
#endif
    void prepareColors();
    void prepareFontSize();
    void adjustFont();

    bool show, showPp;
    int fontPointSize, statFontPointSize, centerPoint;
};

#endif // LOWERTHIRD_H
