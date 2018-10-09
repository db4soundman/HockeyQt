#include "TextualRosterInput.h"
#include <QVBoxLayout>
#include <QRegularExpressionMatchIterator>
#include "SeasonXMLHandler.h"

TextualRosterInput::TextualRosterInput(HockeyTeam *myTeam, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *myLayout = new QVBoxLayout();
    submit.setText("Submit");
    convert.setText("Convert");
    myLayout->addWidget(&rosterInput);
    myLayout->addWidget(&submit);
    //myLayout->addWidget(&convert);
    setLayout(myLayout);

    numberName = QRegularExpression("\\s*(?<num>\\d+)\\s*(?<name>[\\w+-]+,?\\s*[\\w+-]+)[^\n]*\n");
    numberName.setPatternOptions(QRegularExpression::MultilineOption);
    nameNumber = QRegularExpression("\\s*(?<name>[\\w+-]+,?\\s*[\\w+-]+)\\s*(?<num>\\d+)[^\n]*\n");
    nameNumber.setPatternOptions(QRegularExpression::MultilineOption);
    team=myTeam;

    connect(&submit, SIGNAL(clicked(bool)), this, SLOT(parseRoster()));
    connect(&convert, SIGNAL(clicked(bool)), this, SLOT(convertText()));
}

void TextualRosterInput::parseRoster()
{
    QString es = numberName.errorString();
    int eo = numberName.patternErrorOffset();
    if (numberName.match(rosterInput.toPlainText()).hasMatch()) {
        QRegularExpressionMatchIterator i = numberName.globalMatch(rosterInput.toPlainText());
        team->clearRoster();
        while (i.hasNext()) {
            QRegularExpressionMatch match = i.next();
            HockeyPlayer p;
            p.setUni(match.captured("num"));
            p.setName(SeasonXMLHandler::correctName(match.captured("name")));
            team->addPlayer(p);
            this->close();
            emit team->rosterChanged();
        }
        HockeyPlayer empty;
        empty.setName("No Name");
        team->addPlayer(empty);
    } else if (nameNumber.match(rosterInput.toPlainText()).hasMatch()) {
        QRegularExpressionMatchIterator i = nameNumber.globalMatch(rosterInput.toPlainText());
        team->clearRoster();
        while (i.hasNext()) {
            QRegularExpressionMatch match = i.next();
            HockeyPlayer p;
            p.setUni(match.captured("num"));
            p.setName(SeasonXMLHandler::correctName(match.captured("name")));
            team->addPlayer(p);
            this->close();
            emit team->rosterChanged();
        }
        HockeyPlayer empty;
        empty.setName("No Name");
        team->addPlayer(empty);
    }
}

void TextualRosterInput::convertText()
{
    rosterInput.setText(rosterInput.toPlainText());
}
