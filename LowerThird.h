#ifndef LOWERTHIRD_H
#define LOWERTHIRD_H

#include <QGraphicsRectItem>
#include <QLinearGradient>
#include <QPainter>
#include <QObject>
#include <QList>
#include <QString>
#include <QFont>
#include <QColor>
#include "GraphicChooser.txt"

class LowerThird : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
#ifdef GRADIENT_LOOK
    LowerThird(QColor awayColor, QColor homeColor, int screenWidth, QGraphicsItem* parent = 0);
#else
    LowerThird(QColor awayColor, QColor homeColor, int screenWidth, QPixmap pawayLogo, QGraphicsItem* parent = 0);
#endif

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

    void paintPreview(QPainter* painter);

    int getWidth();
    int getHeight();



public slots:
    void hideLt();
    void showLt();
    void showPpComp();
    void prepareForDisplay(QString name, QString number, QString year, QList<QString> statLabels,
                           QList<QString> statValues, bool homeTeam, bool goLive=true);
    void prepareForCustomLt(QString name, QString number, QString year, QList<QString> statLabels,
                           QList<QString> statValues, bool homeTeam,bool goLive=true);
#ifdef GRADIENT_LOOK
    void prepareForPpComp(QString awayName, QString awayLabel, QString awayStat,
                          QString homeName, QString homeLabel, QString homeStat);
#else
    void prepareComp(QString awayName, QString awayLabel, QString homeName, QString homeLabel, QList<QString> stats);
#endif
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

    bool show;
    int fontPointSize, statFontPointSize, centerPoint;
};

#endif // LOWERTHIRD_H
