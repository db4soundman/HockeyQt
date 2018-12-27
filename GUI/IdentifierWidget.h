#ifndef IDENTIFIERWIDGET_H
#define IDENTIFIERWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "identifierl3rd.h"

class IdentifierWidget : public QWidget
{
    Q_OBJECT
public:
    IdentifierWidget(IdentifierL3rd* graphic);

signals:
    void showIdGraphic(QStringList nameRow, QStringList twitterRow);

private slots:
    void showPxPLeft();
    void showPxpRight();

private:
    QPushButton pxpLeft, pxpRight;
    QLabel talent1, talent2, talent3;
};

#endif // IDENTIFIERWIDGET_H
