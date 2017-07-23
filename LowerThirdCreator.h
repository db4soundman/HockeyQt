#ifndef LOWERTHIRDCREATOR_H
#define LOWERTHIRDCREATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QString>
#include <QList>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include "LowerThird.h"

class LowerThirdCreator : public QWidget {
    Q_OBJECT

public:
    LowerThirdCreator(LowerThird* lt, bool standAlone=true);

    QVBoxLayout* getLayout(bool standAlone);

signals:
    void makeCustomLt(QString name, QString number, QString year, QList<QString> header,
                      QList<QString> text, bool homeTeam);
protected slots:
    void clearFields();
    void submitLt();

protected:
    QLineEdit name, num, yr, header;
    QTextEdit text;
    QCheckBox home;
    QPushButton clear, show, previewButton;

};

#endif // LOWERTHIRDCREATOR_H
